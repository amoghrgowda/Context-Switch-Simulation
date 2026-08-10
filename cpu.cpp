#include <iostream>
#include "hardware.hpp"
#include "interrupts.hpp"
#include "process.hpp"

// Creating our CPU here
Registers cpu;

void trigger_cpu_vector(uint8_t vector_id){}