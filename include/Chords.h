#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

namespace cmtk {

class Chord {
public:
    // Constructor
    Chord() = default;
    Chord(std::string chordSymbol, int rootNote = 0)
    {
        setChord(chordSymbol, rootNote);
    }

    // Enum class to represent the quality of the chord
    enum class Quality {
        Major,
        Minor,
        Diminished,
        Augmented,
        Sus2,
        Sus4,
        PowerChord,
    };

    // Function to get the chord tones from a chord symbol
    void setChord(std::string aChordSymbol, int aRootNote = 0)
    {
        chordSymbol = aChordSymbol;
        chordTones = getChordTones(aChordSymbol, aRootNote);
    }

    // Get the chord symbol
    std::string getChordSymbol()
    {
        return chordSymbol;
    }

    // Get the chord tones
    std::vector<int> getChordTones()
    {
        return chordTones;
    }

    // Get the chord tones from a chord symbol
    std::vector<int> getChordTones(const std::string& aChordSymbol, int rootNote = 0){
        auto chordSymbol = aChordSymbol;

        // Chech if the roman numeral contains 'i', 'v', 'I' or 'V'
        bool skip = false;
        if(chordSymbol[0] == 'b' && chordSymbol.find_first_of("ivIV") == std::string::npos)
        {
            skip = true;
        }

        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(!skip){
            while (chordSymbol[0] == 'b' || chordSymbol[0] == '#') {
                if      (chordSymbol[0] == 'b') { rootNote -= 1; }
                else if (chordSymbol[0] == '#') { rootNote += 1; }
                chordSymbol.erase(0,1);
            }
        }

        // Replace start
        replacePrefix(chordSymbol, "Cbm", "cb");
        replacePrefix(chordSymbol, "Cm" , "c" );
        replacePrefix(chordSymbol, "C#m", "c#");
        replacePrefix(chordSymbol, "Dbm", "db");
        replacePrefix(chordSymbol, "Dm" , "d" );
        replacePrefix(chordSymbol, "D#m", "d#");
        replacePrefix(chordSymbol, "Ebm", "eb");
        replacePrefix(chordSymbol, "Em" , "e" );
        replacePrefix(chordSymbol, "E#m", "e#");
        replacePrefix(chordSymbol, "Fbm", "fb");
        replacePrefix(chordSymbol, "Fm" , "f" );
        replacePrefix(chordSymbol, "F#m", "f#");
        replacePrefix(chordSymbol, "Gbm", "gb");
        replacePrefix(chordSymbol, "Gm" , "g" );
        replacePrefix(chordSymbol, "G#m", "g#");
        replacePrefix(chordSymbol, "Abm", "ab");
        replacePrefix(chordSymbol, "Am" , "a" );
        replacePrefix(chordSymbol, "A#m", "a#");
        replacePrefix(chordSymbol, "Bbm", "bb");
        replacePrefix(chordSymbol, "Bm" , "b" );
        replacePrefix(chordSymbol, "B#m", "b#");

        // Test if the first letter of the roman numeral is a lower case letter. If it is then it is a minor chord and the rootNote is lowered by 3 semitones
        // Set chord type
        bool isMajor = isupper(chordSymbol[0]);
        Quality chordQuality = isMajor ? Quality::Major : Quality::Minor;

        // Convert to_lower 
        std::transform(chordSymbol.begin(), chordSymbol.end(), chordSymbol.begin(), ::tolower);

        // Move the rootNote according to the roman numeral
             if (removePrefix(chordSymbol, "iii")){  rootNote += 4;  }
        else if (removePrefix(chordSymbol, "vii")){  rootNote += 11; }
        else if (removePrefix(chordSymbol, "ii" )){  rootNote += 2;  }
        else if (removePrefix(chordSymbol, "iv" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "vi" )){  rootNote += 9;  }
        else if (removePrefix(chordSymbol, "i"  )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "v"  )){  rootNote += 7;  }
        else if (removePrefix(chordSymbol, "c#" )){  rootNote += 1;  }
        else if (removePrefix(chordSymbol, "db" )){  rootNote += 1;  }
        else if (removePrefix(chordSymbol, "d#" )){  rootNote += 3;  }
        else if (removePrefix(chordSymbol, "eb" )){  rootNote += 3;  }
        else if (removePrefix(chordSymbol, "e#" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "fb" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "f#" )){  rootNote += 6;  }
        else if (removePrefix(chordSymbol, "gb" )){  rootNote += 6;  }
        else if (removePrefix(chordSymbol, "g#" )){  rootNote += 8;  }
        else if (removePrefix(chordSymbol, "ab" )){  rootNote += 8;  }
        else if (removePrefix(chordSymbol, "a#" )){  rootNote += 10; }
        else if (removePrefix(chordSymbol, "bb" )){  rootNote += 10; }
        else if (removePrefix(chordSymbol, "cb" )){  rootNote += -1; }
        else if (removePrefix(chordSymbol, "b#" )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "c"  )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "d"  )){  rootNote += 2;  }
        else if (removePrefix(chordSymbol, "e"  )){  rootNote += 4;  }
        else if (removePrefix(chordSymbol, "f"  )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "g"  )){  rootNote += 7;  }
        else if (removePrefix(chordSymbol, "a"  )){  rootNote += 9;  }
        else if (removePrefix(chordSymbol, "b"  )){  rootNote += 11; }

        // Change notes if the chord is diminished or augmented
        if      (removePrefix(chordSymbol, "°"    )){ chordQuality = Quality::Diminished; }
        else if (removePrefix(chordSymbol, "+"    )){ chordQuality = Quality::Augmented;  }
        else if (removePrefix(chordSymbol, "sus2" )){ chordQuality = Quality::Sus2;       }
        else if (removePrefix(chordSymbol, "sus4" )){ chordQuality = Quality::Sus4;       }
        else if (removePrefix(chordSymbol, "5"    )){ chordQuality = Quality::PowerChord; }

        // Initialize the chord tones vector based on the chord type
        std::vector<int> chordTones;
        switch (chordQuality)
        {
            case Quality::Major:      chordTones = {0, 4,  7}; break;
            case Quality::Minor:      chordTones = {0, 3,  7}; break;
            case Quality::Diminished: chordTones = {0, 3,  6}; break;
            case Quality::Augmented:  chordTones = {0, 4,  8}; break;
            case Quality::Sus2:       chordTones = {0, 2,  7}; break;
            case Quality::Sus4:       chordTones = {0, 5,  7}; break;
            case Quality::PowerChord: chordTones = {0,     7}; break;
            default:                                             break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            chordTones.push_back(9);
        }
        else if(removePrefix(chordSymbol, "7")){
            if(chordQuality == Quality::Diminished){ chordTones.push_back(9); }
            else chordTones.push_back(10);
        }
        else if(removePrefix(chordSymbol, "9")){ 
            if(chordQuality == Quality::Diminished){ 
                chordTones.push_back(9); 
            }
            else {
                chordTones.push_back(10);
            }
                chordTones.push_back(14);
        }
        else if(removePrefix(chordSymbol, "11")){ 
            if(chordQuality == Quality::Diminished){ 
                chordTones.push_back(9); 
            }
            else {
                chordTones.push_back(10);
            }
            chordTones.push_back(14);
            chordTones.push_back(17);
        }
        else if(removePrefix(chordSymbol, "13")){ 
            if(chordQuality == Quality::Diminished){ 
                chordTones.push_back(9); 
            }
            else {
                chordTones.push_back(10);
            }
            chordTones.push_back(14);
            chordTones.push_back(17);
            chordTones.push_back(21);
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            chordTones.push_back(11);
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            chordTones.push_back(11);
            chordTones.push_back(14);
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            chordTones.push_back(11);
            chordTones.push_back(14);
            chordTones.push_back(17);
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            chordTones.push_back(11);
            chordTones.push_back(14);
            chordTones.push_back(17);
            chordTones.push_back(21);
        }

        // Flatten the 5th
        if(removePrefix(chordSymbol, "b5"      )){ chordTones[2] -= 1; chordQuality = Quality::Diminished; }
        else if(removePrefix(chordSymbol, "#5" )){ chordTones[2] += 1; chordQuality = Quality::Diminished; }

        // Remove notes if required
        if(removePrefix(chordSymbol, "no1")){ chordTones[0] = -1; }
        if(removePrefix(chordSymbol, "no3")){ chordTones[1] = -1; }
        if(removePrefix(chordSymbol, "no5")){ chordTones[2] = -1; }

        // Erase all that is below zero
        chordTones.erase(std::remove_if(chordTones.begin(), chordTones.end(), [](int i){ return i < 0; }), chordTones.end());

        // Add the rootNote to each of the chord tones
        for (int i = 0; i < chordTones.size(); i++) {
            chordTones[i] += rootNote;
        }

        if(chordSymbol.size() > 0){
            std::cerr << "Warning: Unrecognized chord symbol: " << aChordSymbol << " : " << chordSymbol << std::endl;
        }

        // Return the chord tones
        return chordTones;

    }

    void minimizeZeroDistances(std::vector<int>& chordTones)
    {
        for(auto& note : chordTones){
            if(note >= 6) note -= 12;
        }

        // Sort the chord tones
        std::sort(chordTones.begin(), chordTones.end());
    }

    void moveNthBy(std::vector<int>& chordTones, int n, int by)
    {
        chordTones[n] += by;
        std::sort(chordTones.begin(), chordTones.end());
    }

    void print(const std::string& chordSymbol)
    {
        std::cout << chordSymbol << "\t";
        std::vector<int> chordTones = getChordTones(chordSymbol);
        // minimizeZeroDistances(chordTones);
        // moveNthBy(chordTones, 2, -12);
        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << std::endl;
    }

    void print()
    {
        std::cout << chordSymbol << "\t";
        std::vector<int> chordTones = getChordTones(chordSymbol);
        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << std::endl;
    } 

    void printProgression(const std::vector<std::string>& progression)
    {
        for (int i = 0; i < progression.size(); i++) {
            print(progression[i]);
        }
    }

private:
    // Function to test if string starts with anoter string. If it does then remove the prefix from the string
    static bool removePrefix(std::string& s, const std::string& prefix)
    {
        const bool test = s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
        if(test) s.erase(0,prefix.size());
        return test;
    }

    // Function to replace a substring with another substring, but only if the substring is found at the beginning of the string
    static bool replacePrefix(std::string& str, std::string from, std::string to)
    {
        if (str.find(from) == 0) {
            str.replace(0, from.length(), to);
            return true;
        }
        return false;
    }

    // Function to replace a substring with another substring, but only if the substring is found at the beginning of the string
    static bool removeAt(std::string& str, std::string from, std::string to)
    {
        if (str.find(from) == 0) {
            str.replace(0, from.length(), to);
            return true;
        }
        return false;
    }

    std::string      chordSymbol;
    std::vector<int> chordTones;

};


class ChordProgression 
{
public:
    ChordProgression() = default;
    // Constructor to create a chord progression from a vector of chords
    ChordProgression(const std::vector<Chord>& chords)
    {
        this->setChordProgression(chords);
    }
    // Constructor to create a chord progression from a vector of chord symbols
    ChordProgression(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        this->setChordProgression(chordSymbols, rootNote);
    }
    // Constructor to create a chord progression from a string of chord symbols
    ChordProgression(const std::string& chordSymbols, const int rootNote = 0)
    {
        this->setChordProgression(chordSymbols, rootNote);
    }

    // Function to set the chord progression from a vector of chords
    void setChordProgression(const std::vector<Chord>& chords)
    {
        this->chords = chords;
    }

    // Function to set the chord progression from a vector of chord symbols
    void setChordProgression(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        for (int i = 0; i < chordSymbols.size(); i++) {
            chords.push_back(Chord(chordSymbols[i], rootNote));
        }
    }

    // Function to set the chord progression from string of chord symbols
    void setChordProgression(std::string chordSymbols, const int rootNote = 0)
    {

        // Remove all spaces from the chord symbols
        chordSymbols.erase(std::remove(chordSymbols.begin(), chordSymbols.end(), ' '), chordSymbols.end());

        std::vector<std::string> chordSymbolsVector;
        std::string chordSymbol;
        for (int i = 0; i < chordSymbols.size(); i++) {
            auto c = chordSymbols[i];
            if (c == '|' || c == ','){
                if(chordSymbol.size() > 0){
                    chordSymbolsVector.push_back(chordSymbol);
                    chordSymbol = "";
                }
            } 
            else {
                chordSymbol += chordSymbols[i];
            }
        }
        if(chordSymbol.size() > 0)
            chordSymbolsVector.push_back(chordSymbol);
        setChordProgression(chordSymbolsVector, rootNote);
    }

    // Function to add a chord to the progression
    void addChord(const Chord& chord)
    {
        chords.push_back(chord);
    }

    // Function to add a chord to the progression
    void addChord(const std::string& chordSymbol, int rootNote = 0)
    {
        chords.push_back(Chord(chordSymbol, rootNote));
    }

    // Function clear the progression
    void clear()
    {
        chords.clear();
    }

    // Print the chord progression
    void print()
    {
        for(auto& chord : chords) chord.print();
    }

    // Index Operator Overload
    Chord& operator[](int index)
    {
        return chords[index];
    }

private:
    std::vector<Chord> chords;
};



} // namespace cmtk