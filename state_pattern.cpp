// Concept

// The State pattern allows an object to change its behavior when its 
// internal state changes.
// Instead of using big if/else or switch statements, each state is 
// encapsulated in a separate class.
// The object delegates behavior to the current state class.
// Think of it like a finite state machine (FSM): a machine with 
// multiple states, and transitions between them.

// Real-world Analogy

// Imagine a cricket match scoreboard:
// It can be in First Innings state or Second Innings state.
// Depending on the state, the scoreboard displays runs differently 
// (e.g., target available in 2nd innings).
// Instead of if (firstInnings) ... else ..., we just swap the "state object".


// State Pattern — Concept
// The State pattern lets an object change its behavior when its internal state changes.
// Instead of using long if-else or switch statements, you represent each state as a 
// separate class.
// The object delegates behavior to the current state object.

// Useful when:
// An object has multiple states, and its behavior changes based on state.
// You want to avoid complex conditionals.

// How to compile and run - 
// digambarmandhare@Digambars-Air designpatterns % g++ -std=c++17 state_pattern.cpp 
// digambarmandhare@Digambars-Air designpatterns % ./a.out 
// Green light → Cars can go
// Yellow light → Prepare to stop
// Red light → Cars must stop
// Green light → Cars can go
// Yellow light → Prepare to stop
// Red light → Cars must stop

#include<iostream>
#include<memory>

class State;
class TrafficLight;

class TrafficLight {
    private:
        std::unique_ptr<State> state;
    public:
        TrafficLight(std::unique_ptr<State> initialState);
        void setState(std::unique_ptr<State> newState);
        void request();
};

class State {
    public:
        virtual ~State() = default;
        virtual void handle(TrafficLight& light) = 0;
};

// Concrete State
class GreenState : public State {
    public:
        void handle(TrafficLight& light) override;
};

class YellowState : public State {
    public:
        void handle(TrafficLight& light) override;
};

class RedState : public State {
    public:
        void handle(TrafficLight& light) override;
};

// Implementation of Traffic light 
TrafficLight::TrafficLight(std::unique_ptr<State> initialState)
 : state(std::move(initialState)) { }

 void TrafficLight::setState(std::unique_ptr<State> newState) {
    state = std::move(newState);
 }

 void TrafficLight::request() {
    state->handle(*this);
}

// Implementation of States
void GreenState::handle(TrafficLight& light) {
    std::cout << "Green light → Cars can go\n";
    light.setState(std::make_unique<YellowState>());
}

void YellowState::handle(TrafficLight& light) {
    std::cout << "Yellow light → Prepare to stop\n";
    light.setState(std::make_unique<RedState>());
}

void RedState::handle(TrafficLight& light) {
    std::cout << "Red light → Cars must stop\n";
    light.setState(std::make_unique<GreenState>());
}

// Client
int main() {
    TrafficLight light(std::make_unique<GreenState>());

    for (int i = 0; i < 6; i++) {
        light.request();
    }
    return 0;
}