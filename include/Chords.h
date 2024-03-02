#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>


class Chords {
public:

    enum class ChordType {
        Major,
        Minor,
        Diminished,
        Augmented,
        Sus2,
        Sus4
    };

    // Function to test if string starts with anoter string. If it does then remove the prefix from the string
    static bool startsWith(std::string& s, const std::string& prefix)
    {
        const bool test = s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
        if(test) s.erase(0,prefix.size());
        return test;
    }

    // Get the chord tones from roman numeral
    static std::vector<int> getChordTones(std::string romanNumeral, int rootNote = 0){

        // Chech if the roman numeral contains 'i', 'v', 'I' or 'V'
        bool skip = false;
        if(romanNumeral[0] == 'b' && romanNumeral.find_first_of("ivIV") == std::string::npos)
        {
            skip = true;
        }


        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(!skip){
        while (romanNumeral[0] == 'b' || romanNumeral[0] == '#') {
            if      (romanNumeral[0] == 'b') { rootNote -= 1; }
            else if (romanNumeral[0] == '#') { rootNote += 1; }
            romanNumeral.erase(0,1);
        }
        }

        // Test if the first letter of the roman numeral is a lower case letter. If it is then it is a minor chord and the rootNote is lowered by 3 semitones
        // Set chord type
        bool isMajor = isupper(romanNumeral[0]);
        bool isMinor = !isMajor;
        ChordType chordType = isMajor ? ChordType::Major : ChordType::Minor;

        // Convert to_lower 
        std::transform(romanNumeral.begin(), romanNumeral.end(), romanNumeral.begin(), ::tolower);

        // Move the rootNote according to the roman numeral
             if (startsWith(romanNumeral, "iii")){  rootNote += 4;  }
        else if (startsWith(romanNumeral, "vii")){  rootNote += 11; }
        else if (startsWith(romanNumeral, "ii" )){  rootNote += 2;  }
        else if (startsWith(romanNumeral, "iv" )){  rootNote += 5;  }
        else if (startsWith(romanNumeral, "vi" )){  rootNote += 9;  }
        else if (startsWith(romanNumeral, "i"  )){  rootNote += 0;  }
        else if (startsWith(romanNumeral, "v"  )){  rootNote += 7;  }
        else if (startsWith(romanNumeral, "c#" )){  rootNote += 1;  }
        else if (startsWith(romanNumeral, "db" )){  rootNote += 1;  }
        else if (startsWith(romanNumeral, "d#" )){  rootNote += 3;  }
        else if (startsWith(romanNumeral, "eb" )){  rootNote += 3;  }
        else if (startsWith(romanNumeral, "e#" )){  rootNote += 5;  }
        else if (startsWith(romanNumeral, "f#" )){  rootNote += 6;  }
        else if (startsWith(romanNumeral, "gb" )){  rootNote += 6;  }
        else if (startsWith(romanNumeral, "g#" )){  rootNote += 8;  }
        else if (startsWith(romanNumeral, "ab" )){  rootNote += 8;  }
        else if (startsWith(romanNumeral, "a#" )){  rootNote += 10; }
        else if (startsWith(romanNumeral, "bb" )){  rootNote += 10; }
        else if (startsWith(romanNumeral, "cb" )){  rootNote += 11; }
        else if (startsWith(romanNumeral, "b#" )){  rootNote += 0;  }
        else if (startsWith(romanNumeral, "c"  )){  rootNote += 0;  }
        else if (startsWith(romanNumeral, "d"  )){  rootNote += 2;  }
        else if (startsWith(romanNumeral, "e"  )){  rootNote += 4;  }
        else if (startsWith(romanNumeral, "f"  )){  rootNote += 5;  }
        else if (startsWith(romanNumeral, "g"  )){  rootNote += 7;  }
        else if (startsWith(romanNumeral, "a"  )){  rootNote += 9;  }
        else if (startsWith(romanNumeral, "b"  )){  rootNote += 11; }


        // Test if the first part of the string matches a roman numeral. If it does, then assign the chord tones to the chordTones vector
        std::vector<int> chordTones;
        // Chords in the Major scale
        if(isMajor){  chordTones = {0, 4,  7};   }
        else       {  chordTones = {0, 3,  7};   }

        // Change notes if the chord is diminished or augmented
        if      (startsWith(romanNumeral, "°"    )){ chordTones[2] -= 1; chordType = ChordType::Diminished; }
        else if (startsWith(romanNumeral, "+"    )){ chordTones[2] += 1; chordType = ChordType::Augmented;  }
        else if (startsWith(romanNumeral, "sus2" )){ chordTones[1] -= isMajor ? 2 : 1; chordType = ChordType::Sus2;  }
        else if (startsWith(romanNumeral, "sus4" )){ chordTones[1] += isMajor ? 1 : 2; chordType = ChordType::Sus4;  }

        // Add Extension
        if(startsWith(romanNumeral, "6")){
            if(chordType == ChordType::Diminished){ chordTones.push_back(9); }
            else chordTones.push_back(9);
        }
        else if(startsWith(romanNumeral, "7")){
            if(chordType == ChordType::Diminished){ chordTones.push_back(9); }
            else chordTones.push_back(10);
        }
        else if(startsWith(romanNumeral, "maj7")){ 
            chordTones.push_back(11);
        }




        // Flatten the 5th
        if(startsWith(romanNumeral, "b5"      )){ chordTones[2] -= 1; chordType = ChordType::Diminished; }
        else if(startsWith(romanNumeral, "#5" )){ chordTones[2] += 1; chordType = ChordType::Diminished; }

        // Remove notes if required
        if(startsWith(romanNumeral, "no1")){ chordTones[0] = -1; }
        if(startsWith(romanNumeral, "no3")){ chordTones[1] = -1; }
        if(startsWith(romanNumeral, "no5")){ chordTones[2] = -1; }

        // Erase all that is below zero
        chordTones.erase(std::remove_if(chordTones.begin(), chordTones.end(), [](int i){ return i < 0; }), chordTones.end());

        // Add the rootNote to each of the chord tones
        for (int i = 0; i < chordTones.size(); i++) {
            chordTones[i] += rootNote;
        }

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

    void printChordTones(const std::string& romanNumeral)
    {
        std::cout << romanNumeral << "\t";
        std::vector<int> chordTones = getChordTones(romanNumeral);
        // minimizeZeroDistances(chordTones);
        // moveNthBy(chordTones, 1, 12);
        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << std::endl;
    }

    void printProgression(const std::vector<std::string>& progression)
    {
        for (int i = 0; i < progression.size(); i++) {
            printChordTones(progression[i]);
        }
    }


};

