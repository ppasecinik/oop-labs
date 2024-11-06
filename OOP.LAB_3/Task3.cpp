#include <iostream>
#include <string>

using namespace std;

enum class Intensity { LIGHT, NORMAL, STRONG };
enum class SyrupType { MACADAMIA, VANILLA, COCONUT, CARAMEL, CHOCOLATE, POPCORN };

string intensityToString(Intensity intensity) {
    switch (intensity) {
    case Intensity::LIGHT: return "Light";
    case Intensity::NORMAL: return "Normal";
    case Intensity::STRONG: return "Strong";
    default: return "Unknown";
    }
}

string syrupTypeToString(SyrupType syrup) {
    switch (syrup) {
    case SyrupType::MACADAMIA: return "Macadamia";
    case SyrupType::VANILLA: return "Vanilla";
    case SyrupType::COCONUT: return "Coconut";
    case SyrupType::CARAMEL: return "Caramel";
    case SyrupType::CHOCOLATE: return "Chocolate";
    case SyrupType::POPCORN: return "Popcorn";
    default: return "Unknown";
    }
}

class Coffee {
protected:
    Intensity intensity;
    string name;

public:
    Coffee(Intensity intensity, const string& name)
        : intensity(intensity), name(name) {}

    virtual void printDetails() const {
        cout << "Coffee: " << name << endl << endl;
    }
};

class Cappuccino : public Coffee {
protected:
    int mlOfMilk;

public:
    Cappuccino(Intensity intensity, int mlOfMilk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(mlOfMilk) {}


    Cappuccino makeCappuccino() const {
        cout << "Making Cappuccino" << endl;
        cout << "Intensity set to " << intensityToString(intensity) << endl;
        cout << "Adding " << mlOfMilk << " ml of milk" << endl;
        return *this;
    }
};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgOfPumpkinSpice;

public:
    PumpkinSpiceLatte(Intensity intensity, int mlOfMilk, int mgOfPumpkinSpice)
        : Cappuccino(intensity, mlOfMilk), mgOfPumpkinSpice(mgOfPumpkinSpice) {
        name = "Pumpkin Spice Latte";
    }

    PumpkinSpiceLatte makePumpkinSpiceLatte() const {
        cout << "Making Pumpkin Spice Latte" << endl;
        cout << "Intensity set to " << intensityToString(intensity) << endl;
        cout << "Adding " << mlOfMilk << " ml of milk" << endl;
        cout << "Adding " << mgOfPumpkinSpice << " mg of pumpkin spice" << endl;
        return *this;
    }
};

class Americano : public Coffee {
protected:
    int mlOfWater;

public:
    Americano(Intensity intensity, int mlOfWater)
        : Coffee(intensity, "Americano"), mlOfWater(mlOfWater) {}

    Americano makeAmericano() const {
        cout << "Making Americano" << endl;
        cout << "Intensity set to " << intensityToString(intensity) << endl;
        cout << "Adding " << mlOfWater << " ml of water" << endl;
        return *this;
    }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;

public:
    SyrupCappuccino(Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk), syrup(syrup) {
        name = "Syrup Cappuccino";
    }

    SyrupCappuccino makeSyrupCappuccino() const {
        cout << "Making Syrup Cappucino" << endl;
        cout << "Intensity set to " << intensityToString(intensity) << endl;
        cout << "Adding " << mlOfMilk << " ml of milk" << endl;
        cout << "Syrup type set to " << syrupTypeToString(syrup) << endl;
        return *this;
    }
};

int main() {
    Cappuccino cappuccino(Intensity::NORMAL, 200);
    cappuccino.makeCappuccino().printDetails();

    PumpkinSpiceLatte pumpkinSpiceLatte(Intensity::LIGHT, 150, 50);
    pumpkinSpiceLatte.makePumpkinSpiceLatte().printDetails();

    Americano americano(Intensity::STRONG, 300);
    americano.makeAmericano().printDetails();

    SyrupCappuccino syrupCappuccino(Intensity::NORMAL, 200, SyrupType::VANILLA);
    syrupCappuccino.makeSyrupCappuccino().printDetails();

    return 0;
}

