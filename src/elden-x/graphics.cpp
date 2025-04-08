#include <elden-x/graphics.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static er::GXBS::globals **address = nullptr;

er::GXBS::globals *er::GXBS::globals::instance() {
    if (!address) {
        address = modutils::scan<er::GXBS::globals *>({
            .aob = "ba 08 00 00 00"      // mov edx, 8
                   "b9 10 10 00 00"      // mov ecx, 0x1010
                   "e8 ????????"         // call HeapAlloc
                   "??????????"          // ??
                   "48 85 c0"            // test rax, rax
                   "74 09"               // je 34
                   "48 8b c8"            // mov rcx, rax
                   "e8 ????????"         // call ??
                   "90"                  // nop
                   "48 89 05 ????????",  // mov [gxglobals], rax
            .offset = 0x22,
            .relative_offsets = {{3, 7}},
        });

        if (!address) {
            SPDLOG_ERROR("Unable to find graphics globals. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
