int replace_line(const char *file_in, const char *file_out, const char *content,
                 int n);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        replace_line(argv[1], "test", "je remplace la ligne 4\n", 4);
    }
}
