FILESGOOD="tests/good/*"

for f in $FILESGOOD
do
    ./src/tc -bBA $f > output1.tig
    if [ $? != 0 ] ; then
        echo -e "\e[31m[FAILED]: \e[0m$f"
        continue
    fi
    ./src/tc -bBA output1.tig > error
    if [ $? == 0 ] ; then
        echo -e "\e[32m[SUCCESS]: \e[0m$f"
    else
        echo -e "\e[31m[FAILED]: \e[0m$f"
        rm error
    fi
    rm output1.tig
done

FILESTC2="tests/tc2/*"
for f in $FILESTC2
do
    ./src/tc -bBA $f > output1.tig
    if [ $? != 0 ] ; then
        echo -e "\e[31m[FAILED]: \e[0m$f"
        continue
    fi
    ./src/tc -bBA output1.tig > error
    if [ $? == 0 ] ; then
        echo -e "\e[32m[SUCCESS]: \e[0m$f"
    else
        echo -e "\e[31m[FAILED]: \e[0m$f"
        rm error
    fi
    rm output1.tig
done

FILETYPE="tests/type/*"
for f in $FILETYPE
do
    ./src/tc -bBA $f > output1.tig
    if [ $? != 0 ] ; then
        echo -e "\e[31m[FAILED]: \e[0m$f"
        continue
    fi
    ./src/tc -bBA output1.tig > error
    if [ $? == 0 ] ; then
        echo -e "\e[32m[SUCCESS]: \e[0m$f"
    else
        echo -e "\e[31m[FAILED]: \e[0m$f"
        rm error
    fi
    rm output1.tig
done
rm error
echo -e "\e[0m"
