/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct bonfire_warp_tab_param_st {
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
     * @brief Text ID
     *
     * Tab Display Name Text ID [MenuText]
     */
    int textId{0};

    /**
     * @brief Sort ID
     *
     * Tab display order sort ID. Line up from the left with aim
     */
    int sortId{0};

    /**
     * @brief Icon ID
     *
     * Tab icon ID. Menu resource compliance
     */
    unsigned short iconId{0};

    unsigned char pad[2];
};

};
};

static_assert(sizeof(er::paramdef::bonfire_warp_tab_param_st) == 16,
              "BONFIRE_WARP_TAB_PARAM_ST paramdef size does not match detected size");
