#include <memory> 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ChatRoom;

class User{
public:
  string name;
  weak_ptr<ChatRoom> currentRoom;
  User(string n) : name(n) {}

  void send(string msg){
    if (auto room = currentRoom.lock()){
      // .lock() checks wehther the strong_count ==0. If yes, then return nullptr and says not valid room.
      // else, it incrementes the shared_count by 1, return a shared_ptr (temp) to the object
      cout << name << "sends to room: " << msg << endl;
    }else{
      cout << name << "I'm not in a valid room" << endl;
    }
  }
};

class ChatRoom{
public:
  vector<shared_ptr<User>> members;
  ~ChatRoom() {cout << "ChatRoom destroyed" << endl;}
};

int main(){
  auto myRoom = make_shared<ChatRoom>(); // myRoom pointer is a shared owner of the ChatRoom object address
  auto alice = make_shared<User>("Alice"); // alice pointer is a shared owner of the Alice User object

  myRoom->members.push_back(alice);
  alice->currentRoom = myRoom;

  alice->send("Hello everyone");
  myRoom.reset(); // Release myRoom pointer to stop pointing at ChatRoom. Decrement shared count. If shared_count =0, then deconstructor called (Deallocate the ChatRoom object). The control block stays in RAM.
  alice->send("Is anyone there?");
  return 0;
}

