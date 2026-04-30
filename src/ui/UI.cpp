#include "UI.h"
#include <string>

using namespace std;

void UI::printMenu() {
    cout << endl;
    cout << "1 - Manage song repository." << endl;
    cout << "2 - Manage playlist." << endl;
    cout << "0 - Exit." << endl;
}

void UI::printRepositoryMenu() {
    cout << "Possible commands: " << endl;
    cout << "\t 1 - Add song." << endl;
    cout << "\t 2 - Display all." << endl;
    cout << "\t 0 - Back." << endl;
}

void UI::printPlayListMenu() {
    cout << "Possible commands: " << endl;
    cout << "\t 1 - Add song." << endl;
    cout << "\t 2 - Add songs by artist." << endl;
    cout << "\t 3 - Play." << endl;
    cout << "\t 4 - Next." << endl;
    cout << "\t 0 - Back." << endl;
}

void UI::addSongToRepo() {
    cout << "Enter the artist: ";
    std::string artist;
    getline(cin, artist);
    cout << "Enter the title: ";
    std::string title;
    getline(cin, title);
    double minutes = 0, seconds = 0;
    cout << "Enter the duration: " << endl;
    cout << "\tMinutes: ";
    cin >> minutes;
    cin.ignore();
    cout << "\tSeconds: ";
    cin >> seconds;
    cin.ignore();
    cout << "Youtube link: ";
    std::string link;
    getline(cin, link);

    this->ctrl.addSongToRepository(artist, title, minutes, seconds, link);
}

void UI::displayAllSongsRepo() {
    const std::vector<Song> songs = this->ctrl.getRepo().getSongs();
    if (songs.empty()) {
        cout << "There are no songs in the repository." << endl;
        return;
    }

    for (const auto& s : songs) {
        Duration d = s.getDuration();
        cout << s.getArtist() << " - " << s.getTitle() << "; " << d.getMinutes() << ":" << d.getSeconds() << endl;
    }
}

void UI::addSongToPlaylist() {
    cout << "Enter the artist: ";
    std::string artist;
    getline(cin, artist);
    cout << "Enter the title: ";
    std::string title;
    getline(cin, title);

    const auto songOptional = ctrl.getRepo().findByArtistAndTitle(artist, title);
    // search for the song in the repository
    if (!songOptional.has_value()) {
        cout << "There are no songs with the given query in the repository." << endl;
        return;
    }

    ctrl.addSongToPlaylist(songOptional.value());
}

void UI::addAllSongsByArtistToPlaylist() {
    cout << "Enter the artist: ";
    std::string artist;
    getline(cin, artist);

    ctrl.addAllSongsByArtistToPlaylist(artist);
}

void UI::playSongsFromPlaylist() {
    if (ctrl.getPlaylist().isEmpty()) {
        cout << "Nothing to play, the playlist is empty." << endl;
        return;
    }

    auto songOptional = ctrl.getPlaylist().getCurrentSong();
    if (!songOptional.has_value()) {
        cerr << "There are no songs in the playlist." << endl;
        return;
    }

    const Song &song = songOptional.value();
    cout << "Now playing: " << song.getArtist() << " - " << song.getTitle() << endl;
    ctrl.startPlaylist();
}

void UI::nextSongFromPlaylist() {
    ctrl.getPlaylist().next();
}

void UI::run() {
    while (true) {
    mainMenu:
        printMenu();
        int command{0};
        cout << "Input the command: ";
        cin >> command;
        cin.ignore();
        if (command == 0)
            break;

        // repository management
        if (command == 1) {
            while (true) {
                printRepositoryMenu();
                int commandRepo{0};
                cout << "Input the command: ";
                cin >> commandRepo;
                cin.ignore();
                switch (commandRepo) {
                    case 0:
                        goto mainMenu;
                    case 1:
                        addSongToRepo();
                        break;
                    case 2:
                        displayAllSongsRepo();
                        break;
                    default:
                        cout << "\nUnrecognized command." << endl;
                }
            }
        }

        // playlist management
        if (command == 2) {
            while (true) {
                printPlayListMenu();
                int commandPlaylist{0};
                cout << "Input the command: ";
                cin >> commandPlaylist;
                cin.ignore();
                switch (commandPlaylist) {
                    case 0:
                        goto mainMenu;
                    case 1:
                        addSongToPlaylist();
                        break;
                    case 2:
                        addAllSongsByArtistToPlaylist();
                        break;
                    case 3:
                        playSongsFromPlaylist();
                        break;
                    case 4:
                        nextSongFromPlaylist();
                        break;
                    default:
                        cout << "\nUnrecognized command." << endl;
                }
            }
        }
    }
}
