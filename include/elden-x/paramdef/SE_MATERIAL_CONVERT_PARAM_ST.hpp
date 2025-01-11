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
struct se_material_convert_param_st
{
    /**
     * @brief SE material ID
     *
     * Conversion from SFX material ID (3 digits) to SE material ID (2 digits)
     */
    unsigned char seMaterialId{0};

    unsigned char pad[3];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::se_material_convert_param_st) == 4,
              "SE_MATERIAL_CONVERT_PARAM_ST paramdef size does not match detected size");
