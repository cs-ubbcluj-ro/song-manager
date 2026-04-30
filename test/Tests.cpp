#include "Tests.h"
#include <cassert>
#include "controller/Controller.h"
#include "domain/DynamicVector.h"
#include "domain/JsonPlaylist.h"
#include "domain/LinkedList.h"
#include "repository/Repository.h"
#include "domain/Playlist.h"
#include <vector>

void Tests::testSong() {
    Duration d{4, 54};
    Song s{"Ed Sheeran", "I see fire", d, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
    assert(s.getArtist() == "Ed Sheeran");
    assert(s.getTitle() == "I see fire");
    assert(s.getSourceUrl() == "https://www.youtube.com/watch?v=2fngvQS_PmQ");
    assert(s.getDuration().getMinutes() == 4);
    assert(s.getDuration().getSeconds() == 54);
}

void Tests::testDynamicVector() {
    DynamicVector<int> v1{2};
    v1.add(10);
    v1.add(20);
    assert(v1.getSize() == 2);
    assert(v1[1] == 20);
    v1[1] = 25;
    assert(v1[1] == 25);
    v1.add(30);
    assert(v1.getSize() == 3);

    DynamicVector<int> v2{v1};
    assert(v2.getSize() == 3);

    DynamicVector<int> v3 = v1;
    assert(v3[0] == 10);

    // test iterator
    DynamicVector<int>::iterator it = v1.begin();
    assert(*it == 10);
    assert(it != v1.end());
    ++it;
    assert(*it == 25);
    ++it;
    assert(*it == 30);
    ++it;
    assert(it == v1.end());
}

void Tests::testRepository() {
    Repository repo{};
    Song s{"Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
    repo.addSong(s);
    Song res = repo.findByArtistAndTitle("Ed Sheeran", "I see fire").value();
    assert(res.getTitle() == s.getTitle() && res.getArtist() == s.getArtist());
    assert(repo.findByArtistAndTitle("Ed Sheeran", "").has_value() == false);

    std::vector<Song> songs = repo.getSongs();
    assert(songs.size() == 1);
}

void Tests::testPlaylist() {
    Playlist playlist{};
    Song s1{"Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
    Song s2{"Two Steps From Hell", "Heart of Courage", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0"};
    playlist.addSong(s1);
    playlist.addSong(s2);

    assert(playlist.isEmpty() == false);
    playlist.next();
    assert(playlist.getCurrentSong().value().getArtist() == s2.getArtist());

    playlist.next();
    assert(playlist.getCurrentSong().value().getArtist() == s1.getArtist());
}

void Tests::testController() {
    Repository repo{};
    Controller ctrl{repo};
    ctrl.addSongToRepository("Ed Sheeran", "I see fire", 4, 54, "https://www.youtube.com/watch?v=2fngvQS_PmQ");
    ctrl.addSongToRepository("Two Steps From Hell", "Heart of Courage", 8, 12,
                             "https://www.youtube.com/watch?v=XYKUeZQbMF0");
    Song s{"Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
    ctrl.addSongToPlaylist(s);
    ctrl.addAllSongsByArtistToPlaylist("Two Steps From Hell");

    assert(ctrl.getRepo().getSongs().size() == 2);

    Playlist list = ctrl.getPlaylist();
    assert(list.isEmpty() == false);
    assert(list.getCurrentSong().value().getArtist() == "Ed Sheeran");
}

void Tests::testLinkedList() {
    LinkedList<int> list{};
    list.add(10);
    list.add(20);
    assert(list.getSize() == 2);
    assert(list[0] == 10);
    assert(list[1] == 20);
}

std::string Tests::generateRandomFilename(const std::string &prefix) {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(now);
    std::string path = prefix + "_" + std::to_string(timestamp) + ".json";
    return path;
}

void Tests::testJsonPlaylist() {
    auto path = generateRandomFilename("playlist");
    JsonPlaylist playlist{path};
    Song s1{"Ed Sheeran", "I see fire", Duration{4, 54}, "https://www.youtube.com/watch?v=2fngvQS_PmQ"};
    Song s2{"Two Steps From Hell", "Heart of Courage", Duration{8, 12}, "https://www.youtube.com/watch?v=XYKUeZQbMF0"};
    playlist.addSong(s1);
    playlist.addSong(s2);
    playlist.writeToFile();

    JsonPlaylist playlist2{path};
    assert(playlist2.getCurrentSong().value().getArtist() == "Ed Sheeran");
    playlist2.next();
    assert(playlist2.getCurrentSong().value().getArtist() == "Two Steps From Hell");
}

void Tests::testAll() {
    testSong();
    testDynamicVector();
    testRepository();
    testController();
    testPlaylist();
    testLinkedList();
    testJsonPlaylist();
}
