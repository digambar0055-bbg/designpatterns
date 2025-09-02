// Intent:
// Convert the interface of a class into another interface clients expect. 
// Adapter lets classes work together that couldn’t otherwise due to incompatible interfaces.

// Real-world Analogy:
// Think of a travel adapter plug—your charger (client) works with it even if 
// the wall socket (adaptee) is of a different shape.

// When to Use:
//  - You want to use an existing class but its interface doesn't match what you need.
//  - You want to create a reusable class that cooperates with unrelated or unforeseen classes.

// Key Components:
// Target – The interface expected by the client.
// Adaptee – The existing class with a different interface.
// Adapter – Bridges the gap between Target and Adaptee.


#include<iostream>
#include<cmath>

using namespace std;

class RoundPeg {
public:
    virtual double getRadius() const = 0;
    virtual ~RoundPeg() = default;
};

class SimpleRoundPeg : public RoundPeg {
    double radius;
public:
    SimpleRoundPeg(double r) : radius(r) {}
    double getRadius() const override {
        return radius;
    }
};

// Adaptee (incompatible interface)
class SquarePeg {
    double width;
public:
    SquarePeg(double w) : width(w) {}
    double getWidth() const {
        return width;
    }
};

class SquarePegAdapter : public RoundPeg {
    SquarePeg& squarePeg;
public:
    SquarePegAdapter(SquarePeg& peg) : squarePeg(peg) {}
    double getRadius() const override {
        // Whatever logic you have
        return (squarePeg.getWidth() * std::sqrt(2)) / 2.0;
    }
};

// RoundHole
class RoundHole {
    double radius;
public:
    RoundHole(double r) : radius(r) {}

    bool fits(RoundPeg& peg) const {
        return peg.getRadius() <= radius;
    }
};

int main(){
    RoundHole hole(5.0);
    SimpleRoundPeg reoundPeg(5.0);

    SquarePeg smallSquarePeg(5.0);
    SquarePeg largeSquarePeg(10.0);

    SquarePegAdapter smallAdapter(smallSquarePeg);
    SquarePegAdapter largeSquarePeg(largeSquarePeg);

    std::cout << std::boolalpha;
    std::cout << "Round peg fits? " << hole.fits(roundPeg) << "\n";
    std::cout << "Small square peg fits via adapter? " << hole.fits(smallAdapter) << "\n";
    std::cout << "Large square peg fits via adapter? " << hole.fits(largeAdapter) << "\n";

    return 0;
}
