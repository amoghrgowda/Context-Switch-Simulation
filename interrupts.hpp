#pragma once
#include <cstdint>

// Simulated Interrupt Descriptor Table Entry
struct IDTEntry{
    uint8_t vector_id; // (x86) # of vector capped at 256 for backward compatibility. 
    void (*handler_address)();
};

extern IDTEntry idt[256]; // each IDT entry has its own vector ID and points to a unique handler

void sys_call_trap_handler();
void timer_interrupt_handler();
void setup_idt();