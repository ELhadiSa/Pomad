################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
tuto_pomad.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
tuto_pomad.list \

OBJCOPY_BIN += \
tuto_pomad.bin \


# All Target
all: tuto_pomad.elf secondary-outputs

# Tool invocations
tuto_pomad.elf: $(OBJS) $(USER_OBJS)
	arm-none-eabi-gcc -o "tuto_pomad.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 --specs=nosys.specs -Wl,-Map="tuto_pomad.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

tuto_pomad.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "tuto_pomad.list"
	@echo 'Finished building: $@'
	@echo ' '

tuto_pomad.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "tuto_pomad.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
