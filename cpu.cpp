// Simulated CPU 64-bit register set in the order:
// Instruction pointer, stack pointer, Gen purp Rgst A & B, CPU flags.
struct Registers{
    uint64_t rip {};
    uint64_t rsp {};
    uint64_t rax {};
    uint64_t rbx {};
    uint64_t rflags {0x200}; // enable hardware interrupt by setting Interrupt Flag (IF) to 1
};

// Simulated hardware stack frame - 
// CPU microcode stores these into RAM (the stack)
// before changing initial state upon interrupt/trap
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

// Simulated Interrupt Descriptor Table Entry
struct IDTEntry{
    uint8_t vector_id; // (x86) # of vector capped at 256 for backward compatibility. 
    void (*handler_address)();
};

constexpr size_t KERNEL_STACK_SIZE = 16384;