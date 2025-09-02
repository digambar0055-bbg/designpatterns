// Intent:
// Decouple an abstraction from its implementation so that the two can vary independently.

// Real-World Analogy:
// Imagine a remote control (abstraction) that works with multiple TV brands (implementations).
// You don’t want to rewrite the remote for every TV brand — instead, bridge them.

// Abstraction       →      RemoteControl
//    |
//    → RefinedAbstraction  → AdvancedRemote

// Implementation     →      Device (TV, Radio, etc.)
//    |
//    → ConcreteImplementation


// Abstraction defines the high-level control (e.g., RemoteControl)
// Implementor defines the low-level interface (e.g., Device)
// They are connected via composition, not inheritance.

// How to compile - g++ -std=c++17 bridge_pattern_3.cpp

#include<iostream>

// Implementor
class Devise {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~Devise() = default;
};

// Concrete implementor 1 
class TV : public Devise {
public:
    void turnOn() override {
        std::cout << "Turning on TV" << std::endl;
    }

    void turnOff() override {
        std::cout << "Turning off TV" << std::endl;
    }
};

// Concrete implemetor 2
class Radio : public Devise {
    public:
        void turnOn() override {
            std::cout << "Turning on Radio" << std::endl;
        }

        void turnOff() override {
            std::cout << "Turning off Radio" << std::endl;
        }
};

// Abstraction 
class RemoteControl {
    std::shared_ptr<Devise> devise;
    public:
        RemoteControl(std::shared_ptr<Devise> dev) :
            devise(std::move(dev)) {}
        virtual void turnOn() {
            devise->turnOn();
        }

        virtual void turnOff() {
            devise->turnOff();
        }

        virtual ~RemoteControl() = default;
};

// Refined Abstraction 
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(std::shared_ptr<Devise> dev) :
            RemoteControl(std::move(dev)) {}

    void mute() {
        std::cout << "Mutting the devise" << std::endl;
    }
};

int main() {
    std::shared_ptr<Devise> tv = std::make_shared<TV>();

    AdvancedRemoteControl remote(tv);
    remote.turnOn();
    remote.turnOff();
    remote.mute();

    std::shared_ptr<Devise> radio = std::make_shared<Radio>();

    AdvancedRemoteControl remoteRadio(radio);
    remoteRadio.turnOn();
    remoteRadio.turnOff();
    remoteRadio.mute();

    return 0;
}

