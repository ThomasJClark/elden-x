#include <spdlog/spdlog.h>
#include <chrono>
#include <thread>

#include <elden-x/params/solo_param_repository.hpp>
#include <elden-x/utils/modutils.hpp>

static er::CS::SoloParamRepository **address = nullptr;

bool er::CS::SoloParamRepository::are_params_ready() {
    auto solo_param_repository = er::CS::SoloParamRepository::instance();
    if (!solo_param_repository) {
        return false;
    }

    for (auto entry : solo_param_repository->param_entries) {
        if (!entry.res_cap[0]) {
            return false;
        }
    }

    return true;
}

void er::CS::SoloParamRepository::wait_for_params() {
    SPDLOG_DEBUG("Waiting for params...");

    while (!are_params_ready()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
