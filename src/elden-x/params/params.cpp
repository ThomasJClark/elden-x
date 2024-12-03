#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

#include <elden-x/params/params.hpp>
#include <elden-x/utils/modutils.hpp>

static from::CS::SoloParamRepository **address = nullptr;

from::CS::SoloParamRepository *from::CS::SoloParamRepository::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::SoloParamRepository *>({
            .aob = "48 8B 0D ?? ?? ?? ?? 48 85 C9 0F 84 ?? ?? ?? ?? 45 33 C0 BA 90",
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            SPDLOG_ERROR("Unable to find SoloParamRepository. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}

bool from::CS::SoloParamRepository::are_params_ready()
{
    auto solo_param_repository = from::CS::SoloParamRepository::instance();
    if (!solo_param_repository)
    {
        return false;
    }

    for (auto entry : solo_param_repository->param_entries)
    {
        if (!entry.res_cap[0])
        {
            return false;
        }
    }

    return true;
}

void from::CS::SoloParamRepository::wait_for_params()
{
    SPDLOG_INFO("Waiting for params...");

    while (!are_params_ready())
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
