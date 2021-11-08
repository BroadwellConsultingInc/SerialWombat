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
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/5d13b2f6316787563902b20380778ec8bd8e2fa9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/63b295ed23330bb331994a62e0bf5e3fccd5d1cf.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/ea835c7b85c50fd01649fd5103d4bcf2e989c97.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/e79a5f393cfd257b4f16566b31a0100a4d1827.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/ab2e29915efaf777fb8f541d4fafa4924d232e91.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/981e663ea4976bb7e420095a353e97cc23455460.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/1250c030ed1e1648026af8aa90436caa4d21bb9f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/7e1df3bde460c66aae8ccc40ad99fbcbe30a70f6.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/e6e02d080dade0f74488977b90040922d68b9cbb.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/ce6065cb077736afe22e342685dbf4b706586464.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/e920c64bc3fcf243c4e6f18e04747ae89294e277.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/b5923b00ca1d24b83454ab2508fe46a1bfdda741.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/87aec6beb40a2088f92a60fda9f1cf843ea87a3b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/f3334da57db341b708a0e484080e3e644f1703e9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/bd5234c59ae8aae568949ae96ddef119e29b7e4e.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/295ff9af339a727eb4431a61b4c7119944bf0d3a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/7d98b39560eeb3f73e5f446c0d8fd27b79b8182c.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/7f62d706988be4e3cd1087273d14dceb67f8d01a.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/ad623555ce29218b29ebbda377e6b965b509de6d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/6109340bae04815eaba129f3cba807d2f985728b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/718223c453224074555adb39890ca137be2d621b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/275911920/adc1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  .generated_files/1eb36b37501ea86953ecbb2a1546c4b9cb1e28bf.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/adc1.c  -o ${OBJECTDIR}/_ext/275911920/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/adc1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/clock.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  .generated_files/7e3d2e1a36e9f532861d8caec5656d8312dbd146.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/275911920/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/clock.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/crc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  .generated_files/877fbac874305f9b47a15c8417bbf22d4e4f333f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/crc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/crc.c  -o ${OBJECTDIR}/_ext/275911920/crc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/crc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/cvr.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  .generated_files/e004a19204708c6a48bf064fe051c57c6797d116.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/cvr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/cvr.c  -o ${OBJECTDIR}/_ext/275911920/cvr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/cvr.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/dma.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  .generated_files/5d969bf31891766610391575ee9ca18287d61a5b.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/dma.c  -o ${OBJECTDIR}/_ext/275911920/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/dma.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  .generated_files/da21d09ee8908471ea6f1e94a75627148c9e333.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c1.c  -o ${OBJECTDIR}/_ext/275911920/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/i2c2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  .generated_files/7a6e7b9f07902ef71220e2ad1df165cdaa0a3113.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/i2c2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/i2c2.c  -o ${OBJECTDIR}/_ext/275911920/i2c2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/i2c2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/interrupt_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  .generated_files/ebce846695b26dd5f9c2edf4171b27a35e7299e9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/275911920/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/interrupt_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/mcc.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  .generated_files/962dec6a4ebb7749163b251acc2a528ceac1edef.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/275911920/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/mcc.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/pin_manager.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  .generated_files/494f080b5464ff688ff96ee47abb6e1150203f90.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/275911920/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/pin_manager.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/system.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  .generated_files/c4b9374347248cf3961e095ce94c85487fa05e76.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/275911920/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/system.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  .generated_files/109304babed6bbdaad70016c9e609f21054d9379.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr1.c  -o ${OBJECTDIR}/_ext/275911920/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  .generated_files/7388214f3b5e7d2888f0e86d094b657d3910133f.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr2.c  -o ${OBJECTDIR}/_ext/275911920/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/tmr3.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  .generated_files/3e09a9fd1460557cb8b6957851a254d58ce11537.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/tmr3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/tmr3.c  -o ${OBJECTDIR}/_ext/275911920/tmr3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/tmr3.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/traps.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  .generated_files/10320f150b455fd836b1c7d28d734f0309a3e067.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/275911920/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/traps.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart1.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  .generated_files/3bbf7aa41b69d21acf3e21ea3886b4ff9adbc813.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart1.c  -o ${OBJECTDIR}/_ext/275911920/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart1.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/275911920/uart2.o: ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  .generated_files/45b59b740f4b3b526b3a570155df5a73f4e3840d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/275911920" 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/275911920/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files/uart2.c  -o ${OBJECTDIR}/_ext/275911920/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/275911920/uart2.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main_boot.o: main_boot.c  .generated_files/98ce326f8c2a17349154f17d23e5741d0e1e48e9.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_boot.o.d 
	@${RM} ${OBJECTDIR}/main_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_boot.c  -o ${OBJECTDIR}/main_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/protocol_boot.o: protocol_boot.c  .generated_files/33bbe530991af5dacbce75c684f3ada1a797191d.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol_boot.o.d 
	@${RM} ${OBJECTDIR}/protocol_boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  protocol_boot.c  -o ${OBJECTDIR}/protocol_boot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/protocol_boot.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o: ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  .generated_files/7c1c5a7324a7face4941a807ae6d8e07f1a728ce.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1497480854" 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d 
	@${RM} ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SerialWombat18A_18B.X/pic24fj256ga702/pinDigitalHwSpecific.c  -o ${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1497480854/pinDigitalHwSpecific.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/998979777/asciiConversion.o: ../../SerialWombatCommon/asciiConversion.c  .generated_files/c1afba7b2132a0cc731e23337c9561cde85fa8f1.flag .generated_files/8ab545786e3347d84c0f15a0012cf6e8148ea312.flag
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../SerialWombatCommon/asciiConversion.c  -o ${OBJECTDIR}/_ext/998979777/asciiConversion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/998979777/asciiConversion.o.d"      -mno-eds-warn  -omf=elf -DBOOT -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../SerialWombat18A_18B.X/pic24fj256ga702/mcc_generated_files" -I"../../SerialWombatCommon" -I"../SerialWombat18A_18B.X/pic24fj256ga702" -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
