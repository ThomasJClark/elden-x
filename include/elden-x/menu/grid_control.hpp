#pragma once

namespace from
{
namespace CS
{

/**
 * Stores the state of any grid or list selection dialog (talk lists, main menu, etc.)
 */
class GridControl
{
  public:
    virtual ~GridControl() = default;

    unsigned char unk8[0xc8];

    /** The number of menu items added to the current dialog */
    int item_count;

    /** The currently selected menu item */
    int current_item;

    unsigned char unkd8[0x6f0];
};

static_assert(0x8 == __builtin_offsetof(GridControl, unk8));
static_assert(0xd0 == __builtin_offsetof(GridControl, item_count));
static_assert(0xd4 == __builtin_offsetof(GridControl, current_item));
static_assert(0xd8 == __builtin_offsetof(GridControl, unkd8));
static_assert(0x7c8 == sizeof(GridControl));

}
}
