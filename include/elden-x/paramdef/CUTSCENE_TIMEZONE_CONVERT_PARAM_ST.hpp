/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct cutscene_timezone_convert_param_st {
    /**
     * @brief Pre-conversion time zone start time [hour]
     *
     * Start time of the time zone to be converted to cutscene time [hour]
     */
    float SrcTimezoneStart{0.f};

    /**
     * @brief Cutscene time after conversion [hour]
     *
     * Enter the time used during cutscene playback in hours [hour]
     */
    float DstCutscenTime{0.f};
};

};
};

static_assert(sizeof(er::paramdef::cutscene_timezone_convert_param_st) == 8,
              "CUTSCENE_TIMEZONE_CONVERT_PARAM_ST paramdef size does not match detected "
              "size");
