# @file makefile
# @engineer Matthew Hardenburgh
# @date 11/1/2019
# @copyright Matthew Hardenburgh 2019
# @liscence GNU GPL v3

STARTUP_DEFS=-D__STARTUP_CLEAR_BSS -D__START=main 
ARCH_FLAGS=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORE_PERIPHERALS=corePeripherals/systick/systick.o corePeripherals/nvic/nvic.o corePeripherals/sbc/sbc.o corePeripherals/mpu/mpu.o corePeripherals/fpu/fpu.o adc/adc.o
# CXXFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) -c -g -std=c++11 -Wall -W -Werror -pedantic -Os -flto -ffunction-sections -fdata-sections -fno-exceptions 
CXXFLAGS=$(ARCH_FLAGS) $(STARTUP_DEFS) -c -g -std=c++11 -Wall -W -Werror -pedantic 
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
	arm-none-eabi-objdump main.elf -S > disasembly.txt
	arm-none-eabi-size main.elf


main.elf: startup_ARMCM4.o main.o register/register.o $(CORE_PERIPHERALS) systemControl/systemControl.o gpio/gpio.o timer/generalPurposeTimer.o pwm/pwm.o
	$(CXX) $^ $(ARCH_FLAGS) $(STARTUP_DEFS) -g -std=c++11 -Wall -W -Werror -pedantic -Os -flto -ffunction-sections -fdata-sections -fno-exceptions $(LFLAGS) -o $@
	# $(CXX) $^ $(ARCH_FLAGS) $(STARTUP_DEFS) -g -std=c++11 -Wall -W -Werror -pedantic  $(LFLAGS) -o $@

startup_ARMCM4.o: startup_ARMCM4.S
	$(CXX) $^ $(CXXFLAGS)

main.o: main.cpp main.h register/register.h
	$(CXX) $^ $(CXXFLAGS)

register.o: register.cpp register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

systick.o: corePeripherals/systick/systick.cpp corePeripherals/systick/systick.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

nvic.o: corePeripherals/nvic/nvic.cpp corePeripherals/nvic/nvic.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

sbc.o: corePeripherals/sbc/sbc.cpp corePeripherals/sbc/sbc.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

mpu.o: corePeripherals/mpu/mpu.cpp corePeripherals/mpu/mpu.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

fpu.o: corePeripherals/fpu/fpu.cpp corePeripherals/fpu/fpu.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

systemControl.o: systemControl/systemControl.cpp systemControl/systemControl.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

gpio.o: gpio/gpio.cpp gpio/gpio.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

generalPurposeTimer.o: timer/generalPurposeTimer.cpp timer/generalPurposeTimer.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

pwm.o: pwm/pwm.cpp pwm/pwm.h register/register.h
	$(CXX) $^ $(CXXFLAGS) -o $@

adc.o: adc/adc.cpp adc/adc.h
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -f *.o *.elf *.bin *.gch
	find . -name "*.o" -type f -delete
	find . -name "*.gch" -type f -delete


