#pragma once

#include "singletons.hpp"
#include "task_groups.hpp"

namespace er {
namespace FD4 {
template <typename T>
class FD4TimeTemplate {
public:
    virtual ~FD4TimeTemplate() = default;
    T value;
};

struct task_data {
    FD4TimeTemplate<float> time;
    task_group group;
    int seed;
};

/**
 * Has something to do with the OS thread that the task is running on. Each task group is always
 * in the same affinity, and most are in thread0.
 */
enum class task_affinity : unsigned char {
    thread0 = 0,
    thread1 = 1,
    thread2 = 2,
    thread3 = 3,
    thread4 = 4,
    thread5 = 5,
};

class FD4TaskBase {
private:
    int unk8;
    int unkc;

public:
    virtual FD4RuntimeClass *get_runtime_class() {
        return nullptr;  // unimplemented
    };

    virtual ~FD4TaskBase() = default;

    virtual void execute(task_data *data, task_group group, task_affinity affinity) = 0;
};
}

namespace CS {
class CSEzTask;

class CSEzTaskProxy : public FD4::FD4TaskBase {
private:
    CS::CSEzTask *owner;
    FD4::task_group group;
};

/**
 * Base class of tasks. Override this and implement execute() to create a custom taskk, and
 * register it with the CSTask singleton to make it run
 */
class CSEzTask : public FD4::FD4TaskBase {
private:
    CSEzTaskProxy *proxy;
};

class CSTask : public FD4::FD4Singleton<CSTask, FD4::singleton_index::CSTask> {
public:
    /**
     * Register the specified task to run asyncronously each frame in the given task group
     */
    void register_task(FD4::task_group group, CSEzTask &task);
};

class CSEzRabbitTaskBase : public CSEzTask {
public:
    int unk18;
    int unk1c;
};

class CSEzRabbitTask : public CSEzRabbitTaskBase {};

template <typename T>
class CSEzUpdateTask : CSEzRabbitTask {
public:
    T *arg;
    void (*callback)(T *arg);

    CSEzUpdateTask(T *arg, void (*callback)(T *arg))
        : arg(arg),
          callback(callback) {}

    virtual void execute(FD4::task_data *data, FD4::task_group group, FD4::task_affinity affinity) {
        callback(arg);
    }
};

}

}
