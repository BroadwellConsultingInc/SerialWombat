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
SOURCEFILES_QUOTED_IF_SPACED=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/BSLIM_app.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c quadEnc.c analogInput.c pulseOutput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseOutput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o.d ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d ${OBJECTDIR}/quadEnc.o.d ${OBJECTDIR}/analogInput.o.d ${OBJECTDIR}/pulseOutput.o.d ${OBJECTDIR}/pulseTimer.o.d ${OBJECTDIR}/debounce.o.d ${OBJECTDIR}/protectedOutput.o.d ${OBJECTDIR}/watchdog.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/protocol.o.d ${OBJECTDIR}/asciiConversion.o.d ${OBJECTDIR}/pinRegisters.o.d ${OBJECTDIR}/queue.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o ${OBJECTDIR}/quadEnc.o ${OBJECTDIR}/analogInput.o ${OBJECTDIR}/pulseOutput.o ${OBJECTDIR}/pulseTimer.o ${OBJECTDIR}/debounce.o ${OBJECTDIR}/protectedOutput.o ${OBJECTDIR}/watchdog.o ${OBJECTDIR}/main.o ${OBJECTDIR}/protocol.o ${OBJECTDIR}/asciiConversion.o ${OBJECTDIR}/pinRegisters.o ${OBJECTDIR}/queue.o

# Source Files
SOURCEFILES=pic24fj256ga702/mcc_generated_files/clock.c pic24fj256ga702/mcc_generated_files/crc.c pic24fj256ga702/mcc_generated_files/cvr.c pic24fj256ga702/mcc_generated_files/dma.c pic24fj256ga702/mcc_generated_files/i2c1.c pic24fj256ga702/mcc_generated_files/i2c2.c pic24fj256ga702/mcc_generated_files/interrupt_manager.c pic24fj256ga702/mcc_generated_files/mcc.c pic24fj256ga702/mcc_generated_files/pin_manager.c pic24fj256ga702/mcc_generated_files/system.c pic24fj256ga702/mcc_generated_files/tmr1.c pic24fj256ga702/mcc_generated_files/tmr2.c pic24fj256ga702/mcc_generated_files/tmr3.c pic24fj256ga702/mcc_generated_files/traps.c pic24fj256ga702/mcc_generated_files/uart1.c pic24fj256ga702/mcc_generated_files/uart2.c pic24fj256ga702/mcc_generated_files/adc1.c pic24fj256ga702/mcc_generated_files/BSLIM_app.c pic24fj256ga702/wombatasm.s pic24fj256ga702/pinDigitalHwSpecific.c pic24fj256ga702/updatePulse.c quadEnc.c analogInput.c pulseOutput.c pulseTimer.c debounce.c protectedOutput.c watchdog.c main.c protocol.c asciiConversion.c pinRegisters.c queue.c



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
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/7edc5a18e9fc7fce980e71994ae9b6dbcad0500d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/efbe072347edd66782828b8b430e390b0b8532b8.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/adeff432288e6b356b4fc74a5c7a7be513e47f3b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/2a8b16950aac874d4fc2eb19faf097c059f801b6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/78abb868e13f9b3cac6e86688288a9c1bf32f2a1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/13d68f89f0b490f3c457647f7787881e6541d5e4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/9aeb6ceae6130a37c6094013af8cf100475bef28.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/a89a2f07ffe32ede2dfbf7f0b0cd1e4a4cf68877.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/35e9cdf541b7440f21047b151aa7a0db3d459654.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/c459b186ec85d19c57775ca151897c528ea2f030.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/e56a0f8e1ca47f40cf175ec02dd6bdf7840ecefc.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/77708259ba182ced6b69d76d3d185bb12896f86b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/f2ad696bbf854c6584679136b29e752c76fbc81a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/5efc044e43c129578edf3dcb9f7524aa5ec58340.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/e37b18439e3b0cd4bae1f5afd43c048e267f2c02.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/23d334103f76725dc8e34c16a3cdb93c10fe8bc6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/e4f9098479ef96c0cb217bb0861b0ca4ae5bb715.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o: pic24fj256ga702/mcc_generated_files/BSLIM_app.c  .generated_files/51256557e8ddbe9bebf751b2bde6cdef39aa2a30.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/BSLIM_app.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/ae2169e13ce9e6c4e9b5f03205427da89913877.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/2d98e5c021a01740279cdc6e67c4d4e0bd15902e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/e451ad0b1ee947a120e9d83b094e483b346a1792.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/b6eafc07b19dc17108b3868833c184ac8171a430.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOutput.o: pulseOutput.c  .generated_files/1a911c79ee9cb7178d54812d8ebc1144b43861dc.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOutput.o.d 
	@${RM} ${OBJECTDIR}/pulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOutput.c  -o ${OBJECTDIR}/pulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/9e011a2ecfd36e1c56e3b775dffda6a52c2d6801.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/7ce11798ea3a44fc40b04e6fe16a54411d2ba6ee.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/e565103cdfa4d21d3ed7e15b69caedfea6791f4d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/28a97ee2cc5352251e43413620011e20e207eca.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/52b405c361a4da92c4733a5b3c13bfc1adc483c7.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/e48464bca926d628399672d27c459c169e977df6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/58a05350d843a686e97fce4b39bd197f07a49ca3.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/e1a47b92dc8bb0f46b55f6fe6d37b964e86cd052.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/13116efc91aa6c97328175d5b3b3109c015c4541.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o: pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/c2001faacfb4907bb9376bd597d363bcf90638c6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o: pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/50c8eedb56dc40d131edc7ededa4beade5a20a65.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/crc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o: pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/98e8e6f4f703a6f8c5dbd41a8c4b38f205f1cd35.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/cvr.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o: pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/ae9c4938d7aa7956b9ebdc82150fe04ac20f6179.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/dma.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o: pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/8db76fb839ffcb87baf0aee78d2593fbdc59eb47.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o: pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/b02e359c5437d790d89d70f20f5f0210a0da38b4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/i2c2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o: pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/80879665c05b84bda969d0ab3449239a29b63c04.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o: pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/928c936df55b1a500b2f9bb041525e0b8d93f754.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o: pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/7eff749383d2458a3c5af79f97403adce4e2e28f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o: pic24fj256ga702/mcc_generated_files/system.c  .generated_files/d83d1b110b7edbf14461851e2aad8be61b4ce3de.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o: pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/3756bc784c02555c9ce1738d07c57c0491328486.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o: pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/3ff0e93fc89a24515b64da8480e3c9999bd2a45c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o: pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/a50aeaceacb749987f721bfea209adf1b0b4f47e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/tmr3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o: pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/8516ba49f1926f03e9138f74d54cbf0cd7538ac1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o: pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/315ababccb2a31ac2a371ca290bab39db4e2e9c0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o: pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/d11bd667bbb41de849ad478873490a6851e92d58.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/uart2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o: pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/81461c6644ebb0eb0da3d9fa9e619ba2ffb54060.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o: pic24fj256ga702/mcc_generated_files/BSLIM_app.c  .generated_files/62a1d698b5fb69c995bbdcbc6f163a6351c33f02.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/mcc_generated_files/BSLIM_app.c  -o ${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/mcc_generated_files/BSLIM_app.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o: pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/c7f7e704b41fb3b8bc5eba8d2f86d361b7abee4a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pic24fj256ga702/updatePulse.o: pic24fj256ga702/updatePulse.c  .generated_files/db00c72175a955b7f97671656fee4874a90de295.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/updatePulse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pic24fj256ga702/updatePulse.c  -o ${OBJECTDIR}/pic24fj256ga702/updatePulse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pic24fj256ga702/updatePulse.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/quadEnc.o: quadEnc.c  .generated_files/cf583e621608dd9414d3a03512974d0e6c713c2d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.o.d 
	@${RM} ${OBJECTDIR}/quadEnc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  quadEnc.c  -o ${OBJECTDIR}/quadEnc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/quadEnc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/analogInput.o: analogInput.c  .generated_files/1d86978506ff6661e2abbdc8302dffaef5a9e41e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.o.d 
	@${RM} ${OBJECTDIR}/analogInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  analogInput.c  -o ${OBJECTDIR}/analogInput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/analogInput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseOutput.o: pulseOutput.c  .generated_files/62028fc9668f99bd72934bd8f07eb83168c4a7c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseOutput.o.d 
	@${RM} ${OBJECTDIR}/pulseOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseOutput.c  -o ${OBJECTDIR}/pulseOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pulseTimer.o: pulseTimer.c  .generated_files/42d9ef7a44a3e002560149edb8e7db00527e98d7.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.o.d 
	@${RM} ${OBJECTDIR}/pulseTimer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pulseTimer.c  -o ${OBJECTDIR}/pulseTimer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pulseTimer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/debounce.o: debounce.c  .generated_files/5a21314dbb4a21502f148fcd4b0a982be594b762.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.o.d 
	@${RM} ${OBJECTDIR}/debounce.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  debounce.c  -o ${OBJECTDIR}/debounce.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/debounce.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protectedOutput.o: protectedOutput.c  .generated_files/346883719e469f8d771b505bb66f040667d4a0e7.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protectedOutput.o.d 
	@${RM} ${OBJECTDIR}/protectedOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protectedOutput.c  -o ${OBJECTDIR}/protectedOutput.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protectedOutput.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/watchdog.o: watchdog.c  .generated_files/c1e62bf278dc7e1e7b7c7500bceec7cd49c336ef.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.o.d 
	@${RM} ${OBJECTDIR}/watchdog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  watchdog.c  -o ${OBJECTDIR}/watchdog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/watchdog.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/bfe392e15e20e11bb71057cbe5d77e973b006fe.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol.o: protocol.c  .generated_files/fb8ab0a7c369b8354333681299fa16cfd6f7df.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.o.d 
	@${RM} ${OBJECTDIR}/protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol.c  -o ${OBJECTDIR}/protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/asciiConversion.o: asciiConversion.c  .generated_files/408dae2d091d3e9b7b3473ab2469e230b6796bd.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asciiConversion.c  -o ${OBJECTDIR}/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/asciiConversion.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pinRegisters.o: pinRegisters.c  .generated_files/cdf09f75e314027bddd38e3d9887f5a63b16aa7a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinRegisters.o.d 
	@${RM} ${OBJECTDIR}/pinRegisters.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pinRegisters.c  -o ${OBJECTDIR}/pinRegisters.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pinRegisters.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/queue.o: queue.c  .generated_files/8c0efd35804f3a5d4e53dbd5c1936eed02683f0f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  queue.c  -o ${OBJECTDIR}/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -mlarge-code -O0 -I"pic24fj256ga702" -I"pic24fj256ga702/mcc_generated_files" -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic24fj256ga702/wombatasm.o: pic24fj256ga702/wombatasm.s  .generated_files/9d541a754a3587aea8e721c9ce77c85d95e67b01.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/pic24fj256ga702" 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/pic24fj256ga702/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/pic24fj256ga702/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../../SerialWombatCommon" -Wa,-MD,"${OBJECTDIR}/pic24fj256ga702/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_app.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../SerialWombatCommon" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-ivt,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
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
