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
struct gparam_ref_settings_param_st
{
    /**
     * @brief Do you remove it from the NT version output?
     *
     * Parameters marked with ○ are excluded in the NT version package.
     */
    bool disableParam_NT : 1 {false};

    /**
     * @brief Reserve for package output 1
     */
    unsigned char disableParamReserve1 : 7;

    /**
     * @brief Reserve for package output 2
     */
    unsigned char disableParamReserve2[3];

    /**
     * @brief Referenced map ID
     *
     * Specify the referenced map number. Legacy: m10_10_00_00-> 10010000, Open:
     * m60_ ?? _ ?? _ ??-> m60000000
     */
    int RefTargetMapId{-1};

    unsigned char Reserve[24];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::gparam_ref_settings_param_st) == 32,
              "GPARAM_REF_SETTINGS_PARAM_ST paramdef size does not match detected size");
