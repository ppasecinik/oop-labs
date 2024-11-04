#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

class FileReader {
public:
    string readFileIntoString(const string& path) {
        ifstream file(path);
        if (!file) {
            cerr << "Error: Cannot open file " << path << endl;
            return "";
        }
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

class TextData {
private:
    string fileName;
    string text;
    int numberOfVowels;
    int numberOfConsonants;
    int numberOfLetters;
    int numberOfSentences;
    string longestWord;

    void analyzeText() {
        numberOfVowels = 0;
        numberOfConsonants = 0;
        numberOfLetters = 0;
        numberOfSentences = 0;
        longestWord = "";

        istringstream iss(text);
        string word;
        while (iss >> word) {
            numberOfLetters += word.length();

            for (char c : word) {
                unsigned char uc = static_cast<unsigned char>(c);  // Cast once to unsigned char

                if (isalpha(uc)) {  // Check if it's an alphabetic character
                    if (isVowel(uc)) {  // Pass the unsigned char directly to isVowel
                        numberOfVowels++;
                    }
                    else {
                        numberOfConsonants++;
                    }
                }
            }

            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
        }

        // Count sentences (basic method based on '.', '!', and '?')
        numberOfSentences = countSentences();
    }

    // Helper method to check if a character is a vowel
    bool isVowel(unsigned char c) {  // Accept unsigned char
        c = tolower(c);  // No need to cast again
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    // Helper method to count sentences
    int countSentences() {
        return count_if(text.begin(), text.end(), [](char c) {
            return c == '.' || c == '!' || c == '?';
            });
    }

public:
    TextData(const string& fileName, const string& text)
        : fileName(fileName), text(text) {
        analyzeText();
    }

    string getFilename() const {
        return fileName;
    }

    string getText() const {
        return text;
    }

    int getNumberOfVowels() const {
        return numberOfVowels;
    }

    int getNumberOfConsonants() const {
        return numberOfConsonants;
    }

    int getNumberOfLetters() const {
        return numberOfLetters;
    }

    int getNumberOfSentences() const {
        return numberOfSentences;
    }

    string getLongestWord() const {
        return longestWord;
    }

    void printInfo() const {
        cout << "Filename: " << fileName << endl;
        cout << "Text: " << text << endl;
        cout << "Number of vowels: " << numberOfVowels << endl;
        cout << "Number of consonants: " << numberOfConsonants << endl;
        cout << "Number of letters: " << numberOfLetters << endl;
        cout << "Number of sentences: " << numberOfSentences << endl;
        cout << "Longest word: " << longestWord << endl << endl; 
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename1> <filename2> ..." << endl;
        return 1;
    }

    FileReader fileReader;

    // Iterate through each file path passed as command line argument
    for (int i = 1; i < argc; ++i) {
        string filePath = argv[i];
        string text = fileReader.readFileIntoString(filePath);

        if (text.empty()) {
            continue; // Skip to the next file if the current file could not be read
        }

        TextData textData(filePath, text);
        textData.printInfo();
    }

    return 0;
}

