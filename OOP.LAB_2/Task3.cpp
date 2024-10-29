#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Display {
private:
    int width;
    int height;
    float pix;
    string model;

public:
    Display(int w, int h, float p, const string& m)
        : width(w), height(h), pix(p), model(m) {}

    void compareSize(Display m) {
        int thisArea = width * height;
        int otherArea = m.width * m.height;
        cout << "Comparing size of " << model << " and " << m.model << ":\n";
        if (thisArea > otherArea) {
            cout << model << " is larger than " << m.model << ".\n\n";
        }
        else if (thisArea < otherArea) {
            cout << model << " is smaller than " << m.model << ".\n\n";
        }
        else {
            cout << model << " is the same size as " << m.model << ".\n\n";
        }
    }

    void compareSharpness(Display m) {
        cout << "Comparing sharpness of " << model << " and " << m.model << ":\n";
        if (pix > m.pix) {
            cout << model << " is sharper than " << m.model << ".\n\n";
        }
        else if (pix < m.pix) {
            cout << model << " is less sharp than " << m.model << ".\n\n";
        }
        else {
            cout << model << " has the same sharpness as " << m.model << ".\n\n";
        }
    }

    void compareWithMonitor(Display m) {
        cout << "Comparing " << model << " with " << m.model << ":\n\n";
        compareSize(m);
        compareSharpness(m);
    }

    float getPixelDensity() const {
        return pix;
    }

    string getModel() const {
        return model;
    }
};

class Assistant {
private:
    string assistantName;
    vector<Display> assignedDisplays;

public:
    Assistant(const string& name) : assistantName(name) {}

    void assignDisplay(const Display& d) {
        assignedDisplays.push_back(d);
        cout << "Assigned display: " << d.getModel() << " to " << assistantName << ".\n";
    }

    void assist() {
        cout << assistantName << " is assisting with the following displays:\n";
        for (size_t i = 0; i < assignedDisplays.size(); ++i) {
            cout << "Display " << (i + 1) << ": " << assignedDisplays[i].getModel() << "\n";
            for (size_t j = i + 1; j < assignedDisplays.size(); ++j) {
                assignedDisplays[i].compareWithMonitor(assignedDisplays[j]);
            }
        }
    }

    Display buyBestDisplay() {
        if (assignedDisplays.empty()) {
            throw runtime_error("No displays assigned.");
        }

        // Find the display with the highest pixel density
        Display bestDisplay = assignedDisplays[0];
        size_t bestIndex = 0;

        for (size_t i = 1; i < assignedDisplays.size(); ++i) {
            if (assignedDisplays[i].getPixelDensity() > bestDisplay.getPixelDensity()) {
                bestDisplay = assignedDisplays[i];
                bestIndex = i; // Store the index of the best display
            }
        }

        assignedDisplays.erase(assignedDisplays.begin() + bestIndex);
        cout << "Your assistent Alice advice to buy: " << bestDisplay.getModel() << " with pixel density of " << bestDisplay.getPixelDensity() << ".\n";
        return bestDisplay;
    }
};

int main() {
    Assistant assistant("Alice");

    Display display1(1920, 1080, 100.0f, "Display A");
    Display display2(2560, 1440, 120.0f, "Display B");
    Display display3(1920, 1080, 200.0f, "Display C");
    Display display4(1920, 1080, 180.0f, "Display D");

    assistant.assignDisplay(display1);
    assistant.assignDisplay(display2);
    assistant.assignDisplay(display3);
    assistant.assignDisplay(display4);

    assistant.assist();

    try {
        assistant.buyBestDisplay();
    }
    catch (const exception& e) {
        cerr << e.what() << "\n";
    }

    return 0;
}
