#pragma once

#include <iostream>

class Duration {
private:
    double minutes = 0;
    double seconds = 0;

public:
    Duration() = default;

    Duration(const double min, const double sec) : minutes{min}, seconds{sec} {
    }

    double getMinutes() const { return minutes; }
    double getSeconds() const { return seconds; }
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
    Song(const std::string &a, const std::string &t, const Duration &d, const std::string &s)
        : artist{a}, title{t}, duration{d}, sourceUrl{s} {
    }

    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getSourceUrl() const { return sourceUrl; }
    Duration getDuration() const { return duration; }

    // Plays the current song: the page corresponding to the source link is opened in a browser.
    void play() const;
};
