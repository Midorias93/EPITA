#include <fstream>
#include <iostream>
#include <libzork/story/node.hh>
#include <memory>
#include <stdexcept>

#include "exceptions.hh"
#include "story/node_impl.hh"

namespace libzork::story
{

    std::unique_ptr<Node> make_node(const std::string& name,
                                    const fs::path& script_path)
    {
        std::string text;
        std::string line;
        std::ifstream file(script_path);
        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                text += line;
                text += "\n";
            }
            return std::make_unique<NodeImpl>(NodeImpl(name, text));
        }
        else
            throw std::runtime_error("make-node : file impossible a ouvrir");
    }

} // namespace libzork::story
