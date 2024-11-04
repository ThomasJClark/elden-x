#pragma once

#include "popup_menu.hpp"

namespace from
{
namespace CS
{

class CSMenuManImp
{
  public:
    virtual ~CSMenuManImp() = default;

    unsigned char unk8[0x78];

    CS::CSPopupMenu *popup_menu;
};

}
}
