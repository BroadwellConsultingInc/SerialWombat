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
SOURCEFILES_QUOTED_IF_SPACED=../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c main_boot.c protocol_boot.c ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s ../../SerialWombatCommon/asciiConversion.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/275911920/adc1.o ${OBJECTDIR}/_ext/275911920/clock.o ${OBJECTDIR}/_ext/275911920/crc.o ${OBJECTDIR}/_ext/275911920/cvr.o ${OBJECTDIR}/_ext/275911920/dma.o ${OBJECTDIR}/_ext/275911920/i2c1.o ${OBJECTDIR}/_ext/275911920/i2c2.o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o ${OBJECTDIR}/_ext/275911920/mcc.o ${OBJECTDIR}/_ext/275911920/pin_manager.o ${OBJECTDIR}/_ext/275911920/system.o ${OBJECTDIR}/_ext/275911920/tmr1.o ${OBJECTDIR}/_ext/275911920/tmr2.o ${OBJECTDIR}/_ext/275911920/tmr3.o ${OBJECTDIR}/_ext/275911920/traps.o ${OBJECTDIR}/_ext/275911920/uart1.o ${OBJECTDIR}/_ext/275911920/uart2.o ${OBJECTDIR}/main_boot.o ${OBJECTDIR}/protocol_boot.o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o ${OBJECTDIR}/_ext/1497480854/wombatasm.o ${OBJECTDIR}/_ext/998979777/asciiConversion.o ${OBJECTDIR}/_ext/1542527744/flash.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/275911920/adc1.o.d ${OBJECTDIR}/_ext/275911920/clock.o.d ${OBJECTDIR}/_ext/275911920/crc.o.d ${OBJECTDIR}/_ext/275911920/cvr.o.d ${OBJECTDIR}/_ext/275911920/dma.o.d ${OBJECTDIR}/_ext/275911920/i2c1.o.d ${OBJECTDIR}/_ext/275911920/i2c2.o.d ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d ${OBJECTDIR}/_ext/275911920/mcc.o.d ${OBJECTDIR}/_ext/275911920/pin_manager.o.d ${OBJECTDIR}/_ext/275911920/system.o.d ${OBJECTDIR}/_ext/275911920/tmr1.o.d ${OBJECTDIR}/_ext/275911920/tmr2.o.d ${OBJECTDIR}/_ext/275911920/tmr3.o.d ${OBJECTDIR}/_ext/275911920/traps.o.d ${OBJECTDIR}/_ext/275911920/uart1.o.d ${OBJECTDIR}/_ext/275911920/uart2.o.d ${OBJECTDIR}/main_boot.o.d ${OBJECTDIR}/protocol_boot.o.d ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d ${OBJECTDIR}/_ext/1542527744/flash.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/275911920/adc1.o ${OBJECTDIR}/_ext/275911920/clock.o ${OBJECTDIR}/_ext/275911920/crc.o ${OBJECTDIR}/_ext/275911920/cvr.o ${OBJECTDIR}/_ext/275911920/dma.o ${OBJECTDIR}/_ext/275911920/i2c1.o ${OBJECTDIR}/_ext/275911920/i2c2.o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o ${OBJECTDIR}/_ext/275911920/mcc.o ${OBJECTDIR}/_ext/275911920/pin_manager.o ${OBJECTDIR}/_ext/275911920/system.o ${OBJECTDIR}/_ext/275911920/tmr1.o ${OBJECTDIR}/_ext/275911920/tmr2.o ${OBJECTDIR}/_ext/275911920/tmr3.o ${OBJECTDIR}/_ext/275911920/traps.o ${OBJECTDIR}/_ext/275911920/uart1.o ${OBJECTDIR}/_ext/275911920/uart2.o ${OBJECTDIR}/main_boot.o ${OBJECTDIR}/protocol_boot.o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o ${OBJECTDIR}/_ext/1497480854/wombatasm.o ${OBJECTDIR}/_ext/998979777/asciiConversion.o ${OBJECTDIR}/_ext/1542527744/flash.o

# Source Files
SOURCEFILES=../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c main_boot.c protocol_boot.c ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s ../../SerialWombatCommon/asciiConversion.c ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s



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
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/91f47bfdcebaa06c3f8b1683a79b7b16f9af47be.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/5eb9173881a3747b5c5c5864aadb8b5bd6264ab0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/b3d3bd6d1871b9fec9c4e9a8ac7cd51af7fb850.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/25fe5207cd735ddc1dfbf99b9151913204e2afc5.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/442b2ebae3bbde361b86206356932b7a227d96b4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/338964b610955cb11cf6ee9d8fcc7db9685f302b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/f552038cabb9fb780e329cf1e2897d4e32506533.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/1d5b9c8be378c0ef9d9978a24b7cc95d9aaef39.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/970ec0516af65e0deace053c40a2a7b9f2c5fde8.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/80c0b471cfe0b78cd3a24320bf325c05bb68f107.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/86021a629bced4e81e054ddb4b4681d24693e3ac.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/7dec823881a612d5c35075feff9ab540f61a0197.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/8a1c636eeb9c9af7f7a065d7c7db7c7a767acdf0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/fa199b6396f161be388441d5ccaa1c885fd8f5bb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/c64eadab33d513b1c0c1f2e87adf2e5be6cd069e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/f88b844769c900e66f34199bf5eb52d1a6f10dfc.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/6e25ad431c2f10e01aecb06eaf1d1f6540323d5a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/fac5e7703713e234d452bfa75f3d2736e2593be0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/697fc952b52a6e120bf39327f6491cfbe3268c37.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/eefb4dfdf7db708e55eca75facd13ecbde1967da.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/5256be9930bfcda838a8ebefed845062f02cc7ab.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/bf6b7d59cce65237975fb276ea37090a4300e912.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/d318546cb8e9f4b40a4c47e25e3732e1328dee7a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/456a79bee58dde7421d060b2e51dd68b4015128d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/23f5fe7d5b2610ea2ea57c78c39b186e6a479b0c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/a60453b107a1abf5925bcdaf03d69c9f5d77c806.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/aa7509ff58ebaae09d208f10b5c533edbb6db5d5.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/dd8f999741aa37813c95a92bc656ccba4a09a0c6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/1215108a52d95e91533be5faac91e79f886053f4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/4539bf3ba810510768456dc98ee68546000b64f4.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/c5b178c56657197e568aa61aa3ac3eaca4401c88.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/a8426639969fa446f218714d1c67cbb0fd821733.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/1b948d8bb522f9130a8d5bf545f3e8cb5cc99888.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/9cae888baccdca82ad1370b975539d7f6da7bde3.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/ac366dce483b21297b1ab5055e822095801cf39c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/5bd3e9198b5476e27b913221dc152784a15a6bd0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/f1e2d475f863f177bd91fe8ecbe49f836557b0d0.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/bb18dcf9651ea4aa94577fcce68d169c65d94fa2.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/599e3e2ea8c1a996fcc882e533811deaae478048.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/b765e3457f11c4f6a04b13fc53a6e215346e26b9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/9c91de2b6665b10e6526aa35f237a0963adf478a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/fe6abc77f3b0f4a3d0f74c089db54331441fdd62.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/1385c31b1d8bb3161837a5aef1ad2f240d7cdb86.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/7db7f9f03ff6a0295ef2ce9a77610a62336e1888.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/22aff80358fcbdb7ec450446f9246b40de40b741.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/3d897a0c2d1672f047d7004bdfd88d688ed9067e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
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
