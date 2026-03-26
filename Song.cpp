#include "Song.h"

Song::Song() : title(""), artist(""), duration(Duration()), source("") {
}

Song::Song(const std::string &artist, const std::string &title, const Duration &duration, const std::string &source) {
    this->artist = artist;
    this->title = title;
    this->duration = duration;
    this->source = source;
}

void Song::play() {
    const std::string url = this->getSource();

#ifdef _WIN32
    std::string cmd = "start \"\" \"" + url + "\"";
#elif __APPLE__
    std::string cmd = "open \"" + url + "\"";
#else
    std::string cmd = "xdg-open \"" + url + "\"";
#endif

    system(cmd.c_str());
}
