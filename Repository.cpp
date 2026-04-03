#include "Repository.h"
#include <string>

using namespace std;

void Repository::addSong(const Song &s) {
    songs.add(s);
}

std::optional<Song> Repository::findByArtistAndTitle(const std::string &artist, const std::string &title) {
    for (auto song: songs) {
        if (song.getArtist() == artist && song.getTitle() == title) {
            return song;
        }
    }

    return std::nullopt;
}
