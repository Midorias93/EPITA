#!/bin/sh

if [ $# -ne 1 ]
then
    exit 1
else
    num=$1
    resulta=1
    while [ $num -ne 0 ]
    do
        resulta=$(($resulta * $num))
        num=$(($num - 1))
    done
    echo $resulta
    exit 0
fi
