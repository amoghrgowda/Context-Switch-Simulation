#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

constexpr size_t KERNEL_STACK_SIZE = 16384; // 16 KB

struct KernelStack{
    uint8_t memory[KERNEL_STACK_SIZE];
    
    uint64_t get_top_address() const{
        // We return in 64 bits so that it can be loaded directly onto the CPU register
        return reinterpret_cast<uint64_t>(&memory[KERNEL_STACK_SIZE]); 
        // The above memory seem to be accessing array out-of-bounds memory but it is intentional.
        // CPU performs pre-decrement push (decrements first and then pushes data in).
    }
};

struct PCB{
    int pid;
    std::string name;
    KernelStack kstack; // private kernel stack for each process.
    uint64_t saved_kernel_sp; // saves the stack pointer of the kernel stack before pausing.
};

extern PCB* current_process;