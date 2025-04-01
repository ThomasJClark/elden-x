#include <elden-x/task.hpp>
#include <elden-x/utils/modutils.hpp>

#include <spdlog/spdlog.h>

typedef void cs_task_imp_register_task_fn(er::CS::CSTask *, er::task_group, er::CS::CSEzTask *);

static cs_task_imp_register_task_fn *cs_task_imp_register_task;

void er::CS::CSTask::register_task(task_group group, CSEzTask &task)
{
    if (!cs_task_imp_register_task)
    {
        cs_task_imp_register_task = modutils::scan<cs_task_imp_register_task_fn>({
            .aob = "e8 ????????"       // call DLPanic
                   "48 8b 0d ????????" // mov rcx, GLOBAL_CSTask
                   "4c 8b c7"          // mov r8, rdi
                   "8b d3"             // mov edx, ebx
                   "e8 ????????",      // call CS::CSTaskImp::RegisterTask
            .offset = 17,
            .relative_offsets = {{1, 5}},
        });

        if (!cs_task_imp_register_task)
        {
            SPDLOG_ERROR("Unable to find CS::CSTaskImp::RegisterTask. Incompatible game version?");
            return;
        }
    }

    cs_task_imp_register_task(this, group, &task);
}
