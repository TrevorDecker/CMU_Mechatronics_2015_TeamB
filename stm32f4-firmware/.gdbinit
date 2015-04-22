# target remote localhost:3333
target extended-remote localhost:3333
monitor reset
monitor halt
file main.elf
directory ./

