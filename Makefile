# @file makefile
# @engineer Matthew Hardenburgh
# @date 11/1/2019
# @copyright Matthew Hardenburgh 2019
# @liscence GNU GPL v3

STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main 
ARCH_FLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CXXFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) -c -g -std=c++11 -Wall -W -Werror -pedantic -Os -flto -ffunction-sections -fdata-sections # removed -Os flag
CXX=arm-none-eabi-g++
USE_NANO=--specs=nano.specs

# Use seimhosting or not
USE_SEMIHOST=--specs=rdimon.specs
USE_NOHOST=--specs=nosys.specs

GC=-Wl,--gc-sections

MAP=-Wl,-Map=main.map

LDSCRIPTS= -T gcc.ld
LFLAGS=$(USE_NANO) $(USE_SEMIHOST) $(LDSCRIPTS) $(GC) $(MAP)


main.bin: main.elf
	arm-none-eabi-objcopy -O binary main.elf main.bin
	arm-none-eabi-size main.elf

main.elf: startup_ARMCM4.o main.o register.o systick.o nvic.o sbc.o mpu.o fpu.o systemControl.o gpio.o generalPurposeTimer.o
	$(CXX) $^ $(ARCH_FLAGS) $(STARTUP_DEFS) -g -std=c++11 -Wall -W -Werror -pedantic -Os -flto -ffunction-sections -fdata-sections  -fno-exceptions $(LFLAGS) -o $@
 
startup_ARMCM4.o: startup_ARMCM4.S
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

main.o: main.cpp register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

register.o: register.cpp register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

systick.o: corePeripherals/systick/systick.cpp corePeripherals/systick/systick.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

nvic.o: corePeripherals/nvic/nvic.cpp corePeripherals/nvic/nvic.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

sbc.o: corePeripherals/sbc/sbc.cpp corePeripherals/sbc/sbc.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

mpu.o: corePeripherals/mpu/mpu.cpp corePeripherals/mpu/mpu.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

fpu.o: corePeripherals/fpu/fpu.cpp corePeripherals/fpu/fpu.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

systemControl.o: systemControl/systemControl.cpp systemControl/systemControl.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

gpio.o: gpio/gpio.cpp gpio/gpio.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

generalPurposeTimer.o: timer/generalPurposeTimer.cpp timer/generalPurposeTimer.h register.h
	$(CXX) $^ $(CXXFLAGS) -fno-exceptions

clean:
	rm -f *.o *.elf *.bin *.gch


