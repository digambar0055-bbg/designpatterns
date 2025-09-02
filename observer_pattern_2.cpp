#include<iostream>
#include<vector>


// How to compile - 
// g++ -std=c++17 observer_pattern_2.cpp
using namespace std;

/*
Class Hierarchy Diagram:

          +------------------+
          |    Observer      |<-----------------------------+
          +------------------+                              |
          | + update(int)    |<---------+                   |
          +------------------+         |                   |
                 ▲                    ▲                    ▲
        +----------------+   +----------------+   +---------------------+
        | ConsoleLogger  |   |  StatTracker   |   |   DigambarObserver  |
        +----------------+   +----------------+   +---------------------+
        | + update(int)  |   | + update(int)  |   | + update(int)       |
        +----------------+   +----------------+   +---------------------+

                           +----------------+
                           |    Subject     |
                           +----------------+
                           | - vector<Observer*> |
                           | - int value         |
                           | + attach()          |
                           | + setValue()        |
                           | + notifyAll()       |
                           +----------------+

Summary:
- Observer is an abstract interface with `update(int)` method.
- ConsoleLogger, StatTracker, and DigambarObserver are concrete implementations of Observer.
- Subject maintains a list of Observers and notifies them when its internal value changes.
*/


// Observer interface
class Observer {
    public:
        virtual void update(int v) = 0;
        virtual ~Observer() {};
};

// Subject to be observed
class Subject {
        std::vector<Observer*> observer;
        int value;
    public:
        void attach(Observer *obs) {
            observer.push_back(obs);
        }

        void setValue(int v) {
            value = v;
            notifyAll();
        }

        void notifyAll() {
            for (auto o: observer) {
                o->update(value);
            }
        }
};

class ConsoleLogger : public Observer {
    public:
        void update(int value) override {
            cout << "[ConsoleLogger] Value changed to: " << value << endl;
        }
};

class StatTracker : public Observer {
    public:
        void update(int value) override {
            cout << "[StatTracker] Value tracked: " << value << endl;
        }
};

// New class 
class DigambarObserver : public Observer {
    public:
        void update(int v) override {
            cout << "[DigambarObserver] Value: " << v << endl;
        }
};

int main() {
    Subject subject;
    ConsoleLogger consoleLogger;
    StatTracker statTracker;
    DigambarObserver digObserver;

    subject.attach(&consoleLogger);
    subject.attach(&statTracker);
    subject.attach(&digObserver);

    subject.setValue(10);
    subject.setValue(34);
    return 0;
}