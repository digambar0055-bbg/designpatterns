#include<iostream>
#include<vector>
#include<string>

class Observer;

class Subject {
    private:
        std::vector<Observer*> observer;
        int state;
    public:
        void attach(Observer* obs) {
            observer.push_back(obs);
        }

        void setState(int s) {
            state = s;
            notifyAll();
        }

        int getState() const {
            return state;
        }

        void notifyAll();
};

// Observer Interface
class Observer {
    public:
        virtual void update(Subject *subject) = 0;
};

class ConcreteObserver : public Observer {
    private:
        std::string name;
    
    public:
        ConcreteObserver(const std::string &n) : name(n) {}

        void update(Subject *subject) override {
            std::cout << name << "Received update. New state: " << subject->getState() << std::endl;
        }
};

// Defination of notifyAll
void Subject::notifyAll()
{
    for (auto obs : observer) {
        obs->update(this);
    }
}

int main() {
    return 0;
}