// Intent:
// Separate algorithms from the objects on which they operate.
// This lets you add new operations to existing object structures 
// without modifying the structures.

// Example Context:
// You have a file system composed of Files and Directorys.
// You want to perform operations like displaying names or 
// counting files — without changing the actual File or Directory 
// classes every time you need a new operation.



#include <iostream>
#include <vector>

// How to compile - g++ -std=c++17 visitor.cpp

// Forward declarations for Visitor to know these types
class File;
class Directory;

 // Visitor Interface
 class Visitor{
    public:
        virtual void visit(File *file) = 0;
        virtual void visit(Directory *directory) = 0;
        virtual ~Visitor() = default; 
 };

 // Element interface
 class Element{
    public:
        virtual void accept(Visitor *visitor) = 0;
        virtual ~Element() = default;
 };

// Concrete Element : File
 class File : public Element{
    private:
        std::string name;
    public:
        explicit File(std::string name) : name(std::move(name)) {}
                
        void accept(Visitor *visitor) override {
            visitor->visit(this);
        }

        std::string getName() const { return name;  }
 };

// Concrete Element : Directory
class Directory : public Element{
    private:
        std::string name;
        std::vector<Element*> elements;
    public:
        explicit Directory(std::string name) : name(std::move(name)) {}

        void addElement(Element *element)
        {
            elements.push_back(element);
        }

        void accept(Visitor *visitor)
        {
            visitor->visit(this);
            for(Element *element : elements)
            {
                element->accept(visitor);
            }
        }

        std::string getName() const { return name; }
};

// Define concrete visitors
class DisplayName : public Visitor{
    public:
        void visit(File *file) override {
            std::cout << "File Name: " << file->getName() << std::endl;
        }

        void visit(Directory *directory) override {
            std::cout << "Directory Name: " << directory->getName() << std::endl; 
        }
};

// Concrete Visitor : Display file count
class CountFileVisitor : public Visitor{
        int fileCount = 0;
    public:
        void visit(File *file) override {
            fileCount++;
        }

        void visit(Directory *Directory) override {
            std::cout << "File count not applicable for Directroy";
        }

        int getFileCount() const {
            return fileCount;
        }
};

int main()
{
    // Create File system structure
    Directory root("root");
    File file1("file1");
    File file2("file2");

    Directory subDir("subDir");
    File file3("file3");

    // Build hierarchy
    root.addElement(&file1);
    root.addElement(&file2);
    subDir.addElement(&file3);
    root.addElement(&subDir);

    // Use display 
    DisplayName displayVisitor;
    root.accept(&displayVisitor);
}
