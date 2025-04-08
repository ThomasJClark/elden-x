#pragma once

#include "./stl.hpp"

/**
 * https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12commandqueue
 */
class ID3D12CommandQueue;

/**
 * https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nn-dxgi1_4-idxgiswapchain3
 */
class IDXGISwapChain3;

namespace er {
namespace GXBS {

class GXCommandQueue {
public:
    virtual ~GXCommandQueue() = 0;

    struct command_queue_holder {
        void *allocator;
        ID3D12CommandQueue *command_queue;
    };

    command_queue_holder *command_queue_holder;
};

class GXSwapChainOperatorForMultiWindow {
public:
    virtual ~GXSwapChainOperatorForMultiWindow() = 0;

    struct swap_chain_holder {
        IDXGISwapChain3 *swap_chain;
    };

    struct swap_chain_entry {
        swap_chain_holder *swap_chain_holder;
        unsigned char unk8[0x168];
    };

    vector<swap_chain_entry> &swap_chains;
};

/**
 * Singleton that contains pointers to a bunch of global graphics objects
 */
class globals {
private:
    unsigned char unk0[0x18];
    GXCommandQueue *command_queue;
    unsigned char unk20[0x120];
    GXSwapChainOperatorForMultiWindow *swap_chain_operator;
    unsigned char unk10[0xec8];

public:
    static globals *instance();

    ID3D12CommandQueue *get_command_queue() {
        if (!command_queue || !command_queue->command_queue_holder) return nullptr;
        return command_queue->command_queue_holder->command_queue;
    }

    IDXGISwapChain3 *get_swap_chain() {
        if (!swap_chain_operator) return nullptr;

        auto &swap_chains = swap_chain_operator->swap_chains;
        if (swap_chains.empty()) return nullptr;

        return swap_chains[0].swap_chain_holder->swap_chain;
    }
};

}
}