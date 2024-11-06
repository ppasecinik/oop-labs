#include <iostream>
#include <string>

using namespace std;

enum class Intensity { LIGHT, NORMAL, STRONG };
enum class SyrupType { MACADAMIA, VANILLA, COCONUT, CARAMEL, CHOCOLATE, POPCORN };

class Coffee {
protected:
    Intensity intensity;
     string name;

public:
    Coffee(Intensity intensity, const  string& name)
        : intensity(intensity), name(name) {}

    virtual void printDetails() const {
         cout << "Coffee: " << name << "\nCoffee Intensity: " << static_cast<int>(intensity) <<  endl;
    }
};

class Cappuccino : public Coffee {
protected:
    int mlOfMilk;

public:
    Cappuccino(Intensity intensity, int mlOfMilk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(mlOfMilk) {}

    void printDetails() const override {
        Coffee::printDetails(); 
         cout << name << " Milk: " << mlOfMilk << " ml" <<  endl;
    }
};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgOfPumpkinSpice;

public:
    PumpkinSpiceLatte(Intensity intensity, int mlOfMilk, int mgOfPumpkinSpice)
        : Cappuccino(intensity, mlOfMilk), mgOfPumpkinSpice(mgOfPumpkinSpice) {
        name = "PumpkinSpiceLatte";
    }

    void printDetails() const override {
        Cappuccino::printDetails(); 
         cout << "Pumpkin Spice: " << mgOfPumpkinSpice << " mg" <<  endl;
    }
};

class Americano : public Coffee {
protected:
    int mlOfWater;

public:
    Americano(Intensity intensity, int mlOfWater)
        : Coffee(intensity, "Americano"), mlOfWater(mlOfWater) {}

    void printDetails() const override {
        Coffee::printDetails(); 
         cout << "Water: " << mlOfWater << " ml" <<  endl;
    }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;

public:
    SyrupCappuccino(Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk), syrup(syrup) {
        name = "SyrupCappuccino";
    }

    void printDetails() const override {
        Cappuccino::printDetails(); 
         cout << "Syrup: " << static_cast<int>(syrup) <<  endl;
    }
};

int main() {
    Cappuccino cappuccino(Intensity::NORMAL, 200);
    cappuccino.printDetails();

    PumpkinSpiceLatte pumpkinSpiceLatte(Intensity::LIGHT, 150, 50);
    pumpkinSpiceLatte.printDetails();

    Americano americano(Intensity::STRONG, 300);
    americano.printDetails();

    SyrupCappuccino syrupCappuccino(Intensity::NORMAL, 200, SyrupType::VANILLA);
    syrupCappuccino.printDetails();

    return 0;
}
