#include <iostream>
#include <memory>

using namespace std;

/*
    ===============================
    ABSTRACT FACTORY DESIGN PATTERN
    ===============================

    👉 Intent:
       Provide an interface for creating families of related or dependent objects
       without specifying their concrete classes.

    👉 Use Case:
       Suppose we are building a cross-platform UI library. We want to be able to
       create a Button and a CheckBox for different platforms (e.g., Windows and Mac),
       but we don't want the client code to care about which platform is currently in use.

    👉 Benefits:
       - Promotes consistency among products of the same family.
       - Isolates creation logic from usage.
       - Makes adding new product families easier.

    👉 Participants:
       - AbstractProduct (e.g., Button, CheckBox)
       - ConcreteProduct (e.g., WindowsButton, MacButton)
       - AbstractFactory (e.g., GUIFactory)
       - ConcreteFactory (e.g., WindowsFactory, MacFactory)
*/

// ========== Abstract Products ==========

class Button {
public:
    virtual void paint() = 0; // Abstract method to draw the button
    virtual ~Button() {}
};

class CheckBox {
public:
    virtual void render() = 0; // Abstract method to render the checkbox
    virtual ~CheckBox() {}
};

// ========== Concrete Products for Windows ==========

class WindowsButton : public Button {
public:
    void paint() override {
        cout << "Painting Windows button" << endl;
    }
};

class WindowsCheckBox : public CheckBox {
public:
    void render() override {
        cout << "Rendering Windows CheckBox" << endl;
    }
};

// ========== Concrete Products for Mac ==========

class MacButton : public Button {
public:
    void paint() override {
        cout << "Painting Mac button" << endl;
    }
};

class MacCheckBox : public CheckBox {
public:
    void render() override {
        cout << "Rendering Mac CheckBox" << endl;
    }
};

// ========== Abstract Factory ==========

class GUIFactory {
public:
    // Factory methods to create abstract products
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<CheckBox> createCheckBox() const = 0;
    virtual ~GUIFactory() = default;
};

// ========== Concrete Factories ==========

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<CheckBox> createCheckBox() const override {
        return std::make_unique<WindowsCheckBox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<CheckBox> createCheckBox() const override {
        return std::make_unique<MacCheckBox>();
    }
};

// ========== Platform Enum ==========
// Used to determine which factory to instantiate.

enum class Platform {
    Windows,
    Mac
};

// ========== Factory Selector Function ==========
// Returns the correct concrete factory based on the platform.

std::unique_ptr<GUIFactory> createFactory(Platform platform) {
    if (platform == Platform::Windows) {
        return std::make_unique<WindowsFactory>();
    } else {
        return std::make_unique<MacFactory>();
    }
}

// ========== Client Code ==========
// Uses the abstract factory interface to create and render UI components.

void renderUI(const GUIFactory& factory) {
    auto button = factory.createButton();     // Create button via factory
    auto checkbox = factory.createCheckBox(); // Create checkbox via factory

    button->paint();     // Use the product without knowing its exact type
    checkbox->render();  // Use the product without knowing its exact type
}

// ========== Main Function ==========
// Demonstrates using the abstract factory to switch between platforms.

int main() {
    // Simulate Windows UI rendering
    Platform platform = Platform::Windows;
    auto factory = createFactory(platform);
    renderUI(*factory);

    // Simulate Mac UI rendering
    platform = Platform::Mac;
    factory = createFactory(platform);
    renderUI(*factory);

    return 0;
}
