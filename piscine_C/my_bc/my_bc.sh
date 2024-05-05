#!/bin/sh

if [ $# -eq 1 ]
then
    echo "$(($1))"
fi

while read line
do
    echo "$(($line))"
done
