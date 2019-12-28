# @file makefile
# @engineer Matthew Hardenburgh
# @date 11/1/2019
# @copyright Matthew Hardenburgh 2019
# @liscence GNU GPL v3

STARTUP_DEFS= -D__STARTUP_CLEAR_BSS -D__START=main -D__NO_SYSTEM_INIT
ARCH_FLAGS= -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
COMPILE_FLAGS= -c -g -Wall -W -Werror -pedantic -fno-exceptions 
COMPILER= arm-none-eabi
USE_NANO=--specs=nano.specs

# Use seimhosting or not
USE_SEMIHOST=--specs=rdimon.specs
USE_NOHOST=--specs=nosys.specs

GC=--gc-sections

MAP=-Map=main.map

main.bin: main.elf
	$(COMPILER)-objcopy -O binary main.elf main.bin

main.elf: nokeep.ld startup_ARMCM4.o main.o register.o systick.o nvic.o sbc.o mpu.o fpu.o systemControl.o systemClock.o gpioControl.o gpio.o
	$(COMPILER)-ld -T $^ -o main.elf $(GC) $(MAP)
 
startup_ARMCM4.o: startup_ARMCM4.S
	$(COMPILER)-g++ $^ $(ARCH_FLAGS) $(STARTUP_DEFS) $(COMPILE_FLAGS) 
  
main.o: main.cpp register.h
	$(COMPILER)-g++ $^ $(ARCH_FLAGS) $(COMPILE_FLAGS) -fdata-sections

register.o: register.cpp register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

systick.o: corePeripherals/systick/systick.cpp corePeripherals/systick/systick.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS) 

nvic.o: corePeripherals/nvic/nvic.cpp corePeripherals/nvic/nvic.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

sbc.o: corePeripherals/sbc/sbc.cpp corePeripherals/sbc/sbc.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

mpu.o: corePeripherals/mpu/mpu.cpp corePeripherals/mpu/mpu.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

fpu.o: corePeripherals/fpu/fpu.cpp corePeripherals/fpu/fpu.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

systemControl.o: systemControl/systemControl.cpp systemControl/systemControl.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

systemClock.o: systemControl/systemClock.cpp systemControl/systemClock.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

gpioControl.o: gpio/gpioControl.cpp gpio/gpioControl.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

gpio.o: gpio/gpio.cpp gpio/gpio.h register.h
	$(COMPILER)-g++ $^ $(COMPILE_FLAGS) $(ARCH_FLAGS)

clean:
	rm -f *.o *.elf *.bin


