#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Course; // forward declaration

class Lesson {
public:
    std::string title;
    std::weak_ptr<Course> currentCourse;

    Lesson(const std::string& t) : title(t) {}
    void start(); // declared only
};

class Course {
public:
    std::string name;
    std::vector<std::shared_ptr<Lesson>> lessons;

    Course(const std::string& n) : name(n) {}
    ~Course() { std::cout << "Course " << name << " deleted.\n"; }
};

// define AFTER Course is complete
void Lesson::start() {
    if (auto course = currentCourse.lock()) {
        std::cout << "Starting " << title << " from course " << course->name << "\n";
    } else {
        std::cout << "Starting " << title << " (Course Unavailable)\n";
    }
}

int main() {
    auto course = std::make_shared<Course>("Operating Systems");
    auto lesson = std::make_shared<Lesson>("Processes & Scheduling");

    course->lessons.push_back(lesson);
    lesson->currentCourse = course;

    lesson->start();
    course.reset();
    lesson->start();
}
