/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct sfx_block_res_share_param {
    /**
     * @brief Block Sfx resource reference map number
     *
     * The map number that references the resource. Set the numerical value of
     * the map number. (m12_34_56_78 → 12345678)
     */
    unsigned int shareBlockRsMapUidVal{0};
};

};
};

static_assert(sizeof(er::paramdef::sfx_block_res_share_param) == 4,
              "SFX_BLOCK_RES_SHARE_PARAM paramdef size does not match detected size");
