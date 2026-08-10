#include "interrupts.hpp"
#include "cpu.hpp"
#include <iostream>

// Kernel handler
void sys_call_trap_handler() {
    std::cout << "  [KERNEL] Executing Syscall Trap Handler...\n";
    std::cout << "  [KERNEL] Register RAX = " << cpu.rax << " (System Call ID)\n";
}

void timer_interrupt_handler() {
    std::cout << "  [KERNEL] Timer Interrupt Fired! Schedular Preempting...\n";
}

// Register Handlers into the fake IDT
void setup_idt() {
    idt[14] = {14, sys_call_trap_handler};      // Vector 14 will handle the Trap/Page Fault
    idt[32] = {32, timer_interrupt_handler};    // Vector 32 will handle a Timer Interrupt
}