#include <iostream>
#include "process.hpp"
#include "cpu.hpp"
#include "interrupts.hpp"

int main(){
    setup_idt();

    PCB process1{101,"Some_app.exe",{}, 0};
    current_process = &process1;

    // creating fake user-space process state
    cpu.rsp = 0x7FFF0000;
    cpu.rip = 0x00401010;
    cpu.rax = 1;

    std::cout<<" [User space] process is running. RSP is 0x"<<std::hex<<cpu.rsp<<" and RIP is 0x"<<cpu.rip<<std::dec<<"\n";

    // simulating syscall here
    trigger_cpu_vector(14);

    // simulate timer interrupt
    trigger_cpu_vector(32);
    return 0;
}