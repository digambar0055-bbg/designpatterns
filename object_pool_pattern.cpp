// What is the Object Pool Pattern?
// The Object Pool Pattern is a creational pattern that 
// manages a pool of reusable objects. Instead of creating 
// and destroying objects frequently, you reuse them from the pool, 
// which boosts performance and reduces overhead.

// When to Use
//  - Object creation/destruction is expensive
//  - You need a fixed number of reusable objects
//  - You want to avoid memory fragmentation
//  - Useful in game development, network programming, multithreaded systems

// Basic Structure
// ObjectPool – Manages available and in-use objects
// ReusableObject – The object type being pooled
// Client – Asks for and returns objects from the pool

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

class Connection {
    public:
        Connection(int id) : id_(id), inUse_(false) {}

        void query(const std::string& sql) {
            std::cout << "Connection " << id_ << " executing query: " << sql << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
        }
        
        void connect() {
            std::cout << "Connection " << id_ << " established." << std::endl;
        }        

        void disconnect() {
            std::cout << "Connection " << id_ << " closed." << std::endl;
        }

        int getId() const { return id_; }
        bool isInUse() const { return inUse_; }
        void setInUse(bool inUse) { inUse_ = inUse; }

    private:
        int id_;
        int inUse_; 
};

// The object pool 
class ConnectionPool {
    public:
        ConnectionPool(size_t size) : poolSize(size) {
            for (size_t i = 0; i < size; i++){
                available.push_back(std::make_unique<Connection>(i));
            }
        }

        // Acquire a connection from the pool
        std::unique_ptr<Connection, std::function<void(Connection*)>> acquire() {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until a connection is available
            cond.wait(lock, [this]() { return !available.empty(); });

            auto conn = std::move(available.back());
            available.pop_back();

            // Custom deleter returns the connection to the pool
            auto deleter = [this](Connection* ptr) {
                std::unique_lock<std::mutex> lock(mtx);
                available.push_back(std::unique_ptr<Connection>(ptr));
                cond.notify_one();
            };

            return std::unique_ptr<Connection, decltype(deleter)>(conn.release(), deleter);
        }

    private:
        size_t  poolSize;
        std::vector<std::unique_ptr<Connection>> available;
        std::mutex mtx;
        std::condition_variable cond;
};

// Client Code
void clientTask(ConnectionPool& pool, int clientId) {
    auto conn = pool.acquire();
    conn->query("SELECT * FROM users WHERE id = " + std::to_string(clientId));
}

int main() {
    ConnectionPool pool(2); // Only 2 connections in the pool

    std::thread t1(clientTask, std::ref(pool), 1);
    std::thread t2(clientTask, std::ref(pool), 2);
    std::thread t3(clientTask, std::ref(pool), 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}