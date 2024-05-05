#include "stdin_to_file.hh"

#include <iostream>

ssize_t stdin_to_file(const std::string& filename)
{
    std::ofstream file;
    file.open(filename);
    std::string i;
    int compte = 0;
    if (file.is_open())
    {
        while (std::cin >> i)
        {
            compte++;
            file << i;
            file << "\n";
        }
    }
    return compte;
}
