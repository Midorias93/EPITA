test_bind1() {
    file=break-outside-loop
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_bind2() {
    file=invalid-function-redefinition-1
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file"
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_bind3() {
    file=invalid-type-redefinition
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file"
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_bind4() {
    file=test18
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file"
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_bind5() {
    file=test19
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file"
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_bind6() {
    file=undeclared-variable
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_bind7() {
    file=unknown-record
    ./../src/tc -bBA bind/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 4 ] ; then
        echo -e "\e[31m[ FAIL ] \e[0m first : bind/$file"
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
}

test_tc2_1() {
    file=1s-and-2s
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_tc2_2() {
    file=for-loop
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_tc2_3() {
    file=hello-world
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_tc2_4() {
    file=parens
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_tc2_5() {
    file=precedence
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}


test_tc2_6() {
    file=simple-fact
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test_tc2_7() {
    file=string-escapes
    ./../src/tc -bBA tc2/"$file".tig > output1.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m first : bind/$file --> "
        cat error
        return
    else
        echo -e "\e[32m[ PASS ] \e[0m first : bind/$file"
    fi
    ./../src/tc -bBA output1.tig > output2.tig 2> error
    n=$(echo $?)
    if [ "$n" -ne 0 ] ; then
        echo -ne "\e[31m[ FAIL ] \e[0m second : bind/$file --> "
        cat error
    else
        echo -e "\e[32m[ PASS ] \e[0m second : bind/$file"
    fi
}

test() {
    echo "========================================================================================"
    test_bind1
    echo "----------------------------------------------------------------------------------------"
    test_bind2
    echo "----------------------------------------------------------------------------------------"
    test_bind3
    echo "----------------------------------------------------------------------------------------"
    test_bind4
    echo "----------------------------------------------------------------------------------------"
    test_bind5
    echo "----------------------------------------------------------------------------------------"
    test_bind6
    echo "----------------------------------------------------------------------------------------"
    test_bind7
    echo "----------------------------------------------------------------------------------------"
    test_tc2_1
    echo "----------------------------------------------------------------------------------------"
    test_tc2_2
    echo "----------------------------------------------------------------------------------------"
    test_tc2_3
    echo "----------------------------------------------------------------------------------------"
    test_tc2_4
    echo "----------------------------------------------------------------------------------------"
    test_tc2_5
    echo "----------------------------------------------------------------------------------------"
    echo "----------------------------------------------------------------------------------------"
    test_tc2_6
    echo "----------------------------------------------------------------------------------------"
    test_tc2_7
    echo "========================================================================================"
    rm output1.tig output2.tig error
}

test
