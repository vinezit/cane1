################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SRC_SRCS += \
..\src/init_stack.src 

C_SRCS += \
..\src/cane.c \
..\src/dbsct.c \
..\src/function.c \
..\src/global.c \
..\src/init.c \
..\src/interrupt_handlers.c \
..\src/mtu.c \
..\src/pfc.c \
..\src/reset_program.c \
..\src/run.c \
..\src/sbrk.c \
..\src/sensor.c \
..\src/serial.c \
..\src/vector_table.c \
..\src/wall.c 

C_DEPS += \
./src/cane.d \
./src/dbsct.d \
./src/function.d \
./src/global.d \
./src/init.d \
./src/interrupt_handlers.d \
./src/mtu.d \
./src/pfc.d \
./src/reset_program.d \
./src/run.d \
./src/sbrk.d \
./src/sensor.d \
./src/serial.d \
./src/vector_table.d \
./src/wall.d 

SRC_DEPS += \
./src/init_stack.d 

OBJS += \
./src/cane.obj \
./src/dbsct.obj \
./src/function.obj \
./src/global.obj \
./src/init.obj \
./src/init_stack.obj \
./src/interrupt_handlers.obj \
./src/mtu.obj \
./src/pfc.obj \
./src/reset_program.obj \
./src/run.obj \
./src/sbrk.obj \
./src/sensor.obj \
./src/serial.obj \
./src/vector_table.obj \
./src/wall.obj 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	scandep1 -MM -MP -MF"$(@:%.obj=%.d)" -MT"$(@:%.obj=%.obj)" -MT"$(@:%.obj=%.d)"   -I"C:\PROGRA~2\Renesas\Hew\Tools\Renesas\Sh\9_4_3/include" -D_SH   -D_SH2=1  -D_BIG=1 -D__STDC_VERSION__=199409L  -D__HITACHI__=1 -D__HITACHI_VERSION__=0x0904 -D_SH=1 -D__RENESAS__=1 -D__RENESAS_VERSION__=0x0904 -U_WIN32 -UWIN32 -U__WIN32__ -U__GNUC__ -U__GNUC_MINOR__ -U__GNUC_PATCHLEVEL__   -E -quiet -I. -C "$<"
	shc -lang=c -object="$(@:%.d=%.obj)"  -include="C:\PROGRA~2\Renesas\Hew\Tools\Renesas\Sh\9_4_3/include"  -gbr=auto -opt_range=all -infinite_loop=0 -global_alloc=1 -global_volatile=0 -struct_alloc=1 -del_vacant_loop=0 -macsave=1 -cpu=sh2 -nologo -chgincpath -errorpath  -define=_SH   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/%.obj: ../src/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: Assembler'
	asmsh -literal=pool,branch,jump,return -nolist -cpu=sh2 -nodebug -nologo -chgincpath -errorpath -object="$@" "$<"
	@echo 'Finished building: $<'
	@echo.

