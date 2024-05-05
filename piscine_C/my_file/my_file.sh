#!/bin/sh

for arg
do
    if [ -f "$arg" ]
    then
        echo $arg: file
        continue
    elif [ -d "$arg" ]
    then
        echo $arg: directory
        continue
    else
        echo $arg: unknown
        continue
    fi
done
