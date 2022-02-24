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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=scpi/utils.c scpi/units.c scpi/parser.c scpi/minimal.c scpi/lexer.c scpi/ieee488.c scpi/fifo.c scpi/error.c scpi/expression.c func.c hw.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/scpi/utils.o ${OBJECTDIR}/scpi/units.o ${OBJECTDIR}/scpi/parser.o ${OBJECTDIR}/scpi/minimal.o ${OBJECTDIR}/scpi/lexer.o ${OBJECTDIR}/scpi/ieee488.o ${OBJECTDIR}/scpi/fifo.o ${OBJECTDIR}/scpi/error.o ${OBJECTDIR}/scpi/expression.o ${OBJECTDIR}/func.o ${OBJECTDIR}/hw.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/scpi/utils.o.d ${OBJECTDIR}/scpi/units.o.d ${OBJECTDIR}/scpi/parser.o.d ${OBJECTDIR}/scpi/minimal.o.d ${OBJECTDIR}/scpi/lexer.o.d ${OBJECTDIR}/scpi/ieee488.o.d ${OBJECTDIR}/scpi/fifo.o.d ${OBJECTDIR}/scpi/error.o.d ${OBJECTDIR}/scpi/expression.o.d ${OBJECTDIR}/func.o.d ${OBJECTDIR}/hw.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/scpi/utils.o ${OBJECTDIR}/scpi/units.o ${OBJECTDIR}/scpi/parser.o ${OBJECTDIR}/scpi/minimal.o ${OBJECTDIR}/scpi/lexer.o ${OBJECTDIR}/scpi/ieee488.o ${OBJECTDIR}/scpi/fifo.o ${OBJECTDIR}/scpi/error.o ${OBJECTDIR}/scpi/expression.o ${OBJECTDIR}/func.o ${OBJECTDIR}/hw.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=scpi/utils.c scpi/units.c scpi/parser.c scpi/minimal.c scpi/lexer.c scpi/ieee488.c scpi/fifo.c scpi/error.c scpi/expression.c func.c hw.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ128GP306
MP_LINKER_FILE_OPTION=,--script=p24HJ128GP306.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/scpi/utils.o: scpi/utils.c  .generated_files/flags/default/6e54635a1f73d6031f3009a6d02f0fce77a58102 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/utils.o.d 
	@${RM} ${OBJECTDIR}/scpi/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/utils.c  -o ${OBJECTDIR}/scpi/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/units.o: scpi/units.c  .generated_files/flags/default/3a19900093423cb4a98ccb1a9549a170d35849eb .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/units.o.d 
	@${RM} ${OBJECTDIR}/scpi/units.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/units.c  -o ${OBJECTDIR}/scpi/units.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/units.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/parser.o: scpi/parser.c  .generated_files/flags/default/e5d5130a1b4fb2c33e2edd550a41ad26eab18cf8 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/parser.o.d 
	@${RM} ${OBJECTDIR}/scpi/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/parser.c  -o ${OBJECTDIR}/scpi/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/parser.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/minimal.o: scpi/minimal.c  .generated_files/flags/default/8fe14307d0fdc850d687c1188d70255533c3416 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/minimal.o.d 
	@${RM} ${OBJECTDIR}/scpi/minimal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/minimal.c  -o ${OBJECTDIR}/scpi/minimal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/minimal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/lexer.o: scpi/lexer.c  .generated_files/flags/default/7a49026e02c775bfbb30ae1a0902f277c9fc8c94 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/lexer.o.d 
	@${RM} ${OBJECTDIR}/scpi/lexer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/lexer.c  -o ${OBJECTDIR}/scpi/lexer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/lexer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/ieee488.o: scpi/ieee488.c  .generated_files/flags/default/a419823affa4ef1c69b1583b4cea2ccbbe1433cc .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/ieee488.o.d 
	@${RM} ${OBJECTDIR}/scpi/ieee488.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/ieee488.c  -o ${OBJECTDIR}/scpi/ieee488.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/ieee488.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/fifo.o: scpi/fifo.c  .generated_files/flags/default/c47598f33041337d93a785bf2965bd7eb9649e43 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/fifo.o.d 
	@${RM} ${OBJECTDIR}/scpi/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/fifo.c  -o ${OBJECTDIR}/scpi/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/fifo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/error.o: scpi/error.c  .generated_files/flags/default/7f7c492010910ec58a9149334653ed0cac9fcd75 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/error.o.d 
	@${RM} ${OBJECTDIR}/scpi/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/error.c  -o ${OBJECTDIR}/scpi/error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/error.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/expression.o: scpi/expression.c  .generated_files/flags/default/361b90e704bfdfc49a7bf7895b4bc26d18a6acc7 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/expression.o.d 
	@${RM} ${OBJECTDIR}/scpi/expression.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/expression.c  -o ${OBJECTDIR}/scpi/expression.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/expression.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/func.o: func.c  .generated_files/flags/default/c7e57e60b41c0efd6b1998d2ad6f5c6bb53dd5d3 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/func.o.d 
	@${RM} ${OBJECTDIR}/func.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  func.c  -o ${OBJECTDIR}/func.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/func.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hw.o: hw.c  .generated_files/flags/default/d671aa883e48ba31f44a03f5779f5b2b43988f5e .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hw.o.d 
	@${RM} ${OBJECTDIR}/hw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hw.c  -o ${OBJECTDIR}/hw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hw.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/f736ed428c0cff628068af15f0ad3ea8c12e9ef1 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/scpi/utils.o: scpi/utils.c  .generated_files/flags/default/69439a0c51c8ee22c53554162362770a1a726f43 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/utils.o.d 
	@${RM} ${OBJECTDIR}/scpi/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/utils.c  -o ${OBJECTDIR}/scpi/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/utils.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/units.o: scpi/units.c  .generated_files/flags/default/1baa1ff3b18d6be934673894f77aba09d83a6c3d .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/units.o.d 
	@${RM} ${OBJECTDIR}/scpi/units.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/units.c  -o ${OBJECTDIR}/scpi/units.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/units.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/parser.o: scpi/parser.c  .generated_files/flags/default/1bd9e1e3c46ad39c5d87e7b90c3055185c9b4e00 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/parser.o.d 
	@${RM} ${OBJECTDIR}/scpi/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/parser.c  -o ${OBJECTDIR}/scpi/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/parser.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/minimal.o: scpi/minimal.c  .generated_files/flags/default/e5ac2c1e4a2eb5771f3ad39747cc09e88ebeae85 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/minimal.o.d 
	@${RM} ${OBJECTDIR}/scpi/minimal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/minimal.c  -o ${OBJECTDIR}/scpi/minimal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/minimal.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/lexer.o: scpi/lexer.c  .generated_files/flags/default/a32cb9fbd0eb3de66aa8a2e014a25faba7bbfb01 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/lexer.o.d 
	@${RM} ${OBJECTDIR}/scpi/lexer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/lexer.c  -o ${OBJECTDIR}/scpi/lexer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/lexer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/ieee488.o: scpi/ieee488.c  .generated_files/flags/default/fcf51abec65033e6409d97f2f5abe84dfc945efc .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/ieee488.o.d 
	@${RM} ${OBJECTDIR}/scpi/ieee488.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/ieee488.c  -o ${OBJECTDIR}/scpi/ieee488.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/ieee488.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/fifo.o: scpi/fifo.c  .generated_files/flags/default/c27e74eeeac17685c730ff65e915d5ac9f69f6e3 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/fifo.o.d 
	@${RM} ${OBJECTDIR}/scpi/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/fifo.c  -o ${OBJECTDIR}/scpi/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/fifo.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/error.o: scpi/error.c  .generated_files/flags/default/f1782234ef8443b00c1ca19b563dcaf1e1202df2 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/error.o.d 
	@${RM} ${OBJECTDIR}/scpi/error.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/error.c  -o ${OBJECTDIR}/scpi/error.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/error.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/scpi/expression.o: scpi/expression.c  .generated_files/flags/default/82b9099170ff88115ced5816c2996f5d0a06bb31 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}/scpi" 
	@${RM} ${OBJECTDIR}/scpi/expression.o.d 
	@${RM} ${OBJECTDIR}/scpi/expression.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  scpi/expression.c  -o ${OBJECTDIR}/scpi/expression.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/scpi/expression.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/func.o: func.c  .generated_files/flags/default/7770cb70c2c805fafd37712720824b5991457f69 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/func.o.d 
	@${RM} ${OBJECTDIR}/func.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  func.c  -o ${OBJECTDIR}/func.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/func.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/hw.o: hw.c  .generated_files/flags/default/29557427e219ca51058eb31f90a3d2162d2d74d8 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hw.o.d 
	@${RM} ${OBJECTDIR}/hw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hw.c  -o ${OBJECTDIR}/hw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/hw.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/54dd3fe03ba6cebe1d52b82af20441f2a8cd2db2 .generated_files/flags/default/c3bcb89a839b6aab43a2e4502bbfa70e66d2d91a
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=1024,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/smu_front_p24.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
