# Strong Ownership vs. Observation Exercise  
**Online Classroom System**

## Goal
Reinforce your understanding of **Strong Ownership (`shared_ptr`)** vs **Observation (`weak_ptr`)** using a different but structurally identical scenario.

---

## The Scenario: The Course and the Lessons

### The Course
- Owns a collection of Lessons  
- If the Course is deleted, all its Lessons should be deleted from RAM  
- **Strong ownership**

### The Lesson
- Needs to know which Course it belongs to  
- A Lesson must **not** own the Course  
- Deleting the Course must **not** be prevented by Lessons  
- **Observation only**

---

## Your Exercise: The Classroom System

### Task
Write the C++ code for two classes:

- **Lesson**
  - Contains a `std::string title`
  - Contains a spectator pointer to a `Course`

- **Course**
  - Contains a `std::string name`
  - Contains a `std::vector` of strong pointers to `Lesson`s

---

## The Goal

Implement a `start()` method in the `Lesson` class.

Inside `start()`:

- Use `.lock()` to check if the Course still exists  
- If the Course exists, print:  
  **`Starting [Lesson] from course [Course]`**
- If the Course has been deleted, print:  
  **`Starting [Lesson] (Course Unavailable)`**

---

## Visualizing the Ownership

- Course → Lesson : **shared ownership**
- Lesson → Course : **observation only**
- No ownership cycles
- No memory leaks
- Deterministic destruction

---

## Starting Template (Assume C++11)

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Course; // Forward declaration

class Lesson {
public:
    std::string title;
    // TODO: Add a weak_ptr to a Course

    Lesson(std::string t) : title(t) {}

    void start() {
        // TODO: Use .lock() to check if the Course still exists
        // TODO: If exists: print "Starting [Lesson] from course [Course]"
        // TODO: Else: print "Starting [Lesson] (Course Unavailable)"
    }
};

class Course {
public:
    std::string name;
    // TODO: Add a vector of shared_ptr to Lessons

    Course(std::string n) : name(n) {}
    ~Course() { std::cout << "Course " << name << " deleted.\n"; }
};

int main() {
    // TODO: 1) Create a Course (shared_ptr)

    // TODO: 2) Create a Lesson (shared_ptr)

    // TODO: 3) Set up the relationship:
    //         - Course strongly owns the Lesson
    //         - Lesson observes the Course

    // TODO: 4) Call start() (should show Course name)

    // TODO: 5) Reset the Course shared_ptr

    // TODO: 6) Call start() again (should show "Course Unavailable")

    return 0;
}
