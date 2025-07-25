#include <array>
#include <codecvt>
#include <filesystem>
#include <locale>
#include <span>
#include <stdexcept>
#include <string>

#ifdef ER_WITH_HOOKS
    #include <MinHook.h>
#endif

#include <Pattern16.h>
#include <spdlog/spdlog.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winver.h>

#include "elden-x/utils/modutils.hpp"

using namespace std;

static span<unsigned char> memory;

static string sus_filenames[] = {
    "ALI213.ini",      "ColdAPI.ini",   "ColdClientLoader.ini",  "CPY.ini",
    "ds.ini",          "hlm.ini",       "local_save.txt",        "SmartSteamEmu.ini",
    "steam_api.ini",   "steam_emu.ini", "steam_interfaces.ini",  "steam_settings",
    "SteamConfig.ini", "valve.ini",     "Language Selector.exe",
};

bool modutils::sus = false;

void modutils::initialize() {
#ifdef ER_NIGHTREIGN
    #define EXE_NAME "nightreign.exe"
#else
    #define EXE_NAME "eldenring.exe"
#endif

    HMODULE module_handle = GetModuleHandleA(EXE_NAME);
    if (!module_handle) {
        throw runtime_error("Failed to get handle for " EXE_NAME " process");
    }

    wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> convert;

    wchar_t exe_filename[MAX_PATH] = {0};
    GetModuleFileNameW(module_handle, exe_filename, MAX_PATH);
    SPDLOG_DEBUG("Found handle for " EXE_NAME " process: {}", convert.to_bytes(exe_filename));

    auto exe_directory = filesystem::path(exe_filename).parent_path();
    for (auto i = 0; i < size(sus_filenames); i++) {
        if (filesystem::exists(exe_directory / sus_filenames[i])) {
            sus = true;
            SPDLOG_ERROR("Game may be modified, compatibility is unlikely [{}]", i);
        }
    }

    MEMORY_BASIC_INFORMATION memory_info;
    if (VirtualQuery((void *)module_handle, &memory_info, sizeof(memory_info)) == 0) {
        throw runtime_error("Failed to get virtual memory information");
    }

    IMAGE_DOS_HEADER *dos_header = (IMAGE_DOS_HEADER *)module_handle;
    IMAGE_NT_HEADERS *nt_headers =
        (IMAGE_NT_HEADERS *)((ULONG64)memory_info.AllocationBase + (ULONG64)dos_header->e_lfanew);

    if ((dos_header->e_magic == IMAGE_DOS_SIGNATURE) &&
        (nt_headers->Signature == IMAGE_NT_SIGNATURE)) {
        memory = {(unsigned char *)memory_info.AllocationBase,
                  nt_headers->OptionalHeader.SizeOfImage};
    }

#ifdef ER_WITH_HOOKS
    auto mh_status = MH_Initialize();
    if (mh_status != MH_OK) {
        throw runtime_error(string("Error initializing MinHook: ") + MH_StatusToString(mh_status));
    }
#endif
}

void modutils::deinitialize() {
#ifdef ER_WITH_HOOKS
    MH_Uninitialize();
#endif
}

uintptr_t modutils::impl::scan_memory(uintptr_t address, const std::string &aob) {
    if (!address) {
        address = (uintptr_t)memory.data();
    }

    if (!aob.empty()) {
        ptrdiff_t size = (uintptr_t)&memory.back() - address;
        address = (uintptr_t)Pattern16::scan((void *)address, size, aob);
    }

    return address;
}

uintptr_t modutils::impl::apply_offsets(
    uintptr_t address,
    ptrdiff_t offset,
    const modutils::scanopts::relative_offsets_type &relative_offsets) {
    if (address) {
        address += offset;

        for (auto [first, second] : relative_offsets) {
            ptrdiff_t offset = *reinterpret_cast<int *>(address + first) + second;
            address += offset;
        }
    }

    return address;
}

uintptr_t modutils::impl::scan(const scanopts &opts) {
    auto result = scan_memory((uintptr_t)opts.address, opts.aob);
    return apply_offsets(result, opts.offset, opts.relative_offsets);
}

#ifdef ER_WITH_HOOKS
void modutils::impl::hook(void *function, void *detour, void **trampoline) {
    auto mh_status = MH_CreateHook(function, detour, trampoline);
    if (mh_status != MH_OK) {
        throw runtime_error(string("Error creating hook: ") + MH_StatusToString(mh_status));
    }
    mh_status = MH_QueueEnableHook(function);
    if (mh_status != MH_OK) {
        throw runtime_error(string("Error queueing hook: ") + MH_StatusToString(mh_status));
    }
}

void modutils::enable_hooks() {
    auto mh_status = MH_ApplyQueued();
    if (mh_status != MH_OK) {
        throw runtime_error(string("Error enabling hooks: ") + MH_StatusToString(mh_status));
    }
}
#endif
