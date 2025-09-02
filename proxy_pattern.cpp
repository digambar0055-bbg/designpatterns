// Intent
// Provide a surrogate or placeholder for another object to control access to it.

// Real-World Analogy
// Think of a credit card as a proxy for your bank account. When you swipe the card, 
// it doesn’t access the cash directly—it checks balance, processes the payment, 
// and deducts accordingly.

// Types of Proxies
// 1. Virtual Proxy – Lazy loading (e.g., load image only when needed)
// 2. Protection Proxy – Access control (e.g., different users have different access levels)
// 3. Remote Proxy – For communication over a network (e.g., RPC)
// 4. Smart Proxy – Adds extra functionality like logging, counting references

#include <iostream>
#include <memory>
#include <string>

// Subject
class Image {
    public:
        virtual void display() const = 0;
        virtual ~Image() = default;
};

class RealImage : public Image {
    std::string filename;
public :
    RealImage(const std::string& fname) : filename(fname) {
        loadFromDisk(filename);
    }

    void loadFromDisk() const {
        std::cout << "Loading image " << filename << std::endl;
    }
    void display() const override {
        std::cout << "Display Image " << filename << std::endl; 
    }
};

// Proxy 
class ProxyImage : public Image {
    std::string filename;
    mutable std::unique_ptr<RealImage> realImage;
    public:
        ProxyImage(const std::string& fname) : 
            filename(fname), realImage(nullptr) {}

        void display() const override {
            if (!realImage) {
                realImage = std::make_unique<RealImage>(filename);
            }
            realImage->display();
        }
};

int main() 
{
    Image *img1 = new ProxyImage("photo1.jpg");
    Image *img2 = new ProxyImage("photo2.jpg");

    std::cout << "Images created";

    img1->display();
    img2->display();

    delete img1;
    delete img2;

    return 0;    
}