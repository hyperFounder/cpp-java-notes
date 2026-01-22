#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<int> a = make_unique<int>(42);
    unique_ptr<int> b = make_unique<int>(7);

    cout << *a << " " << *b << endl; // 42 7

    b = std::move(a);  // MOVE ASSIGNMENT

    // After this:
    // - b now owns the 42
    // - a is nullptr
    // - the old 7 is destroyed

    if (!a) cout << "a is null\n";
    cout << *b << endl; // 42
}
