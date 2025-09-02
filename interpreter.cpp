// Intent

// Define a grammar for a simple language and use an interpreter to interpret its sentences.
// Each symbol (terminal or non-terminal) in the grammar is represented by a class.
// Expressions are built as an Abstract Syntax Tree (AST), and interpretation 
// is done recursively.

// Real-world analogy

// Think of a calculator parsing arithmetic expressions like 5 + 3 - 2.
// Each operator (+, -) and number is interpreted as part of the grammar.

// Structure (UML concepts)

// AbstractExpression → declares interpret(context).
// TerminalExpression → represents a leaf node (like numbers).
// NonTerminalExpression → represents operators, combining multiple expressions.
// Context → holds global information (e.g., variable values).
// Client → builds the AST and triggers interpretation.

#include<iostream>
#include<string>
#include<memory>
#include<unordered_map>

class Context {
    std::unordered_map<std::string, int> variable;
    public:
        void setVariable(const std::string& name, int value) {
            variable[name] = value;
        }

        int getVariable(const std::string& name) const {
            auto it = variable.find(name);
            if (it != variable.end()) return it->second;
            throw std::runtime_error("Variable not found: " + name);
        }
};

// Abstract expression
class Expression {
    public:
        virtual ~Expression() {}
        virtual int interpret(const Context& ctx) const = 0;
};

class VariableExpression : public Expression {
    std::string name;
    public:
        VariableExpression(const std::string& n) : name(n) {}
        int interpret(const Context& ctx) const override {
            return ctx.getVariable(name);
        }
};

class NumberExpression : public Expression {
    int number;
    public:
        NumberExpression(int n) : number(n) {}
        int interpret(const Context& ctx) const override {
            return number;
        }
};

class AddExpression : public Expression {
    std::shared_ptr<Expression> left, right;
    public:
        AddExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) :
            left(l), right(r) {}
        int interpret(const Context& ctx) const override {
            return left->interpret(ctx) + right->interpret(ctx);
        }
};


class SubExpression : public Expression {
    std::shared_ptr<Expression> left, right;
    public:
        SubExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) :
            left(l), right(r) {}
        int interpret(const Context& ctx) const override {
            return left->interpret(ctx) - right->interpret(ctx);
        }
};

// Client
int main() {
    Context ctx;
    ctx.setVariable("x", 10);
    ctx.setVariable("y", 5);

    // Build expression: (x + y) - 3
    std::shared_ptr<Expression> expression =
        std::make_shared<SubExpression>(
            std::make_shared<AddExpression>(
                std::make_shared<VariableExpression>("x"),
                std::make_shared<VariableExpression>("y")
            ),
            std::make_shared<NumberExpression>(3)
        );

    std::cout << "(x + y) - 3 = " << expression->interpret(ctx) << "\n"; // 12

    return 0;
}