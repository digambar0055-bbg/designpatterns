// What is the Decorator Pattern?
// Decorator allows behavior to be added to an individual object, 
// dynamically, without affecting the behavior of other objects from the same class.

// It’s useful when:
// You want to add features to objects without changing their structure.
// You want to avoid subclassing for each feature combination.

// Real-World Analogy
// Imagine a coffee shop:
// You order a basic Espresso.
// You can decorate it with Milk, Whipped Cream, or Mocha.
// Each topping wraps the base drink and adds its own cost and description.

// How to compile - g++ -std=c++17 decorator_pattern.cpp
 
#include <iostream>
#include <string>
#include <memory>

class Coffee {
    public:
        virtual std::string getDescription() const = 0;
        virtual double getCost() const = 0;
        virtual ~Coffee() = default;
};

class SimpleCoffee : public Coffee {
    public:
        std::string getDescription() const override {
            return "Simple Coffee";
        }

        double getCost() const override {
            return 1.5;
        }
};

// Decorator 
class CoffeeDecorator : public Coffee {
    protected:
        std::unique_ptr<Coffee> coffee;
    public:
        CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
};

// Concrete Decorator - Milk
class MilkDecorator : public CoffeeDecorator {
    public:
        MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

        std::string getDescription() const override {
            return coffee->getDescription() + ", Milk";
        }

        double getCost() const override {
            return coffee->getCost() + 0.5;
        }
};

// Concrete Decorator - Whip
class WhipDecorator : public CoffeeDecorator {
    public:
        WhipDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

        std::string getDescription() const override {
            return coffee->getDescription() + ", Whip";
        }

        double getCost() const override {
            return coffee->getCost() + 2.5;
        }
};

int main() {
    std::unique_ptr<Coffee> coffee = std::make_unique<SimpleCoffee>();
    coffee = std::make_unique<MilkDecorator>(std::move(coffee));
    coffee = std::make_unique<WhipDecorator>(std::move(coffee));

    std::cout << "Order: " <<  coffee->getDescription() << std::endl;
    std::cout << "Cost: " << coffee->getCost() << std::endl;
}