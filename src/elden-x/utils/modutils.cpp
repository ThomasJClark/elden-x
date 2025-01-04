#include <codecvt>
#include <filesystem>
#include <locale>
#include <map>
#include <span>
#include <stdexcept>
#include <string>

#include <MinHook.h>
#include <Pattern16.h>
#include <spdlog/spdlog.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winver.h>

#include "elden-x/utils/modutils.hpp"

using namespace std;

static span<unsigned char> memory;

static unordered_map<string, void **> singleton_addresses;

static string sus_filenames[] = {
    "ALI213.ini",      "ColdAPI.ini",   "ColdClientLoader.ini",  "CPY.ini",
    "ds.ini",          "hlm.ini",       "local_save.txt",        "SmartSteamEmu.ini",
    "steam_api.ini",   "steam_emu.ini", "steam_interfaces.ini",  "steam_settings",
    "SteamConfig.ini", "valve.ini",     "Language Selector.exe",
};

static uintptr_t scan_memory(uintptr_t address, const std::string &aob)
{
    if (!address)
    {
        address = (uintptr_t)memory.data();
    }

    if (!aob.empty())
    {
        ptrdiff_t size = (uintptr_t)&memory.back() - address;
        address = (uintptr_t)Pattern16::scan((void *)address, size, aob);
    }

    return address;
}

static void *apply_offsets(uintptr_t address, ptrdiff_t offset,
                           modutils::scanopts::relative_offsets_type relative_offsets)
{
    if (address)
    {
        address += offset;

        for (auto [first, second] : relative_offsets)
        {
            ptrdiff_t offset = *reinterpret_cast<int *>(address + first) + second;
            address += offset;
        }
    }

    return reinterpret_cast<void *>(address);
}

/**
 * Singleton finder AOB stolen from TGA
 *
 * https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/blob/427134e30b06476341f670e083d5d5cd0e029b3e/table_files/include/tga/fd4_singleton.h
 */
static void find_singletons()
{
    struct runtime_class_st;
    typedef const char *get_singleton_name_fn(runtime_class_st *);

    uintptr_t match = 0;
    while (match = scan_memory(match ? match + 50 : 0,
                               "48 8b ?? ????????" // mov ??, [singleton_address]
                               "48 85 ??"          // test reg, reg
                               "75 2e"             // jnz +2e
                               "48 8d 0d ????????" // lea rcx, [runtime_class]
                               "e8 ????????"       // call get_singleton_name
                               "4c 8b c8"          // mov r9, rax
                               "4c 8d 05 ????????" // lea r8, ??
                               "ba ?? ?? 00 00"    // mov edx, ??
                               "48 8d 0d ????????" // lea rcx, [file_path]
                               "e8 ????????"       // call ??
                               ))
    {
        auto singleton_address = (void **)apply_offsets(match, 0, {{3, 7}});
        auto runtime_class = (runtime_class_st *)apply_offsets(match, 12, {{3, 7}});
        auto get_singleton_name = (get_singleton_name_fn *)apply_offsets(match, 19, {{1, 5}});

        auto singleton_name = get_singleton_name(runtime_class);

        bool already_found = false;
        for (auto [name, address] : singleton_addresses)
        {
            if (singleton_name == name || address == singleton_address)
            {
                already_found = true;
                break;
            }
        }

        if (!already_found)
        {
            singleton_addresses[singleton_name] = singleton_address;
        }
    }
}

void modutils::initialize()
{
    HMODULE module_handle = GetModuleHandleA("eldenring.exe");
    if (!module_handle)
    {
        throw runtime_error("Failed to get handle for eldenring.exe process");
    }

    wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> convert;

    wchar_t exe_filename[MAX_PATH] = {0};
    GetModuleFileNameW(module_handle, exe_filename, MAX_PATH);
    SPDLOG_INFO("Found handle for eldenring.exe process: {}", convert.to_bytes(exe_filename));

    auto exe_directory = filesystem::path(exe_filename).parent_path();
    for (auto i = 0; i < size(sus_filenames); i++)
    {
        if (filesystem::exists(exe_directory / sus_filenames[i]))
        {
            SPDLOG_ERROR("Game may be modified, compatibility is unlikely [{}]", i);
        }
    }

    MEMORY_BASIC_INFORMATION memory_info;
    if (VirtualQuery((void *)module_handle, &memory_info, sizeof(memory_info)) == 0)
    {
        throw runtime_error("Failed to get virtual memory information");
    }

    IMAGE_DOS_HEADER *dos_header = (IMAGE_DOS_HEADER *)module_handle;
    IMAGE_NT_HEADERS *nt_headers =
        (IMAGE_NT_HEADERS *)((ULONG64)memory_info.AllocationBase + (ULONG64)dos_header->e_lfanew);

    if ((dos_header->e_magic == IMAGE_DOS_SIGNATURE) &&
        (nt_headers->Signature == IMAGE_NT_SIGNATURE))
    {
        memory = {(unsigned char *)memory_info.AllocationBase,
                  nt_headers->OptionalHeader.SizeOfImage};
    }

    auto mh_status = MH_Initialize();
    if (mh_status != MH_OK)
    {
        throw runtime_error(string("Error initializing MinHook: ") + MH_StatusToString(mh_status));
    }

    find_singletons();
}

void modutils::deinitialize()
{
    MH_Uninitialize();
}

void *modutils::impl::scan(const scanopts &opts)
{
    auto result = scan_memory((uintptr_t)opts.address, opts.aob);
    return apply_offsets(result, opts.offset, opts.relative_offsets);
}

void modutils::impl::hook(void *function, void *detour, void **trampoline)
{
    auto mh_status = MH_CreateHook(function, detour, trampoline);
    if (mh_status != MH_OK)
    {
        throw runtime_error(string("Error creating hook: ") + MH_StatusToString(mh_status));
    }
    mh_status = MH_QueueEnableHook(function);
    if (mh_status != MH_OK)
    {
        throw runtime_error(string("Error queueing hook: ") + MH_StatusToString(mh_status));
    }
}

void *modutils::impl::get_singleton_address(const std::string &singleton_name)
{
    auto address_it = singleton_addresses.find(singleton_name);
    if (address_it == singleton_addresses.end())
    {
        SPDLOG_ERROR("Error looking up unknown singleton {}", singleton_name);
        return nullptr;
    }
    return *address_it->second;
}

void modutils::enable_hooks()
{
    auto mh_status = MH_ApplyQueued();
    if (mh_status != MH_OK)
    {
        throw runtime_error(string("Error enabling hooks: ") + MH_StatusToString(mh_status));
    }
}
