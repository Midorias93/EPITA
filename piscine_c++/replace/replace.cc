#include "replace.hh"

#include <fstream>
#include <iostream>

void replace(const std::string& input_filename,
             const std::string& output_filename, const std::string& src_token,
             const std::string& dst_token)
{
    std::ifstream fileinput;
    std::ofstream fileoutput;

    fileinput.open(input_filename);
    fileoutput.open(output_filename);

    if (fileinput.is_open())
    {
        if (fileoutput.is_open())
        {
            std::string line;
            std::string word;
            while (getline(fileinput, line))
            {
                for (size_t i = 0; i < line.size(); i++)
                {
                    size_t j = 0;
                    word.clear();
                    while (src_token.size() != j && line[i] == src_token[j])
                    {
                        word += line[i];
                        j++;
                        i++;
                    }
                    if (j == src_token.size())
                    {
                        i--;
                        fileoutput << dst_token;
                    }
                    else if (word.size() != 0)
                    {
                        i--;
                        fileoutput << word;
                    }
                    else
                    {
                        fileoutput << line[i];
                    }
                }
                fileoutput << "\n";
            }
        }
        else
        {
            std::cerr << "Cannot write output file\n";
        }
    }
    else
    {
        std::cerr << "Cannot open input file\n";
    }
}
