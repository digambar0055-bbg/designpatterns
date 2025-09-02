// Intent
// Encapsulate a request as an object, thereby letting you:
// Parameterize clients with different requests.
// Queue, log, and undo/redo operations.
// Decouple the sender (invoker) from the receiver.

// Problem
// A GUI button, a menu item, or a remote control shouldn’t know how to 
// perform the action — it should only trigger it.
// You want undo/redo support.
// You want to log or queue requests for later execution

// Solution
// Define a Command interface with an execute() method.
// Each ConcreteCommand knows the Receiver and calls the right operation on it.
// An Invoker triggers the command without knowing what it does.
// The Client wires up the invoker with the command(s).

// Roles:
// Command: Abstract interface (execute).
// ConcreteCommand: Implements execute by calling receiver’s action.
// Receiver: Knows how to perform the actual operation.
// Invoker: Asks the command to carry out the request.
// Client: Creates command and sets it in the invoker.

// How to comiple and execute - 
// digambarmandhare@Digambars-Air design_patterns_cpp % g++ -std=c++17 command.cpp 
// digambarmandhare@Digambars-Air design_patterns_cpp % ./a.out 
// Light is ON
// Light is OFF

#include<iostream>
#include<memory>

class Command {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
};

class Light {
    public:
        void turnOn() {
            std::cout << "Light is ON" << std::endl;
        }

        void turnOff() {
            std::cout << "Light is OFF" << std::endl;
        }
};

class LightOnCommand : public Command {
    Light& light;
    public:
        LightOnCommand(Light& l) : light(l) {}
        void execute () override {
            light.turnOn();
        }
};


class LightOffCommand : public Command {
    Light& light;
    public:
        LightOffCommand(Light& l) : light(l) {}
        void execute () override {
            light.turnOff();
        }
};

class RemoteControl {
    std::unique_ptr<Command> command;
    public:
        void setCommand(std::unique_ptr<Command> cmd) {
            command = std::move(cmd);
        }

        void pressButton() {
            if (command) command->execute();
        }
};

int main() {
    Light livingRoomLight;

    RemoteControl remote;

    remote.setCommand(std::make_unique<LightOnCommand>(livingRoomLight));
    remote.pressButton();

    remote.setCommand(std::make_unique<LightOffCommand>(livingRoomLight));
    remote.pressButton();
}