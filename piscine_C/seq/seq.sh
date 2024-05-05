#!/bin/sh

if [ $# -ne 3 ]
then
    echo "Usage: ./seq.sh FIRST INCREMENT LAST" >&2
    exit 1
elif [ "$2" -eq 0 ]
then
    exit 1
else
    if [ "$1" -eq "$3" ]
    then
        echo $1
    elif [ "$3" -gt "$1" ]
    then
        if [ "$2" -lt 0 ]
        then
            exit 1
        else
            i=0
            n=$(($1 + $i * $2))
            while [ "$n" -le $3 ]
            do
                echo "$n"
                i=$(($i + 1))
                n=$(($1 + $i * $2))
            done
            exit 0
        fi
    else
        if [ $2 -gt 0 ]
        then
            exit 1
        else
            i=0
            n=$(($1 + $i * $2))
            while [ "$n" -ge "$3" ]
            do
                echo "$n"
                i=$(($i + 1))
                n=$(($1 + $i * $2))
            done
            exit 0
        fi
    fi
fi
