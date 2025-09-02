#include<iostream>
#include<functional>

using namespace std;

// Base class
class Shape {
    public:
        virtual void draw() = 0;
        virtual ~Shape() {}
};

// Concrete class 
class Circle : public Shape {
    public:
        void draw () override {
            cout << "Drawing circle" << endl;             
        }
};

class Square : public Shape {
    public:
        void draw() override {
            cout << "Drawing square" << endl;
         }
};

// Registry based factory
class ShapeFactory {
    public:
        using CreatorFunc = std::function<std::unique_ptr<Shape>()>;
        static ShapeFactory& instance() {
            static ShapeFactory factory;
            return factory;
        }

        void registerShape(const std::string &name, CreatorFunc creator) {
            creators[name] = creator;
        }

        std::unique_ptr<Shape> create(const std::string &name) {
            auto it = creators.find(name);
            if(it != creators.end()) {
                return (it->second)();
            }
            return nullptr;
        }
    private:
        std::unordered_map<std::string, CreatorFunc> creators;
};

// Auto-register helper 
template<typename T>
class ShapeRegistrar {
    public:
        ShapeRegistrar(const std::string& name) {
            ShapeFactory.instance().registerShape(name, [](){
                return std::make_unique<T>();
            });
        }
};

// Register classes
static Shape