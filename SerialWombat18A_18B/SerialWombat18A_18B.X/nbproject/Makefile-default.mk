#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c quadEnc.c analogInput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c TM1637.c ws2812.c touch.c uartHw.c servo.c pwm.c outputScale.c resistanceInput.c uartSw.c throughputConsumer.c matrixKeypad.c inputProcess.c pinInputProcessor.c pulseOnChange.c hfServo.c ultrasonicDistance.c liquidCrystal.c HSClock.c HSCounter.c PS2Keyboard.c i2cController.c vga.c hBridge.c queuedPulseOutput.c MAX7219Matrix.c swI2cRoutines.c Font5x7.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c swMath.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/TM1637.o ${OBJECTDIR}/ws2812.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/uartHw.o ${OBJECTDIR}/servo.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/outputScale.o ${OBJECTDIR}/resistanceInput.o ${OBJECTDIR}/uartSw.o ${OBJECTDIR}/throughputConsumer.o ${OBJECTDIR}/matrixKeypad.o ${OBJECTDIR}/inputProcess.o ${OBJECTDIR}/pinInputProcessor.o ${OBJECTDIR}/pulseOnChange.o ${OBJECTDIR}/hfServo.o ${OBJECTDIR}/ultrasonicDistance.o ${OBJECTDIR}/liquidCrystal.o ${OBJECTDIR}/HSClock.o ${OBJECTDIR}/HSCounter.o ${OBJECTDIR}/PS2Keyboard.o ${OBJECTDIR}/i2cController.o ${OBJECTDIR}/vga.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/queuedPulseOutput.o ${OBJECTDIR}/MAX7219Matrix.o ${OBJECTDIR}/swI2cRoutines.o ${OBJECTDIR}/Font5x7.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/swMath.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d ${OBJECTDIR}/timingResource.o.d ${OBJECTDIR}/quadEnc.o.d ${OBJECTDIR}/analogInput.o.d ${OBJECTDIR}/pulseTimer.o.d ${OBJECTDIR}/debounce.o.d ${OBJECTDIR}/protectedOutput.o.d ${OBJECTDIR}/watchdog.o.d ${OBJECTDIR}/TM1637.o.d ${OBJECTDIR}/ws2812.o.d ${OBJECTDIR}/touch.o.d ${OBJECTDIR}/uartHw.o.d ${OBJECTDIR}/servo.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/outputScale.o.d ${OBJECTDIR}/resistanceInput.o.d ${OBJECTDIR}/uartSw.o.d ${OBJECTDIR}/throughputConsumer.o.d ${OBJECTDIR}/matrixKeypad.o.d ${OBJECTDIR}/inputProcess.o.d ${OBJECTDIR}/pinInputProcessor.o.d ${OBJECTDIR}/pulseOnChange.o.d ${OBJECTDIR}/hfServo.o.d ${OBJECTDIR}/ultrasonicDistance.o.d ${OBJECTDIR}/liquidCrystal.o.d ${OBJECTDIR}/HSClock.o.d ${OBJECTDIR}/HSCounter.o.d ${OBJECTDIR}/PS2Keyboard.o.d ${OBJECTDIR}/i2cController.o.d ${OBJECTDIR}/vga.o.d ${OBJECTDIR}/hBridge.o.d ${OBJECTDIR}/queuedPulseOutput.o.d ${OBJECTDIR}/MAX7219Matrix.o.d ${OBJECTDIR}/swI2cRoutines.o.d ${OBJECTDIR}/Font5x7.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/protocol.o.d ${OBJECTDIR}/asciiConversion.o.d ${OBJECTDIR}/pinRegisters.o.d ${OBJECTDIR}/queue.o.d ${OBJECTDIR}/swMath.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/TM1637.o ${OBJECTDIR}/ws2812.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/uartHw.o ${OBJECTDIR}/servo.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/outputScale.o ${OBJECTDIR}/resistanceInput.o ${OBJECTDIR}/uartSw.o ${OBJECTDIR}/throughputConsumer.o ${OBJECTDIR}/matrixKeypad.o ${OBJECTDIR}/inputProcess.o ${OBJECTDIR}/pinInputProcessor.o ${OBJECTDIR}/pulseOnChange.o ${OBJECTDIR}/hfServo.o ${OBJECTDIR}/ultrasonicDistance.o ${OBJECTDIR}/liquidCrystal.o ${OBJECTDIR}/HSClock.o ${OBJECTDIR}/HSCounter.o ${OBJECTDIR}/PS2Keyboard.o ${OBJECTDIR}/i2cController.o ${OBJECTDIR}/vga.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/queuedPulseOutput.o ${OBJECTDIR}/MAX7219Matrix.o ${OBJECTDIR}/swI2cRoutines.o ${OBJECTDIR}/Font5x7.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/swMath.o

# Source Files
SOURCEFILES=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c quadEnc.c analogInput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c TM1637.c ws2812.c touch.c uartHw.c servo.c pwm.c outputScale.c resistanceInput.c uartSw.c throughputConsumer.c matrixKeypad.c inputProcess.c pinInputProcessor.c pulseOnChange.c hfServo.c ultrasonicDistance.c liquidCrystal.c HSClock.c HSCounter.c PS2Keyboard.c i2cController.c vga.c hBridge.c queuedPulseOutput.c MAX7219Matrix.c swI2cRoutines.c Font5x7.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c swMath.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA702
MP_LINKER_FILE_OPTION=,--script="p24FJ256GA702_app.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/91880a4c9ea46a7237d177bf882926cdc52f0013.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/e22a7068db8799f0b94b42498afb9219d0679f0b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/9a7f7c725a6c0aa6fd51805650944b7a6ed61192.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/ec94e51248acad108295f46e4718f20e6e98b21c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/ce165a84acb94b22cc282d771d557a32889ae809.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/efcaeae23c7bbbe961622c4fc4b94c37ec2d7357.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/4623a29232c3a06a1a2be191711e2ba90187eec0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/878a4d6ab07f1d396520670f77fc11ee2c7f3a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/be0e969bf8b76e776ac01a40f24098475a4c23c8.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/41f1c589683df80fc59f012076698c747f43fb70.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/a15eebda3d7496a6c2c3ce79cd84534f1f6e949f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/e278a461646fa470b53d55d94a0bcdf84c26d7.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/8b390a32e285b45919cb82e9f51df0b72806011a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/7eef7d50df1e02c32295228edf585c0e226453a9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/9a5e16757661a2656761d4692fe0855835afbe30.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/f34664ab2ba4ab435fcfd043c0d87e5e68095cb0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/17212b52352e60fd6d8a52d70ac5bcc130c7835b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/e4e28b2db7d7a4b9a154313e4a14a18a66afc08.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/6baf25cd046f688e819f2b5055dc5d50b3f07f4e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/41c0d48008a402f8519978963d5bd3bb504df928.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/fe6b61e0f83d0425a74ea21593a5051977dd9a20.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/5dd6d460c738aa4eea1e9e19486ad4d5768dd466.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/c5dde945277d1a8a93c007a6731a170e376b0633.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/9a7ba2c8448ca45a4c41f0d5143b4b263ec66acb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/be3dacb501717f88b130df5425e7e1dfd6adaff4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/f10297ade381be026d3f556f7de2187471bf7140.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/cb68e02014aacd95dfc37c9f6d17f643fd2ea666.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TM1637.o: TM1637.c  .generated_files/defa6233da61836e81413d2cd67de99509724c0e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TM1637.o.d 
	@${RM} ${OBJECTDIR}/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TM1637.c  -o ${OBJECTDIR}/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TM1637.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ws2812.o: ws2812.c  .generated_files/e2e4236890caef768372e14dad6874c91ed488aa.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812.o.d 
	@${RM} ${OBJECTDIR}/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ws2812.c  -o ${OBJECTDIR}/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ws2812.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/d559aab310e6353398ac2f629dd868826f9c4083.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartHw.o: uartHw.c  .generated_files/e22974ce707cc50ddf846062916bd7100de79f60.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartHw.o.d 
	@${RM} ${OBJECTDIR}/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartHw.c  -o ${OBJECTDIR}/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartHw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/servo.o: servo.c  .generated_files/5e076f210d93d3e2430f2d714190386f6ba7d376.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.o.d 
	@${RM} ${OBJECTDIR}/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo.c  -o ${OBJECTDIR}/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/servo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/f20f83a52c228290d3b06bb0a845e63b8888304d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/outputScale.o: outputScale.c  .generated_files/47fdb4fbf8f03cb1f1993fe6838322b78d54405a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputScale.o.d 
	@${RM} ${OBJECTDIR}/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  outputScale.c  -o ${OBJECTDIR}/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/outputScale.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/resistanceInput.o: resistanceInput.c  .generated_files/37660259bd3101c760a2b2dc5ff3570cda3b0a3c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  resistanceInput.c  -o ${OBJECTDIR}/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/resistanceInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartSw.o: uartSw.c  .generated_files/3b8c78b5d53e01e8053167821254be81bc059342.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartSw.o.d 
	@${RM} ${OBJECTDIR}/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartSw.c  -o ${OBJECTDIR}/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartSw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/throughputConsumer.o: throughputConsumer.c  .generated_files/f7660d985f34a058a7af1cd60514408a534aa951.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  throughputConsumer.c  -o ${OBJECTDIR}/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/throughputConsumer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/matrixKeypad.o: matrixKeypad.c  .generated_files/1cc3d0b1cc2df0f62bb5d5cd8585dcbf36cf892.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  matrixKeypad.c  -o ${OBJECTDIR}/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/matrixKeypad.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/inputProcess.o: inputProcess.c  .generated_files/cd65f9f3d2e8dd482e4c35547933704f1dc90673.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  inputProcess.c  -o ${OBJECTDIR}/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/inputProcess.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinInputProcessor.o: pinInputProcessor.c  .generated_files/aceb895e129bee9d6745bce3eda183e1e465492.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinInputProcessor.c  -o ${OBJECTDIR}/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinInputProcessor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOnChange.o: pulseOnChange.c  .generated_files/979676870b1d98f8fea7b15609b4217d5bf5fb28.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOnChange.c  -o ${OBJECTDIR}/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOnChange.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hfServo.o: hfServo.c  .generated_files/bc9cd02b7b003ff2ce24dc16e69fcddb07ed8506.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hfServo.o.d 
	@${RM} ${OBJECTDIR}/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hfServo.c  -o ${OBJECTDIR}/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hfServo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ultrasonicDistance.o: ultrasonicDistance.c  .generated_files/140282ae3ce71fd33a605784ff634b102ed3e10f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrasonicDistance.c  -o ${OBJECTDIR}/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ultrasonicDistance.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/liquidCrystal.o: liquidCrystal.c  .generated_files/abca601d7f0e14d4a7dcff187a87df84c7f0a314.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  liquidCrystal.c  -o ${OBJECTDIR}/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/liquidCrystal.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSClock.o: HSClock.c  .generated_files/6d827ea7777d420d93e911c57f5a00e3d17d898b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSClock.o.d 
	@${RM} ${OBJECTDIR}/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSClock.c  -o ${OBJECTDIR}/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSClock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSCounter.o: HSCounter.c  .generated_files/a61fe6d6f0d9c000d165cfbcc991464f80e3ea57.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSCounter.c  -o ${OBJECTDIR}/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSCounter.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PS2Keyboard.o: PS2Keyboard.c  .generated_files/3a2f613f95ac2b3b2df0b88aa0d2648e56875a5e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PS2Keyboard.c  -o ${OBJECTDIR}/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PS2Keyboard.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cController.o: i2cController.c  .generated_files/422e36d24191ce575314a4d1f6a82d15eac4f310.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2cController.o.d 
	@${RM} ${OBJECTDIR}/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cController.c  -o ${OBJECTDIR}/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cController.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/vga.o: vga.c  .generated_files/b63e396a2a83f7744e1cfbecae8f8f6b368ec433.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vga.o.d 
	@${RM} ${OBJECTDIR}/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  vga.c  -o ${OBJECTDIR}/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/vga.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/c8d3ac606fb607f1ab576b330ab441faceef4c79.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hBridge.c  -o ${OBJECTDIR}/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queuedPulseOutput.o: queuedPulseOutput.c  .generated_files/c8b93169b6664e958f598d94ba31301e533a6360.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queuedPulseOutput.c  -o ${OBJECTDIR}/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queuedPulseOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/MAX7219Matrix.o: MAX7219Matrix.c  .generated_files/89f16780832a5d35bd6b6ef1f24e3762147591e2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  MAX7219Matrix.c  -o ${OBJECTDIR}/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/MAX7219Matrix.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swI2cRoutines.o: swI2cRoutines.c  .generated_files/2416d8340685d88f74e90e8bbb4275f2f5beca88.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swI2cRoutines.c  -o ${OBJECTDIR}/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swI2cRoutines.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Font5x7.o: Font5x7.c  .generated_files/3c4fd56cc3ed04d00706cc12f875979eecbb11eb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Font5x7.c  -o ${OBJECTDIR}/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Font5x7.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/8d47295724e3f06038ab8208ebfa8db9ee4cee9f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/2df8f4adb2ab4e08ffb900ed9404606952926792.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/8e91dfdcd006f6216490ec8992b4522e48b57b56.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/8eb60ef701539dc8ae30a9420b6d996bc12ab4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/e6b98be488455566e2c6056e50b21968d8516524.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swMath.o: swMath.c  .generated_files/f7a28e9d0a933e0b36302ab50a57afb1865d4f4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swMath.o.d 
	@${RM} ${OBJECTDIR}/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swMath.c  -o ${OBJECTDIR}/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swMath.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/fc86ffd2bf8211cdf278092b7ad36d34344d0479.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/a1df72426118b5325dfd7ca37bee80eb957b8b0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/fde9ca16b6fda23c23bb06e483243bcaeabed617.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/c35a89d0157a35a82d8945a7f2772f1fd46a80a0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/4a83f6db5d4017e69635d51a2ab8f61e805fe3cb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/822e99164cffc7b40846a0c589fa60a4a2ee1b0e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/aa2555056b1768f517c75ebbbbcfc04a8612de38.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/b76611f87933acc9e30bbbd96c7825848db9e36.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/b6e0e63ca7f615cbed06adf96a28f6e2e49c8301.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/823771c70474db74d55dd363ee605439d610e460.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/db4bffc0a9d1b1dcfed2fc39c7541268f9540e1b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/21dddf6368a13a2a633e91733e879e9461267301.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/3bb7be9b878efec8ab275a4c16a57b2740e269d2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/3414cfbc811914cf7e31da404a7bd5266b46e12b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/1ac7620a8ad179d5297c14d295569c95a6704d39.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/a0217211b001975740e2bff1909fa0cf0b384a38.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/aefa3081b85f76e7d1ef28e1ba194052699e05f0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/6b933be3c1159b6fbf7d11d9c8d11c0275dbfdea.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/e9800b10aef3b57b855deac33a5ee930b6f146a6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/cfdebfffe02dfdd02a0f039bab80976b87d18ab1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/55eecda4c473ec4002661bab9ea5637b1dd4b6e2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/8460685024d602083bd7fc4cce947c943ff80750.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/92ca8e7008296f7a2fd8e30fc1fb808c1a53b2aa.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/42178cf0c6abc65959d39a5b48ecfa4046ddd655.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/714c6f355aca902da0833191e264c42dc3cd1d35.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/1c32b46b2d5ef7aab24d25ffaead1750553c647f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/edb1cdcf9cdacf90198a0d3187681efbdc0364c3.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TM1637.o: TM1637.c  .generated_files/c976ad168cf04f434ec17caa4f76eefa16ffe94e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TM1637.o.d 
	@${RM} ${OBJECTDIR}/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TM1637.c  -o ${OBJECTDIR}/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TM1637.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ws2812.o: ws2812.c  .generated_files/2a9c2320da31d38a9d8e2856fe91e3308daeca1e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812.o.d 
	@${RM} ${OBJECTDIR}/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ws2812.c  -o ${OBJECTDIR}/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ws2812.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/225585b760485415195ff07fd841781a5ccabb25.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartHw.o: uartHw.c  .generated_files/d44669ff4e7575bf5a2950bedc99c34435e51e98.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartHw.o.d 
	@${RM} ${OBJECTDIR}/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartHw.c  -o ${OBJECTDIR}/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartHw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/servo.o: servo.c  .generated_files/e7a8b7073dcf0a2ca02830ef82be0df5477a07a1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.o.d 
	@${RM} ${OBJECTDIR}/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo.c  -o ${OBJECTDIR}/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/servo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/1dbeae05deb9674817a80b291500ced356f4bd66.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/outputScale.o: outputScale.c  .generated_files/9acb20d1e0a554d249ba492c5831582941438694.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputScale.o.d 
	@${RM} ${OBJECTDIR}/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  outputScale.c  -o ${OBJECTDIR}/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/outputScale.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/resistanceInput.o: resistanceInput.c  .generated_files/3e0d5e380f2ae06f1138c5a3c143d3aa92904c0b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  resistanceInput.c  -o ${OBJECTDIR}/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/resistanceInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartSw.o: uartSw.c  .generated_files/386806bf4bbc46c36218767e2a77542243f1cf67.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartSw.o.d 
	@${RM} ${OBJECTDIR}/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartSw.c  -o ${OBJECTDIR}/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartSw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/throughputConsumer.o: throughputConsumer.c  .generated_files/8dc092c585d172b5c9c168e737ace409ce289838.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  throughputConsumer.c  -o ${OBJECTDIR}/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/throughputConsumer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/matrixKeypad.o: matrixKeypad.c  .generated_files/d99dd694fcccfd1509a5a2e1a017fa790f94942.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  matrixKeypad.c  -o ${OBJECTDIR}/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/matrixKeypad.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/inputProcess.o: inputProcess.c  .generated_files/1133bc774654778852e1a763ed6d03a78cc6674d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  inputProcess.c  -o ${OBJECTDIR}/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/inputProcess.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinInputProcessor.o: pinInputProcessor.c  .generated_files/220bbd6995fe551157e794393525cb3a0ace28d5.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinInputProcessor.c  -o ${OBJECTDIR}/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinInputProcessor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOnChange.o: pulseOnChange.c  .generated_files/9892a16af48a827570ebe061c5e5411114dc5389.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOnChange.c  -o ${OBJECTDIR}/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOnChange.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hfServo.o: hfServo.c  .generated_files/e47fe32738c1a7e358e3be65bfe2debe65dac4c2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hfServo.o.d 
	@${RM} ${OBJECTDIR}/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hfServo.c  -o ${OBJECTDIR}/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hfServo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ultrasonicDistance.o: ultrasonicDistance.c  .generated_files/ec84bf2a42a6e3a810fa56dbf0f25090bdc30f0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrasonicDistance.c  -o ${OBJECTDIR}/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ultrasonicDistance.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/liquidCrystal.o: liquidCrystal.c  .generated_files/387ecd9b22da9f6bfdbb8a15d30b743879501159.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  liquidCrystal.c  -o ${OBJECTDIR}/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/liquidCrystal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSClock.o: HSClock.c  .generated_files/7fe7cb7bc72181012cc24e74757f3610eb00cfa1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSClock.o.d 
	@${RM} ${OBJECTDIR}/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSClock.c  -o ${OBJECTDIR}/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSClock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSCounter.o: HSCounter.c  .generated_files/c2fb3a76c9cedf038102fef2303a8f5bcecee986.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSCounter.c  -o ${OBJECTDIR}/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSCounter.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PS2Keyboard.o: PS2Keyboard.c  .generated_files/17f7303b70f1efa59b440061a1bcb081a99a3ba7.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PS2Keyboard.c  -o ${OBJECTDIR}/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PS2Keyboard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cController.o: i2cController.c  .generated_files/ba2778a1050172ce7b21799fcc2f632be703a98a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2cController.o.d 
	@${RM} ${OBJECTDIR}/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cController.c  -o ${OBJECTDIR}/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cController.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/vga.o: vga.c  .generated_files/557af84fac4f82a4d7226e74f54a19af9bfbc6eb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vga.o.d 
	@${RM} ${OBJECTDIR}/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  vga.c  -o ${OBJECTDIR}/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/vga.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/7ea8aa1ae69f12105940a5add060c00a7ac8a94c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hBridge.c  -o ${OBJECTDIR}/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queuedPulseOutput.o: queuedPulseOutput.c  .generated_files/bfbde5d057b54dc66fac086eebe0974cf1b5e252.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queuedPulseOutput.c  -o ${OBJECTDIR}/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queuedPulseOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/MAX7219Matrix.o: MAX7219Matrix.c  .generated_files/3321da06db00a3627ec0b630b0dcff083939ec74.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  MAX7219Matrix.c  -o ${OBJECTDIR}/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/MAX7219Matrix.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swI2cRoutines.o: swI2cRoutines.c  .generated_files/67a37f3bc32c9e539f8a5c17fb98a01300cb1d29.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swI2cRoutines.c  -o ${OBJECTDIR}/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swI2cRoutines.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Font5x7.o: Font5x7.c  .generated_files/10b67cccd2e1b993d1109a52613bbc4b4f7cb9ed.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Font5x7.c  -o ${OBJECTDIR}/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Font5x7.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/ceda84c4622fbab8e522054cfa831e7a789e488.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/1d53eba8c3bb48315b2b17a229cd4559019438b8.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/7cef7af982f4cf718e353d1a1395bc0fc8c1c583.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/d77194ea6872dde6123fcfac723e302d6c8a8e01.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/898d278d59cdb4c418d47951f52176b673f53d59.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swMath.o: swMath.c  .generated_files/5b82344ba599901fb853340a3db212a6a6314b3c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swMath.o.d 
	@${RM} ${OBJECTDIR}/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swMath.c  -o ${OBJECTDIR}/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swMath.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/562438c5685c97489b938387c23e6a7ac6af818.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/9d541a754a3587aea8e721c9ce77c85d95e67b01.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/cac09a5faf1f88915cfb089d1293444a5ee7bd75.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/dc1c35f8c47650292b1ee5ddc1355cb16d4b213e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ256GA702_app.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_app.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800 -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
