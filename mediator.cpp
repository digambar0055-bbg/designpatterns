// Intent
// Define an object (the Mediator) that encapsulates how a set of 
// objects interact. This promotes loose coupling by preventing objects 
// from referring to each other directly and lets you vary their interaction independently.

// Real-world analogy
// Think of air traffic control.
// Planes (colleagues) don’t talk to each other directly.
// The control tower (mediator) coordinates landings, takeoffs, and communications.
// Without a mediator, every plane would need to track every other plane → chaos.

//         +----------------+
//         |    Mediator    | <--- abstract interface
//         +----------------+
//               ^
//               |
//         +-----------------+
//         | ConcreteMediator|
//         +-----------------+
//          /         \
//         /           \
// +----------+   +-----------+
// | Colleague|   | Colleague |
// +----------+   +-----------+

// Mediator → defines interface for communication.
// ConcreteMediator → implements coordination logic.
// Colleague → objects that communicate via mediator.

// Example scenario
// We’ll implement a ChatRoom mediator where users send 
// messages through the mediator, not directly.

// How to compile and run - 
// digambarmandhare@Digambars-Air design_patterns_cpp % g++ -std=c++17 mediator.cpp
// digambarmandhare@Digambars-Air design_patterns_cpp % ./a.out 
// [Alice sends]: Hi Everyonce
// [John receives from Alice]: Hi Everyonce
// [Bob receives from Alice]: Hi Everyonce
// [Bob sends]: Hello Alice!
// [Alice receives from Bob]: Hello Alice!
// [John receives from Bob]: Hello Alice!
// [John sends]: Hey folks!
// [Alice receives from John]: Hey folks!
// [Bob receives from John]: Hey folks!

#include<iostream>
#include<vector>
#include<string>
#include<memory>

class User;

class ChatMediator{
    public:
        virtual ~ChatMediator() = default;
        virtual void sendMessage(const std::string& message, User* sender) = 0;
        virtual void addUser(std::shared_ptr<User> user) = 0;
};

class User {
    std::string name;
    ChatMediator* mediator;
    
    public:
        virtual ~User() = default;
        User(const std::string& n, ChatMediator* m) : name(n), mediator(m) {}

        std::string getName() { return name; }

        virtual void send(const std::string& message) {
            std::cout << "[" << name << " sends]: " << message << std::endl;
            mediator->sendMessage(message, this);
        }

        virtual void receive(const std::string& message, const std::string& senderName) {
            std::cout << "[" << name << " receives from " << senderName << "]: "
                    << message << std::endl;
        }
};

class ChatRoom : public ChatMediator {
    std::vector<std::shared_ptr<User>> users;

    public:
        void addUser(std::shared_ptr<User> user) override {
            users.push_back(user);
        }

        void sendMessage(const std::string& message, User* sender) override {
            for (auto& user : users) {
                if (sender != user.get()) {
                    user->receive(message, sender->getName());
                }
            }
        }
};

int main() {
    ChatRoom chatRoom;

    auto alice = std::make_shared<User>("Alice", &chatRoom);
    auto john = std::make_shared<User>("John", &chatRoom);
    auto bob = std::make_shared<User>("Bob", &chatRoom);

    chatRoom.addUser(alice);
    chatRoom.addUser(john);
    chatRoom.addUser(bob);

    alice->send("Hi Everyonce");
    bob->send("Hello Alice!");
    john->send("Hey folks!");

    return 0;
}