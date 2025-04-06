#pragma once

#include "grid_control.hpp"
#include "menu_window.hpp"

namespace er {
namespace CS {

/**
 * Base class of all dialogs where the player can select an item from a grid or list
 */
class GenericListSelectDialog : public CS::MenuWindow {
public:
    virtual ~GenericListSelectDialog() = default;

    CS::GridControl grid_control;

    unsigned char unk1200[0x60];
};

static_assert(0xa38 == __builtin_offsetof(GenericListSelectDialog, grid_control));
static_assert(0x1200 == __builtin_offsetof(GenericListSelectDialog, unk1200));
static_assert(0x1260 == sizeof(GenericListSelectDialog));

}
}
