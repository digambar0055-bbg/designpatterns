// Use Case: Database Access Control with Protection Proxy
// Imagine you’re building a system with multiple user roles (Admin, Guest, etc.), 
// and you want to restrict database operations based on the user’s role. 
// You don’t want to expose the real database handler directly to unauthorized users.

// Structure
// Database – interface (Subject)
// RealDatabase – real database access implementation (RealSubject)
// DatabaseProxy – controls access to RealDatabase based on role
// User – has a role (e.g., Admin, Guest)

#include <iostream>
#include <string>

class Database {
    public:
        virtual void read() const = 0;
        virtual void write(const std::string& data) const = 0;
        virtual ~Database() = default;
};

class RealDatabase : public Database {
    public:
        void read() const override {
            std::cout << "[Database] Reading from the database" << std::endl; 
        }

        void write(const std::string& data) const override {
            std::cout << "[Database] Writing to the database: " 
                << data << std::endl;
        }
};

enum class Role {
    Guest,
    Admin
};

class DatabaseProxy : public Database {
    Role role;
    std::shared_ptr<RealDatabase> realDb;

    public:
        DatabaseProxy(Role role) : 
            realDb(std::make_shared<RealDatabase>()),
            role(role) {}

        void read() const override {
            std::cout << "[Proxy] Access granted for reading";
            realDb->read();
        }

        void write(const std::string& data) const override {
            if (role == Role::Guest) {
                std::cout << "[Proxy] Access denied. Write access need Admin role" 
                 << std::endl;
            }
            else if (role == Role::Admin) {
                std::cout << "[Proxy] Write access granted." << std::endl;
                realDb->write(data);
            }
        }
};

int main() {
    DatabaseProxy *db1 = new DatabaseProxy(Role::Guest);
    db1->read();
    db1->write("Guest trying to write");

    std::cout << "\n--- Admin User ---\n";
    Database* adminDb = new DatabaseProxy(Role::Admin);
    adminDb->read();
    adminDb->write("Admin update");

    delete db1;
    delete adminDb;
    return 0;
    return 0;
}