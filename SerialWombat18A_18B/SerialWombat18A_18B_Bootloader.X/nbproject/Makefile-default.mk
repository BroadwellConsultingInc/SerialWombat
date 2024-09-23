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
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GA702
MP_LINKER_FILE_OPTION=,--script="p24FJ256GA702_boot.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/75248cefe88690ab74dfe58392cd9078cdf11d29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/bf72fa16f2bd3eb4609ce529bcf68f5a72a38c06 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/11cd8aea18f57bb6d7819076d13ea4e8e3cd968d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/f1456e16cf25456172c706694b25ab94824da43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/aeb31f6aeebe978609ba720b5f1a0596f3e1390e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/66da7e5ad709caa3858b55e63ae4c803182c9e60 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/c29bf5639778ff04431b5039b64cdf2b16c5ae44 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/f180a717da46878db95f5de922712aa7af4378b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/2d25eced5c889dfdcd80abf652d5a0bc5e2f028 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/4344f3720fba6e6a7555d0ebbe64f442713dfeef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/eaee959a11669466d1579997367f788a89e4f7b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/f4d9d5bca44fc220cde901854f07ce13430c990 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/b92dfce79311f5025bf15fcf2e5f71dc203ab120 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/c2a531f1fef5057580df48c833b459c022d035a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/4ac55e220c4789cd65ddc0f2fa0356455f69bf7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/672d9e49668a5f74a5a99438b54fe97767208cb4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/2ee35ce067f79908b09c2be16427e60fe31bff49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/flags/default/69e69e5b28c2066514235054228969a9314b602d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/flags/default/fc54ce4fe7ca47ea147a3fa184a9648cf2903b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/93e67dfd58de8695b016dce7ead16522f6c2448d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/flags/default/20ed8b6aaef124b60cb34af805970e5a9fbad1b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/flags/default/fc7f6b22c60854b3921f4626029edc6a28439f10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/flags/default/11ab730c40a294fa35ef2730a4ded5431a8f23e8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/flags/default/3c38b933e4ae200ef92c0aa0dd1c5eb056430ac8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/flags/default/abd81963883dc89033f03f5c9f6750edccf448a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/flags/default/54c1f96d1dfe759b1186ee6de08427056abc73f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/flags/default/337e2e8122f4740dc3af8fb3b1300c956f810cca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/flags/default/2b98f3ece51df06a34beff7127d13bb7104b06b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/c1505fbe2baafcc34a5f3edcd6eaaca320c2a76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/flags/default/4695e9c8b547606f1347936cd48ae857169d0767 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/flags/default/8a90af2fb692428bbeee121daeb658daa37a16cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/flags/default/6670f222598edbfc2871d5721deab07d533c8955 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/flags/default/d017ab1b1996067dfe530614ef5b1309996fc99c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/flags/default/3a962b1c9aa7273bd93c250005525ec644d2568c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/flags/default/9144ee6438295f512a636063e6d3151896bf6e80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/flags/default/6bdf18a377a8026c7b370e009960449bea55165b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/flags/default/bc39384a4893d8790b1be0da168fb09b02ee0e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/flags/default/59d1fe842e16707aebfb22366a7879b7f454759d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/flags/default/434f50c9d7a20ea91f887f5e33efdaff50ddaeaf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/flags/default/b17e4ea22a5c9073005166913aafb419428fb67c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/flags/default/a6a15f9f9df589a57f549c92167eb4ab1908318b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/flags/default/ee2817d60ba88ee94b324537013eca4aef533645 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O2 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/b91df5b5ee97c04405e9ae03c920a59b122eb681 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/flags/default/9b951d4d1a85bd5eb39191aefdaad2859b3f6471 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1542527744/flash.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  .generated_files/flags/default/e972506e94543bdf44fb6dd936b6b277f7811cbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1542527744" 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1542527744/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/memory/flash.s  -o ${OBJECTDIR}/_ext/1542527744/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1542527744/flash.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/wombatasm.o: ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  .generated_files/flags/default/6c2855fe0dacf3116adbb3c9ac3790e5cfa90d7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/wombatasm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/wombatasm.s  -o ${OBJECTDIR}/_ext/1497480854/wombatasm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wa,-MD,"${OBJECTDIR}/_ext/1497480854/wombatasm.o.d",--defsym=__MPLAB_BUILD=1,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p24FJ256GA702_boot.gld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p24FJ256GA702_boot.gld ../SerialWombat18A_18B.X/dist/default/production/SerialWombat18A_18B.X.production.hex
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" -break=55E00  ${DISTDIR}/SerialWombat18A_18B_Bootloader.X.${IMAGE_TYPE}.hex ../SerialWombat18A_18B.X/dist/default/production/SerialWombat18A_18B.X.production.hex -odist/${CND_CONF}/production/SerialWombat18A_18B_Bootloader.X.production.unified.hex

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
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
