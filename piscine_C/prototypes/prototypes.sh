#!/bin/sh

sed -n -E 's/^[^ {}#/*].*\(.*\)$/&;/p' "$1"
