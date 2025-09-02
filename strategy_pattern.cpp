// How to compile and exectute - 
// digambarmandhare@Digambars-Air design_patterns_cpp % g++ -std=c++17 strategy_pattern.cpp 
// digambarmandhare@Digambars-Air design_patterns_cpp % ./a.out 
// Paid 100 using credit card
// Paid 200 using pay pal

// Definition

// The Strategy Pattern defines a family of algorithms, encapsulates each one, 
// and makes them interchangeable.
// It lets the algorithm vary independently from the clients that use it.

// When to Use

// When you want to switch between different algorithms at runtime.
// When you want to avoid big if-else or switch statements.
// When multiple classes differ only in their behavior.


// Real-life Analogy

// A navigation app:
// You can choose “Fastest Route”, “Shortest Route”, or “Avoid Tolls”.
// The app doesn’t change — only the strategy (route algorithm) does.

#include<iostream>
#include<memory>


// Strategy Interface
class PaymentStrategy {
    public:
        virtual void pay(int amount) = 0;
        virtual ~PaymentStrategy() = default;
};

// Concrete Strategy
class CrediCardPayment : public PaymentStrategy {
    public:
        void pay(int amount) override {
            std::cout << "Paid " << amount << " using credit card" << std::endl;
        }
};

class PayPalPayment : public PaymentStrategy {
    public:
        void pay(int amount) override {
            std::cout << "Paid " <<  amount << " using pay pal" << std::endl;
        }
};

class PaymentContext {
    private:
        std::unique_ptr<PaymentStrategy> paymentStrategy;
    public:
        void setStrategy(std::unique_ptr<PaymentStrategy> s) {
            paymentStrategy = std::move(s);
        }

        void executePayment(int amount) {
            if(paymentStrategy){
                paymentStrategy->pay(amount);
            }
            else {
                std::cout << "No payment strategy selected" << std::endl;
            }
        }
};


int main() {
    PaymentContext context;

    context.setStrategy(std::make_unique<CrediCardPayment>());
    context.executePayment(100);

    context.setStrategy(std::make_unique<PayPalPayment>());
    context.executePayment(200);
}