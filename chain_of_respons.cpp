// Chain of Responsibility Pattern

// Intent: Pass a request along a chain of handlers until one of them handles it.
// Use case: Logging frameworks, event handling, middleware in web servers.
// Example in C++: Different loggers (InfoLogger, DebugLogger, ErrorLogger) 
// form a chain; a log request passes through until the right one handles it.

// Intent
// Allow multiple objects to handle a request without coupling the sender to a 
// specific receiver. The request is passed along a chain of handlers until one processes it.

// Problem
// You have multiple handlers for a request (e.g., authentication, logging, authorization).
// You don’t want the client to hard-code which handler should process it.
// You want the system to be flexible so that you can add/remove handlers easily.

// Solution

// Create a chain of handler objects, each having a reference to the next handler.
// Each handler decides either to:
// Handle the request, or
// Pass it to the next handler in the chain.


// How to compile and run - 
// digambarmandhare@Digambars-Air design_patterns_cpp % g++ -std=c++17 chain_of_respons.cpp 
// digambarmandhare@Digambars-Air design_patterns_cpp % ./a.out 
// AuthHandler: Handled AUTH request
// LoggingHandler : Handled LOG request
// ErrorHandler : Handled ERROR request
// ErrorHandler : No handler found

#include<iostream>
#include<string>
#include<memory>

// Abstract handler 
class Handler {
    protected:
        std::shared_ptr<Handler> next;
    public:
        void setNextHandler(std::shared_ptr<Handler> handler) {
            next = handler;
        }

        virtual void handleRequest(const std::string& request) {
            if (next) {
                next->handleRequest(request);
            }
        }
};

// Concrete Handler 
class AuthHandler : public Handler {
    public:
        void handleRequest(const std::string& request) override {
            if (request == "AUTH") {
                std::cout << "AuthHandler: Handled AUTH request" << std::endl;
            } else if (next) {
                next->handleRequest(request);
            }
        }
};

class LoggingHandler : public Handler {
    public:
        void handleRequest(const std::string& request) override {
            if (request == "LOG") {
                std::cout << "LoggingHandler : Handled LOG request" << std::endl;
            }
            else if (next) {
                next->handleRequest(request);
            }
        }
};

class ErrorHandler : public Handler {
    public :
        void handleRequest(const std::string& request) override {
            if (request == "ERROR") {
                std::cout << "ErrorHandler : Handled ERROR request" << std::endl;
            }
            else if (next) {
                next->handleRequest(request);
            }
            else {
                std::cout << "ErrorHandler : No handler found" << std::endl;
            }
        }
};

int main() {
    auto auth = std::make_shared<AuthHandler>();
    auto log = std::make_shared<LoggingHandler>();
    auto error = std::make_shared<ErrorHandler>();

    auth->setNextHandler(log);
    log->setNextHandler(error);

    // Send Requests
    auth->handleRequest("AUTH");
    auth->handleRequest("LOG");
    auth->handleRequest("ERROR");
    auth->handleRequest("UNKNOWN");

    return 0;
}