#include <elden-x/game_man.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static er::CS::GameMan **address = nullptr;

er::CS::GameMan *er::CS::GameMan::instance()
{
    if (!address)
    {
        address = modutils::scan<er::CS::GameMan *>({
            .aob = "48 8B 05 ?? ?? ?? ??" // mov rax, qword ptr [GameMan]
                   "80 B8 ?? ?? ?? ?? 0D" // cmp byte ptr rax->???, 13
                   "0F 94 C0"             // sete al
                   "C3",                  // ret
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
