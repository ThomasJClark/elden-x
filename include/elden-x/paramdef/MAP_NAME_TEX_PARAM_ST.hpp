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
struct map_name_tex_param_st
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
     * @brief R
     *
     * Color information (R) of the map image before conversion. Pixels with
     * matching RGB values are associated with this parameter
     */
    unsigned char srcR{0};

    /**
     * @brief G
     *
     * Color information (G) of the map image before conversion. Pixels with
     * matching RGB values are associated with this parameter
     */
    unsigned char srcG{0};

    /**
     * @brief B
     *
     * Color information (B) of the map image before conversion. Pixels with
     * matching RGB values are associated with this parameter
     */
    unsigned char srcB{0};

    unsigned char pad1[1];

    /**
     * @brief Map name ID_for displaying place names
     *
     * Map name ID for displaying place names [PlaceName] (0: invalid value)
     */
    int mapNameId{0};

    unsigned char pad2[4];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::map_name_tex_param_st) == 16,
              "MAP_NAME_TEX_PARAM_ST paramdef size does not match detected size");
