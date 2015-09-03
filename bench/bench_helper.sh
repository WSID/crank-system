#!/usr/bin/sh

function gen_log () {
	for P in $@; do
		gtester $P -o $P.log
	done
}

function cpy_log () {
	PATH=$1
	shift
	
	SUFFIX=$1
	shift

	for P in $@; do
		cp $P.log $P.$SUFFIX.log
	done
}

TASK=$1
shift

if [ s$TASK == s"gen" ]; then
	gen_log $*
elif [ s$TASK == s"cpy" ]; then
	cpy_log $*
fi
