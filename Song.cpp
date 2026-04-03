#include "Song.h"

void Song::play() const {
    const std::string url = this->getSource();

#ifdef _WIN32
    const std::string cmd = "start \"\" \"" + url + "\"";
#elif __APPLE__
    const std::string cmd = "open \"" + url + "\"";
#else
    const std::string cmd = "xdg-open \"" + url + "\"";
#endif

    system(cmd.c_str());
}
