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
    
i=0

for arg
do
    if [ $valeur_file -eq 1 ]
    then
        name_file=$arg
        valeur_file=$((valeur_file+1))
    fi
    if [ $valeur_number -eq 1 ]
    then
        number=$arg
        valeur_number=$((valeur_number+1))
    fi
    if [ $valeur_extension -eq 1 ]
    then
        extension=$arg
        valeur_extension=$((valeur_extension+1))
    fi
    if [ $valeur_file -ne 2 ] && [ $arg = "--filename" ] || [ $arg = "-f" ]
    then
        valeur_file=$((valeur_file+1))
    fi
    if [ $valeur_number -ne 2 ] && [ $arg = "--number" ] || [ $arg = "-n" ]
    then
       valeur_number=$((valeur_number+1)) 
    fi
    if [ $valeur_extension -ne 2 ] && [ $arg = "--extension" ] || [ $arg = "-e" ]
    then
        valeur_extension=$((valeur_extension+1))
    fi
done

i=0

while [ $i -ne $number ]
do
    touch "$name_file-$((i+1)).$extension"
    i=$((i+1))
done
