################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp src/*.src src/*.p src/*.pp *.bls *.libelf *.lbk *.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CP_DEPS)),)
-include $(CP_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CP_UPPER_DEPS)),)
-include $(CP_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(ABS_DEPS)),)
-include $(ABS_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
CONVERTOR_OUTPUT_OUTPUTS += \
cane3.mot \

LINKER_OUTPUT_OUTPUTS += \
cane3.abs \

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
cane3.lib \

# All Target
all: cane3.mot
	@echo 'Build complete.'

# Tool invocations
cane3.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Converter'
	optlnk   "C:\Users\ilove\e2_studio\caneworkspace3\cane3\Release\cane3.abs" -form=stype  -output="C:\Users\ilove\e2_studio\caneworkspace3\cane3\Release\cane3.mot"
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

cane3.abs: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	optlnk  -subcommand="LinkerSubCommand.tmp"  -library="C:\Users\ilove\E2_STU~1\CANEWO~3\cane3\Release\cane3.lib" -noprelink -list="cane3.map" -nooptimize -nodebug -output="C:\Users\ilove\e2_studio\caneworkspace3\cane3\Release\cane3.abs" -rom=D=R -nomessage -nologo
	@echo 'Finished building:'
	@echo.

cane3.lib:  
	@echo 'Invoking: Standard Library'
	lbgsh -head=runtime,new,ctype,math,mathf,stdarg,stdio,stdlib,string,ios,complex,cppstring -gbr=auto -cpu=sh2 -output="cane3.lib"
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
	-$(RM) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS) 
	-rm -rf "src"/*.obj "src"/*.d "src"/*.src "src"/*.p "src"/*.pp "src"/*.mrc "src"/*.prn
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-C:\Renesas\E2_STU~1\DEBUGC~1\SH\SH_CON~1.EXE cane3.abs cane3.x
	@echo.

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
