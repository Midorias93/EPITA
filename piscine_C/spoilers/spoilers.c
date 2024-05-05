#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(STDERR_FILENO, "Invalid number of arguments\n", 28);
        return 1;
    }
    else
    {
        int stream = open(argv[1], O_RDONLY);
        if (stream == -1)
        {
            write(STDERR_FILENO, "Could not open file\n", 20);
            return 1;
        }
        char lettre[1];
        char spoiler[2] = { 0 };
        int a = read(stream, lettre, 1);
        int compte = 0;
        while (a != 0)
        {
            if (!isspace(*lettre))
            {
                spoiler[compte % 2] = *lettre;
                compte++;
            }
            a = read(stream, lettre, 1);
        }
        if (spoiler[0] == 0 || spoiler[1] == 0)
        {
            write(STDERR_FILENO, "File is not long enough\n", 24);
            return 1;
        }
        if ((compte % 2) == 0)
        {
            char affichage[] = { spoiler[0], spoiler[1], '\n' };
            write(STDOUT_FILENO, affichage, 3);
        }
        else
        {
            char affichage[] = { spoiler[1], spoiler[0], '\n' };
            write(STDOUT_FILENO, affichage, 3);
        }
        close(stream);
        return 0;
    }
}
