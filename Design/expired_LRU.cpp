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

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;

// map key存失效时间，value存song
// 链表实现 LRU

class Song {
  string name_;
  int expired_time_;
  bool is_deleted_ = false;

  Song *prev = nullptr;
  Song *next = nullptr;

 public:
  Song() {}
  Song(string name, int expired_time)
      : name_(name), expired_time_(expired_time) {}
  friend class SongList;  // 为了让SongList可以访问Song的private成员
};

class SongList {
  Song *front;  // 哨兵节点
  Song *back;
  int size_;
  int clock_ = 0;

  unordered_map<string, Song *> songs;
  map<int, Song *> expired_time;

  void EvictItems();
  void Print() {
    Song *cur = front->next;
    printf("Head -> ");
    while (cur != back) {
      printf("%s -> ", cur->name_.c_str());
      cur = cur->next;
    }
    printf("Tail\n");
  }

 public:
  SongList(int size) : size_(size) {
    front = new (Song);
    back = new (Song);
    front->next = back;
    back->prev = front;
  }
  ~SongList() {
    Song *cur = front;
    while (cur) {
      Song *next = cur->next;
      delete cur;
      cur = next;
    }
  }
  Song *Get(string name);
  void Set(string name, Song *song);
  void SetClock(int clock) {
    printf("SetClock %d\n", clock);
    clock_ = clock;
  }
};

Song *SongList::Get(string name) {
  EvictItems();
  if (songs.count(name) > 0) {
    printf("Get song %s\n", name.c_str());
    songs[name]->prev->next = songs[name]->next;
    songs[name]->next->prev = nullptr;
    songs[name]->next->prev = songs[name]->prev;
    songs[name]->next = front->next;
    songs[name]->prev = front;
    front->next = songs[name];
    songs[name]->next->prev = songs[name];
    return songs[name];
  }
  printf("song %s not exists\n", name.c_str());
  return nullptr;
};

void SongList::Set(string name, Song *song) {
  EvictItems();
  if (songs.count(name) > 0) {
    printf("song %s already exists\n", name.c_str());
    songs[name]->prev->next = songs[name]->next;
    songs[name]->next->prev = songs[name]->prev;
    expired_time.erase(songs[name]->expired_time_);
    delete songs[name];
  }

  printf("Set song %s\n", name.c_str());
  songs[name] = song;
  expired_time[song->expired_time_] = song;
  song->next = front->next;
  song->prev = front;
  front->next = song;
  song->next->prev = song;
}

void SongList::EvictItems() {
  printf("EvictItems\n");
  for (auto kv : expired_time) {
    if (kv.first > clock_) break;
    printf("delete expired song %s\n", kv.second->name_.c_str());
    Song *deletedSong = kv.second;
    deletedSong->prev->next = deletedSong->next;
    deletedSong->next->prev = deletedSong->prev;

    songs.erase(deletedSong->name_);
    expired_time.erase(deletedSong->expired_time_);
    delete deletedSong;
  }

  // printf("songs.size(): %d ~ size_: %d\n", int(songs.size()), size_);
  for (int i = songs.size() - size_; i > 0; i--) {
    printf("delete least used song %s\n", back->prev->name_.c_str());
    Song *deletedSong = back->prev;
    back->prev = deletedSong->prev;
    deletedSong->prev->next = back;

    songs.erase(deletedSong->name_);
    expired_time.erase(deletedSong->expired_time_);
    delete deletedSong;
  }
  Print();
}

int main() {
  SongList songList(5);
  Song *song1 = new Song("song1", 1);
  Song *song2 = new Song("song2", 2);
  Song *song3 = new Song("song3", 3);
  Song *song4 = new Song("song4", 4);
  Song *song5 = new Song("song5", 5);
  Song *song6 = new Song("song6", 6);
  Song *song7 = new Song("song7", 7);

  songList.Set("song1", song1);
  songList.Set("song2", song2);
  songList.Set("song3", song3);
  songList.Set("song4", song4);
  songList.Set("song5", song5);

  // Test retrieval
  assert(songList.Get("song1") == song1);
  assert(songList.Get("song2") == song2);
  assert(songList.Get("song3") == song3);
  assert(songList.Get("song4") == song4);
  assert(songList.Get("song5") == song5);

  // Test eviction of least recently used
  songList.Set("song6", song6);
  assert(songList.Get("song6") == song6);
  assert(songList.Get("song1") ==
         nullptr);  // song1 should be evicted since it was least recently used
  songList.Set("song7", song7);
  assert(songList.Get("song7") == song7);
  assert(songList.Get("song2") ==
         nullptr);  // song2 should be evicted since it was least recently used

  // Test eviction by expiration
  songList.SetClock(4);
  assert(songList.Get("song3") == nullptr);
  assert(songList.Get("song4") == nullptr);
  assert(songList.Get("song5") == song5);
  assert(songList.Get("song6") == song6);
  assert(songList.Get("song7") == song7);

  std::cout << "All tests passed!" << std::endl;

  return 0;
}
