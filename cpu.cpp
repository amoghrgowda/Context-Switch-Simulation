#include <iostream>
#include "cpu.hpp"
#include "interrupts.hpp"
#include "process.hpp"

void trigger_cpu_vector(uint8_t vector_id){
    std::cout << "\nCPU triggering Vector ID: "<< static_cast<int>(vector_id)<<"\n"; 

    // Multiple steps happen when a cpu vector is triggered, I will try my best to cover them accurately

    //Step 1: Switching RSP to Kernel stack. CPU needs to push the RSP into kernel stack of that process.
    // Caveat: If the CPU was in user mode, it first needs to switch to kernel mode and then push. (not doing this here for simplicity)
    uint64_t old_user_rsp = cpu.rsp;
    cpu.rsp = current_process -> kstack.get_top_address(); // on real hardware, CPU just reads the TSS register.
    std::cout << " [CPU] Flipped the RSP from user stack (0x" << std::hex << old_user_rsp << ") to Kernel Stack (0x"<< cpu.rsp <<")\n"<< std::dec;

    // STEP 2: Push Hardware Trap Frame
    // In reality, a HardwareTrapFrame is just a mental model/virtual collection of certain important CPU registers. It doesn't physically exist anywhere.
    HardwareTrapFrame hw_frame{cpu.rip, cpu.rflags, old_user_rsp};
    // This "HTF" is copied onto the RAM (Kernel stack).
    push_onto_stack(cpu.rsp, hw_frame);

    // In short, in real CPU, what happens is the CPU stores the registers (virtually grouped as Hardware Trap Frame) -
    // - into the location provided by TSS register (which is the top of the kernel stack).

    // STEP C : Push Software Context Frame (General purp registers, placed lower memory address compared to HTF).
    SoftwareContextFrame sw_frame{cpu.rax, cpu.rbx};
    push_onto_stack(cpu.rsp, sw_frame);

    // STEP D: Jumping to respective handler via IDT Lookup
    idt[vector_id].handler_address();   // The handler does its thing to serve the interrupt...

    // next steps : restore the contexts BUT it is done in the exact reverse order of being pushed (stack, duh).

    // STEP E : restore software context
    SoftwareContextFrame restored_sw = pop_from_stack<SoftwareContextFrame>(cpu.rsp);
    cpu.rax = restored_sw.saved_rax;
    cpu.rbx = restored_sw.saved_rbx;

    //STEP F: Restore hardware context and return (iret 
    // or iretq on 64-bit is the opposite of whatever mechanism did automatic push into kernel stack)
    HardwareTrapFrame restored_hw = pop_from_stack<HardwareTrapFrame>(cpu.rsp);
    cpu.rip = restored_hw.saved_rip;
    cpu.rflags = restored_hw.saved_rflags;
    cpu.rsp = restored_hw.saved_user_rsp;

    std::cout<<" [CPU] Executed iret. Restored User RSP to 0x"<<std::hex<<cpu.rsp<<std::dec<<"\n";
}