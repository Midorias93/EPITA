int reverse_content(const char *file_in, const char *file_out);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        reverse_content(argv[1], "test");
    }
}
