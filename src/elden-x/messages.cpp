#include <elden-x/messages.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static er::CS::MsgRepositoryImp **address = nullptr;

er::CS::MsgRepositoryImp *er::CS::MsgRepositoryImp::instance()
{
    if (!address)
    {
        address = modutils::scan<er::CS::MsgRepositoryImp *>({
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
