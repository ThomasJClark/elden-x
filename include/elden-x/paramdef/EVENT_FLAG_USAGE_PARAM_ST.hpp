/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct event_flag_usage_param_st {
    /**
     * @brief Use
     *
     * Use of the flag.
     */
    unsigned char usageType{0};

    /**
     * @brief Playlog category
     *
     * Valid only when the usage is "ON / OFF". If this is set, the play log
     * will be collected when the flag is turned ON.
     */
    unsigned char playlogCategory{0};

    unsigned char padding1[2];

    /**
     * @brief Number of secured flags
     *
     * Set to 1 for "ON / OFF". In the case of "frame allocation" and "integer",
     * "parameter number-parameter number + number of secured flags-1" is
     * secured.
     */
    int flagNum{1};

    unsigned char padding2[24];
};

};
};
