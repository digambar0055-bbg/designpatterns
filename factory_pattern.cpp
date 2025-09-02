// Pattern - Creational
// Intent:
// Define an interface for creating an object, but let subclasses decide 
// which class to instantiate. The Factory Method lets a class defer 
// instantiation to subclasses.

// Use Case Example:
// Suppose you're building a Notification system that can send SMS or 
// Email notifications depending on user preference.

// UML in Brief:
// Product: defines the interface of objects the factory method creates.
// ConcreteProduct: implements the Product interface.
// Creator: declares the factory method that returns a Product object.
// ConcreteCreator: overrides the factory method to return an instance of a ConcreteProduct.

// Key Points:
// Promotes loose coupling: the client depends on abstract NotificationFactory, 
// not concrete classes.
// Makes your code open for extension, but closed for modification (OCP from SOLID).

#include<iostream>

class Notification {
public:
    virtual void notifyUser() = 0;
    virtual ~Notification() = default;
};

class SMSNotification : public Notification {
    public:
        void notifyUser() override {
            std::cout << "Sending SMS notification to client" << std::endl;
        }
};

class EmailNotification : public Notification {
    public:
        void notifyUser() override {
            std::cout << "Sending Email notification to client" << std::endl;
        }
};

class NotificationFactory {
    public:
        virtual std::unique_ptr<Notification> createNotification() = 0;
        virtual ~NotificationFactory() = default;
};

class SMSNotificationFactory : public NotificationFactory {
    public:
        std::unique_ptr<Notification> createNotification() override {
            return std::make_unique<SMSNotification>();
        }
};

class EmailNotificationFactory : public NotificationFactory {
    public:
        std::unique_ptr<Notification> createNotification() override {
            return std::make_unique<EmailNotification>();
        }
};

void clientCode(NotificationFactory& factory) {
    std::unique_ptr<Notification> notification = factory.createNotification();
    notification->notifyUser();
}

int main() {
    SMSNotificationFactory smsNotificationFactory;
    EmailNotificationFactory emailNotificationFactory;

    clientCode(smsNotificationFactory);
    clientCode(emailNotificationFactory);

    return 0;
}
