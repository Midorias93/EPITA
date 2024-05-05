#!/bin/sh

i=$1
somme=1

if [ $# -ne 1 ]
then
    exit 1
else
    while [ $i -ne 0 ]
    do
        somme=$((somme*i))
        i=$((i-1))
    done
fi
echo $somme
exit 0
