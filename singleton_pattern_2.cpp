#include<iostream>

// How to compile - g++ -std=c++17 singleton_pattern_2.cpp 
class Singleton {
    private:
        Singleton() {
            std::cout << "Singleton constructor called" << std::endl;
        }
        // Delete the copy constructor
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        Singleton(const Singleton&&) = delete;
        Singleton& operator=(const Singleton&&) = delete;

    public:
        static Singleton& getInstance(){
            static Singleton instance;
            return instance;
        }

        void doSomething() {
            std::cout << "Singleton doing something" << std::endl;
        }
};

// Usage 
int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();

    s1.doSomething();

    if (&s1 == &s2) {
        std::cout << "Confirmed its Singleton" << std::endl;
    }
    else {
        std::cout << "Not Singleton" << std::endl;
    }
}

