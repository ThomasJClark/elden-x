#include <elden-x/chr/world_chr_man.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::WorldChrManImp **address = nullptr;

from::CS::WorldChrManImp *from::CS::WorldChrManImp::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::WorldChrManImp *>({
            .aob = "48 8b 05 ?? ?? ?? ??"  // mov rax, [WorldChrMan]
                   "48 85 c0"              // test rax, rax
                   "74 0f"                 // jz end_label
                   "48 39 88 08 e5 01 00", // cmp [rax + 0x1e508], rcx
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            spdlog::error("Unable to find WorldChrMan. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
