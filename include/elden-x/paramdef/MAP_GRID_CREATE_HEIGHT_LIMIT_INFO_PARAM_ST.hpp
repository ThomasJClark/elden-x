/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct map_grid_create_height_limit_info_param_st {
    /**
     * @brief Grid can be constructed Height Min [m]
     *
     * Minimum height that can be built in the grid [m]. (LOD 2 units)
     */
    float GridEnableCreateHeightMin{-99999.f};

    /**
     * @brief Grid can be constructed Height Max [m]
     *
     * Maximum height that can be constructed in the grid [m]. (LOD 2 units)
     */
    float GridEnableCreateHeightMax{99999.f};

    unsigned char Reserve[24];
};

};
};

static_assert(sizeof(er::paramdef::map_grid_create_height_limit_info_param_st) == 32,
              "MAP_GRID_CREATE_HEIGHT_LIMIT_INFO_PARAM_ST paramdef size does not match "
              "detected size");
