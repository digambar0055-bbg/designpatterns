// Iterator Pattern

// Intent
// Provide a way to sequentially access elements of a 
// collection without exposing its underlying representation.

// Structure
// Iterator (Interface) – defines operations for iteration (hasNext(), next()).
// ConcreteIterator – implements the traversal for a specific collection.
// Aggregate (Interface) – defines a method to create an iterator.
// ConcreteAggregate – holds the collection and provides its iterator.

// UML-like View
// Aggregate  <|-- ConcreteAggregate
// Iterator   <|-- ConcreteIterator

// ConcreteAggregate --creates--> ConcreteIterator

#include<iostream>
#include<vector>
#include<memory>

template <typename T>
class Iterator {
    public:
        virtual bool hasNext() = 0;
        virtual T next() = 0;
        virtual ~Iterator() = default;
};

// Aggregate Interface
template <typename T>
class Aggregate {
    public:
        
};