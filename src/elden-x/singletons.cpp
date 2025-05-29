#include <elden-x/singletons.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <map>
#include <string>
#include <thread>

using namespace std;

static const map<string, er::FD4::singleton_index> singleton_indexes = {
#define SINGLETON(name) {#name, er::FD4::singleton_index::name},
#include <elden-x/singletons.inl>
#undef SINGLETON
};

array<void **, static_cast<unsigned int>(er::FD4::singleton_index::count)>
    er::FD4::impl::singleton_addresses;

typedef const char *get_runtime_class_name_fn(er::FD4::FD4RuntimeClass *);

/**
 * Singleton finder AOB stolen from TGA
 *
 * https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/blob/427134e30b06476341f670e083d5d5cd0e029b3e/table_files/include/tga/fd4_singleton.h
 */
void er::FD4::find_singletons() {
    // Wait until SetBaseAddr() has been called in WinMain so we know static data has been
    // initialized. This should happen almost immediately, but if there are multiple DLL mods with
    // blocking DllMains it may be delayed.
    auto &base_addr = *modutils::scan<HMODULE>({
        .aob = "ff 15 ????????"  // call [CommandLineToArgvW]
               "48 8b ce"        // mov rcx, rsi
               "48 8b f8"        // mov rdi, rax
               "e8 ????????",    // call SetBaseAddr
        .offset = 12,
        .relative_offsets = {{1, 5}, {3, 7}},
    });
    while (!base_addr) this_thread::yield();

    uintptr_t match = 0;
    while (match = modutils::impl::scan_memory(match ? match + 50 : 0,
                                               "48 8b ?? ????????"  // mov ??, [singleton_address]
                                               "48 85 ??"           // test reg, reg
                                               "75 2e"              // jnz +2e
                                               "48 8d 0d ????????"  // lea rcx, [runtime_class]
                                               "e8 ????????"        // call get_runtime_class_name
                                               "4c 8b c8"           // mov r9, rax
                                               "4c 8d 05 ????????"  // lea r8, ??
                                               "ba ?? ?? 00 00"     // mov edx, ??
                                               "48 8d 0d ????????"  // lea rcx, [file_path]
                                               "e8 ????????"        // call ??
                                               )) {
        auto singleton_address = (void **)modutils::impl::apply_offsets(match, 0, {{3, 7}});
        auto runtime_class =
            (FD4::FD4RuntimeClass *)modutils::impl::apply_offsets(match, 12, {{3, 7}});
        auto get_runtime_class_name =
            (get_runtime_class_name_fn *)modutils::impl::apply_offsets(match, 19, {{1, 5}});

        auto singleton_name = get_runtime_class_name(runtime_class);
        auto singleton_index_it = singleton_indexes.find(singleton_name);
        if (singleton_index_it == singleton_indexes.end()) {
            SPDLOG_WARN("Unknown singleton {} at {}", singleton_name, (void *)singleton_address);
            continue;
        }

        auto &addr = impl::singleton_addresses[static_cast<size_t>(singleton_index_it->second)];
        if (!addr) {
            addr = singleton_address;
        }
    }

    for (auto [singleton_name, singleton_index] : singleton_indexes) {
        if (!impl::singleton_addresses[static_cast<size_t>(singleton_index)]) {
            SPDLOG_WARN("Can't find singleton {}", singleton_name);
        }
    }
}
