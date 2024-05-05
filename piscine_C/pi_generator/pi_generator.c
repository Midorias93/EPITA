double pi_generator(int precision)
{
    double resultat = 1;
    while (precision > 0)
    {
        resultat = (1.0 + resultat * (precision / (precision * 2.0 + 1.0)));
        precision--;
    }
    return 2 * resultat;
}
