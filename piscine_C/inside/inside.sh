#!/bin/sh

if [ $# -ne 1 ]
then
    echo "Sorry, expected 1 argument but $# were passed"
    exit 1
else
    if [ -f $1 ]
    then
        cat $1
        exit 0
    else
        echo "$1:
	is not a valid file"
        exit 2
    fi
fi
