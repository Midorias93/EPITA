if [ $# -ne 1 ]
then
    exit 1
else
    if [ -f "$1" ]
    then
        while IFS='' read -r ligne
        do
            num="$(echo "$ligne" | wc -c)"
            if [ $num -gt "80" ]
            then
                printf "%s\n" "$ligne"
            fi
        done < $1
        exit 0
    else
        exit 1
    fi
fi
