#include <elden-x/session.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::CSSessionManagerImp **address = nullptr;

from::CS::CSSessionManagerImp *from::CS::CSSessionManagerImp::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::CSSessionManagerImp *>({
            .aob = "48 8b 05 ?? ?? ?? ??"  // mov rax, qword ptr [CSSessionManager]
                   "39 78 08"              // cmp dword ptr [rax + 0x8], edi
                   "0f 84 ?? ?? ?? ??"     // je end_label
                   "4d 8b af 90 12 00 00", // mov r13, qword ptr [r15 + 0x1290]
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            SPDLOG_ERROR("Unable to find CSSessionManagerImp. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
