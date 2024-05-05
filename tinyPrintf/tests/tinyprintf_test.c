#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/tinyprintf.h"

TestSuite(Basics, .timeout = 10);
TestSuite(pour_centage, .timeout = 10);

Test(Basics, affiche_string1)
{
    cr_redirect_stdout();
    tinyprintf("");
    fflush(NULL);
    cr_expect_stdout_eq_str("");
}

Test(Basics, affiche_string2)
{
    cr_redirect_stdout();
    tinyprintf("Romain le plus beau");
    fflush(NULL);
    cr_expect_stdout_eq_str("Romain le plus beau");
}

Test(pour_centage, pour100_pour100)
{
    cr_redirect_stdout();
    tinyprintf("%% %% %t");
    fflush(NULL);
    cr_expect_stdout_eq_str("% % %t");
}

Test(pour_centage, affiche_cont_s)
{
    cr_redirect_stdout();
    tinyprintf("test %s", "romain");
    fflush(NULL);
    cr_expect_stdout_eq_str("test romain");
}

Test(pour_centage, affiche_cont_d)
{
    cr_redirect_stdout();
    tinyprintf("test %d", 2147483647);
    fflush(NULL);
    cr_expect_stdout_eq_str("test 2147483647");
}

Test(pour_centage, affiche_cont_c)
{
    cr_redirect_stdout();
    tinyprintf("test %c", 'g');
    fflush(NULL);
    cr_expect_stdout_eq_str("test g");
}

Test(pour_centage, affiche_cont_c2)
{
    cr_redirect_stdout();
    tinyprintf("test %c", 80);
    fflush(NULL);
    cr_expect_stdout_eq_str("test P");
}

Test(pour_centage, affiche_cont_o)
{
    cr_redirect_stdout();
    tinyprintf("test %o", 4294967295);
    fflush(NULL);
    cr_expect_stdout_eq_str("test 37777777777");
}

Test(pour_centage, affiche_cont_x)
{
    cr_redirect_stdout();
    tinyprintf("test %x", 3245);
    fflush(NULL);
    cr_expect_stdout_eq_str("test cad");
}

Test(pour_centage, affiche_cont_u)
{
    cr_redirect_stdout();
    tinyprintf("test %u", 65535);
    fflush(NULL);
    cr_expect_stdout_eq_str("test 65535");
}

Test(hard, affiche_pleint_de_truc)
{
    cr_redirect_stdout();
    tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(NULL);
    cr_expect_stdout_eq_str("Hello [42] world!");
}

Test(hard, affiche_pleint_de_truc2)
{
    cr_redirect_stdout();
    tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(NULL);
    cr_expect_stdout_eq_str("Hello [2a] world!");
}

Test(hard, affiche_pleint_de_truc3)
{
    cr_redirect_stdout();
    tinyprintf("%%s", "in your head");
    fflush(NULL);
    cr_expect_stdout_eq_str("%s");
}

Test(hard, affiche_pleint_de_truc4)
{
    cr_redirect_stdout();
    tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    fflush(NULL);
    cr_expect_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
}

Test(Basic, test_chiffre_negatif)
{
    cr_redirect_stdout();
    tinyprintf("%d", -12);
    fflush(NULL);
    cr_expect_stdout_eq_str("-12");
}

Test(Basic, format_NULL)
{
    cr_redirect_stdout();
    int i = tinyprintf(NULL);
    fflush(NULL);
    cr_expect_eq(i,0);
}

Test(Basic, taille)
{
    cr_redirect_stdout();
    int j = tinyprintf("test");
    fflush(NULL);
    cr_expect_eq(j,4);
}

Test(hard, taille_hard)
{
    cr_redirect_stdout();
    int k = tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(NULL);
    cr_expect_eq(k,17);
}

Test(hard, taille_hard2)
{
    int l = tinyprintf("%s [%o] %c", "Hello", 42, 'l');
    printf("%d",l);
    cr_redirect_stdout();
    int k = tinyprintf("%s [%o] %c", "Hello", 42, 'l');
    fflush(NULL);
    cr_expect_eq(k,12);
}
