// Intent:
// Provide a unified interface to a set of interfaces in a subsystem.
// Facade defines a higher-level interface that makes the subsystem easier to use.

// Real-World Analogy:
// When you go to a restaurant, you don’t deal with the kitchen, chef, or cashier directly.
// You just talk to the waiter (Facade) who handles everything behind the scenes.

// Problem It Solves:
// You have a complex subsystem with many interdependent classes. 
// You want to provide a simplified interface for common operations.

// Structure 
// Client → Facade → Subsystem1, Subsystem2, Subsystem3...

// How to compile - c++ -std=c++17 facade_pattern.cpp
#include<iostream>

class DVDPlayer {
    public:
        void on() {
            std::cout << "DVD Player ON" << std::endl;
        }

        void play(const std::string& movie) {
            std::cout << "Playing movie: " 
                << movie 
                << std::endl;
        }

        void off() {
            std::cout << "DVD Player OFF" << std::endl;
        }
};

class Projector {
    public:
        void on() {
            std::cout << "Projector ON" << std::endl;
        }

        void wideScreen() {
            std::cout << "Projector in widescreen mode" << std::endl;
        }

        void off() {
            std::cout << "Projector OFF" << std::endl;
        }
};

class SoundSystem {
    public:
        void on() {
            std::cout << "SoundSystem ON" << std::endl;
        }

        void setSurroundSound() {
            std::cout << "Sound in surround mode" << std::endl;
        }

        void off() {
            std::cout << "Sound system OFF" << std::endl;
        }
};

// Facade 
class HomeTheater {
    DVDPlayer dvd;
    Projector projector;
    SoundSystem sound;

    public:
        void watchMovie(const std::string& movie) {
            std::cout << "Get ready to watch movie..." << std::endl;
            projector.on();
            projector.wideScreen();
            sound.on();
            sound.setSurroundSound();
            dvd.on();
            dvd.play(movie);
        }

        void endMovie() {
        std::cout << "Shutting movie theater down...\n";
        dvd.off();
        sound.off();
        projector.off();
    }
};

// --- Usage ---
int main() {
    HomeTheater theater;
    theater.watchMovie("Inception");
    std::cout << "------\n";
    theater.endMovie();
}