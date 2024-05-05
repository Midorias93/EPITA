#!/bin/sh

if [ $# -eq 0 ]
then
	rm *.txt
else
	rm *.$1
fi


