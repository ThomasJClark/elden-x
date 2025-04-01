#pragma once

#include "singletons.hpp"
#include "task_groups.hpp"

namespace er
{
namespace FD4
{
template <typename T> class FD4TimeTemplate
{
  public:
    virtual ~FD4TimeTemplate() = default;
    T value;
};

struct task_data
{
    FD4TimeTemplate<float> time;
    task_group group;
    int seed;
};

class FD4TaskBase
{
  private:
    int unk8;
    int unkc;

  public:
    virtual FD4RuntimeClass *get_runtime_class()
    {
        return nullptr; // unimplemented
    };

    virtual ~FD4TaskBase() = default;

    virtual void execute(task_data *data) = 0;
};
}

namespace CS
{
class CSEzTask;

class CSEzTaskProxy : public FD4::FD4TaskBase
{
  private:
    CS::CSEzTask *owner;
    task_group group;
};

/**
 * Base class of tasks. Override this and implement execute() to create a custom taskk, and
 * register it with the CSTask singleton to make it run
 */
class CSEzTask : public FD4::FD4TaskBase
{
  private:
    CSEzTaskProxy *proxy;
};

class CSTask : public FD4::FD4Singleton<CSTask, FD4::singleton_index::CSTask>
{
  public:
    /**
     * Register the specified task to run asyncronously each frame in the given task group
     */
    void register_task(task_group group, CSEzTask &task);
};
}

}
