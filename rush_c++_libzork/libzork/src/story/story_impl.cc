#include "story/story_impl.hh"

#include <cassert>
#include <httplib.h>
#include <libzork/store/store.hh>
#include <yaml-cpp/yaml.h>

#include "exceptions.hh"
#include "store/store_impl.hh"
#include "story/node_impl.hh"

namespace libzork::story
{
    std::shared_ptr<Node> StoryImpl::find_node(std::string name)
    {
        for (std::shared_ptr<Node> node : this->nodes_)
        {
            if (node->get_name() == name)
                return node;
        }
        return nullptr;
    }

    StoryImpl::StoryImpl(const fs::path& path)
    {
        YAML::Node config = YAML::LoadFile(path);
        this->tile_ = config["title"].as<std::string>();
        const YAML::Node& root = config["story"];
        std::string source;

        for (auto node : root)
        {
            source = path.parent_path().string() + "/";
            source += config["scripts-path"].as<std::string>() + "/"
                + node["script"].as<std::string>();
            std::shared_ptr<Node> added =
                make_node(node["name"].as<std::string>(), source);
            this->nodes_.push_back(added);
        }
        if (!this->nodes_.empty())
            this->current_ = this->nodes_[0].get();
    else
            this->current_ = nullptr;

        std::shared_ptr<Node> parent_node;
        std::shared_ptr<Node> choice_node;

        for (auto node : root)
        {
            parent_node = this->find_node(node["name"].as<std::string>());
            if (parent_node)
            {
                for (auto target : node["choices"])
                {
                    choice_node =
                        this->find_node(target["target"].as<std::string>());
                    if (choice_node)
                    {
                        parent_node->add_choice(
                            choice_node.get(),
                            target["text"].as<std::string>());
                    }
                }
            }
        }
    }

    const std::string& StoryImpl::get_title() const
    {
        return this->tile_;
    }

    const Node* StoryImpl::get_current() const
    {
        return this->current_;
    }

    void StoryImpl::set_current(const Node* node)
    {
        this->current_ = node;
    }

    const store::Store* StoryImpl::get_store() const
    {
        return this->store_;
    }

    std::ostream& StoryImpl::display(std::ostream& os) const
    {
        os << "digraph story {\n";
        for (const std::shared_ptr<Node>& node : this->nodes_)
        {
            auto option = dynamic_cast<NodeImpl*>(node.get());

            std::vector<std::string> list_option = option->list_name();

            if (list_option.empty())
                continue;

            os << "\"" << node->get_name() << "\" -> ";

            if (list_option.size() == 1)
                os << "\"" << list_option[0] << "\";\n";

            else
            {
                os << "{ ";
                for (size_t i = 1; i < list_option.size(); i++)
                {
                    os << "\"" << list_option[i - 1] << "\""
                       << " ";
                }
                os << "\"" << list_option[list_option.size() - 1] << "\" };\n";
            }
        }
        os << "}\n";
        return os;
    }

} // namespace libzork::story
