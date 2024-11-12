#include <elden-x/gamedata/game_data_man.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::GameDataMan **address = nullptr;

from::CS::GameDataMan *from::CS::GameDataMan::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::GameDataMan *>({
            .aob = "48 8B 05 ?? ?? ?? ??" // mov rax, [GameDataMan]
                   "48 85 C0"             // test rax, rax
                   "74 05"                // je 10
                   "48 8B 40 58"          // move rax, [rax + 0x58]
                   "C3"                   // ret
                   "C3",                  // ret
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            spdlog::error("Unable to find GameDataMan. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
