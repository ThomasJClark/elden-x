#pragma once

#include "./utils/modutils.hpp"

#include <utility>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

namespace from
{
namespace CS
{

class CSWindow;
class CSScreenModeCtrl;

class CSWindow
{
  public:
    virtual ~CSWindow() = 0;

    static CSWindow *instance()
    {
        return modutils::get_singleton<CSWindow>("CSWindow");
    }

    enum class screen_mode : int
    {
        window = 0,
        fullscreen = 1,
        borderless_window = 2,
    };

    enum class quality_level : int
    {
        off = 0,
        low = 1,
        medium = 2,
        high = 3,
        max = 4,
    };

    struct graphics_settings
    {
        screen_mode screen_mode;
        bool auto_detect_best_rendering_settings;
        quality_level graphics_quality;
        quality_level texture_quality;
        quality_level antialiasing_quality;
        quality_level ssao;
        quality_level depth_of_field;
        quality_level motion_blur;
        quality_level shadow_quality;
        quality_level lighting_quality;
        quality_level effects_quality;
        quality_level reflection_quality;
        quality_level water_surface_quality;
        quality_level shader_quality;
        quality_level volumetric_quality;
        quality_level ray_tracing_quality;
        quality_level global_illumination_quality;
        quality_level grass_quality;
    };

    HWND hwnd;
    int unk10[4];
    std::pair<int, int> window_position;
    std::pair<int, int> window_size;
    int unk30[2];
    CSScreenModeCtrl *screen_mode_ctrl;
    int unk40[8];
    bool unk60;
    bool window_focused_previous;
    bool window_full_screen;
    bool window_focused;
    int unk64[32];
    graphics_settings graphics_settings;
};

static_assert(0x8 == __builtin_offsetof(CSWindow, hwnd));
static_assert(0x20 == __builtin_offsetof(CSWindow, window_position));
static_assert(0x28 == __builtin_offsetof(CSWindow, window_size));
static_assert(0x38 == __builtin_offsetof(CSWindow, screen_mode_ctrl));
static_assert(0x61 == __builtin_offsetof(CSWindow, window_focused_previous));
static_assert(0x62 == __builtin_offsetof(CSWindow, window_full_screen));
static_assert(0x63 == __builtin_offsetof(CSWindow, window_focused));
static_assert(0xe4 == __builtin_offsetof(CSWindow, graphics_settings.screen_mode));
static_assert(0xe8 ==
              __builtin_offsetof(CSWindow, graphics_settings.auto_detect_best_rendering_settings));
static_assert(0xec == __builtin_offsetof(CSWindow, graphics_settings.graphics_quality));
static_assert(0xf0 == __builtin_offsetof(CSWindow, graphics_settings.texture_quality));
static_assert(0xf4 == __builtin_offsetof(CSWindow, graphics_settings.antialiasing_quality));
static_assert(0xf8 == __builtin_offsetof(CSWindow, graphics_settings.ssao));
static_assert(0xfc == __builtin_offsetof(CSWindow, graphics_settings.depth_of_field));
static_assert(0x100 == __builtin_offsetof(CSWindow, graphics_settings.motion_blur));
static_assert(0x104 == __builtin_offsetof(CSWindow, graphics_settings.shadow_quality));
static_assert(0x108 == __builtin_offsetof(CSWindow, graphics_settings.lighting_quality));
static_assert(0x10c == __builtin_offsetof(CSWindow, graphics_settings.effects_quality));
static_assert(0x110 == __builtin_offsetof(CSWindow, graphics_settings.reflection_quality));
static_assert(0x114 == __builtin_offsetof(CSWindow, graphics_settings.water_surface_quality));
static_assert(0x118 == __builtin_offsetof(CSWindow, graphics_settings.shader_quality));
static_assert(0x11c == __builtin_offsetof(CSWindow, graphics_settings.volumetric_quality));
static_assert(0x120 == __builtin_offsetof(CSWindow, graphics_settings.ray_tracing_quality));
static_assert(0x124 == __builtin_offsetof(CSWindow, graphics_settings.global_illumination_quality));
static_assert(0x128 == __builtin_offsetof(CSWindow, graphics_settings.grass_quality));
static_assert(0x130 == sizeof(CSWindow));

}
}
