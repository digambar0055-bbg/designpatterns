// Builder Design Pattern (Creational Pattern)
// Intent
// When object construction is complex and involves many steps, Builder pattern helps 
// encapsulate the construction logic.
// Allows step-by-step creation of a product with different representations (or variants).

// When to Use
// You want to create a complex object (e.g., a House, Car, Computer) step by step.
// The construction process must allow different representations.
// You want to reuse the same construction process for different objects.

// Real-life Analogy:
// Think of a Restaurant:
// You tell the waiter how you want your burger built 
// (e.g., with cheese, no onion, extra sauce).
// The builder (chef) assembles the burger step-by-step.

// Use Case Example:
// Imagine you're building a complex "Product" like a House with 
// multiple optional parts — walls, roof, garden, swimming pool, etc. You don’t want to 
// call a constructor with a dozen parameters.
// Builder pattern helps you build such objects step-by-step.

#include<iostream>
#include<string>

using namespace std;

class House {
    public:
        void setWalls(const string& walls) { this->walls = walls; }
        void setRoof(const string& roof) { this->roof = roof; }
        void setGarden(const string& garden) { this->garden = garden; }
        void showHouse() const {
            cout << "Walls: " << walls << endl;
            cout << "Roof: " << roof << endl;
            cout << "Garden: " << garden << endl;
        }
    private:
        string walls, roof, garden;
};

// Builder interface
class HouseBuilder {
    public:
        virtual void buildWalls() = 0;
        virtual void buildRoof() = 0;
        virtual void buildGarden() = 0;
        virtual House* getHouse() = 0;
        virtual ~HouseBuilder() = default;
};

// Concrete builder 
class LuxuryHouseBuilder : public HouseBuilder {
    private:
        House* house;
    public:
        LuxuryHouseBuilder() { house = new House(); }
        
        void buildWalls() override {
            house->setWalls("Marbel walls"); 
        }

        void buildRoof() override {
            house->setRoof("Glass Roof");
        }

        void buildGarden() override {
            house->setGarden("Luxury Garden with fountain");
        }

        House* getHouse() override {
            return house;
        }
};

// Director
class Engineer {
    private:
        HouseBuilder* builder;
    public:
        Engineer(HouseBuilder* b) : builder(b) {}

        void constructHouse() {
            builder->buildWalls();
            builder->buildRoof();
            builder->buildGarden();
        }

        House* getHouse() {
            return builder->getHouse();
        }
};

// Main
int main() {
    LuxuryHouseBuilder builder;
    Engineer engineer(&builder);

    engineer.constructHouse();
    House *house = engineer.getHouse();
    house->showHouse();

    delete house;
    return 0;
}


// Key Takeaways:
// Role	            Description
// Product	        The complex object being built (House)
// Builder	        Interface with steps to build the product
// ConcreteBuilder	Implements the building steps
// Director	        Controls the order of steps (optional)

