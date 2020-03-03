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
	${OBJECTDIR}/_ext/56252444/cwsw_event.o \
	${OBJECTDIR}/_ext/511dfd52/main.o \
	${OBJECTDIR}/_ext/511dfd52/sim_event_cb.o \
	${OBJECTDIR}/_ext/f47e93e2/cwsw_lib.o


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

${OBJECTDIR}/_ext/56252444/cwsw_event.o: ../../src/cwsw_event.c
	${MKDIR} -p ${OBJECTDIR}/_ext/56252444
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/56252444/cwsw_event.o ../../src/cwsw_event.c

${OBJECTDIR}/_ext/511dfd52/main.o: ../app/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/main.o ../app/main.c

${OBJECTDIR}/_ext/511dfd52/sim_event_cb.o: ../app/sim_event_cb.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/sim_event_cb.o ../app/sim_event_cb.c

${OBJECTDIR}/_ext/f47e93e2/cwsw_lib.o: ../cwsw_lib/src/cwsw_lib.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f47e93e2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f47e93e2/cwsw_lib.o ../cwsw_lib/src/cwsw_lib.c

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
