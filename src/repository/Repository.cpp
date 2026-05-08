#include "Repository.h"

using namespace std;

void Repository::addSong(const Song &s) {
    songs.push_back(s);
}

void Repository::removeSong(const Song &s) {
    const auto it = std::find(this->songs.begin(), this->songs.end(), s);
    if (it == this->songs.end()) {
        cerr << "Song not found" << endl;
        return;
    }
    songs.erase(it);
}

std::optional<Song> Repository::findByArtistAndTitle(const std::string &artist, const std::string &title) {
    for (auto song: songs) {
        if (song.getArtist() == artist && song.getTitle() == title) {
            return song;
        }
    }

    return std::nullopt;
}
