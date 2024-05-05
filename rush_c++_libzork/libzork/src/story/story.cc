#include <libzork/story/story.hh>

#include "exceptions.hh"
#include "story/story_impl.hh"

namespace libzork::story
{

    std::unique_ptr<Story> make_story(const fs::path& path)
    {
        return std::make_unique<StoryImpl>(StoryImpl(path));
    }

} // namespace libzork::story
