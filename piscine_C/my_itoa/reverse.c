int taille = i;
i = 0;
while (i <= taille / 2)
{
    retenu = s[taille - i];
    s[taille - i] = s[i];
    s[i] = retenu;
    i++;
}
taille++;
s[taille] = '\0';
return s;
