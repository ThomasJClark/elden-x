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

class GXDeviceContext;
class GXProxyDeviceContext;
class GXRenderThread;

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
    struct globals_impl {
        void *unk0;
        void *unk8;
        int unk10;  // 0
        GXCommandQueue *command_queue;
        GXProxyDeviceContext *proxy_device_context;
        unsigned char unk28;  // 0xc0
        GXDeviceContext *device_context;
        unsigned char unk38[0x20];
        void *unk58;
        void *unk60;
        void *unk68;
        void *unk70;
        void *unk78;
        void *unk80;
        GXDeviceContext *device_context2;
        unsigned char unk90[0xb0];
        GXSwapChainOperatorForMultiWindow *swap_chain_operator;
        unsigned char unk148[0xd70];
        // GXRenderThread 6d0
        bool resize_requested;
        unsigned char unkeb9[0x157];
    } impl;

    static_assert(0x0 == __builtin_offsetof(globals_impl, unk0));
    static_assert(0x8 == __builtin_offsetof(globals_impl, unk8));
    static_assert(0x10 == __builtin_offsetof(globals_impl, unk10));
    static_assert(0x18 == __builtin_offsetof(globals_impl, command_queue));
    static_assert(0x28 == __builtin_offsetof(globals_impl, unk28));
    static_assert(0x30 == __builtin_offsetof(globals_impl, device_context));
    static_assert(0x38 == __builtin_offsetof(globals_impl, unk38));
    static_assert(0x88 == __builtin_offsetof(globals_impl, device_context2));
    static_assert(0x90 == __builtin_offsetof(globals_impl, unk90));
    static_assert(0x140 == __builtin_offsetof(globals_impl, swap_chain_operator));
    static_assert(0x148 == __builtin_offsetof(globals_impl, unk148));
    static_assert(0xeb8 == __builtin_offsetof(globals_impl, resize_requested));
    static_assert(0xeb9 == __builtin_offsetof(globals_impl, unkeb9));
    static_assert(0x1010 == sizeof(globals_impl));

public:
    static globals *instance();

    ID3D12CommandQueue *get_command_queue() {
        if (!impl.command_queue || !impl.command_queue->command_queue_holder) return nullptr;
        return impl.command_queue->command_queue_holder->command_queue;
    }

    IDXGISwapChain3 *get_swap_chain() {
        if (!impl.swap_chain_operator) return nullptr;

        auto &swap_chains = impl.swap_chain_operator->swap_chains;
        if (swap_chains.empty()) return nullptr;

        return swap_chains[0].swap_chain_holder->swap_chain;
    }

    /**
     * If true, the resolution or fullscreen settings have changed. This is set to false during the
     * DrawStep task group, and DirectX calls are made to allocate new resources.
     */
    bool is_resize_requested() { return impl.resize_requested; }
};

}
}