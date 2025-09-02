// Intent:
// Compose objects into tree-like structures to represent part-whole hierarchies.
// Clients can treat individual objects and compositions uniformly.

// Real-World Analogy:
// Think of a file system:
// A File is a leaf.
// A Folder can contain both files and other folders.
// But whether it's a file or folder, you can open, delete, or 
// display both using the same interface.

// Component (e.g., FileSystemObject)
//  ├── Leaf (e.g., File)
//  └── Composite (e.g., Folder) → has children of type Component


#include<iostream>
#include<vector>

// Component
class FileSystemEntity {
    public:
        virtual void showDetails(int indent = 0) const = 0;
        virtual ~FileSystemEntity() = default;
};

// Leaf
class File : public FileSystemEntity {
        std::string name;
    public:
        File(std::string n) : name(std::move(n)) {}

        void showDetails(int indent = 0) const override {
            std::cout  << std::string(indent, ' ') << "- File: " <<
                name << std::endl;
        }
};

// Composite
class Folder : public FileSystemEntity {
    std::string name;
    std::vector<std::shared_ptr<FileSystemEntity>> children;

    public:
        Folder(std::string n) : name(std::move(n)) {}
        void add(const std::shared_ptr<FileSystemEntity>& entity) {
            children.push_back(entity);
        }
        void showDetails(int indent = 0) const override {
            std::cout << std::string(indent, ' ') << name << ": " << std::endl;
            for (const auto& child: children) {
                child->showDetails(indent + 2);
            }
        }
};

int main() {
    auto file1 = std::make_shared<File>("Resume.pdf");
    auto file2 = std::make_shared<File>("Photo.jpg");
    auto file3 = std::make_shared<File>("Design.docx");

    auto workFolder = std::make_shared<Folder>("Work");
    workFolder->add(file1);
    workFolder->add(file3);

    auto homeFolder = std::make_shared<Folder>("Home");
    homeFolder->add(file2);
    homeFolder->add(workFolder);

    homeFolder->showDetails();
}