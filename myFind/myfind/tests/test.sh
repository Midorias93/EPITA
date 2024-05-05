test1 ()
{
    touch .ref.out
    touch .test.out

    REF_OUT=".ref.out"
    TEST_OUT=".test.out"


    find dossier_test "!" "(" -name a -o -type d "(" -user romain -a "!" "(" -name qux -o -name feur ")" ")" ")" > "$REF_OUT"
    exitcode_ref="$?"
    ./myfind_test dossier_test "!" "(" -name a -o -type d "(" -user romain -a "!" "(" -name qux -o -name feur ")" ")" ")" > "$TEST_OUT"
    exitcode_test="$?"

    diff "$REF_OUT" "$TEST_OUT"
    exitcode="$?"
    echo $exitcode_test
    echo $exitcode_ref

    if [ "$exitecode" -eq  0 ]
    then
        echo "[OK]"
    else
        echo "[FAIL]"
    fi
}

test1
