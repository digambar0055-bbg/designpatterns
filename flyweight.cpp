// Intent:
// To minimize memory usage by sharing as much data as possible with similar objects.

// Use Case:
// When you need to create a large number of objects, and many of them share common data.

#include<iostream>
#include<unordered_map>
#include<memory>

class CharacterStyle {
    std::string font;
    int size;
    std::string color;

    public:
        CharacterStyle(const std::string &f, int s, const std::string &c)
            : font(f), size(s), color(c) {}
};

// Flyweight factory
class CharacterStyleFactory {
    public:
        std::shared_ptr<CharacterStyle> GetStyle(const std::string &font,
        int size,
        const std::string &color) {
            std::string key = font + std::to_string(size) + color;
            if(styles.find(key) == styles.end()) {
                styles[key] = std::make_shared(CharacterStyle(font, size, color))
            }
            return styles[key];
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<CharacterStyle>> styles;
};

// The flyweight: stores the shared state
class Character {
    char symbol;
    int x;
    int y;
    std::shared_ptr<CharacterStyle> style;

    public:
        Character(char sym, int x, int y, std::shared_ptr<CharacterStyle> style)
            : symbol(sym), x(x), y(y), style(style) {}

        void display(int x, int y) {
            std::cout << "Char: " << symbol
            << " At: (" << x << ", " << y;
        }
}

// Client
class Document {
    public:
        void AddCharacter(char symbol,
        int x, int y,
        const std::string& font,
        int size,
        const std::string &colour) {
            auto style = 
        }

    private:
        std::
};

int main() {
    return 0;
}