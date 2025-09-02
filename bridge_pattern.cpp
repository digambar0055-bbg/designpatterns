#include <iostream>

using namespace std;

class Devise {
    public:
        virtual void powerOn() = 0;
        virtual void powerOff() = 0;
        virtual ~Devise() = default;  
};

class TV : public Devise {
    public:
        void powerOn() override {
            cout << "TV is ON" << endl;
        }

        void powerOff() override {
            cout << "TV is OFF" << endl;
        }
};

class Radio : public Devise {
    public:
        void powerOn() override {
            cout << "Radio is ON" << endl;
        }

        void powerOff() override {
            cout << "Radio is OFF" << endl;
        }
};

class RemoteControl
{
    protected:
        Devise *devise;
    public:
        RemoteControl(Devise *devise) : devise(devise) {}
        virtual void togglePower() = 0;
        virtual ~RemoteControl() = default;
};

class BaiscRemote : public RemoteControl {
    public:
        BaiscRemote(Devise *devise) : RemoteControl(devise) {}
        void togglePower() override {
            cout << "Basic Remote : ";
            devise->powerOn();
        }
};

class AdvancedRemote : public RemoteControl {
    public:
        AdvancedRemote(Devise *devise) : RemoteControl(devise) {}
        void togglePower() override {
            cout << "Advanced Remote: ";
            devise->powerOn();
            cout << "Volume set to 50 " << endl;
        }
};

int main() {
    Radio radio;
    TV tv;

    BaiscRemote baiscRemote(&radio);
    AdvancedRemote advancedRemote(&tv);

    baiscRemote.togglePower();
    advancedRemote.togglePower();

    return 0;
}