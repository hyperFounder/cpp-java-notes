# Strong Ownership vs. Observation Exercise  
**Music Streaming Service (Spotify-style)**

## Goal
Test your understanding of **Strong Ownership (`shared_ptr`)** vs **Observation (`weak_ptr`)** using a clean, realistic model.

---

## The Scenario: The Artist and the Songs

### The Artist
- Owns a collection of Songs  
- If the Artist is deleted from the system, their Songs should also be deleted from RAM  
- **Strong ownership**

### The Song
- Needs to know who its Artist is  
- A Song must **not** own the Artist  
- Deleting the Artist must **not** be prevented by Songs  
- **Observation only**

---

## Your Exercise: The Music Service

### Task
Write the C++ code for two classes:

- **Song**
  - Contains a `std::string title`
  - Contains a spectator pointer to an `Artist`

- **Artist**
  - Contains a `std::string name`
  - Contains a `std::vector` of strong pointers to `Song`s

---

## The Goal

Implement a `play()` method in the `Song` class.

Inside `play()`:

- Use `.lock()` to check if the Artist still exists  
- If the Artist exists, print:  
  **`Playing [Song] by [Artist]`**
- If the Artist has been deleted, print:  
  **`Playing [Song] (Artist Unknown)`**

---

## Visualizing the Ownership

- Artist → Song : **shared ownership**
- Song → Artist : **observation only**
- No cycles
- No memory leaks
- Deterministic destruction

---

## Starting Template (Assume C++11)

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Artist; // Forward declaration

class Song {
public:
    std::string title;
    // TODO: Add a weak_ptr to an Artist

    Song(std::string t) : title(t) {}

    void play() {
        // TODO: Use .lock() to check if the Artist still exists.
        // TODO: If exists: print "Playing [Song] by [Artist]"
        // TODO: Else: print "Playing [Song] (Artist Unknown)"
    }
};

class Artist {
public:
    std::string name;
    // TODO: Add a vector of shared_ptr to Songs

    Artist(std::string n) : name(n) {}
    ~Artist() { std::cout << "Artist " << name << " deleted.\n"; }
};

int main() {
    // TODO: 1) Create an Artist (shared_ptr)

    // TODO: 2) Create a Song (shared_ptr)

    // TODO: 3) Set up the relationship:
    //         - Artist strongly owns the Song (push into vector)
    //         - Song observes the Artist (assign weak_ptr from shared_ptr)

    // TODO: 4) Call play() (should show Artist name)

    // TODO: 5) Reset the Artist shared_ptr

    // TODO: 6) Call play() again (should show "Artist Unknown")

    return 0;
}

```
