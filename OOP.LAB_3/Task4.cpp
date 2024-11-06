#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Intensity { LIGHT, NORMAL, STRONG };
enum SyrupType { MACADAMIA, VANILLA, COCONUT, CARAMEL, CHOCOLATE, POPCORN };

string intensityToString(Intensity intensity) {
    switch (intensity) {
    case LIGHT: return "Light";
    case NORMAL: return "Normal";
    case STRONG: return "Strong";
    default: return "Unknown";
    }
}

string syrupTypeToString(SyrupType syrup) {
    switch (syrup) {
    case MACADAMIA: return "Macadamia";
    case VANILLA: return "Vanilla";
    case COCONUT: return "Coconut";
    case CARAMEL: return "Caramel";
    case CHOCOLATE: return "Chocolate";
    case POPCORN: return "Popcorn";
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
        cout << "Your Coffee: " << name << endl;
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
        cout << "Making Syrup Cappuccino" << endl;
        cout << "Intensity set to " << intensityToString(intensity) << endl;
        cout << "Adding " << mlOfMilk << " ml of milk" << endl;
        cout << "Syrup type set to " << syrupTypeToString(syrup) << endl;
        return *this;
    }
};

class Barista {
public:
    Coffee* createCoffee() {
        string coffeeType;
        Intensity intensity = NORMAL; // Default intensity
        int mlOfMilk, mlOfWater, mgOfPumpkinSpice;
        SyrupType syrup = VANILLA; // Default syrup type

        cout << "What type of coffee would you like? (Cappuccino, PumpkinSpiceLatte, Americano, SyrupCappuccino): ";
        cin >> coffeeType;

        cout << "Choose the intensity (Light, Normal, Strong): ";
        string intensityChoice;
        cin >> intensityChoice;
        if (intensityChoice == "Light") {
            intensity = LIGHT;
        }
        else if (intensityChoice == "Normal") {
            intensity = NORMAL;
        }
        else if (intensityChoice == "Strong") {
            intensity = STRONG;
        }

        if (coffeeType == "Cappuccino") {
            cout << "How much milk would you like?(ml): ";
            cin >> mlOfMilk;
            Cappuccino* cappuccino = new Cappuccino(intensity, mlOfMilk);
            cappuccino->makeCappuccino();
            cappuccino->printDetails();
            return cappuccino;
        }
        else if (coffeeType == "PumpkinSpiceLatte") {
            cout << "How much milk would you like?(ml): ";
            cin >> mlOfMilk;
            cout << "What amount of pumpkin spice would you like to add? (mg): ";
            cin >> mgOfPumpkinSpice;
            PumpkinSpiceLatte* pumpkinSpiceLatte = new PumpkinSpiceLatte(intensity, mlOfMilk, mgOfPumpkinSpice);
            pumpkinSpiceLatte->makePumpkinSpiceLatte();
            pumpkinSpiceLatte->printDetails();
            return pumpkinSpiceLatte;
        }
        else if (coffeeType == "Americano") {
            cout << "How much water would you like?(ml): ";
            cin >> mlOfWater;
            Americano* americano = new Americano(intensity, mlOfWater);
            americano->makeAmericano();
            americano->printDetails();
            return americano;
        }
        else if (coffeeType == "SyrupCappuccino") {
            cout << "How much milk would you like?(ml): ";
            cin >> mlOfMilk;
            cout << "What syrup type would you prefer?(Macadamia, Vanilla, Coconut, Caramel, Chocolate, Popcorn): ";
            string syrupChoice;
            cin >> syrupChoice;
            if (syrupChoice == "Macadamia") syrup = MACADAMIA;
            else if (syrupChoice == "Vanilla") syrup = VANILLA;
            else if (syrupChoice == "Coconut") syrup = COCONUT;
            else if (syrupChoice == "Caramel") syrup = CARAMEL;
            else if (syrupChoice == "Chocolate") syrup = CHOCOLATE;
            else if (syrupChoice == "Popcorn") syrup = POPCORN;
            SyrupCappuccino* syrupCappuccino = new SyrupCappuccino(intensity, mlOfMilk, syrup);
            syrupCappuccino->makeSyrupCappuccino();
            syrupCappuccino->printDetails();
            return syrupCappuccino;
        }

        return nullptr;
    }

    void takeMultipleOrders() {
        vector<Coffee*> orders;
        char orderMore;

        cout << "Welcome to our coffee shop!\n";

        do {
            Coffee* coffee = createCoffee();
            if (coffee != nullptr) {
                orders.push_back(coffee);
            }

            cout << "\nWould you like to order another coffee? (y/n): ";
            cin >> orderMore;

        } while (orderMore == 'y' || orderMore == 'Y');

        cout << endl;
        cout << "Thank you so much for choosing us! We're so happy to have crafted your perfect coffee.\n";
        cout << "Enjoy your coffee and see you soon!\n";
        cout << "Have a nice day!";

        // Free allocated memory
        for (auto& coffee : orders) {
            delete coffee;
        }
    }
};

int main() {
    Barista barista;

    barista.takeMultipleOrders();

    return 0;
}
