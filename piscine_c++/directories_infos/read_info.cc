#include <cstdint>
#include <istream>
#include <sstream>
#include <string>

#include "directory_info.hh"

DirectoryInfo read_info(std::istream& stream)
{
    std::string line;
    std::getline(stream, line);

    if (line.size() == 0)
        return DirectoryInfo();

    std::stringstream ss(line);

    std::string name;
    if (!(ss >> name))
        return DirectoryInfo();
    size_t size;
    if (!(ss >> size))
        return DirectoryInfo();
    std::uint16_t right;
    if (!(ss >> std::oct >> right))
        return DirectoryInfo();
    std::string owner;
    if (!(ss >> owner))
        return DirectoryInfo();
    std::string caca;
    if (ss >> caca)
        return DirectoryInfo();
    return DirectoryInfo(name, size, right, owner);
}
