#include<iostream>

using namespace std;

// Implementor
class Formatter {
    public:
        virtual std::string format(const std::string &title, const std::string& body) = 0;
        virtual ~Formatter() = default;
};

// Concrete Implementor
class HTMLFormatter : public Formatter {
    public:
        std::string format(const std::string& title, const std::string& body) override {
            return "<html><h1>" + title + "</h1><p>" + body + "</p></html>";
        }
};

class JSONFormatter : public Formatter {
    public:
        std::string format(const std::string& title, const std::string& body) override {
            return "{\"title\": \"" + title + "\", \"body\": \"" + body + "\"}";
        }
};

// Abstraction 
class Report {
    protected:
        std::shared_ptr<Formatter> formatter;

    public:
        Report(std::shared_ptr<Formatter> fmt) : formatter(std::move(fmt)) {}
        virtual std::string generate() = 0;
        virtual ~Report() = default;
};

// Redefined abstraction
class SalesReport : public Report {
    public:
        SalesReport(std::shared_ptr<Formatter> fmt) : Report(std::move(fmt)) {}
        std::string generate() override {
            return formatter->format("Sales Report", "Revenue: $5000");
        }
 };

 // Redefined abstraction 
 class InventoryReport : public Report {
    public:
        InventoryReport(std::shared_ptr<Formatter> fmt) : Report(std::move(fmt)) {}
        std::string generate() override {
            return formatter->format("Inventory Report", "Revenue: $6000");
        }
 };

int main() {

    auto jsonFormatter = std::make_shared<JSONFormatter>();
    auto htmlFormatter = std::make_shared<HTMLFormatter>();

    SalesReport salesJson(jsonFormatter);
    InventoryReport inventoryHtml(htmlFormatter);

    std::cout << salesJson.generate() << endl;
    std::cout << inventoryHtml.generate() << endl;

    return 0;
}