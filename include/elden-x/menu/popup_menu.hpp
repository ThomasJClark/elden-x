#pragma once

#include "menu_window.hpp"

namespace er
{
namespace CS
{

class CSMenuManImp;

class CSPopupMenu
{
  public:
    virtual ~CSPopupMenu() = default;

    CS::CSMenuManImp *owner;
    CS::MenuWindow *window;
};

}
}
