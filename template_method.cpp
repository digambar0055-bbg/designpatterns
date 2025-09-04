// Template Method Pattern — Concept

// Defines the skeleton of an algorithm in a base class.
// Subclasses can override certain steps of the algorithm without changing 
// the algorithm’s overall structure.
// Useful when you have common workflows but allow customization in specific parts.
// 👉 Classic example: Data Processing Pipeline, Game AI turns, Report generation.

// How to compile and run - 
// digambarmandhare@Digambars-Air designpatterns % g++ -std=c++17 template_method.cpp 
// digambarmandhare@Digambars-Air designpatterns % ./a.out 
// CSV Pipeline:
// Reading CSV data
// Processing CSV data
// Saving data to database
// JSON pipeline:
// Reading CSV data
// Processing CSV data
// Saving data to database


#include<iostream>

class DataProcessing {
    public:
        void process() {
            readData();
            processData();
            saveData();
        }

        virtual ~DataProcessing() = default;
    protected:
        virtual void readData() = 0;
        virtual void processData() = 0;

        virtual void saveData() {
            std::cout << "Saving data to database" << std::endl;
        }
};

class CSVProcessing : public DataProcessing {
    protected:
        void readData() override {
            std::cout << "Reading CSV data" << std::endl;
        }

        void processData() override {
            std::cout << "Processing CSV data" << std::endl;
        }
};

class JSONProcessing : public DataProcessing {
    protected:
        void readData() override {
            std::cout << "Reading JSON data" << std::endl;
        }

        void processData() override {
            std::cout << "Processing JSON data" << std::endl;
        }

        void saveData() override {
            std::cout << "'Saving JSON data to file" << std::endl;
        }
};

int main() {
    CSVProcessing csv;
    JSONProcessing json;

    std::cout << "CSV Pipeline:" << std::endl;
    csv.process();

    std::cout << "JSON pipeline:" << std::endl;
    csv.process();

    return 0;
}



