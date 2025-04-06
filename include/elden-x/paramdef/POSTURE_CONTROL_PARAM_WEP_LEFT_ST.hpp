/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct posture_control_param_wep_left_st {
    /**
     * @brief Left arm_front and back
     */
    short a000_leftArmFB{0};

    /**
     * @brief Left wrist_front and back
     */
    short a000_leftWristFB{0};

    /**
     * @brief Left wrist_inside and outside
     */
    short a000_leftWristIO{0};

    /**
     * @brief Left arm_front and back
     */
    short a002_leftArmFB{0};

    /**
     * @brief Left wrist_front and back
     */
    short a002_leftWristFB{0};

    /**
     * @brief Left wrist_inside and outside
     */
    short a002_leftWristIO{0};

    /**
     * @brief Left arm_front and back
     */
    short a003_leftArmFB{0};

    /**
     * @brief Left wrist_front and back
     */
    short a003_leftWristFB{0};

    /**
     * @brief Left wrist_inside and outside
     */
    short a003_leftWristIO{0};

    unsigned char pad[14];
};

};
};

static_assert(sizeof(er::paramdef::posture_control_param_wep_left_st) == 32,
              "POSTURE_CONTROL_PARAM_WEP_LEFT_ST paramdef size does not match detected "
              "size");
