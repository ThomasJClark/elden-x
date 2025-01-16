#pragma once

#include "param_file.hpp"

#include "../singletons.hpp"

namespace er
{

namespace FD4
{

class FD4ResCap
{
  public:
    virtual ~FD4ResCap() = default;

    unsigned char unk8[0x78];
};

class FD4ParamResCap : public FD4ResCap
{
  public:
    virtual ~FD4ParamResCap() = default;

    param::param_file *file;
};

}

namespace CS
{

class ParamResCap : public FD4::FD4ResCap
{
  public:
    virtual ~ParamResCap() = default;

    FD4::FD4ParamResCap *fd4_param_res_cap;
};

class SoloParamRepository
    : public FD4::FD4ResCap,
      public FD4::FD4Singleton<SoloParamRepository, FD4::singleton_index::SoloParamRepository>
{
  public:
    static bool are_params_ready();

    static void wait_for_params();

    virtual ~SoloParamRepository() = default;

    param::param_file *get_param_file(param::param_index index)
    {
        auto res_cap = param_entries[static_cast<int>(index)].res_cap[0];
        if (!res_cap)
            return nullptr;

        auto fd4_res_cap = res_cap->fd4_param_res_cap;
        if (!fd4_res_cap)
            return nullptr;

        return fd4_res_cap->file;
    }

  private:
    struct
    {
        int res_cap_count;
        ParamResCap *res_cap[8];
    } param_entries[int(param::param_index::PARAM_COUNT)];
};

}

}
