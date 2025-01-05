#pragma once

namespace from
{
namespace CS
{

/**
 * Source:
 * https://github.com/vswarte/chains-bindings/blob/main/crates/game/src/cs/world_chr_man.rs#L170
 */
template <typename T> class ChrSet
{
  public:
    unsigned char unk8[0x50];

    virtual unsigned int capacity(){};
    virtual T *at(unsigned int index){};
    virtual T &operator[](unsigned int index){};
    virtual void unkfn3(){};
    virtual void unkfn4(){};
    virtual void unkfn5(){};
    virtual void unkfn6(){};
    virtual void unkfn7(){};
    virtual void unkfn8(){};
    virtual void unkfn9(){};
    virtual void unkfn10(){};
    virtual void unkfn11(){};
    virtual void unkfn12(){};
    virtual void unkfn13(){};
};

}
}
