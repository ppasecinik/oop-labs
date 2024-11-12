#include <iostream>
#include <string>

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
};
/*
int main() {

    Display display1(1920, 1080, 100.0f, "Display A");
    Display display2(2560, 1440, 120.0f, "Display B");
    Display display3(1920, 1080, 200.0f, "Display C");

    display1.compareWithMonitor(display2);
    cout << "\n";
    display2.compareWithMonitor(display3);
    cout << "\n";
    display1.compareWithMonitor(display3);

    return 0;
}
*/


