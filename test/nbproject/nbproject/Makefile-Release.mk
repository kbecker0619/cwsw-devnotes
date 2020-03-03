#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/f3d31002/ports_api.o \
	${OBJECTDIR}/_ext/28111b26/cwsw_arch.o \
	${OBJECTDIR}/_ext/b0466254/cwsw_clock_svc.o \
	${OBJECTDIR}/_ext/e9e0d2e0/cwsw_event.o \
	${OBJECTDIR}/_ext/5fe49f66/cwsw_evqueue.o \
	${OBJECTDIR}/_ext/bb2ddd8b/cwsw_lib.o \
	${OBJECTDIR}/_ext/a00d43e7/cwsw_swtimer.o \
	${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o \
	${OBJECTDIR}/_ext/e89cc024/CritSect.o \
	${OBJECTDIR}/_ext/511dfd52/main.o \
	${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/f3d31002/ports_api.o: ../../bsw/ecu/cwsw_arch/inc/i386/peripheral/ports/ports_api.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f3d31002
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f3d31002/ports_api.o ../../bsw/ecu/cwsw_arch/inc/i386/peripheral/ports/ports_api.c

${OBJECTDIR}/_ext/28111b26/cwsw_arch.o: ../../bsw/ecu/cwsw_arch/src/i386/cwsw_arch.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28111b26
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28111b26/cwsw_arch.o ../../bsw/ecu/cwsw_arch/src/i386/cwsw_arch.c

${OBJECTDIR}/_ext/b0466254/cwsw_clock_svc.o: ../../bsw/svc/cwsw_clock/src/cwsw_clock_svc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b0466254
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b0466254/cwsw_clock_svc.o ../../bsw/svc/cwsw_clock/src/cwsw_clock_svc.c

${OBJECTDIR}/_ext/e9e0d2e0/cwsw_event.o: ../../bsw/svc/cwsw_event/src/cwsw_event.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e9e0d2e0
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9e0d2e0/cwsw_event.o ../../bsw/svc/cwsw_event/src/cwsw_event.c

${OBJECTDIR}/_ext/5fe49f66/cwsw_evqueue.o: ../../bsw/svc/cwsw_evq/src/cwsw_evqueue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/5fe49f66
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5fe49f66/cwsw_evqueue.o ../../bsw/svc/cwsw_evq/src/cwsw_evqueue.c

${OBJECTDIR}/_ext/bb2ddd8b/cwsw_lib.o: ../../bsw/svc/cwsw_lib/src/cwsw_lib.c
	${MKDIR} -p ${OBJECTDIR}/_ext/bb2ddd8b
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bb2ddd8b/cwsw_lib.o ../../bsw/svc/cwsw_lib/src/cwsw_lib.c

${OBJECTDIR}/_ext/a00d43e7/cwsw_swtimer.o: ../../bsw/svc/cwsw_swtimer/src/cwsw_swtimer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/a00d43e7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a00d43e7/cwsw_swtimer.o ../../bsw/svc/cwsw_swtimer/src/cwsw_swtimer.c

${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o: ../../bsw/svc/src/cwsw_svc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/ae0ac54c
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o ../../bsw/svc/src/cwsw_svc.c

${OBJECTDIR}/_ext/e89cc024/CritSect.o: ../app/cwsw_lib_prj/CritSect.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e89cc024
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e89cc024/CritSect.o ../app/cwsw_lib_prj/CritSect.c

${OBJECTDIR}/_ext/511dfd52/main.o: ../app/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/main.o ../app/main.c

${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o: ../libs/cwsw_board/none/src/cwsw_board.c
	${MKDIR} -p ${OBJECTDIR}/_ext/bf66c54b
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o ../libs/cwsw_board/none/src/cwsw_board.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
