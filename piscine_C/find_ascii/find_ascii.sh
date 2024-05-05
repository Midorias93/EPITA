for i in $(ls "$1")
do
    file $1/$i | grep "ASCII"
done

