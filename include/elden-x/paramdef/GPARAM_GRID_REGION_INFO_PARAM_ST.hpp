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
struct gparam_grid_region_info_param_st
{
    /**
     * @brief Open local ID for MapGparam
     *
     * Open local ID for MapGparam. Used for the XX part of
     * m60_00_00XX.gparamxml
     */
    unsigned int GparamGridRegionId{0};

    unsigned char Reserve[28];
};

}; // namespace paramdef
}; // namespace er
