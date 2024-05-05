#/bin/sh

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
        reste=$(($1%$2))
        num1=$1
        num2=$2
        while [ $reste -ne 0 ]
        do
            reste=$(($1%$2))
            num2=$(($1/$2))
            num1=$num2
        done
        echo $num2
        exit 0
    fi
fi
