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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s main_boot.c protocol_boot.c ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s ../../SerialWombatCommon/asciiConversion.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/275911920/adc1.o ${OBJECTDIR}/_ext/275911920/clock.o ${OBJECTDIR}/_ext/275911920/crc.o ${OBJECTDIR}/_ext/275911920/cvr.o ${OBJECTDIR}/_ext/275911920/dma.o ${OBJECTDIR}/_ext/275911920/i2c1.o ${OBJECTDIR}/_ext/275911920/i2c2.o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o ${OBJECTDIR}/_ext/275911920/mcc.o ${OBJECTDIR}/_ext/275911920/pin_manager.o ${OBJECTDIR}/_ext/275911920/system.o ${OBJECTDIR}/_ext/275911920/tmr1.o ${OBJECTDIR}/_ext/275911920/tmr2.o ${OBJECTDIR}/_ext/275911920/tmr3.o ${OBJECTDIR}/_ext/275911920/traps.o ${OBJECTDIR}/_ext/275911920/uart1.o ${OBJECTDIR}/_ext/275911920/uart2.o ${OBJECTDIR}/_ext/1542527744/flash.o ${OBJECTDIR}/main_boot.o ${OBJECTDIR}/protocol_boot.o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o ${OBJECTDIR}/_ext/1497480854/wombatasm.o ${OBJECTDIR}/_ext/998979777/asciiConversion.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/275911920/adc1.o.d ${OBJECTDIR}/_ext/275911920/clock.o.d ${OBJECTDIR}/_ext/275911920/crc.o.d ${OBJECTDIR}/_ext/275911920/cvr.o.d ${OBJECTDIR}/_ext/275911920/dma.o.d ${OBJECTDIR}/_ext/275911920/i2c1.o.d ${OBJECTDIR}/_ext/275911920/i2c2.o.d ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d ${OBJECTDIR}/_ext/275911920/mcc.o.d ${OBJECTDIR}/_ext/275911920/pin_manager.o.d ${OBJECTDIR}/_ext/275911920/system.o.d ${OBJECTDIR}/_ext/275911920/tmr1.o.d ${OBJECTDIR}/_ext/275911920/tmr2.o.d ${OBJECTDIR}/_ext/275911920/tmr3.o.d ${OBJECTDIR}/_ext/275911920/traps.o.d ${OBJECTDIR}/_ext/275911920/uart1.o.d ${OBJECTDIR}/_ext/275911920/uart2.o.d ${OBJECTDIR}/_ext/1542527744/flash.o.d ${OBJECTDIR}/main_boot.o.d ${OBJECTDIR}/protocol_boot.o.d ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/275911920/adc1.o ${OBJECTDIR}/_ext/275911920/clock.o ${OBJECTDIR}/_ext/275911920/crc.o ${OBJECTDIR}/_ext/275911920/cvr.o ${OBJECTDIR}/_ext/275911920/dma.o ${OBJECTDIR}/_ext/275911920/i2c1.o ${OBJECTDIR}/_ext/275911920/i2c2.o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o ${OBJECTDIR}/_ext/275911920/mcc.o ${OBJECTDIR}/_ext/275911920/pin_manager.o ${OBJECTDIR}/_ext/275911920/system.o ${OBJECTDIR}/_ext/275911920/tmr1.o ${OBJECTDIR}/_ext/275911920/tmr2.o ${OBJECTDIR}/_ext/275911920/tmr3.o ${OBJECTDIR}/_ext/275911920/traps.o ${OBJECTDIR}/_ext/275911920/uart1.o ${OBJECTDIR}/_ext/275911920/uart2.o ${OBJECTDIR}/_ext/1542527744/flash.o ${OBJECTDIR}/main_boot.o ${OBJECTDIR}/protocol_boot.o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o ${OBJECTDIR}/_ext/1497480854/wombatasm.o ${OBJECTDIR}/_ext/998979777/asciiConversion.o

# Source Files
SOURCEFILES=../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s main_boot.c protocol_boot.c ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s ../../SerialWombatCommon/asciiConversion.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA702
MP_LINKER_FILE_OPTION=,--script="p24FJ256GA702_boot.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/7f94753343703c844df3bcbd4c624c25bdb45c79.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/6558e8c9e9281b3a458c6b278c372991543cce0a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/e69bd13b3e92404f44fcba50ff14057e9e64c8fd.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/7ea669cde1a1ca7e22e6c08e2ccf8447286e7c0f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/818445a69877441df40f95388c6e8b154bc3512f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/388631f01513343621f16d8b482db670ac5170e5.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/806aedad66ac6d7cf70cb3129edfc335848234ba.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/3bfcf67ec8be918f5de5b440e31251926626ed37.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/c2fe233bb8ffec8c5959b66e9caf84fc9d76e4f9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/c6ef2fbbc03ee68296fa2e7146a174a74fa272ae.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/573a49c593cf63988f15564c02ae83dbee97aa2f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/97fb43d5720e4ad771f3452cfff0853a510281d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/8f4a6159fcf7dfb5d22ba6b64adfb7f8b2256db2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/e4a6c4ce70c3f7c68afbe91960eabf12fe0ac7c2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/7a17008e4bbaab4e02891356796ea5ef1bb4e78c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/ac8f1a30cd2ec1bee1a9b19c94fc44da92e3734e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/e3ce5b0197c1f83240d52a2b7856344a465d48c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/51b1c5d71710087630ab1c43b587e5c561583be9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/578ed9a85e595dbda2472112f58687455714e5a8.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/1704cb96337594918872d9ddafc92e280118f66c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/57f2ab22cf266b4b86e956b19c8cc4fff157453d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/1250ded7f0da1d6a43b4682306456779e432ce72.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/2faff685df6747d6931ad9ee92babd02ca6da71c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/26e42b541eeee713db37da7b8b7e0865067c55f5.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/48ca47aa56a43ccf4795f86f36d0e63c43ae3186.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/ae47e80b5bb0046d0c6c74cc52c801c301c90822.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/86ce6d9905a0d9b5e160c0f078bf28e7cedd883b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/7d6cb42a627552e211ebcd2f8e5df23e17e99fa2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/4aa804bdcad81fbfb4069449073e9ca751954c1a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/661111219ee13c2bd955fbba74b2b69710e8b11a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/c3a73ca2efecbda9b8de110c328eeae9ca63598.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/341d936318037f09c77eabaaaa5e5dca3e56ff31.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/b897fa024be4a4a6accd164f9f5ba2067454ffa2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/69f588002853857fdd477923fe439001e72809cc.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/19f0cb9a592407544a9155b914900a165eb1993f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/85bee6c2edfd1c0b7b442c57c13b3fae4d3381d4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/1a288765a3777e1b2777c233647ff3e815e7b43b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/8aac0f38dbeba87eab71ef2b74eaa115aae07a4d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/84770935a707e507efdbf9164ffee0d6b645a0fa.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/22fc5852324535d1ed8a891d87834a42bcba81df.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/c18d0fdeaa807480b9a8b2b22687c9e9e506c695.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/7694f79095b9e1e63933ab8d53623d2b9e2ecd3a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/7db7f9f03ff6a0295ef2ce9a77610a62336e1888.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/1385c31b1d8bb3161837a5aef1ad2f240d7cdb86.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/3d897a0c2d1672f047d7004bdfd88d688ed9067e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/22aff80358fcbdb7ec450446f9246b40de40b741.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ256GA702_boot.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_boot.gld ../SerialWombat18A_18B.X/dist/default/production/SerialWombat18A_18B.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v5.45/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v5.45/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" -break=55E00  dist/${CND_CONF}/${IMAGE_TYPE}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.hex ../SerialWombat18A_18B.X/dist/default/production/SerialWombat18A_18B.X.production.hex -odist/${CND_CONF}/production/SerialWombat18A_18B_Bootloader.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd ../SerialWombat18A_18B.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd ../SerialWombat18A_18B.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd ../SerialWombat18A_18B.X && rm -rf "build/default" "dist/default"

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
