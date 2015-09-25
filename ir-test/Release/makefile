################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/subdir.mk
-include Libraries/SdFat/utility/subdir.mk
-include Libraries/SdFat/subdir.mk
-include Libraries/SPI/subdir.mk
-include Libraries/IRremote/subdir.mk
-include Libraries/Ethernet/src/utility/subdir.mk
-include Libraries/Ethernet/src/subdir.mk
-include Libraries/DHT/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
ir_test.elf \

EEP += \
ir_test.eep \

FLASH_IMAGE += \
ir_test.hex \


# All Target
all: ir_test

# Tool invocations
ir_test: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-size" -A "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-ar" rcs  "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

ir_test.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.elf"   $(LINK_OBJ) $(AR)  "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/arduino.ar" "-LC:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

ir_test.eep: $(ELF)
	@echo 'Create eeprom image'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.elf" "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.eep"
	@echo 'Finished building: $@'
	@echo ' '

ir_test.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom  "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.elf" "C:/Users/Flower/.flower-platform/workspace/flower-platform-arduino-projects/ir-test/Release/ir_test.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(AR)$(C_DEPS)$(FLASH_IMAGE)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(ELF)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(INO_DEPS)$(AR_OBJ)$(CPP_DEPS)$(PDE_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) ir_test
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
