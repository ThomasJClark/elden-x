#include <elden-x/menu/menu_man.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

static from::CS::CSMenuManImp **address = nullptr;

from::CS::CSMenuManImp *from::CS::CSMenuManImp::instance()
{
    if (!address)
    {
        address = modutils::scan<from::CS::CSMenuManImp *>({
            .aob = "48 8b 05 ?? ?? ?? ??" // mov rax, qword ptr [CSMenuMan]
                   "33 db"                // xor ebx, ebx
                   "48 89 74 ??",         // mov qword ptr [rsp + ??], rsi
            .relative_offsets = {{3, 7}},
        });

        if (!address)
        {
            spdlog::error("Unable to find CSMenuManImp. Incompatible game version?");
            return nullptr;
        }
    }

    return *address;
}
