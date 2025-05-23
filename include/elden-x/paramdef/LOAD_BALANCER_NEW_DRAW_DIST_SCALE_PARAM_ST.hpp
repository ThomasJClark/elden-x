/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct load_balancer_new_draw_dist_scale_param_st {
    /**
     * @brief Activation level (start)
     *
     * Drawing distance scale activation level (start)
     */
    unsigned char DrawDist_LvBegin{21};

    /**
     * @brief Activation level (end)
     *
     * Drawing distance scale activation level (completed)
     */
    unsigned char DrawDist_LvEnd{21};

    unsigned char reserve0[2];

    /**
     * @brief Scale (start)
     *
     * Drawing distance scale (start)
     */
    float DrawDist_ScaleBegin{1.f};

    /**
     * @brief Scale (end)
     *
     * Drawing distance scale (completed)
     */
    float DrawDist_ScaleEnd{1.f};

    /**
     * @brief Activation level (start)
     *
     * Shadow drawing distance scale activation level (start)
     */
    unsigned char ShadwDrawDist_LvBegin{21};

    /**
     * @brief Activation level (end)
     *
     * Shadow drawing distance scale activation level (completed)
     */
    unsigned char ShadwDrawDist_LvEnd{21};

    unsigned char reserve1[2];

    /**
     * @brief Scale (start)
     *
     * Shadow drawing distance scale (start)
     */
    float ShadwDrawDist_ScaleBegin{1.f};

    /**
     * @brief Scale (end)
     *
     * Shadow drawing distance scale (completed)
     */
    float ShadwDrawDist_ScaleEnd{1.f};

    unsigned char reserve2[24];
};

};
};

static_assert(sizeof(er::paramdef::load_balancer_new_draw_dist_scale_param_st) == 48,
              "LOAD_BALANCER_NEW_DRAW_DIST_SCALE_PARAM_ST paramdef size does not match "
              "detected size");
