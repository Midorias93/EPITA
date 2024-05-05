#!/bin/sh

name_file=default
number=1
extension=txt
valeur_file=0
valeur_number=0
valeur_extension=0

if [ $# -eq 0 ]
then
    touch "$name_file-$number.$extension"
    exit
fi

compte=0

for arg
do
    reste=$(($compte % 2))
    if [ $reste -eq 0 ]
    then 
        if [ $arg != "--filename" ] && [ $arg != "--number" ] && [ $arg != "--extension" ] && [ $arg != "-f" ] && [ $arg != "-n" ] && [ $arg != "-e" ]
        then
            exit 1
        fi
    fi
    if [ $valeur_number -eq 1 ]
    then
        number="$arg"
        valeur_number=0
    fi
    if [ $valeur_extension -eq 1 ]
    then
        extension="$arg"
        valeur_extension=0
    fi
    if [ $valeur_file -eq 1 ]
    then
        name_file="$arg"
        valeur_file=0
    fi
    if [ $arg = "--filename" ] || [ $arg = "-f" ]
    then
        valeur_file=1
    fi
    if [ $arg = "--number" ] || [ $arg = "-n" ]
    then
       valeur_number=1
    fi
    if [ $arg = "--extension" ] || [ $arg = "-e" ]
    then
        valeur_extension=1
    fi
    compte=$((compte + 1))
done

i=0

while [ $i -ne $number ]
do
    touch -- "$name_file-$((i+1)).$extension"
    i=$((i+1))
done
