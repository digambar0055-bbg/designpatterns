#include <iostream>
#include <memory>
#include <unordered_map>

// How to compile - g++ -std=c++17 prototype.cpp
class Shape {
    public:
        virtual std::unique_ptr<Shape> clone() const = 0;
        virtual void draw() = 0;
        virtual ~Shape() = default;
};

class Circle : public Shape {
    public:
        Circle() = default;
        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Circle> (*this);
        }

        void draw() override {
            std::cout << "Drawing a circle" << std::endl;
        }
};

class Square : public Shape {
    public:
        Square() = default;
        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Square>(*this);
        }

        void draw() override {
            std::cout << "Drawing a Square" << std::endl;
        }
};

class ShapeFactory {
    std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes;
    public:
        ShapeFactory()
        {
            prototypes["circle"] = std::make_unique<Circle>();
            prototypes["square"] = std::make_unique<Square>();
        }

        std::unique_ptr<Shape> createShape(const std::string& shape){
            if(prototypes.find(shape) != prototypes.end())
            {
                return prototypes[shape]->clone();
            }
            return nullptr;
        }
};

int main()
{
    ShapeFactory factory;
    auto shape1 = factory.createShape("circle");
    shape1->draw();

    auto shape2 = factory.createShape("square");
    shape2->draw();

    return 0;
}