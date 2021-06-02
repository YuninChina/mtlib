#!/bin/sh

#set -e

# for debug
DEBUG_LOG_FILE='&2'
DEBUG_LOG_LEVEL=0

# ANSI COLORS
COLOR_CRE="[K"
COLOR_NORMAL="[0;39m"
COLOR_RED="[1;31m"
COLOR_GREEN="[1;32m"
COLOR_YELLOW="[1;33m"
COLOR_BLUE="[1;34m"
COLOR_MAGENTA="[1;35m"
COLOR_CYAN="[1;36m"
COLOR_WHITE="[1;37m"

# Shell command
TAR=tar
CP=/bin/cp
RM=/bin/rm
GREP=grep
SED=sed
MKDIR=mkdir
CHMOD=chmod
MV=mv
CD=cd
LN=ln
MAKE=make
MKNOD=mknod
PUSHD=pushd 
POPD=popd 
RMDIR=rmdir
DEPMOD=/sbin/depmod
RMDIR=rmdir
MKIMG=mkimage
PATCH=patch
DIFF=diff
TOUCH=touch
CAT=cat
PWD=`pwd`



#unset linux environment variable
ENV_VAR_UNSET()
{
	# cross compile
	unset CC
	unset CFLAGS
	unset LDFLAGS
	unset CROSS_COMPILE
	unset PROCESSOR

	# path
	unset DESTDIR
	unset LIBDIR
	unset INCDIR
	unset BINDIR
	unset LIBPATH
	unset INCPATH
	unset BINPATH
	unset DATAPATH
	
	#misc
	unset PKG_CONFIG
}

e_blank='[        ][      ]*'
e_year='20[0-9][0-9]'
e_month='([1-9]|0[1-9]|1[0-2])'
e_day='([1-9]|0[1-9]|[12][0-9]|3[0-1])'
e_time='([01][0-9]|2[0-3]):[0-5][0-9]'
e_employid='[a-zA-Z][a-zA-Z]*[0-9]{4,}'

#$1: string
#$2: color
ECHO()
{
	[ -n "$2" ] && eval echo -n \"\${${2}}\";
	echo "${1}${COLOR_NORMAL}"
}

#$1 FUNC-LINE
#$2 string
ERR()
{
	echo "${COLOR_RED} ERR${1}: ${2}${COLOR_NORMAL}" >&2
}

#$1 FUNC-LINE
#$2 string
WARN()
{
	echo "${COLOR_YELLOW}WARN${1}: ${2}${COLOR_NORMAL}" >&2
}

#$1 FUNC-LINE
#$2 string
CMD()
{
	echo "${COLOR_GREEN} CMD${1}: ${2}${COLOR_NORMAL}" >&2
}

# $1:
LOG()
{
	echo "${COLOR_CYAN} LOG: ${1}${COLOR_NORMAL}" >&2
}


#$1: string
#$2: level
DEBUG()
{
	local level=$2
	[ -z "$level" ] && { level=0; }
	[ $level -lt $DEBUG_LOG_LEVEL ] && return 0;

	echo "$COLOR_WHITE$1$COLOR_NORMAL" > $DEBUG_LOG_FILE
}


