#!/bin/bash
CODE=$1
BASE=`basename "${CODE}" .c`
OBJECT="${BASE}.o"
sym=`gcc -c "${CODE}"; /usr/bin/nm ${OBJECT} | grep -v 'strdup'| grep -c 'str'`
incl_str=`cat ${CODE}| grep -c 'string.h'`
if [[ "$sym" != "0" ]] || [[ "$incl_str" != "0" ]]; then
    echo DO NOT USE ANY STRING FUNCTION IN $BASE.c OR YOU MAY LOSE MANY POINTS;
    #/usr/bin/nm ${OBJECT} | grep -v 'strdup'| grep 'str'
    exit 1
else
    echo OK. No string functions;
    exit 0
fi


