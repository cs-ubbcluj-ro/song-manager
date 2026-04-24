#pragma once
#include "FilePlaylist.h"
#include <fstream>
#include <nlohmann/json.hpp>

class JsonPlaylist : public FilePlaylist {
private:
    const int INDENTATION = 4;

    void readFromFile() {
        // File does not exist
        if (!std::filesystem::exists(path)) {
            return;
        }

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "File exists but cannot be opened: " << path << std::endl;
            return;
        }

        nlohmann::json data;
        try {
            file >> data;
        } catch (const nlohmann::detail::parse_error &e) {
            std::cerr << "Failed to parse the file: " << e.what() << std::endl;
            return;
        }

        for (const auto &item: data) {
            Duration duration{item["minutes"], item["seconds"]};
            Song song{item["artist"], item["title"], duration, item["url"]};
            this->addSong(song);
        }
    }

public:
    explicit JsonPlaylist(const std::string &filename) : FilePlaylist(filename) {
        readFromFile();
    };

    ~JsonPlaylist() = default;

    void writeToFile() {
        nlohmann::json data;
        for (auto &song: songs) {
            data.push_back({
                {"artist", song.getArtist()},
                {"title", song.getTitle()},
                {"minutes", song.getDuration().getMinutes()},
                {"seconds", song.getDuration().getSeconds()},
                {"url", song.getSourceUrl()}
            });
        }

        std::ofstream file(path);
        file << data.dump(INDENTATION);
        file.close();
    }
};
