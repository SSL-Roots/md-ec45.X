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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=comm/comm.c lib/assert/assert.c lib/ECAN/ECAN.c lib/fifo/fifo.c lib/i2c/i2c_slave_logics.c lib/msgpack/src/endian.c lib/msgpack/src/pack.c lib/msgpack/src/static_zone.c lib/msgpack/src/unpack.c lib/uart_dsPIC33F/uart_dsPIC33F.c lib/xprintf/xprintf.c motor_unit/encorder/encorder.c motor_unit/motor/bridge/bridge.c motor_unit/motor/hall/hall.c motor_unit/motor/motor.c motor_unit/motor_unit.c servo/logger/logger.c servo/servo.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/comm/comm.o ${OBJECTDIR}/lib/assert/assert.o ${OBJECTDIR}/lib/ECAN/ECAN.o ${OBJECTDIR}/lib/fifo/fifo.o ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o ${OBJECTDIR}/lib/msgpack/src/endian.o ${OBJECTDIR}/lib/msgpack/src/pack.o ${OBJECTDIR}/lib/msgpack/src/static_zone.o ${OBJECTDIR}/lib/msgpack/src/unpack.o ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o ${OBJECTDIR}/lib/xprintf/xprintf.o ${OBJECTDIR}/motor_unit/encorder/encorder.o ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o ${OBJECTDIR}/motor_unit/motor/hall/hall.o ${OBJECTDIR}/motor_unit/motor/motor.o ${OBJECTDIR}/motor_unit/motor_unit.o ${OBJECTDIR}/servo/logger/logger.o ${OBJECTDIR}/servo/servo.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/comm/comm.o.d ${OBJECTDIR}/lib/assert/assert.o.d ${OBJECTDIR}/lib/ECAN/ECAN.o.d ${OBJECTDIR}/lib/fifo/fifo.o.d ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d ${OBJECTDIR}/lib/msgpack/src/endian.o.d ${OBJECTDIR}/lib/msgpack/src/pack.o.d ${OBJECTDIR}/lib/msgpack/src/static_zone.o.d ${OBJECTDIR}/lib/msgpack/src/unpack.o.d ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d ${OBJECTDIR}/lib/xprintf/xprintf.o.d ${OBJECTDIR}/motor_unit/encorder/encorder.o.d ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d ${OBJECTDIR}/motor_unit/motor/hall/hall.o.d ${OBJECTDIR}/motor_unit/motor/motor.o.d ${OBJECTDIR}/motor_unit/motor_unit.o.d ${OBJECTDIR}/servo/logger/logger.o.d ${OBJECTDIR}/servo/servo.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/comm/comm.o ${OBJECTDIR}/lib/assert/assert.o ${OBJECTDIR}/lib/ECAN/ECAN.o ${OBJECTDIR}/lib/fifo/fifo.o ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o ${OBJECTDIR}/lib/msgpack/src/endian.o ${OBJECTDIR}/lib/msgpack/src/pack.o ${OBJECTDIR}/lib/msgpack/src/static_zone.o ${OBJECTDIR}/lib/msgpack/src/unpack.o ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o ${OBJECTDIR}/lib/xprintf/xprintf.o ${OBJECTDIR}/motor_unit/encorder/encorder.o ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o ${OBJECTDIR}/motor_unit/motor/hall/hall.o ${OBJECTDIR}/motor_unit/motor/motor.o ${OBJECTDIR}/motor_unit/motor_unit.o ${OBJECTDIR}/servo/logger/logger.o ${OBJECTDIR}/servo/servo.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=comm/comm.c lib/assert/assert.c lib/ECAN/ECAN.c lib/fifo/fifo.c lib/i2c/i2c_slave_logics.c lib/msgpack/src/endian.c lib/msgpack/src/pack.c lib/msgpack/src/static_zone.c lib/msgpack/src/unpack.c lib/uart_dsPIC33F/uart_dsPIC33F.c lib/xprintf/xprintf.c motor_unit/encorder/encorder.c motor_unit/motor/bridge/bridge.c motor_unit/motor/hall/hall.c motor_unit/motor/motor.c motor_unit/motor_unit.c servo/logger/logger.c servo/servo.c main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/comm/comm.o: comm/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/comm" 
	@${RM} ${OBJECTDIR}/comm/comm.o.d 
	@${RM} ${OBJECTDIR}/comm/comm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  comm/comm.c  -o ${OBJECTDIR}/comm/comm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/comm/comm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/comm/comm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/assert/assert.o: lib/assert/assert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/assert" 
	@${RM} ${OBJECTDIR}/lib/assert/assert.o.d 
	@${RM} ${OBJECTDIR}/lib/assert/assert.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/assert/assert.c  -o ${OBJECTDIR}/lib/assert/assert.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/assert/assert.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/assert/assert.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/ECAN/ECAN.o: lib/ECAN/ECAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/ECAN" 
	@${RM} ${OBJECTDIR}/lib/ECAN/ECAN.o.d 
	@${RM} ${OBJECTDIR}/lib/ECAN/ECAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/ECAN/ECAN.c  -o ${OBJECTDIR}/lib/ECAN/ECAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/ECAN/ECAN.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/ECAN/ECAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/fifo/fifo.o: lib/fifo/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/fifo" 
	@${RM} ${OBJECTDIR}/lib/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/lib/fifo/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/fifo/fifo.c  -o ${OBJECTDIR}/lib/fifo/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/fifo/fifo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/fifo/fifo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/i2c/i2c_slave_logics.o: lib/i2c/i2c_slave_logics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/i2c/i2c_slave_logics.c  -o ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/endian.o: lib/msgpack/src/endian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/endian.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/endian.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/endian.c  -o ${OBJECTDIR}/lib/msgpack/src/endian.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/endian.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/endian.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/pack.o: lib/msgpack/src/pack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/pack.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/pack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/pack.c  -o ${OBJECTDIR}/lib/msgpack/src/pack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/pack.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/pack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/static_zone.o: lib/msgpack/src/static_zone.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/static_zone.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/static_zone.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/static_zone.c  -o ${OBJECTDIR}/lib/msgpack/src/static_zone.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/static_zone.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/static_zone.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/unpack.o: lib/msgpack/src/unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/unpack.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/unpack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/unpack.c  -o ${OBJECTDIR}/lib/msgpack/src/unpack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/unpack.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/unpack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o: lib/uart_dsPIC33F/uart_dsPIC33F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/uart_dsPIC33F" 
	@${RM} ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d 
	@${RM} ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/uart_dsPIC33F/uart_dsPIC33F.c  -o ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/xprintf/xprintf.o: lib/xprintf/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/xprintf" 
	@${RM} ${OBJECTDIR}/lib/xprintf/xprintf.o.d 
	@${RM} ${OBJECTDIR}/lib/xprintf/xprintf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/xprintf/xprintf.c  -o ${OBJECTDIR}/lib/xprintf/xprintf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/xprintf/xprintf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/xprintf/xprintf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/encorder/encorder.o: motor_unit/encorder/encorder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/encorder" 
	@${RM} ${OBJECTDIR}/motor_unit/encorder/encorder.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/encorder/encorder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/encorder/encorder.c  -o ${OBJECTDIR}/motor_unit/encorder/encorder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/encorder/encorder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/encorder/encorder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/bridge/bridge.o: motor_unit/motor/bridge/bridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor/bridge" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/bridge/bridge.c  -o ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/hall/hall.o: motor_unit/motor/hall/hall.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor/hall" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/hall/hall.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/hall/hall.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/hall/hall.c  -o ${OBJECTDIR}/motor_unit/motor/hall/hall.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/hall/hall.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/hall/hall.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/motor.o: motor_unit/motor/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/motor.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/motor.c  -o ${OBJECTDIR}/motor_unit/motor/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor_unit.o: motor_unit/motor_unit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit" 
	@${RM} ${OBJECTDIR}/motor_unit/motor_unit.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor_unit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor_unit.c  -o ${OBJECTDIR}/motor_unit/motor_unit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor_unit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor_unit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servo/logger/logger.o: servo/logger/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/servo/logger" 
	@${RM} ${OBJECTDIR}/servo/logger/logger.o.d 
	@${RM} ${OBJECTDIR}/servo/logger/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo/logger/logger.c  -o ${OBJECTDIR}/servo/logger/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servo/logger/logger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servo/logger/logger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servo/servo.o: servo/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/servo" 
	@${RM} ${OBJECTDIR}/servo/servo.o.d 
	@${RM} ${OBJECTDIR}/servo/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo/servo.c  -o ${OBJECTDIR}/servo/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servo/servo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servo/servo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/comm/comm.o: comm/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/comm" 
	@${RM} ${OBJECTDIR}/comm/comm.o.d 
	@${RM} ${OBJECTDIR}/comm/comm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  comm/comm.c  -o ${OBJECTDIR}/comm/comm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/comm/comm.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/comm/comm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/assert/assert.o: lib/assert/assert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/assert" 
	@${RM} ${OBJECTDIR}/lib/assert/assert.o.d 
	@${RM} ${OBJECTDIR}/lib/assert/assert.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/assert/assert.c  -o ${OBJECTDIR}/lib/assert/assert.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/assert/assert.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/assert/assert.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/ECAN/ECAN.o: lib/ECAN/ECAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/ECAN" 
	@${RM} ${OBJECTDIR}/lib/ECAN/ECAN.o.d 
	@${RM} ${OBJECTDIR}/lib/ECAN/ECAN.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/ECAN/ECAN.c  -o ${OBJECTDIR}/lib/ECAN/ECAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/ECAN/ECAN.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/ECAN/ECAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/fifo/fifo.o: lib/fifo/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/fifo" 
	@${RM} ${OBJECTDIR}/lib/fifo/fifo.o.d 
	@${RM} ${OBJECTDIR}/lib/fifo/fifo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/fifo/fifo.c  -o ${OBJECTDIR}/lib/fifo/fifo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/fifo/fifo.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/fifo/fifo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/i2c/i2c_slave_logics.o: lib/i2c/i2c_slave_logics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/i2c/i2c_slave_logics.c  -o ${OBJECTDIR}/lib/i2c/i2c_slave_logics.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/i2c/i2c_slave_logics.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/endian.o: lib/msgpack/src/endian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/endian.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/endian.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/endian.c  -o ${OBJECTDIR}/lib/msgpack/src/endian.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/endian.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/endian.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/pack.o: lib/msgpack/src/pack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/pack.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/pack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/pack.c  -o ${OBJECTDIR}/lib/msgpack/src/pack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/pack.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/pack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/static_zone.o: lib/msgpack/src/static_zone.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/static_zone.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/static_zone.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/static_zone.c  -o ${OBJECTDIR}/lib/msgpack/src/static_zone.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/static_zone.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/static_zone.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/msgpack/src/unpack.o: lib/msgpack/src/unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/msgpack/src" 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/unpack.o.d 
	@${RM} ${OBJECTDIR}/lib/msgpack/src/unpack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/msgpack/src/unpack.c  -o ${OBJECTDIR}/lib/msgpack/src/unpack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/msgpack/src/unpack.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/msgpack/src/unpack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o: lib/uart_dsPIC33F/uart_dsPIC33F.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/uart_dsPIC33F" 
	@${RM} ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d 
	@${RM} ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/uart_dsPIC33F/uart_dsPIC33F.c  -o ${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/uart_dsPIC33F/uart_dsPIC33F.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/xprintf/xprintf.o: lib/xprintf/xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib/xprintf" 
	@${RM} ${OBJECTDIR}/lib/xprintf/xprintf.o.d 
	@${RM} ${OBJECTDIR}/lib/xprintf/xprintf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/xprintf/xprintf.c  -o ${OBJECTDIR}/lib/xprintf/xprintf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/xprintf/xprintf.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/lib/xprintf/xprintf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/encorder/encorder.o: motor_unit/encorder/encorder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/encorder" 
	@${RM} ${OBJECTDIR}/motor_unit/encorder/encorder.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/encorder/encorder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/encorder/encorder.c  -o ${OBJECTDIR}/motor_unit/encorder/encorder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/encorder/encorder.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/encorder/encorder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/bridge/bridge.o: motor_unit/motor/bridge/bridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor/bridge" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/bridge/bridge.c  -o ${OBJECTDIR}/motor_unit/motor/bridge/bridge.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/bridge/bridge.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/hall/hall.o: motor_unit/motor/hall/hall.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor/hall" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/hall/hall.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/hall/hall.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/hall/hall.c  -o ${OBJECTDIR}/motor_unit/motor/hall/hall.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/hall/hall.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/hall/hall.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor/motor.o: motor_unit/motor/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit/motor" 
	@${RM} ${OBJECTDIR}/motor_unit/motor/motor.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor/motor.c  -o ${OBJECTDIR}/motor_unit/motor/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor/motor.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_unit/motor_unit.o: motor_unit/motor_unit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/motor_unit" 
	@${RM} ${OBJECTDIR}/motor_unit/motor_unit.o.d 
	@${RM} ${OBJECTDIR}/motor_unit/motor_unit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_unit/motor_unit.c  -o ${OBJECTDIR}/motor_unit/motor_unit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_unit/motor_unit.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/motor_unit/motor_unit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servo/logger/logger.o: servo/logger/logger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/servo/logger" 
	@${RM} ${OBJECTDIR}/servo/logger/logger.o.d 
	@${RM} ${OBJECTDIR}/servo/logger/logger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo/logger/logger.c  -o ${OBJECTDIR}/servo/logger/logger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servo/logger/logger.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servo/logger/logger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/servo/servo.o: servo/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/servo" 
	@${RM} ${OBJECTDIR}/servo/servo.o.d 
	@${RM} ${OBJECTDIR}/servo/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  servo/servo.c  -o ${OBJECTDIR}/servo/servo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/servo/servo.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/servo/servo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf   -O0 -I"lib" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf    -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf   -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/md-ec45.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
