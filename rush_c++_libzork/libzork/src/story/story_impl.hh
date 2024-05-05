#pragma once

#include <libzork/story/story.hh>

namespace libzork::story
{

    class StoryImpl : public Story
    {
    public:
        StoryImpl(const fs::path& path);
        ~StoryImpl() override = default;

        const std::string& get_title() const override;
        const Node* get_current() const override;
        void set_current(const Node* node) override;
        const store::Store* get_store() const override;
        std::ostream& display(std::ostream& os) const override;
        std::shared_ptr<Node> find_node(std::string name);

    private:
        std::string tile_;
        const Node* current_;
        store::Store* store_ = nullptr;

        std::vector<std::shared_ptr<Node>> nodes_;
    };

} // namespace libzork::story
