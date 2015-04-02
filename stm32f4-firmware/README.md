
# Suggested Toolchain
[GCC Arm Embedded](https://launchpad.net/gcc-arm-embedded)

Copy the downloaded folder to a shared location on your file system and add bin folder to your path.

# Compiling, Programming, and Debugging

The makefile can handle all of these tasks!

Compiling: ```$ make```

Programming: ```$ make program```

Debugging:
You'll probably want to have 2 terminal windows open. One for the openocd client and one for gcc (or your graphical debugger). The makefile will start an openocd client that connects the board's hardware to a gdb server. This is ```$ make debug``` In the other window, you can run gdb. We do not yet have a gdb init file, but could probably make one. The ```$ make gdb``` rule will call the arm-specific gdb version in the makefile.
