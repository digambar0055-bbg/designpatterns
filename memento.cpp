// Intent
// Capture and externalize an object’s 
// internal state so that it can be restored later, without violating encapsulation.

// Real-world analogy
// Think of Undo/Redo in an editor (Word, Photoshop, VSCode).
// Before making a change, the editor stores a snapshot (memento) of the document.
// You can restore a previous snapshot without knowing how the document is structured 
// internally.

// +-----------+        +------------+        +-----------+
// | Originator| <----> |  Memento   | <----> | Caretaker |
// +-----------+        +------------+        +-----------+
//      |   saveState()      stores state         holds mementos
//      |   restoreState()                        (undo/redo)

// Originator: the object whose state we want to save/restore.
// Memento: stores the state of the Originator.
// Caretaker: manages mementos (keeps history, allows undo/redo).

// How to compile and run - 
// digambarmandhare@Digambars-Air designpatterns % g++ -std=c++17 memento.cpp
// digambarmandhare@Digambars-Air designpatterns % ./a.out 
// Initial state: Hello World!
// After first undo: Hello World!
// After second undo: Hello

#include<iostream>
#include<string>
#include<memory>
#include<vector>

class Memento {
    private:
        std::string state;
    public:
        explicit Memento(const std::string& s) : state(s) {}
        std::string getState() const { return state; }
};

class TextEditor {
    private:
        std::string text;
    public:
        void type(const std::string& words) {
            text += words;
        }

        std::string getText() const {
            return text;
        }

        std::shared_ptr<Memento> save() const {
            return std::make_shared<Memento>(text);
        }

        void restore(const std::shared_ptr<Memento>& memento) {
            text = memento->getState();
        }
};

class History {
    private:
        std::vector<std::shared_ptr<Memento> > mementos; 
    public:
        void push(const std::shared_ptr<Memento>& m) {
            mementos.push_back(m);
        }

        std::shared_ptr<Memento> pop() {
            if (mementos.empty()) return nullptr;
            auto m = mementos.back();
            mementos.pop_back();
            return m;
        }
 };

 int main () {
    TextEditor editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());

    editor.type(" World!");
    history.push(editor.save());
    
    std::cout << "Initial state: " << editor.getText() << std::endl;
    
    editor.restore(history.pop());
    std::cout << "After first undo: " << editor.getText() << std::endl;

    editor.restore(history.pop());
    std::cout << "After second undo: " << editor.getText() << std::endl;

    return 0;
 }