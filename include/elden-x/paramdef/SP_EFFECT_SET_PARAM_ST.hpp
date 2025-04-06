/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct sp_effect_set_param_st {
    /**
     * @brief Special effect ID1
     */
    int spEffectId1{-1};

    /**
     * @brief Special effect ID2
     */
    int spEffectId2{-1};

    /**
     * @brief Special effect ID3
     */
    int spEffectId3{-1};

    /**
     * @brief Special effect ID4
     */
    int spEffectId4{-1};
};

};
};

static_assert(sizeof(er::paramdef::sp_effect_set_param_st) == 16,
              "SP_EFFECT_SET_PARAM_ST paramdef size does not match detected size");
