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
ifeq "$(wildcard nbproject/Makefile-local-UART15214.mk)" "nbproject/Makefile-local-UART15214.mk"
include nbproject/Makefile-local-UART15214.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=UART15214
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/adc.c mcc_generated_files/eusart1.c mcc_generated_files/fvr.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr0.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c servo.c pwm.c debounce.c quadEnc.c watchdog.c analogInput.c pulseTimer.c main.c protocol.c LoadCompleteMarker.s device_config_copied_from_bootloader_project.c pinDigitalHwSpecific.c processPins.c ../../SerialWombatCommon/asciiConversion.c ../../SerialWombatCommon/pinRegisters.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/adc.p1 ${OBJECTDIR}/mcc_generated_files/eusart1.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/servo.p1 ${OBJECTDIR}/pwm.p1 ${OBJECTDIR}/debounce.p1 ${OBJECTDIR}/quadEnc.p1 ${OBJECTDIR}/watchdog.p1 ${OBJECTDIR}/analogInput.p1 ${OBJECTDIR}/pulseTimer.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/protocol.p1 ${OBJECTDIR}/LoadCompleteMarker.o ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 ${OBJECTDIR}/pinDigitalHwSpecific.p1 ${OBJECTDIR}/processPins.p1 ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 ${OBJECTDIR}/_ext/998979777/pinRegisters.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/adc.p1.d ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d ${OBJECTDIR}/servo.p1.d ${OBJECTDIR}/pwm.p1.d ${OBJECTDIR}/debounce.p1.d ${OBJECTDIR}/quadEnc.p1.d ${OBJECTDIR}/watchdog.p1.d ${OBJECTDIR}/analogInput.p1.d ${OBJECTDIR}/pulseTimer.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/protocol.p1.d ${OBJECTDIR}/LoadCompleteMarker.o.d ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d ${OBJECTDIR}/pinDigitalHwSpecific.p1.d ${OBJECTDIR}/processPins.p1.d ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/adc.p1 ${OBJECTDIR}/mcc_generated_files/eusart1.p1 ${OBJECTDIR}/mcc_generated_files/fvr.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/servo.p1 ${OBJECTDIR}/pwm.p1 ${OBJECTDIR}/debounce.p1 ${OBJECTDIR}/quadEnc.p1 ${OBJECTDIR}/watchdog.p1 ${OBJECTDIR}/analogInput.p1 ${OBJECTDIR}/pulseTimer.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/protocol.p1 ${OBJECTDIR}/LoadCompleteMarker.o ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 ${OBJECTDIR}/pinDigitalHwSpecific.p1 ${OBJECTDIR}/processPins.p1 ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 ${OBJECTDIR}/_ext/998979777/pinRegisters.p1

# Source Files
SOURCEFILES=mcc_generated_files/adc.c mcc_generated_files/eusart1.c mcc_generated_files/fvr.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr0.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c servo.c pwm.c debounce.c quadEnc.c watchdog.c analogInput.c pulseTimer.c main.c protocol.c LoadCompleteMarker.s device_config_copied_from_bootloader_project.c pinDigitalHwSpecific.c processPins.c ../../SerialWombatCommon/asciiConversion.c ../../SerialWombatCommon/pinRegisters.c



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
	${MAKE}  -f nbproject/Makefile-UART15214.mk dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F15214
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/adc.p1: mcc_generated_files/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adc.p1 mcc_generated_files/adc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adc.d ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart1.p1: mcc_generated_files/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart1.p1 mcc_generated_files/eusart1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart1.d ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/servo.p1: servo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.p1.d 
	@${RM} ${OBJECTDIR}/servo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/servo.p1 servo.c 
	@-${MV} ${OBJECTDIR}/servo.d ${OBJECTDIR}/servo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/servo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pwm.p1: pwm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.p1.d 
	@${RM} ${OBJECTDIR}/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pwm.p1 pwm.c 
	@-${MV} ${OBJECTDIR}/pwm.d ${OBJECTDIR}/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/debounce.p1: debounce.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.p1.d 
	@${RM} ${OBJECTDIR}/debounce.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/debounce.p1 debounce.c 
	@-${MV} ${OBJECTDIR}/debounce.d ${OBJECTDIR}/debounce.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/debounce.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/quadEnc.p1: quadEnc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.p1.d 
	@${RM} ${OBJECTDIR}/quadEnc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/quadEnc.p1 quadEnc.c 
	@-${MV} ${OBJECTDIR}/quadEnc.d ${OBJECTDIR}/quadEnc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/quadEnc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/watchdog.p1: watchdog.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.p1.d 
	@${RM} ${OBJECTDIR}/watchdog.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/watchdog.p1 watchdog.c 
	@-${MV} ${OBJECTDIR}/watchdog.d ${OBJECTDIR}/watchdog.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/watchdog.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/analogInput.p1: analogInput.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.p1.d 
	@${RM} ${OBJECTDIR}/analogInput.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/analogInput.p1 analogInput.c 
	@-${MV} ${OBJECTDIR}/analogInput.d ${OBJECTDIR}/analogInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/analogInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pulseTimer.p1: pulseTimer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.p1.d 
	@${RM} ${OBJECTDIR}/pulseTimer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pulseTimer.p1 pulseTimer.c 
	@-${MV} ${OBJECTDIR}/pulseTimer.d ${OBJECTDIR}/pulseTimer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pulseTimer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/protocol.p1: protocol.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.p1.d 
	@${RM} ${OBJECTDIR}/protocol.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/protocol.p1 protocol.c 
	@-${MV} ${OBJECTDIR}/protocol.d ${OBJECTDIR}/protocol.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/protocol.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/device_config_copied_from_bootloader_project.p1: device_config_copied_from_bootloader_project.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d 
	@${RM} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 device_config_copied_from_bootloader_project.c 
	@-${MV} ${OBJECTDIR}/device_config_copied_from_bootloader_project.d ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pinDigitalHwSpecific.p1: pinDigitalHwSpecific.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinDigitalHwSpecific.p1.d 
	@${RM} ${OBJECTDIR}/pinDigitalHwSpecific.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pinDigitalHwSpecific.p1 pinDigitalHwSpecific.c 
	@-${MV} ${OBJECTDIR}/pinDigitalHwSpecific.d ${OBJECTDIR}/pinDigitalHwSpecific.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pinDigitalHwSpecific.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/processPins.p1: processPins.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/processPins.p1.d 
	@${RM} ${OBJECTDIR}/processPins.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/processPins.p1 processPins.c 
	@-${MV} ${OBJECTDIR}/processPins.d ${OBJECTDIR}/processPins.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/processPins.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/998979777/asciiConversion.p1: ../../SerialWombatCommon/asciiConversion.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 ../../SerialWombatCommon/asciiConversion.c 
	@-${MV} ${OBJECTDIR}/_ext/998979777/asciiConversion.d ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/998979777/pinRegisters.p1: ../../SerialWombatCommon/pinRegisters.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/998979777/pinRegisters.p1 ../../SerialWombatCommon/pinRegisters.c 
	@-${MV} ${OBJECTDIR}/_ext/998979777/pinRegisters.d ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/mcc_generated_files/adc.p1: mcc_generated_files/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adc.p1 mcc_generated_files/adc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adc.d ${OBJECTDIR}/mcc_generated_files/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/eusart1.p1: mcc_generated_files/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart1.p1 mcc_generated_files/eusart1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart1.d ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/fvr.p1: mcc_generated_files/fvr.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/fvr.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/fvr.p1 mcc_generated_files/fvr.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/fvr.d ${OBJECTDIR}/mcc_generated_files/fvr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/fvr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/servo.p1: servo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/servo.p1.d 
	@${RM} ${OBJECTDIR}/servo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/servo.p1 servo.c 
	@-${MV} ${OBJECTDIR}/servo.d ${OBJECTDIR}/servo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/servo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pwm.p1: pwm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.p1.d 
	@${RM} ${OBJECTDIR}/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pwm.p1 pwm.c 
	@-${MV} ${OBJECTDIR}/pwm.d ${OBJECTDIR}/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/debounce.p1: debounce.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debounce.p1.d 
	@${RM} ${OBJECTDIR}/debounce.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/debounce.p1 debounce.c 
	@-${MV} ${OBJECTDIR}/debounce.d ${OBJECTDIR}/debounce.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/debounce.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/quadEnc.p1: quadEnc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/quadEnc.p1.d 
	@${RM} ${OBJECTDIR}/quadEnc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/quadEnc.p1 quadEnc.c 
	@-${MV} ${OBJECTDIR}/quadEnc.d ${OBJECTDIR}/quadEnc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/quadEnc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/watchdog.p1: watchdog.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/watchdog.p1.d 
	@${RM} ${OBJECTDIR}/watchdog.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/watchdog.p1 watchdog.c 
	@-${MV} ${OBJECTDIR}/watchdog.d ${OBJECTDIR}/watchdog.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/watchdog.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/analogInput.p1: analogInput.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analogInput.p1.d 
	@${RM} ${OBJECTDIR}/analogInput.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/analogInput.p1 analogInput.c 
	@-${MV} ${OBJECTDIR}/analogInput.d ${OBJECTDIR}/analogInput.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/analogInput.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pulseTimer.p1: pulseTimer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pulseTimer.p1.d 
	@${RM} ${OBJECTDIR}/pulseTimer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pulseTimer.p1 pulseTimer.c 
	@-${MV} ${OBJECTDIR}/pulseTimer.d ${OBJECTDIR}/pulseTimer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pulseTimer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/protocol.p1: protocol.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/protocol.p1.d 
	@${RM} ${OBJECTDIR}/protocol.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/protocol.p1 protocol.c 
	@-${MV} ${OBJECTDIR}/protocol.d ${OBJECTDIR}/protocol.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/protocol.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/device_config_copied_from_bootloader_project.p1: device_config_copied_from_bootloader_project.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d 
	@${RM} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1 device_config_copied_from_bootloader_project.c 
	@-${MV} ${OBJECTDIR}/device_config_copied_from_bootloader_project.d ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/device_config_copied_from_bootloader_project.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pinDigitalHwSpecific.p1: pinDigitalHwSpecific.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pinDigitalHwSpecific.p1.d 
	@${RM} ${OBJECTDIR}/pinDigitalHwSpecific.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pinDigitalHwSpecific.p1 pinDigitalHwSpecific.c 
	@-${MV} ${OBJECTDIR}/pinDigitalHwSpecific.d ${OBJECTDIR}/pinDigitalHwSpecific.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pinDigitalHwSpecific.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/processPins.p1: processPins.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/processPins.p1.d 
	@${RM} ${OBJECTDIR}/processPins.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/processPins.p1 processPins.c 
	@-${MV} ${OBJECTDIR}/processPins.d ${OBJECTDIR}/processPins.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/processPins.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/998979777/asciiConversion.p1: ../../SerialWombatCommon/asciiConversion.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/998979777/asciiConversion.p1 ../../SerialWombatCommon/asciiConversion.c 
	@-${MV} ${OBJECTDIR}/_ext/998979777/asciiConversion.d ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/998979777/asciiConversion.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/998979777/pinRegisters.p1: ../../SerialWombatCommon/pinRegisters.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/998979777" 
	@${RM} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d 
	@${RM} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/998979777/pinRegisters.p1 ../../SerialWombatCommon/pinRegisters.c 
	@-${MV} ${OBJECTDIR}/_ext/998979777/pinRegisters.d ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/998979777/pinRegisters.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/LoadCompleteMarker.o: LoadCompleteMarker.s  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LoadCompleteMarker.o.d 
	@${RM} ${OBJECTDIR}/LoadCompleteMarker.o 
	${MP_CC} -c $(MP_EXTRA_AS_PRE) -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto   -o ${OBJECTDIR}/LoadCompleteMarker.o  LoadCompleteMarker.s 
	@-${MV} ${OBJECTDIR}/LoadCompleteMarker.d ${OBJECTDIR}/LoadCompleteMarker.o.d 
	@${FIXDEPS} ${OBJECTDIR}/LoadCompleteMarker.o.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/LoadCompleteMarker.o: LoadCompleteMarker.s  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LoadCompleteMarker.o.d 
	@${RM} ${OBJECTDIR}/LoadCompleteMarker.o 
	${MP_CC} -c $(MP_EXTRA_AS_PRE) -mcpu=$(MP_PROCESSOR_OPTION)   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -DXPRJ_UART15214=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto   -o ${OBJECTDIR}/LoadCompleteMarker.o  LoadCompleteMarker.s 
	@-${MV} ${OBJECTDIR}/LoadCompleteMarker.d ${OBJECTDIR}/LoadCompleteMarker.o.d 
	@${FIXDEPS} ${OBJECTDIR}/LoadCompleteMarker.o.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_UART15214=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../../PIC16F15214Bootloader/BootloaderPIC16F15214/BootloaderPIC16F15214.X/dist/default/production/BootloaderPIC16F15214.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.map  -DXPRJ_UART15214=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -mrom=-FFF-FFF -Os -fasmfile -maddrqual=require -DUARTWOMBAT -xassembler-with-cpp -I"." -I"../../SerialWombatCommon" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x140  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v5.45/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v5.45/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/Wombat16F15214.X.${IMAGE_TYPE}.hex ../../../../PIC16F15214Bootloader/BootloaderPIC16F15214/BootloaderPIC16F15214.X/dist/default/production/BootloaderPIC16F15214.X.production.hex -odist/${CND_CONF}/production/Wombat16F15214.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd ../../../../PIC16F15214Bootloader/BootloaderPIC16F15214/BootloaderPIC16F15214.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd ../../../../PIC16F15214Bootloader/BootloaderPIC16F15214/BootloaderPIC16F15214.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd ../../../../PIC16F15214Bootloader/BootloaderPIC16F15214/BootloaderPIC16F15214.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/UART15214
	${RM} -r dist/UART15214

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
