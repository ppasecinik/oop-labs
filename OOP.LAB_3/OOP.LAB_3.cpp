#include <iostream>
#include <string>

using namespace std;
////////////////////
enum class Intensity { LIGHT, NORMAL, STRONG };
enum class SyrupType { MACADAMIA, VANILLA, COCONUT, CARAMEL, CHOCOLATE, POPCORN };

class Coffee {
protected:
    Intensity intensity;
    string name;

public:
    Coffee(Intensity intensity, const  string& name)
        : intensity(intensity), name(name) {}

};

class Cappuccino : public Coffee {
protected:
    int mlOfMilk;

public:
    Cappuccino(Intensity intensity, int mlOfMilk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(mlOfMilk) {}

};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgOfPumpkinSpice;

public:
    PumpkinSpiceLatte(Intensity intensity, int mlOfMilk, int mgOfPumpkinSpice)
        : Cappuccino(intensity, mlOfMilk), mgOfPumpkinSpice(mgOfPumpkinSpice) {
        name = "PumpkinSpiceLatte";
    }

};

class Americano : public Coffee {
protected:
    int mlOfWater;

public:
    Americano(Intensity intensity, int mlOfWater)
        : Coffee(intensity, "Americano"), mlOfWater(mlOfWater) {}

};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;

public:
    SyrupCappuccino(Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk), syrup(syrup) {
        name = "SyrupCappuccino";
    }

};

