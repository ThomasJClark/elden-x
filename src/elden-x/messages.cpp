#include <elden-x/messages.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::MsgRepositoryImp **address = nullptr;

from::CS::MsgRepositoryImp *from::CS::MsgRepositoryImp::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::MsgRepositoryImp *>({
            .aob = "48 8B 3D ?? ?? ?? ?? 44 0F B6 30 48 85 FF 75",
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            SPDLOG_ERROR("Unable to find MsgRepositoryImp. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
