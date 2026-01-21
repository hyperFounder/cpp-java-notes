#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Artist; // Forward declaration

class Song {
public:
    std::string title;
    // TODO: Add a weak_ptr to an Artist
    std::weak_ptr<Artist> currentArtist;
    
    Song(std::string t) : title(t) {}

    void play() {
      if (auto artist = currentArtist.lock()){
	cout << "Playing [Song] by [Artist]" << endl;
        // TODO: Implement the .lock() logic here
      }
	else { // Shared count = 0. 
	  cout << "Playing [Song] (Artist Unknown)";
	}
    }
};

class Artist {
public:
    std::string name;
    // TODO: Add a vector of shared_ptr to Songs
    vector<shared_ptr<Song>> songs;
    
    Artist(std::string n) : name(n) {}
    ~Artist() { std::cout << "Artist " << name << " deleted.\n"; }
};

int main() {
    // 1. Create an Artist (Shared Ownership)
  auto artist = make_shared<Artist>("Julio Iglesias"); // artist is a shared pointer to the Artist object
    
    // 2. Create a Song (Shared Ownership)

    auto song = make_shared<Song>("Cada dia Mas - Julio Iglesias"); // song is a shared pointer to the Song object "Cada dia mas"
    
    // 3. Set up the relationship (Artist owns Song, Song observes Artist)
    artist->songs.push_back(song);
    song->currentArtist = artist;
    
    // 4. Call play() - Should show Artist name
    song->play();
    
    // 5. Reset the Artist pointer
    artist.reset();
    
    // 6. Call play() again - Should show "Artist Unknown"
    song->play();
    
    return 0;
}
