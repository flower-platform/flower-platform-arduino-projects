################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../.ino.cpp 

INO_SRCS += \
../ir-test.ino 

INO_DEPS += \
./ir-test.ino.d 

CPP_DEPS += \
./.ino.cpp.d 

LINK_OBJ += \
./.ino.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=161 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\cores\arduino" -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\variants\standard" -I"D:\Java\arduino-1.6.1\libraries\Ethernet" -I"D:\Java\arduino-1.6.1\libraries\Ethernet\src" -I"C:\Users\Flower\Documents\Arduino\libraries\FlowerPlatformArduino_Runtime2" -I"C:\Users\Flower\Documents\Arduino\libraries\IRremote" -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\libraries\SPI" -I"C:\Users\Flower\Documents\Arduino\libraries\SdFat" -I"C:\Users\Flower\Documents\Arduino\libraries\SdFat\utility" -I"C:\Users\Flower\Documents\Arduino\libraries\DHT" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

ir-test.o: ../ir-test.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:/Java/arduino-1.6.1/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=161 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\cores\arduino" -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\variants\standard" -I"D:\Java\arduino-1.6.1\libraries\Ethernet" -I"D:\Java\arduino-1.6.1\libraries\Ethernet\src" -I"C:\Users\Flower\Documents\Arduino\libraries\FlowerPlatformArduino_Runtime2" -I"C:\Users\Flower\Documents\Arduino\libraries\IRremote" -I"D:\Java\arduino-1.6.1\hardware\arduino\avr\libraries\SPI" -I"C:\Users\Flower\Documents\Arduino\libraries\SdFat" -I"C:\Users\Flower\Documents\Arduino\libraries\SdFat\utility" -I"C:\Users\Flower\Documents\Arduino\libraries\DHT" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


