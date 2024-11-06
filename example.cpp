#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Species {
private:
    string name;
    bool isHumanoid;
    string planet;
    int age;
    vector<string> traits;

public:
    Species(const string& name, bool isHumanoid, const string& planet, int age, const vector<string>& traits)
        : name(name), isHumanoid(isHumanoid), planet(planet), age(age), traits(traits) {}

    // Getters
    string getName() const { return name; }
    bool getIsHumanoid() const { return isHumanoid; }
    string getPlanet() const { return planet; }
    int getAge() const { return age; }
    vector<string> getTraits() const { return traits; }

    bool matches(bool inputIsHumanoid, const string& inputPlanet, int inputAge, const vector<string>& inputTraits) const {
        if (!inputPlanet.empty() && inputPlanet != planet) return false;
        if (inputAge > 0 && inputAge > age) return false;

        for (const auto& inputTrait : inputTraits) {
            if (find(traits.begin(), traits.end(), inputTrait) == traits.end())
                return false;
        }
        return true;
    }
};

class Universe {
private:
    string name;
    vector<Species> speciesList;

public:
    Universe(const string& name, const vector<Species>& speciesList) : name(name), speciesList(speciesList) {}

    // Getters
    string getName() const { return name; }
    vector<Species> getSpeciesList() const { return speciesList; }

    string classifyCreature(bool isHumanoid, const string& planet, int age, const vector<string>& traits) const {
        for (const auto& species : speciesList) {
            if (species.matches(isHumanoid, planet, age, traits)) {
                return species.getName();
            }
        }
        return "";
    }
};

// TODO move to a class
class FileHandler {
public:
    vector<json> readInputFromFile(const string& filename) const {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open the file: " << filename << endl;
            return {};
        }

        json j;
        file >> j;

        if (!j.contains("input")) {
            cout << "Error: Input array not found in JSON." << endl;
            return {};
        }
        return j["input"].get<vector<json>>();
    }

    void writeOutputToFile(const string& filename, const vector<json>& creatures) const {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cout << "Error: Could not open the file: " << filename << endl;
            return;
        }

        file << json(creatures).dump(4);
        file.close();
    }
};

class CreatureClassifier {
private:
    vector<Universe> universes;
    FileHandler fileHandler;

public:
    CreatureClassifier(const vector<Universe>& universes, const FileHandler& fileHandler) : universes(universes), fileHandler(fileHandler) {}

    void classifyAndSaveCreatures(const vector<json>& creatures) const {
        for (const auto& universe : universes) {
            vector<json> classifiedCreatures;  

            for (const auto& creature : creatures) {
                bool isHumanoid = creature.value("isHumanoid", false);
                string planet = creature.value("planet", "");
                int age = creature.value("age", 0);
                vector<string> traits = creature.value("traits", vector<string>());

                string speciesName = universe.classifyCreature(isHumanoid, planet, age, traits);
                if (!speciesName.empty()) {
                    classifiedCreatures.push_back(creature);
                    cout << speciesName << " from " << universe.getName() << endl;
                }
            }

            string filename = universe.getName() + ".json";
            fileHandler.writeOutputToFile(filename, classifiedCreatures);
        }
    }

};

int main() {

    FileHandler fileHandler;


    vector<Universe> universes = {
        Universe("Star Wars", { Species("Wookie", false, "Kashyyyk", 400, { "HAIRY", "TALL" }),
                               Species("Ewok", false, "Endor", 60, { "SHORT", "HAIRY" }) }),
        Universe("Marvel", { Species("Asgardian", true, "Asgard", 5000, { "BLONDE", "TALL" }) }),
        Universe("Hitchhiker's Universe", { Species("Betelgeusian", true, "Betelgeuse", 100, { "EXTRA_ARMS", "EXTRA_HEAD" }),
                                           Species("Vogon", false, "Vogsphere", 200, { "GREEN", "BULKY" }) }),
        Universe("Lord of the Rings", { Species("Elf", true, "Earth", 10000, { "BLONDE", "POINTY_EARS" }),
                           Species("Dwarf", true, "Earth", 200, { "SHORT", "BULKY" }) })
    };

    // Clear files before writing new data
    for (const auto& universe : universes) {
        ofstream(universe.getName() + ".json", ios::trunc).close();
    }

    // TODO load the json data into an object instance
    vector<json> inputData = fileHandler.readInputFromFile("input.json");

    CreatureClassifier classifier(universes, fileHandler);

    classifier.classifyAndSaveCreatures(inputData);

    return 0;
}