#!/bin/sh

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
TURQUOISE="\e[36m"
WHITE="\e[0m"

TOT_PASS=0
TOT_FAIL=0

REF_OUT=/tmp/.ref_out
REF_ERR=/tmp/.ref_err
TEST_OUT=/tmp/.my_out
TEST_ERR=/tmp/.my_err

exect=$(realpath ../../src/42sh)

run_test() {
    [ -e "$1" ] || echo "Missing file $1" 1>&2
    succes=true
    TOT_PASS=$((TOT_PASS+1))

    echo -ne "$BLUE-->> ${WHITE}$1...$WHITE"
    bash --posix -c "$(cat $1)" > $REF_OUT 2> $REF_ERR
    REF_C=$?
    $exect -c "$(cat $1)" > $TEST_OUT 2> $TEST_ERR
    MY_C=$?

    diff --color=always -u $REF_OUT $TEST_OUT >$1.diff
    DIFF_CODE=$?
    if [ $REF_C != $MY_C ]; then
        echo -ne "$RED RETURN$WHITE"
        succes=false
    fi
    if [ $DIFF_CODE != 0 ]; then
        echo -ne "$YELLOW STDOUT $WHITE"
        succes=false
    fi
    if { [ -s $REF_ERR ] && [ ! -s $TEST_ERR ]; } ||
        { [ ! -s $REF_ERR ] && [ -s $TEST_ERR ]; }; then
        echo -ne "$RED STDOUT$WHITE"
        succes=false
    fi

    if $succes; then
        echo -e "$GREEN PASS$WHITE"
        rm -f $1.diff
    else
        [ -s "$(realpath $1.diff)" ] && echo -ne "$RED (cat $(realpath $1.diff))$WHITE"
        echo
        TOT_FAIL=$((TOT_FAIL+1))
    fi
}

run_category() {
    cd $1
    source ./testsuite.sh
    cd - >/dev/null
}

run_testsuite() {
    for category in $@; do
        [ ${category} = "." ] && continue

        echo -e "$TURQUOISE=============================="
        printf " $WHITE%-36s $TURQUOISE%s\n" "${category#*/}"
        echo -e "$TURQUOISE=============================="

        run_category $category
    done
}

run_testsuite $(find . -type d)

PERCENT_SUCCES=$(((TOT_PASS - TOT_FAIL)  * 100 / TOT_PASS))

echo -e "$GREEN=============================="
echo -e " $WHITE RECAP: $([ $PERCENT_SUCCES =  100 ] && echo $GREEN || echo $RED) $PERCENT_SUCCES%"
echo -e " $WHITE Run :$TOT_PASS"
echo -e " $RED Fail :$TOT_FAIL"
echo -e "$GREEN==============================$WHITE"
rm -f $TEST_ERR $REF_ERR $REF_OUT $TEST_OUT


