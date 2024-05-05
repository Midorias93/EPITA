#!/bin/sh

if [ $# -ne 2 ]
then
    exit 1
fi

case "$2" in
    "" | *[!0-9]*)
    exit 1
    ;;
esac

compte=0
lue=0

if [ -f "$1" ]
then
    while read line
    do
        if [ $compte -eq $(($2 - 1)) ]
        then
            printf "%s is %s\n" "$(echo "$line" | cut -d ';' -f 2)"  "$(echo "$line" | cut -d ';' -f 3)"
            lue=1
        fi
        compte=$(($compte + 1))
    done < "$1"
    if [ $lue -eq 1 ]
    then
        exit 0
    else
        exit 1
    fi
else
    exit 1
fi
