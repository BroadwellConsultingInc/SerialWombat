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
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c quadEnc.c analogInput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c TM1637.c ws2812.c touch.c uartHw.c servo.c pwm.c outputScale.c resistanceInput.c uartSw.c throughputConsumer.c matrixKeypad.c inputProcess.c pinInputProcessor.c pulseOnChange.c hfServo.c ultrasonicDistance.c liquidCrystal.c HSClock.c HSCounter.c PS2Keyboard.c i2cController.c vga.c hBridge.c queuedPulseOutput.c MAX7219Matrix.c swI2cRoutines.c frequencyOutput.c Font5x7.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c swMath.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/TM1637.o ${OBJECTDIR}/ws2812.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/uartHw.o ${OBJECTDIR}/servo.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/outputScale.o ${OBJECTDIR}/resistanceInput.o ${OBJECTDIR}/uartSw.o ${OBJECTDIR}/throughputConsumer.o ${OBJECTDIR}/matrixKeypad.o ${OBJECTDIR}/inputProcess.o ${OBJECTDIR}/pinInputProcessor.o ${OBJECTDIR}/pulseOnChange.o ${OBJECTDIR}/hfServo.o ${OBJECTDIR}/ultrasonicDistance.o ${OBJECTDIR}/liquidCrystal.o ${OBJECTDIR}/HSClock.o ${OBJECTDIR}/HSCounter.o ${OBJECTDIR}/PS2Keyboard.o ${OBJECTDIR}/i2cController.o ${OBJECTDIR}/vga.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/queuedPulseOutput.o ${OBJECTDIR}/MAX7219Matrix.o ${OBJECTDIR}/swI2cRoutines.o ${OBJECTDIR}/frequencyOutput.o ${OBJECTDIR}/Font5x7.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/swMath.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d ${OBJECTDIR}/timingResource.o.d ${OBJECTDIR}/quadEnc.o.d ${OBJECTDIR}/analogInput.o.d ${OBJECTDIR}/pulseTimer.o.d ${OBJECTDIR}/debounce.o.d ${OBJECTDIR}/protectedOutput.o.d ${OBJECTDIR}/watchdog.o.d ${OBJECTDIR}/TM1637.o.d ${OBJECTDIR}/ws2812.o.d ${OBJECTDIR}/touch.o.d ${OBJECTDIR}/uartHw.o.d ${OBJECTDIR}/servo.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/outputScale.o.d ${OBJECTDIR}/resistanceInput.o.d ${OBJECTDIR}/uartSw.o.d ${OBJECTDIR}/throughputConsumer.o.d ${OBJECTDIR}/matrixKeypad.o.d ${OBJECTDIR}/inputProcess.o.d ${OBJECTDIR}/pinInputProcessor.o.d ${OBJECTDIR}/pulseOnChange.o.d ${OBJECTDIR}/hfServo.o.d ${OBJECTDIR}/ultrasonicDistance.o.d ${OBJECTDIR}/liquidCrystal.o.d ${OBJECTDIR}/HSClock.o.d ${OBJECTDIR}/HSCounter.o.d ${OBJECTDIR}/PS2Keyboard.o.d ${OBJECTDIR}/i2cController.o.d ${OBJECTDIR}/vga.o.d ${OBJECTDIR}/hBridge.o.d ${OBJECTDIR}/queuedPulseOutput.o.d ${OBJECTDIR}/MAX7219Matrix.o.d ${OBJECTDIR}/swI2cRoutines.o.d ${OBJECTDIR}/frequencyOutput.o.d ${OBJECTDIR}/Font5x7.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/protocol.o.d ${OBJECTDIR}/asciiConversion.o.d ${OBJECTDIR}/pinRegisters.o.d ${OBJECTDIR}/queue.o.d ${OBJECTDIR}/swMath.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/timingResource.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/TM1637.o ${OBJECTDIR}/ws2812.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/uartHw.o ${OBJECTDIR}/servo.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/outputScale.o ${OBJECTDIR}/resistanceInput.o ${OBJECTDIR}/uartSw.o ${OBJECTDIR}/throughputConsumer.o ${OBJECTDIR}/matrixKeypad.o ${OBJECTDIR}/inputProcess.o ${OBJECTDIR}/pinInputProcessor.o ${OBJECTDIR}/pulseOnChange.o ${OBJECTDIR}/hfServo.o ${OBJECTDIR}/ultrasonicDistance.o ${OBJECTDIR}/liquidCrystal.o ${OBJECTDIR}/HSClock.o ${OBJECTDIR}/HSCounter.o ${OBJECTDIR}/PS2Keyboard.o ${OBJECTDIR}/i2cController.o ${OBJECTDIR}/vga.o ${OBJECTDIR}/hBridge.o ${OBJECTDIR}/queuedPulseOutput.o ${OBJECTDIR}/MAX7219Matrix.o ${OBJECTDIR}/swI2cRoutines.o ${OBJECTDIR}/frequencyOutput.o ${OBJECTDIR}/Font5x7.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/swMath.o

# Source Files
SOURCEFILES=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/memory/flash.s pic24fj256ga702/mcc_generated_files/i2c2Controller.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c timingResource.c quadEnc.c analogInput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c TM1637.c ws2812.c touch.c uartHw.c servo.c pwm.c outputScale.c resistanceInput.c uartSw.c throughputConsumer.c matrixKeypad.c inputProcess.c pinInputProcessor.c pulseOnChange.c hfServo.c ultrasonicDistance.c liquidCrystal.c HSClock.c HSCounter.c PS2Keyboard.c i2cController.c vga.c hBridge.c queuedPulseOutput.c MAX7219Matrix.c swI2cRoutines.c frequencyOutput.c Font5x7.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c swMath.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA702
MP_LINKER_FILE_OPTION=,--script="p24FJ256GA702_app.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/34ddf2b9f66dbd8cfa13b1943bfbcf2586ffaf43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/ff0c3a8221deb59084eb86abe6be57829c1d5f14 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/efa9aa0abfdf4b39cc6ce9f572b26309de5391f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/5268b5afb68bf8e3d2613f7dc670b8fd714621ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/9bed762ea44e9cd9365c0bf9dcb5633e89de6248 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/8e2e421c7e3ee91c5eef8bcb1441adb857e68c2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/1a85fdad410c9342bd5b3c2341e76427e9d238f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/6d650b88f633cf192ae1d557eb83035830542da5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/78bc202ce70501a7a47e07b784d5cb194482a9d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/a5e2142760cf204f44afd4a6ed505d0d71f6f0f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/9ba283ff4c03e25e67e26b74557640cf68880ab9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/fdfd8551e33a77c940cd43f115c40c400fb72269 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/a5a855b2963b87685cfca825a2918d1d9b1f1d90 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/f8ced2671457aeabfbb8be5e0061de369f0ad850 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/e2690757d92ab1dbf5fe4f917a80af4c66e923f0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/a239502c06a4552466c39de3c57a020ff66e5ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/789befa72540866794e3dc211ddf3f932d5ac8a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/1be76e0dc970829ece67b78454cff0fa90d9c97e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/96d1108f238313457c70dfa359016e7d9419ec20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/7abd4c82f3969aef3edb19904925234667c63cce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/856ed7d368233c496defd732b812c7a82008a76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/flags/default/f5393d460aaa1a3ab7d3f60f60122f6f468916a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/flags/default/d4bb320618849b9d11f22f57b8095f5f7e18c325 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/flags/default/d4e54cca17012f57c54a4518edb6362a83c781f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/flags/default/e975017d0bdca83261b17a951836fe292b9a370a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/flags/default/3003cc82fa1c73bab984e7707969bc52f7f559f0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/flags/default/a22739ec4143c1c782cc4b4e4d199c8cd260b2e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TM1637.o: TM1637.c  .generated_files/flags/default/6ca9a4fbafeedb15b1ef779b7f29615c3ced7385 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TM1637.o.d 
	@${RM} ${OBJECTDIR}/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TM1637.c  -o ${OBJECTDIR}/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TM1637.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ws2812.o: ws2812.c  .generated_files/flags/default/c87622eea30c8fe089796ab2582815d9407a996b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812.o.d 
	@${RM} ${OBJECTDIR}/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ws2812.c  -o ${OBJECTDIR}/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ws2812.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/flags/default/5c6977cbc4ebf0633e3411a31d11fd7d97f54f3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartHw.o: uartHw.c  .generated_files/flags/default/ff86a945ab83e5802171b9520ea608014055e9a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartHw.o.d 
	@${RM} ${OBJECTDIR}/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartHw.c  -o ${OBJECTDIR}/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartHw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/servo.o: servo.c  .generated_files/flags/default/b0429ab92d9b5f77353d7fce239bd65cc51539f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.o.d 
	@${RM} ${OBJECTDIR}/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo.c  -o ${OBJECTDIR}/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/servo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/flags/default/22a61b0d8f6b6214d664afc5c32a1445085c6e94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/outputScale.o: outputScale.c  .generated_files/flags/default/57278b00fdd1cd01c94519cf7b2e18b90fa6c0e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputScale.o.d 
	@${RM} ${OBJECTDIR}/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  outputScale.c  -o ${OBJECTDIR}/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/outputScale.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/resistanceInput.o: resistanceInput.c  .generated_files/flags/default/1ce5b4f83fe0fa43ce41efd5dc84d2c28228c6f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  resistanceInput.c  -o ${OBJECTDIR}/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/resistanceInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartSw.o: uartSw.c  .generated_files/flags/default/d86b5960ec37440b21244d1b9fd0461ad00b80cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartSw.o.d 
	@${RM} ${OBJECTDIR}/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartSw.c  -o ${OBJECTDIR}/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartSw.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/throughputConsumer.o: throughputConsumer.c  .generated_files/flags/default/b1b9b31f5d01d1d8ed4bff7ec8e4e1f389b17de4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  throughputConsumer.c  -o ${OBJECTDIR}/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/throughputConsumer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/matrixKeypad.o: matrixKeypad.c  .generated_files/flags/default/9af6eb44d4066eaa38b0fc86c7d2a8c9ca2e6857 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  matrixKeypad.c  -o ${OBJECTDIR}/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/matrixKeypad.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/inputProcess.o: inputProcess.c  .generated_files/flags/default/1e4bb2ddd25d3887a180776cf389112411450ac0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  inputProcess.c  -o ${OBJECTDIR}/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/inputProcess.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinInputProcessor.o: pinInputProcessor.c  .generated_files/flags/default/104ae5fb7b46067c6a05a56f19b6f86a798dd91e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinInputProcessor.c  -o ${OBJECTDIR}/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinInputProcessor.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOnChange.o: pulseOnChange.c  .generated_files/flags/default/f647101625727d470d23efea729c273fc1d52a6d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOnChange.c  -o ${OBJECTDIR}/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOnChange.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hfServo.o: hfServo.c  .generated_files/flags/default/2c737199d98751f033fdd7b2c81dd5bdddf1f564 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hfServo.o.d 
	@${RM} ${OBJECTDIR}/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hfServo.c  -o ${OBJECTDIR}/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hfServo.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ultrasonicDistance.o: ultrasonicDistance.c  .generated_files/flags/default/cd8f988640d9e4f4734cb8005b4a45de672ec86c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrasonicDistance.c  -o ${OBJECTDIR}/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ultrasonicDistance.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/liquidCrystal.o: liquidCrystal.c  .generated_files/flags/default/5b82c1f9694d3c7fa33b56f891f9f503b65c57c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  liquidCrystal.c  -o ${OBJECTDIR}/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/liquidCrystal.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSClock.o: HSClock.c  .generated_files/flags/default/7ad176121f23f516efde3dcb122cc074fb707b97 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSClock.o.d 
	@${RM} ${OBJECTDIR}/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSClock.c  -o ${OBJECTDIR}/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSClock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSCounter.o: HSCounter.c  .generated_files/flags/default/1173429215393f1f02226cc75de47fb6d3ef0a41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSCounter.c  -o ${OBJECTDIR}/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSCounter.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PS2Keyboard.o: PS2Keyboard.c  .generated_files/flags/default/77e15d9c4a57d9c12180f7bb7d93ee04e22d00a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PS2Keyboard.c  -o ${OBJECTDIR}/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PS2Keyboard.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cController.o: i2cController.c  .generated_files/flags/default/e1e3eb252c7f0c6352688562541a2019f469f699 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2cController.o.d 
	@${RM} ${OBJECTDIR}/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cController.c  -o ${OBJECTDIR}/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cController.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/vga.o: vga.c  .generated_files/flags/default/55d55ae0379a12434d82e2f0a335280e757a502c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vga.o.d 
	@${RM} ${OBJECTDIR}/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  vga.c  -o ${OBJECTDIR}/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/vga.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/flags/default/2d1992fbd0cdbff2fc77c2bae358092156198e7b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hBridge.c  -o ${OBJECTDIR}/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queuedPulseOutput.o: queuedPulseOutput.c  .generated_files/flags/default/5a76626f45025bf05357f1eaadd3d2ce03d7f1b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queuedPulseOutput.c  -o ${OBJECTDIR}/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queuedPulseOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/MAX7219Matrix.o: MAX7219Matrix.c  .generated_files/flags/default/7502916f20e871eade30cc3039916ffeb424e4f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  MAX7219Matrix.c  -o ${OBJECTDIR}/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/MAX7219Matrix.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swI2cRoutines.o: swI2cRoutines.c  .generated_files/flags/default/57d0577b0d4e7794631eb08fce70c5eb6307b208 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swI2cRoutines.c  -o ${OBJECTDIR}/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swI2cRoutines.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/frequencyOutput.o: frequencyOutput.c  .generated_files/flags/default/624ab9dd53705ba92913b057390552098e1f74ed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  frequencyOutput.c  -o ${OBJECTDIR}/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/frequencyOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Font5x7.o: Font5x7.c  .generated_files/flags/default/bcff292ad423e9b747f5da79191282fb26e4bb99 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Font5x7.c  -o ${OBJECTDIR}/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Font5x7.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/b7c0c267d956b4aa75c063ef04ddec8f418d92e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/d41c495dedd094bf8138c1a39fe7ae9609e35ae9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/a4cf37d7ffe35a5a593837083201e03946bc1d25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/38a13fbf441433547bba838642e48f370fb4239a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/flags/default/f77dda9e729abca3591240f8213d2d7e037ce444 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swMath.o: swMath.c  .generated_files/flags/default/79d2c26e5b2fb7e821e090e4053032c04bb684a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swMath.o.d 
	@${RM} ${OBJECTDIR}/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swMath.c  -o ${OBJECTDIR}/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swMath.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/234dfd2eb4d2e2ac2216bc109c716c42d37695b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/592f881a9cb45af34f7778e1c35aa42160c83f0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/7233197d3d27ed7efbfea672fd97c2bbc94ce92d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/20bf165d04b5b4697ef2a91b9a03b098d6623969 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/4bc1568abbc9e9e732b79eae450bb5a193514f46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/ad7568ea623614430ae0e4a613c9036926c6cd7b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/25f69bcfc046c453804213bce50c221ca2aeeef8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/9b9430dc74011b7cd1b6ddaef3493e6dfd28d4ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/b08fbb5455a3e4bec5a809e57270803daa11ccb9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/6a660bebac85c6134c2ac64edac045d246396831 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/4b650c3b303b9bdfb4ca5e4ee3ea5bc70b017f4d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/b7a333c0cf704d3b576b711d728828c0c07bc161 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/1d88029b52412c45cda1e992ad049f8e364d53fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/7ecee72a8e23d951d2e173e1449a832c5668842a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/771d69d983d8c7993515ad3cc48131f5d31bcbff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/1ab256841407c6437a36f98ad41169f11edae76b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/b0d72f4257bd77dfd757da9154208274a9052072 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o: pic24fj256ga702/mcc_generated_files/i2c2Controller.c  .generated_files/flags/default/1f613e549ba371eb021c0277a9b27203b4f164e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2Controller.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2Controller.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/46a872e856e1248ccc0d5898ab4da31887b96f2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/flags/default/267ca78b39a02d085d6999993e872404ac10a2f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timingResource.o: timingResource.c  .generated_files/flags/default/eb278d2693ed87fd4f1d921f751700612ba007bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timingResource.o.d 
	@${RM} ${OBJECTDIR}/timingResource.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timingResource.c  -o ${OBJECTDIR}/timingResource.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timingResource.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/flags/default/fb1b19ae828cc33213e11f2b1d6c246e78fbb5a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/flags/default/754201736ef18ec1eebc7cb789890b6eb5b4dc59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/flags/default/aa98a4c5165f4c5e4bbc48e19e2e85d0b7789355 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/flags/default/9a310bad04281554e84c5e3a6c18ad514a9e546c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/flags/default/c90419b55c26f40ed4a6ec77278e4bfe467ce9de .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/flags/default/6c9e7abe0068337750aa0c80a70a6cd15220ea5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/TM1637.o: TM1637.c  .generated_files/flags/default/77e3c3aed632058db4449761d83fb99ae5a48334 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TM1637.o.d 
	@${RM} ${OBJECTDIR}/TM1637.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  TM1637.c  -o ${OBJECTDIR}/TM1637.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/TM1637.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ws2812.o: ws2812.c  .generated_files/flags/default/bc495fde3d138c71a383dd1170f9aa08f113d3b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ws2812.o.d 
	@${RM} ${OBJECTDIR}/ws2812.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ws2812.c  -o ${OBJECTDIR}/ws2812.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ws2812.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/flags/default/22fd29644ef74667e663bfe6bbd8705e2d640873 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartHw.o: uartHw.c  .generated_files/flags/default/8ca70cc96cf9ef4917f17f826eb7e9ac4e4422f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartHw.o.d 
	@${RM} ${OBJECTDIR}/uartHw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartHw.c  -o ${OBJECTDIR}/uartHw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartHw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/servo.o: servo.c  .generated_files/flags/default/bbaf10f39f6a251dfbbfc02c6c6485b815e3a19e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.o.d 
	@${RM} ${OBJECTDIR}/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo.c  -o ${OBJECTDIR}/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/servo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm.o: pwm.c  .generated_files/flags/default/5201914be2f83f075982a3940933d4bbf284aa49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm.c  -o ${OBJECTDIR}/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/outputScale.o: outputScale.c  .generated_files/flags/default/7b06f5b30028ec9eb38b5d1de51d9e6938397104 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputScale.o.d 
	@${RM} ${OBJECTDIR}/outputScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  outputScale.c  -o ${OBJECTDIR}/outputScale.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/outputScale.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/resistanceInput.o: resistanceInput.c  .generated_files/flags/default/5823cd2a344638ea731f7f58b6c99f8f26f3d1b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/resistanceInput.o.d 
	@${RM} ${OBJECTDIR}/resistanceInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  resistanceInput.c  -o ${OBJECTDIR}/resistanceInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/resistanceInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uartSw.o: uartSw.c  .generated_files/flags/default/54bd96d9071d23c5bf798cc80bc7389f83cd1782 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uartSw.o.d 
	@${RM} ${OBJECTDIR}/uartSw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uartSw.c  -o ${OBJECTDIR}/uartSw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uartSw.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/throughputConsumer.o: throughputConsumer.c  .generated_files/flags/default/8663fcee5fbfd4a31ab6e8383a2673d139dffb33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/throughputConsumer.o.d 
	@${RM} ${OBJECTDIR}/throughputConsumer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  throughputConsumer.c  -o ${OBJECTDIR}/throughputConsumer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/throughputConsumer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/matrixKeypad.o: matrixKeypad.c  .generated_files/flags/default/39b47af0221db0a305455c53c70b38cc2c98c1de .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/matrixKeypad.o.d 
	@${RM} ${OBJECTDIR}/matrixKeypad.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  matrixKeypad.c  -o ${OBJECTDIR}/matrixKeypad.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/matrixKeypad.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/inputProcess.o: inputProcess.c  .generated_files/flags/default/d3714177288528a206121c6f0a80acdb57eb4e49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputProcess.o.d 
	@${RM} ${OBJECTDIR}/inputProcess.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  inputProcess.c  -o ${OBJECTDIR}/inputProcess.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/inputProcess.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinInputProcessor.o: pinInputProcessor.c  .generated_files/flags/default/c88a959acf8b35ef29b81ac5f3f6152ffa6bf643 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o.d 
	@${RM} ${OBJECTDIR}/pinInputProcessor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinInputProcessor.c  -o ${OBJECTDIR}/pinInputProcessor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinInputProcessor.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOnChange.o: pulseOnChange.c  .generated_files/flags/default/186a1f5bd6af705b59d7944a2326ef5293819ebc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOnChange.o.d 
	@${RM} ${OBJECTDIR}/pulseOnChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOnChange.c  -o ${OBJECTDIR}/pulseOnChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOnChange.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hfServo.o: hfServo.c  .generated_files/flags/default/d7df8f584638b2cbf4fd762551a451a4e933e1cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hfServo.o.d 
	@${RM} ${OBJECTDIR}/hfServo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hfServo.c  -o ${OBJECTDIR}/hfServo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hfServo.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ultrasonicDistance.o: ultrasonicDistance.c  .generated_files/flags/default/749ad23f58f3b78fcd1066761a1f8956c073f1e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o.d 
	@${RM} ${OBJECTDIR}/ultrasonicDistance.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrasonicDistance.c  -o ${OBJECTDIR}/ultrasonicDistance.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ultrasonicDistance.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/liquidCrystal.o: liquidCrystal.c  .generated_files/flags/default/b4a8b1693d726c7993fb3cad04cba5b91085803b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/liquidCrystal.o.d 
	@${RM} ${OBJECTDIR}/liquidCrystal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  liquidCrystal.c  -o ${OBJECTDIR}/liquidCrystal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/liquidCrystal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSClock.o: HSClock.c  .generated_files/flags/default/5e0eb0bc53e6f9fbad3a4ea2e8a305d4ea2044b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSClock.o.d 
	@${RM} ${OBJECTDIR}/HSClock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSClock.c  -o ${OBJECTDIR}/HSClock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSClock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/HSCounter.o: HSCounter.c  .generated_files/flags/default/afb7ef406f0d58f860b81a01b6dba86811480738 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSCounter.o.d 
	@${RM} ${OBJECTDIR}/HSCounter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  HSCounter.c  -o ${OBJECTDIR}/HSCounter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/HSCounter.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/PS2Keyboard.o: PS2Keyboard.c  .generated_files/flags/default/89a4725c1dd7d6c04b1106119eb68abb4b5414b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o.d 
	@${RM} ${OBJECTDIR}/PS2Keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  PS2Keyboard.c  -o ${OBJECTDIR}/PS2Keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/PS2Keyboard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/i2cController.o: i2cController.c  .generated_files/flags/default/2e1a8415ee5b04cdd3f250567e5720cfc0aa5845 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2cController.o.d 
	@${RM} ${OBJECTDIR}/i2cController.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  i2cController.c  -o ${OBJECTDIR}/i2cController.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/i2cController.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/vga.o: vga.c  .generated_files/flags/default/7de0add5f8f62e9bbe52ad22a55a679bb8a5e7f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vga.o.d 
	@${RM} ${OBJECTDIR}/vga.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  vga.c  -o ${OBJECTDIR}/vga.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/vga.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hBridge.o: hBridge.c  .generated_files/flags/default/c3853ba71c38d2dc42d676350d1e88cccd43ae9d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hBridge.o.d 
	@${RM} ${OBJECTDIR}/hBridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hBridge.c  -o ${OBJECTDIR}/hBridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hBridge.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queuedPulseOutput.o: queuedPulseOutput.c  .generated_files/flags/default/ddc4da1933fa0d0a58237c8cae2766420e126b7b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o.d 
	@${RM} ${OBJECTDIR}/queuedPulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queuedPulseOutput.c  -o ${OBJECTDIR}/queuedPulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queuedPulseOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/MAX7219Matrix.o: MAX7219Matrix.c  .generated_files/flags/default/ae8eeb812e0b62f633606154fe77ff4a0e5c588c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o.d 
	@${RM} ${OBJECTDIR}/MAX7219Matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  MAX7219Matrix.c  -o ${OBJECTDIR}/MAX7219Matrix.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/MAX7219Matrix.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swI2cRoutines.o: swI2cRoutines.c  .generated_files/flags/default/b49aa9e5cf14dba84804c97b37d8b0f57eed644f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o.d 
	@${RM} ${OBJECTDIR}/swI2cRoutines.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swI2cRoutines.c  -o ${OBJECTDIR}/swI2cRoutines.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swI2cRoutines.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/frequencyOutput.o: frequencyOutput.c  .generated_files/flags/default/441131d1bc6ad35c79104732b158b9cc05baeddb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/frequencyOutput.o.d 
	@${RM} ${OBJECTDIR}/frequencyOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  frequencyOutput.c  -o ${OBJECTDIR}/frequencyOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/frequencyOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Font5x7.o: Font5x7.c  .generated_files/flags/default/e545c46818e715626d299456a01fa6333df733df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Font5x7.o.d 
	@${RM} ${OBJECTDIR}/Font5x7.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Font5x7.c  -o ${OBJECTDIR}/Font5x7.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Font5x7.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/9cc9704b2d4cff2a0e2147984365ffddb8178f41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/flags/default/a12cfa6e3254bca5af4a826429dd83d022af947a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/flags/default/722846813b8998469a0b64aa1383353a8896d14e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/flags/default/f7ba7adabd29d8983c4a01f803d3b15210e36af6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/flags/default/f706d4bdb845b4965959898b6d90e177ed186390 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/swMath.o: swMath.c  .generated_files/flags/default/4750a168745bf6903bba4f0aa45284691cab2b0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/swMath.o.d 
	@${RM} ${OBJECTDIR}/swMath.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  swMath.c  -o ${OBJECTDIR}/swMath.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/swMath.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O2 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/4011a13541fe5e7a3408a33ac2631afc86e4bb7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/flags/default/aa0ec67292ef1ffa0ee39d44bf153db001320a1c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o: pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/a7a175440f4b50e99f44b057ec4708760f869114 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/memory/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/flags/default/bb716a82db5e8b2e660284a94bacfaca27a1e21b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ256GA702_app.gld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_app.gld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" --fill=0x555555@0x27000:0x27800 -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
