#
# Simple makefile to compile the STM32Cube example code given for the STM32F0xx
# family of ARM processors. This file should be placed in the example/demo
# directory that you wish to compile.
#
# INCLUDEDIRS selects all folders in the package that have header files. Since
#             this is already an inclusive list, it should not need editing.
#
# LIBSOURCES contains all the Driver (HAL/BSP) files that need to be compiled
#            for this specific project. This should be updated with the help
#            of the dependencies file (main.d) generated on any (including 
#            unsucessful) compilation.
#
# Note: The provided code sometimes uses windows backslashes (\) in include
#       paths. Update as needed.
#
# Note: When building the lists for LIBSOURCES, *_ex.c files must come before
#       the generic version of the file. This is necessary for linking to find
#       the extended (board-specific) version of the function.
#
# Example: These sources are meant for the CORTEXM_SysTick example. The file
#          should be saved at STM32Cube_FW_F0_V1.1.0/Projects/
#          STM32F072B-Discovery/Examples/Cortex/CORTEXM_SysTick/Makefile.
#
# Author: Ian Hartwig (ihartwig)
#
# Derived from szczys's makefile in 
# www.github.com/szczys/stm32f0-discovery-basic-template/
#

# build environment
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
MAKE = make
GDB = arm-none-eabi-gdb
OPENOCD = openocd

# location of OpenOCD Board .cfg files (only used with 'make program')
# OPENOCD_BOARD_DIR=/usr/share/openocd/scripts/board
OPENOCD_BOARD_DIR=/usr/local/share/openocd/scripts/board
# Board file (comes with open ocd)
OPENOCD_BOARD_FILE=stm32f429discovery.cfg
# Configuration (cfg) file containing programming directives for OpenOCD
OPENOCD_PROC_FILE=stm32f4-openocd.cfg

# project parameters
PROJ_NAME = main
CPU_FAMILY = STM32F4xx
CPU_MODEL_GENERAL = STM32F429xx
CPU_MODEL_SPECIFIC = STM32F429ZIT6

INCLUDEDIRS =
INCLUDEDIRS += ./Inc
INCLUDEDIRS += ./Drivers/STM32F4xx_HAL_Driver/Inc
INCLUDEDIRS += ./Drivers/CMSIS/Include
INCLUDEDIRS += ./Drivers/CMSIS/Device/ST/STM32F4xx/Include
INCLUDEDIRS += ./Drivers/BSP/STM32F429I-Discovery/
INCLUDEDIRS += ./Utilities/Fonts
INCLUDEDIRS += ./Utilities/Log

LIBSOURCES = 
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
LIBSOURCES += ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c
LIBSOURCES += ./Drivers/BSP/Components/ili9341/ili9341.c
LIBSOURCES += ./Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.c
LIBSOURCES += ./Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.c
LIBSOURCES += ./Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_sdram.c
LIBSOURCES += ./Utilities/Log/lcd_log.c

LIBOBJS = $(LIBSOURCES:.c=.o)

NEWLIB_DIR = newlib-2.2.0-1
NEWLIB_BRANCH_DIR = arm-none-eabi/armv7e-m/fpu/newlib

################################################################################
# auto-generated project paths
SOURCES = $(shell find ./Src -name *.c)
SOURCES += ./Startup/newlib_stubs.c
SOURCES += Startup/startup_stm32f429xx.s # add assembly startup template
OBJ1 = $(SOURCES:.c=.o)
OBJ = $(OBJ1:.s=.o)

LDSCRIPT = ./Startup/STM32F429ZI_FLASH.ld

# general compilation flags (for library and project)
# defines for hal/cmsis libraries
DEFS = -D $(CPU_MODEL_GENERAL) -D ARM_MATH_CM4
# processor-specific flags
MCFLAGS = -mcpu=cortex-m4 -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
OPTIMIZE = -Os
# combine flags
CFLAGS = $(MCFLAGS) $(OPTIMIZE) $(DEFS)
CFLAGS += -Wl,--gc-sections -Wl,-Map=main.map -std=c99
CFLAGS += $(addprefix -I ,$(INCLUDEDIRS))
CFLAGS += -include stm32f4xx_hal_conf.h # apparently everyone needs this config
AFLAGS = $(MCFLAGS)

# project compilation flags
CFLAGS_PROJECT = 
CFLAGS_PROJECT += -L . -lstm32f4 # stm32f4 HAL/BSP
CFLAGS_PROJECT += -L ./newlib -lc # newlib (libc functions)
CFLAGS_PROJECT += -T $(LDSCRIPT) -MD # linker script


.PHONY: all proj clean program debug

all: proj

proj: newlib libstm32f4.a $(PROJ_NAME).elf

newlib:
ifeq ($(wildcard $(NEWLIB_DIR)/Makefile), )
	cd $(NEWLIB_DIR) && ./configure --target arm-none-eabi --disable-newlib-supplied-syscalls
endif
	cd $(NEWLIB_DIR)/$(NEWLIB_BRANCH_DIR) && $(MAKE)
	cp -r $(NEWLIB_DIR)/$(NEWLIB_BRANCH_DIR) ./

libstm32f4.a: $(LIBOBJS)
	@echo
	$(AR) -r $@ $(LIBOBJS)

%.o: %.c
	@echo
# $(eval AUTOINCLUDES = $(addprefix -include ,$(shell find $(dir $<) -name *.h)))
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROJ_NAME).elf: $(SOURCES)
	@echo
	$(CC) $^ -o $@ $(CFLAGS) $(CFLAGS_PROJECT)
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf

# load the program over openocd/jtag/stlink
program: proj
	$(OPENOCD) -f $(OPENOCD_BOARD_DIR)/$(OPENOCD_BOARD_FILE) -f $(OPENOCD_PROC_FILE) -c "stm_flash \"`pwd`/$(PROJ_NAME).bin\"" -c shutdown


debug:
	$(OPENOCD) -f $(OPENOCD_BOARD_DIR)/$(OPENOCD_BOARD_FILE) -f $(OPENOCD_PROC_FILE)

gdb:
	$(GDB)

clean:
	rm $(LIBOBJS) || true
	rm libstm32f4.a || true
	rm $(PROJ_NAME).elf || true
	rm $(PROJ_NAME).hex || true
	rm $(PROJ_NAME).bin || true
	rm $(PROJ_NAME).map || true
	rm $(PROJ_NAME).lst || true
	rm $(PROJ_NAME).d || true

reallyclean: clean
	rm -rf newlib || true
	cd $(NEWLIB_DIR) && $(MAKE) clean
	cd $(NEWLIB_DIR) && rm Makefile
