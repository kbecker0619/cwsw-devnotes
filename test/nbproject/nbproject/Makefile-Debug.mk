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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o \
	${OBJECTDIR}/_ext/e89cc024/CritSect.o \
	${OBJECTDIR}/_ext/511dfd52/main.o \
	${OBJECTDIR}/_ext/70639f51/ports_api.o \
	${OBJECTDIR}/_ext/a083a7f7/cwsw_arch.o \
	${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o \
	${OBJECTDIR}/_ext/c681fccb/cwsw_event.o \
	${OBJECTDIR}/_ext/c681fccb/cwsw_eventtable.o \
	${OBJECTDIR}/_ext/5565b331/cwsw_evqueue.o \
	${OBJECTDIR}/_ext/99759e4b/cwsw_evhandler.o \
	${OBJECTDIR}/_ext/99759e4b/cwsw_evqueue_ex.o \
	${OBJECTDIR}/_ext/99759e4b/cwsw_evthndlrassoc.o \
	${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o


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

${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o: ../../bsw/svc/src/cwsw_svc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/ae0ac54c
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ae0ac54c/cwsw_svc.o ../../bsw/svc/src/cwsw_svc.c

${OBJECTDIR}/_ext/e89cc024/CritSect.o: ../app/cwsw_lib_prj/CritSect.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e89cc024
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e89cc024/CritSect.o ../app/cwsw_lib_prj/CritSect.c

${OBJECTDIR}/_ext/511dfd52/main.o: ../app/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/main.o ../app/main.c

${OBJECTDIR}/_ext/70639f51/ports_api.o: ../libs/cwsw_arch/inc/i386/peripheral/ports/ports_api.c
	${MKDIR} -p ${OBJECTDIR}/_ext/70639f51
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/70639f51/ports_api.o ../libs/cwsw_arch/inc/i386/peripheral/ports/ports_api.c

${OBJECTDIR}/_ext/a083a7f7/cwsw_arch.o: ../libs/cwsw_arch/src/i386/cwsw_arch.c
	${MKDIR} -p ${OBJECTDIR}/_ext/a083a7f7
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a083a7f7/cwsw_arch.o ../libs/cwsw_arch/src/i386/cwsw_arch.c

${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o: ../libs/cwsw_board/none/src/cwsw_board.c
	${MKDIR} -p ${OBJECTDIR}/_ext/bf66c54b
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bf66c54b/cwsw_board.o ../libs/cwsw_board/none/src/cwsw_board.c

${OBJECTDIR}/_ext/c681fccb/cwsw_event.o: ../libs/cwsw_eventqueue/cwsw_event/src/cwsw_event.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c681fccb
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c681fccb/cwsw_event.o ../libs/cwsw_eventqueue/cwsw_event/src/cwsw_event.c

${OBJECTDIR}/_ext/c681fccb/cwsw_eventtable.o: ../libs/cwsw_eventqueue/cwsw_event/src/cwsw_eventtable.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c681fccb
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c681fccb/cwsw_eventtable.o ../libs/cwsw_eventqueue/cwsw_event/src/cwsw_eventtable.c

${OBJECTDIR}/_ext/5565b331/cwsw_evqueue.o: ../libs/cwsw_eventqueue/cwsw_evqueue/src/cwsw_evqueue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/5565b331
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5565b331/cwsw_evqueue.o ../libs/cwsw_eventqueue/cwsw_evqueue/src/cwsw_evqueue.c

${OBJECTDIR}/_ext/99759e4b/cwsw_evhandler.o: ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evhandler.c
	${MKDIR} -p ${OBJECTDIR}/_ext/99759e4b
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/99759e4b/cwsw_evhandler.o ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evhandler.c

${OBJECTDIR}/_ext/99759e4b/cwsw_evqueue_ex.o: ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evqueue_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/99759e4b
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/99759e4b/cwsw_evqueue_ex.o ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evqueue_ex.c

${OBJECTDIR}/_ext/99759e4b/cwsw_evthndlrassoc.o: ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/99759e4b
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/99759e4b/cwsw_evthndlrassoc.o ../libs/cwsw_eventqueue/cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c

${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o: ../libs/cwsw_lib/src/cwsw_lib.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccfc345
	${RM} "$@.d"
	$(COMPILE.c) -g -DXPRJ_NB_${CND_CONF}=1 -I../app/cfg -I../libs/cwsw_lib/inc -I../libs/cwsw_eventqueue/cwsw_event/inc -I../libs/cwsw_eventqueue/cwsw_evqueue/inc -I../libs/cwsw_eventqueue/cwsw_evqueue_ex/inc -I../../bsw/svc/inc -I../libs/cwsw_board/none -I../libs/cwsw_arch/inc/i386 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o ../libs/cwsw_lib/src/cwsw_lib.c

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
