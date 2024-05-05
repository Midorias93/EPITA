#!/bin/sh

if [ $# -ne 2 ]
then
    echo Usage: ./hcf.sh num1 num2
    exit 1
else
    if [ $2 -eq 0 ]
    then
        echo Exception: division by 0
        exit 2
    else
        if [ $1 -eq 0 ]
        then
            echo $2
            exit 0
        fi
        num1=$1
        num2=$2
        reste=$(($num1 % $num2))
        while [ $reste -ne 0 ]
        do
            reste=$(($num1 % $num2))
            num1=$num2
            num2=$reste
        done
        echo $num1
        exit 0
    fi
fi
