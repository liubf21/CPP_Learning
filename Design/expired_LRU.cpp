/**
Player’s cache

For a media player, it should show the recent played songs, could you create a
cache to manage these recents?

Requirements:
1. Cache has a limited size
2. The play URL of a song could be expired for a certain period of time(like
after 24h, the song cannot be played since the URL is expired)
3. Evict item order:
    1. Expired items
    2. Item that least used

The functions below should be implemented :

+ New(int size)
+ Get(key string) Song
+ Set(key string, Song song)
- EvictItems()

**/
 
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <cassert>

struct Song { // use struct instead of class
    std::string name;
    int expiredTime;

    Song(std::string name, int expiredTime)
        : name(std::move(name)), expiredTime(expiredTime) {}

    // No need for manual memory management
};

class SongList {
private:
    struct ListNode {
        std::shared_ptr<Song> song;
        std::shared_ptr<ListNode> prev;
        std::shared_ptr<ListNode> next;

        ListNode(std::shared_ptr<Song> s) : song(std::move(s)) {}
    };

    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
    int maxSize;
    int clock = 0;

    std::unordered_map<std::string, std::shared_ptr<ListNode>> lookup;
    std::map<int, std::shared_ptr<ListNode>> expirationMap;

    void EvictItems();

public:
    explicit SongList(int size) : maxSize(size) {
        head = std::make_shared<ListNode>(nullptr);
        tail = std::make_shared<ListNode>(nullptr);
        head->next = tail;
        tail->prev = head;
    }

    std::shared_ptr<Song> Get(const std::string& name);
    void Set(const std::string& name, std::shared_ptr<Song> song);
    void SetClock(int newClock) { clock = newClock; }
};

void SongList::EvictItems() {
    // Evict expired items
    while (!expirationMap.empty() && expirationMap.begin()->first <= clock) {
        auto expiredNode = expirationMap.begin()->second;
        expirationMap.erase(expirationMap.begin()); // use iterator to erase the element, not the key.(enhance performance)
        lookup.erase(expiredNode->song->name);

        // Remove from list
        expiredNode->prev->next = expiredNode->next;
        expiredNode->next->prev = expiredNode->prev;
    }

    // Evict least recently used items if necessary
    while (int(lookup.size()) > maxSize) {
        auto lruNode = tail->prev;
        lookup.erase(lruNode->song->name);
        expirationMap.erase(lruNode->song->expiredTime);

        // Remove from list
        lruNode->prev->next = tail;
        tail->prev = lruNode->prev;
    }
}

std::shared_ptr<Song> SongList::Get(const std::string& name) {
    EvictItems();
    if (lookup.count(name)) {
        auto node = lookup[name];

        // Move to front
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;

        return node->song;
    }
    return nullptr;
}

void SongList::Set(const std::string& name, std::shared_ptr<Song> song) {
    std::shared_ptr<ListNode> node;

    if (lookup.count(name)) {
        // Replace existing song
        node = lookup[name];
        node->song = song;
        expirationMap.erase(node->song->expiredTime);
    } else {
        // Create a new node
        node = std::make_shared<ListNode>(song);
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    lookup[name] = node;
    expirationMap[song->expiredTime] = node;
}


int main() {
    SongList songList(3);

    auto song1 = std::make_shared<Song>("song1", 1);
    auto song2 = std::make_shared<Song>("song2", 3);
    auto song3 = std::make_shared<Song>("song3", 4);
    auto song4 = std::make_shared<Song>("song4", 5);
    auto song5 = std::make_shared<Song>("song5", 6);

    // Add and retrieve songs
    songList.Set("song1", song1);
    songList.Set("song2", song2);
    songList.Set("song3", song3);
    assert(songList.Get("song1") == song1);
    assert(songList.Get("song2") == song2);
    assert(songList.Get("song3") == song3);

    // Test LRU eviction
    songList.Set("song4", song4);  // Should evict song1 (LRU)
    assert(songList.Get("song1") == nullptr);
    assert(songList.Get("song4") == song4);

    // Access song2 to make it recently used
    assert(songList.Get("song2") == song2);

    // Add a new song, which should evict the least recently used song (song3)
    songList.Set("song5", song5);
    assert(songList.Get("song3") == nullptr);
    assert(songList.Get("song5") == song5);

    // Test eviction by expiration
    songList.SetClock(4);  // Evicts song2 (expired)
    assert(songList.Get("song2") == nullptr);

    // Add the same song again
    auto song2_new = std::make_shared<Song>("song2", 7);
    songList.Set("song2", song2_new);
    assert(songList.Get("song2") == song2_new);

    // Test multiple expirations
    songList.SetClock(6);  // Should evict song4 and song5 (expired)
    assert(songList.Get("song4") == nullptr);
    assert(songList.Get("song5") == nullptr);
    assert(songList.Get("song2") == song2_new);  // song2_new should still be in the cache

    std::cout << "All tests passed!\n";
    return 0;
}
