// Prototype Pattern – Concept
// The Prototype pattern is used when creating a new object is costly, 
// and you want to create a copy (clone) of an existing object instead 
// of building it from scratch.

// Use Cases:
// When object creation is expensive (e.g., loading data, DB access, large initialization).
// When you want to avoid subclassing to create new objects.
// When you need to preserve object state during duplication.

// Key Components
// Prototype Interface: Declares a clone() method.
// Concrete Prototype: Implements the clone() method.
// Client: Uses the clone() method to duplicate objects.

// How to compile - g++ -std=c++17 prototype_pattern.cpp
#include <iostream>
#include <memory>
#include <unordered_map>

class Document {
    public:
        virtual std::unique_ptr<Document> clone() const = 0;
        virtual void print() = 0;
        virtual ~Document() = default;
};

class Resume : public Document {
    private:
        std::string name;
    public:
        Resume(const std::string& name = "Untitled Resume") : name(name) {}
        std::unique_ptr<Document> clone() const override {
            return std::make_unique<Resume>(*this);
        }

        void print() override {
            std::cout << "Resume: " << name << std::endl;
        }
};

class Invoice : public Document {
    private:
        std::string name;
    public:
        Invoice(const std::string& name = "Untitled Invoice") : name(name) {}

        std::unique_ptr<Document> clone() const override {
            return std::make_unique<Invoice>(*this);
        }

        void print() override {
            std::cout << "Invoice name: " << name << std::endl;
        }
};

class TemplateManager {
    private:
        std::unordered_map<std::string, std::unique_ptr<Document>> templates;
     
    public:
        void registerTemplate(const std::string& type, std::unique_ptr<Document> prototype) {
            templates[type] = std::move(prototype);
        }

        std::unique_ptr<Document> createFromTemplate(const std::string &type) const {
            auto it = templates.find(type);
            if(it != templates.end())
            {
                return it->second->clone();
            }

            return nullptr;
        }
};

int main() {
    TemplateManager manager;

    manager.registerTemplate("resume", std::make_unique<Resume>("Software Engineer Resume"));
    manager.registerTemplate("invoice", std::make_unique<Invoice>("DMA Corp"));

    auto doc1 = manager.createFromTemplate("resume");
    auto doc2 = manager.createFromTemplate("invoice");

    doc1->print();
    doc2->print();
}