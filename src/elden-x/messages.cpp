#include <elden-x/messages.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static er::CS::MsgRepository **address = nullptr;

er::CS::MsgRepository *er::CS::MsgRepository::instance() {
    if (!address) {
        address = modutils::scan<er::CS::MsgRepository *>({
            .aob = "48 8B 3D ?? ?? ?? ?? 44 0F B6 30 48 85 FF 75",
            .relative_offsets = {{3, 7}},
        });

        if (!address) {
            SPDLOG_ERROR("Unable to find MsgRepository. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
