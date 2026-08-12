#pragma once
#include <cstdint>
#include <cstddef>
// (I like to heavily document and over-explain my code for convenience)
// Simulated CPU 64-bit register set in the order:
// Instruction pointer, stack pointer, Gen purp Rgst A & B, CPU flags.
struct Registers{
    uint64_t rip {};
    uint64_t rsp {};
    uint64_t rax {};
    uint64_t rbx {};
    uint64_t rflags {0x200}; // enable hardware interrupt by setting Interrupt Flag (IF) to 1
};

//creating our CPU here
inline Registers cpu;

// Simulated hardware stack frame - 
// CPU microcode stores the exact state of CPU into RAM (the kernel stack), particularly, inside this frame.
// This occurs the moment an interrupt fires and before the initial CPU state changes.
struct HardwareTrapFrame{
    uint64_t saved_rip {};
    uint64_t saved_rflags {};
    uint64_t saved_user_rsp {};
};

// Simulated saved register pushed by kernel handler
struct SoftwareContextFrame{
    uint64_t saved_rax {};
    uint64_t saved_rbx {};
};


//Memory push/pop helper functions (Similar to pushq and popq instructions)
template <typename T>
void push_onto_stack(uint64_t& rsp, const T& value) {
    rsp -= sizeof(T); // I think the value in x86-64 systems is decremented at a fixed value of 8 bytes
                     // I don't want to make it too complicated (especially the error handling part) so I will use C++ templates here
    T* stack_location = reinterpret_cast<T*>(rsp);
    *stack_location = value;
}

template <typename T>
T pop_from_stack(uint64_t& rsp){
  T* stack_location = reinterpret_cast<T*>(rsp);
  rsp += sizeof(T);
  return *stack_location;  
}
// end of helper functions