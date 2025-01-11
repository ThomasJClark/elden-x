/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er
{
namespace paramdef
{
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct sound_common_ingame_param_st
{
    /**
     * @brief Parameter Key string
     *
     * Key string of the parameter
     */
    char ParamKeyStr[32];

    /**
     * @brief Parameter Value string
     *
     * Value string of the parameter
     */
    char ParamValueStr[32];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::sound_common_ingame_param_st) == 64,
              "SOUND_COMMON_INGAME_PARAM_ST paramdef size does not match detected size");
