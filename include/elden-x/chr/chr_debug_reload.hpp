
#pragma once

#include "../stl.hpp"

namespace er {

/**
 * The structure in WorldChrMan that contains the list of reload requests
 */
struct chr_debug_reload {
    struct reload_list_item {
        uint8_t unk0[0x40];
        wstring chr_name;

        reload_list_item(const std::wstring_view &chr_name)
            : chr_name(chr_name) {}
    };

    /**
     * List of debug reload requests. Insert e.g. L"c0000" to reload the main player model
     */
    list<reload_list_item> reload_list;

    /**
     * DSAS sets this to 10.f for some reason when reloading
     */
    float unk20;
};

}