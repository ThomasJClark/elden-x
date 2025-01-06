#include <elden-x/game_man.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::GameMan **address = nullptr;

from::CS::GameMan *from::CS::GameMan::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::GameMan *>({
            .aob = "48 8B 3D ?? ?? ?? ?? 44 0F B6 30 48 85 FF 75",
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            SPDLOG_ERROR("Unable to find GameMan. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
