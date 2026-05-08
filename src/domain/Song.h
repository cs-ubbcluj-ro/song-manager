#pragma once

#include <iostream>
#include <utility>
#include <string>

class Duration {
private:
    double minutes = 0;
    double seconds = 0;

public:
    Duration() = default;

    Duration(const double min, const double sec) : minutes{min}, seconds{sec} {
    }

    [[nodiscard]] double getMinutes() const { return minutes; }
    [[nodiscard]] double getSeconds() const { return seconds; }
};

class Song {
private:
    std::string artist;
    std::string title;
    Duration duration{};
    std::string sourceUrl; // YouTube Link

public:
    // default constructor for a song
    Song() = default;

    // constructor with parameters
    Song(std::string a, std::string t, const Duration &d, std::string s)
        : artist{std::move(a)}, title{std::move(t)}, duration{d}, sourceUrl{std::move(s)} {
    }

    [[nodiscard]] std::string getTitle() const { return title; }
    [[nodiscard]] std::string getArtist() const { return artist; }
    [[nodiscard]] std::string getSourceUrl() const { return sourceUrl; }
    [[nodiscard]] Duration getDuration() const { return duration; }

    // Plays the current song: the page corresponding to the source link is opened in a browser.
    void play() const;

    bool operator==(const Song &s) const;
};
