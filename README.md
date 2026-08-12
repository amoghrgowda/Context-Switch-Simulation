# Intro
This is a learning simulation and not a real interrupt controller. I have intentionally simplified some things (e.g. only RIP/RFLAGS/old_RSP are modeled in the hardware trap frame, leaving out SS/RSP/RFLAGS/CS/RIP/error_code set. In software context,only RAX/RBX are modeled in the software context frame instead of the full general-purpose register set. Only a single privilege level transition is shown).

# Build
- Build with a plain g++ command:
```
g++ -std=c++17 -Wall -Wextra -o cpu_sim *.cpp
```
- Then Run:
```
./cpu_sim
```
# Notes
- C++17 (or later) is required for the modern C++ features used (inline keyword and brace-initialized structs like HardwareTrapFrame{},etc).