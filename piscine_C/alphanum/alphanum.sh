#!/bin/sh

while read line
do
    a=0
    val=$(echo "$line" | grep "^[a-zA-Z][a-zA-Z]*$")
    if [ $? -eq 0 ]
    then
        echo "it is a word"
        a=1
    fi
    val=$(echo "$line" | grep "^ *$")
    if [ $? -eq 0 ]
    then
        echo "it is empty"
        a=1
    fi
    val=$(echo "$line" | grep "^[0-9]$")
    if [ $? -eq 0 ]
    then
        echo "it is a digit"
        a=1
    fi
    val=$(echo $line | grep "^[0-9][0-9][0-9]*$")
    if [ $? -eq 0 ]
    then
        echo "it is a number"
        a=1
    fi
    val=$(echo $line | grep "^[[:alnum:]][[:alnum:]][[:alnum:]]*$")
    if [ $? -eq 0 ] && [ $a -eq 0 ]
    then
        echo "it is an alphanum"
        a=1
    fi
    if [ $a -eq 0 ]
    then
        echo "it is too complicated"
        exit 0
    fi
done
