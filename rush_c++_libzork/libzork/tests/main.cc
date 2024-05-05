#include <iostream>
#include <libzork/runner/choice.hh>
#include <libzork/runner/html.hh>
#include <libzork/runner/smart.hh>

int main(int argc, char* argv[])
{
    (void)argc;
    auto story = libzork::story::make_story(argv[1]);
    story->display(std::cout);
}
