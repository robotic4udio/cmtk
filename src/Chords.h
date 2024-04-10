#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <cctype>
#include "Interval.h"
#include "Roman.h" 

namespace cmtk {

// ----------------------------------------------------------------------- //
// ----------------------------- Helper Functions ------------------------ //
// ----------------------------------------------------------------------- //
// Test if string starts with prefix string. If it does then remove the prefix and return true.
inline bool removePrefix(std::string& s, const std::string& prefix)
{
    if(s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0){
        s.erase(0,prefix.size());
        return true;
    }
    return false;
}

// Test if string starts with prefix string. If it does then replace the prefix and return true.
inline bool replacePrefix(std::string& s, const std::string& prefix, const std::string& to)
{
    if(s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0){
        s.replace(0, prefix.length(), to);
        return true;
    }
    return false;
}



// Interval between two notes
inline 
Interval intervalFromNoteName(std::string n, int rootNote)
{   
    // Convert to lower case
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);

    // Get the note number
    switch(rootNote){
        case 0:{ // The key of C
            if(n == "c")  return Interval(1);
            if(n == "d")  return Interval(2);
            if(n == "e")  return Interval(3);
            if(n == "f")  return Interval(4);
            if(n == "g")  return Interval(5);
            if(n == "a")  return Interval(6);
            if(n == "b")  return Interval(7);
            if(n == "cb") return Interval(7);
            if(n == "c#") return Interval(1, 1);
            if(n == "db") return Interval(2,-1);
            if(n == "d#") return Interval(2, 1);
            if(n == "eb") return Interval(3,-1);
            if(n == "e#") return Interval(4);
            if(n == "fb") return Interval(3);
            if(n == "f#") return Interval(4, 1);
            if(n == "gb") return Interval(5,-1);
            if(n == "g#") return Interval(5, 1);
            if(n == "ab") return Interval(6,-1);
            if(n == "a#") return Interval(6, 1);
            if(n == "bb") return Interval(7,-1);
            if(n == "b#") return Interval(7, 1);
        }
        break;
        case 1:{ // The key of C# or Db
            if(n == "c#") return Interval(1);
            if(n == "db") return Interval(1);
            if(n == "d")  return Interval(2,-1);
            if(n == "d#") return Interval(2);
            if(n == "eb") return Interval(2);
            if(n == "e")  return Interval(3,-1);
            if(n == "fb") return Interval(3,-1);
            if(n == "e#") return Interval(3);
            if(n == "f")  return Interval(3);
            if(n == "f#") return Interval(4);
            if(n == "gb") return Interval(4);
            if(n == "g")  return Interval(5,-1);
            if(n == "g#") return Interval(5);
            if(n == "ab") return Interval(5);
            if(n == "a")  return Interval(6,-1);
            if(n == "a#") return Interval(6);
            if(n == "bb") return Interval(6);
            if(n == "b")  return Interval(7,-1);
            if(n == "b#") return Interval(7);
            if(n == "c")  return Interval(7);
            if(n == "cb") return Interval(7,-1);
        }
        break;
        case 2:{ // The key of D
            if(n == "d")  return Interval(1);
            if(n == "e")  return Interval(2);
            if(n == "f#") return Interval(3);
            if(n == "g")  return Interval(4);
            if(n == "a")  return Interval(5);
            if(n == "b")  return Interval(6);
            if(n == "c#") return Interval(7);
            if(n == "db") return Interval(7);
            if(n == "d#") return Interval(1, 1);
            if(n == "eb") return Interval(2,-1);
            if(n == "e#") return Interval(2, 1);
            if(n == "f")  return Interval(3,-1);
            if(n == "fb") return Interval(2);
            if(n == "gb") return Interval(3);
            if(n == "g#") return Interval(4, 1);
            if(n == "ab") return Interval(5,-1);
            if(n == "a#") return Interval(5, 1);
            if(n == "bb") return Interval(6,-1);
            if(n == "b#") return Interval(6, 1);
            if(n == "c")  return Interval(7,-1);
            if(n == "cb") return Interval(6);
        }
        break;
        case 3:{ // The key of D# or Eb
            if(n == "d#") return Interval(1);
            if(n == "eb") return Interval(1);
            if(n == "e")  return Interval(2,-1);
            if(n == "f")  return Interval(2);
            if(n == "f#") return Interval(3,-1);
            if(n == "gb") return Interval(3,-1);
            if(n == "g")  return Interval(3);
            if(n == "g#") return Interval(4, 1);
            if(n == "ab") return Interval(5,-1);
            if(n == "a")  return Interval(5);
            if(n == "a#") return Interval(5, 1);
            if(n == "bb") return Interval(6,-1);
            if(n == "b")  return Interval(6);
            if(n == "b#") return Interval(6, 1);
            if(n == "c")  return Interval(7,-1);
            if(n == "c#") return Interval(7);
            if(n == "db") return Interval(7);
            if(n == "d")  return Interval(1, 1);
            if(n == "fb") return Interval(2,-1);
        }

    }

    // Print error message
    std::cerr << "Error: intervalFromNoteName(): Unrecognized note: " << n << ", with root: " << rootNote << std::endl;

    // Return the root note
    return Interval(1);

}

// Get NoteName from beginnign of string
inline std::string getNoteNameString(std::string& s)
{
    if(s.empty()){
        // Print error message
        std::cerr << "Error: Unrecognized note" << std::endl;
        return "";
    }

    // Convert to string s to lower case
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);

    // Is the note expressed in roman numerals
    if(isRomanChordSymbol(s))
    {
        // Create empty string for result
        std::string result = "";

        // While the first character is a 'b' or '#' add it to the result
        while(s[0] == 'b' || s[0] == '#'){
            if(s[0] == 'b'){ result += "b"; s.erase(0,1); }
            if(s[0] == '#'){ result += "#"; s.erase(0,1); }
        }

        // Loop until no more symbols are found
        bool found = !s.empty();
        while(found){
            found = !s.empty();
            if(s[0] == 'i'){ result += "I"; s.erase(0,1); found = true; }
            if(s[0] == 'v'){ result += "V"; s.erase(0,1); found = true; }
        }

        return result;
    } 

    // Is the note expressed in arabic numerals
    if(isArabicChordSymbol(s))
    {
        // Create empty string for result
        std::string result = "";

        // Check for sharp or flat
        // While the first character is a 'b' or '#' add it to the result
        while(s[0] == 'b' || s[0] == '#'){
            if(s[0] == 'b'){ result += "b"; s.erase(0,1); }
            if(s[0] == '#'){ result += "#"; s.erase(0,1); }
        }

        // Return if empty
        if(s.empty()){ return ""; }

        // Loop until no more symbols are found
        bool found = !s.empty();
        while(found){
            found = !s.empty();
            if(s[0] == '1'){ result += "I";   s.erase(0,1); found = true; }
            if(s[0] == '3'){ result += "III"; s.erase(0,1); found = true; }
            if(s[0] == '2'){ result += "II";  s.erase(0,1); found = true; }
            if(s[0] == '4'){ result += "IV";  s.erase(0,1); found = true; }
            if(s[0] == '5'){ result += "V";   s.erase(0,1); found = true; }
            if(s[0] == '6'){ result += "VI";  s.erase(0,1); found = true; }
            if(s[0] == '7'){ result += "VII"; s.erase(0,1); found = true; }
        }

        return result;
    }
    else 
    {
        // Convert to lower case
        char s0 = s[0];
        char s1 = s[1];

        if(s.size() >= 2){
            if(s1 == '#'){
                if(s0 == 'c'){ s.erase(0,2); return "C#"; };
                if(s0 == 'd'){ s.erase(0,2); return "D#"; };
                if(s0 == 'e'){ s.erase(0,2); return "E#"; };
                if(s0 == 'f'){ s.erase(0,2); return "F#"; };
                if(s0 == 'g'){ s.erase(0,2); return "G#"; };
                if(s0 == 'a'){ s.erase(0,2); return "A#"; };
                if(s0 == 'b'){ s.erase(0,2); return "B#"; };
            }
            else if(s1 == 'b'){
                if(s0 == 'c'){ s.erase(0,2); return "Cb"; };
                if(s0 == 'd'){ s.erase(0,2); return "Db"; };
                if(s0 == 'e'){ s.erase(0,2); return "Eb"; };
                if(s0 == 'f'){ s.erase(0,2); return "Fb"; };
                if(s0 == 'g'){ s.erase(0,2); return "Gb"; };
                if(s0 == 'a'){ s.erase(0,2); return "Ab"; };
                if(s0 == 'b'){ s.erase(0,2); return "Bb"; };
            }
        }
        else if(s.size() >= 1){
            if(s0 == 'c'){ s.erase(0,1); return "C"; };
            if(s0 == 'd'){ s.erase(0,1); return "D"; };
            if(s0 == 'e'){ s.erase(0,1); return "E"; };
            if(s0 == 'f'){ s.erase(0,1); return "F"; };
            if(s0 == 'g'){ s.erase(0,1); return "G"; };
            if(s0 == 'a'){ s.erase(0,1); return "A"; };
            if(s0 == 'b'){ s.erase(0,1); return "B"; };
        }
    }


    // Print error message
    std::cerr << "Error: getNoteNameString(): Unrecognized note" << std::endl;
    return "";
}


// Get Note Number from beginnign of string
inline int getNoteNumber(const std::string& s, int root=0)
{
    if(s.empty()) throw std::runtime_error("Error: Unrecognized note");

    // Is the note expressed in roman numerals
    if(isRomanChordSymbol(s)) return romanPitchToSemitone(s,root);

    // Is the note expressed in arabic numerals
    if(isArabicChordSymbol(s)) return arabicPitchToSemitone(s,root);

    // Convert to lower case
    std::string n = s;
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);    

    // Get the note number
    if     (n == "c")  return 0;
    else if(n == "d")  return 2;
    else if(n == "e")  return 4;
    else if(n == "f")  return 5;
    else if(n == "g")  return 7;
    else if(n == "a")  return 9;
    else if(n == "b")  return 11;
    else if(n == "cb") return 11;
    else if(n == "c#") return 1;
    else if(n == "db") return 1;
    else if(n == "d#") return 3;
    else if(n == "eb") return 3;
    else if(n == "e#") return 5;
    else if(n == "fb") return 4;
    else if(n == "f#") return 6;
    else if(n == "gb") return 6;
    else if(n == "g#") return 8;
    else if(n == "ab") return 8;
    else if(n == "a#") return 10;
    else if(n == "bb") return 10;
    else if(n == "b#") return 0;

    // Throw error
    throw std::runtime_error("Error: getNoteNumber(): Unrecognized note: " + s);
}









// ----------------------------------------------------------------------- //
// ----------------------------- Chord Class ----------------------------- //
// ----------------------------------------------------------------------- //
class Chord {
public:
    // Constructor
    Chord() = default;
    Chord(const std::string& chordSymbol, int rootNote = 0)
    {
        setChord(chordSymbol, rootNote);
    }

    Chord(const Intervals& intervals, int rootNote=0)
    {
        setChord(intervals,rootNote);
    }

    // Enum class to represent the quality of the chord
    enum class Quality {
        Major,
        Minor,
        Diminished,
        HalfDiminished,
        Augmented,
        Sus2,
        Sus4,
        PowerChord,
    };


    // Create a chord from a set of intervals
    void setChord(const Intervals& aIntervals, int aRootNote)
    {
        auto intervals = aIntervals;
        intervals.print();
        std::string chordSymbol = "";
        bool maj = false;
        if     (intervals.contains("3 b7", "#5 b6")){ chordSymbol = "dom"  ; intervals.remove("3")           ; }
        else if(intervals.contains("3 #5", "b3 5" )){ chordSymbol = "aug"  ; intervals.remove("3")           ; }
        else if(intervals.contains("b3 b5","3 5"  )){ chordSymbol = "dim"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("3"            )){ chordSymbol = "maj"  ; intervals.remove("3"); maj=true ; }
        else if(intervals.contains("b3"           )){ chordSymbol = "min"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("2 5","3 b3"   )){ chordSymbol = "sus2" ; intervals.remove("2")           ; }
        else if(intervals.contains("4 5","3 b3"   )){ chordSymbol = "sus4" ; intervals.remove("4")           ; }
        else if(intervals.contains("5"            )){ chordSymbol = "5"    ;                                 ; }

        // Add Extension
        if     (intervals.contains("b7 9 11 13"  )){ chordSymbol += "13"      ; intervals.remove("b7 9 11 13"   );  }
        else if(intervals.contains("b7 b9 11 13" )){ chordSymbol += "13 b9"   ; intervals.remove("b7 b9 11 13"  );  }
        else if(intervals.contains("b7 9 b11 13" )){ chordSymbol += "13 b11"  ; intervals.remove("b7 9 b11 13"  );  }
        else if(intervals.contains("b7 b9 b11 13")){ chordSymbol += "13 b9b11"; intervals.remove("b7 b9 b11 13" );  }
        else if(intervals.contains("b7 9 11"     )){ chordSymbol += "11"      ; intervals.remove("b7 9 11" );  }
        else if(intervals.contains("b7 b9 11"    )){ chordSymbol += "11 b9"   ; intervals.remove("b7 b9 11");  }
        else if(intervals.contains("b7 9"        )){ chordSymbol += "9"       ; intervals.remove("b7 9" );  }
        else if(intervals.contains("b7"          )){ chordSymbol += "7"       ; intervals.remove("b7" );  }
        else if(intervals.contains("7 9 11 13"   )){ chordSymbol += maj ? "13" : "Maj13" ; intervals.remove("7 9 11 13" );  }
        else if(intervals.contains("7 b9 11 13"  )){ chordSymbol += maj ? "13 b9" : "Maj13 b9" ; intervals.remove("7 b9 11 13" );  }
        else if(intervals.contains("7 9 b11 13"  )){ chordSymbol += maj ? "13 b11" : "Maj13 b11" ; intervals.remove("7 9 b11 13" );  }
        else if(intervals.contains("7 b9 b11 13" )){ chordSymbol += maj ? "13 b9b11" : "Maj13 b9b11" ; intervals.remove("7 b9 b11 13" );  }
        else if(intervals.contains("7 9 11"      )){ chordSymbol += maj ? "11" : "Maj11" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 b9 11"     )){ chordSymbol += maj ? "11 b9" : "Maj11 b9" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 9"         )){ chordSymbol += maj ? "9"  : "Maj9"  ; intervals.remove("7 9" );  }
        else if(intervals.contains("7"           )){ chordSymbol += maj ? "7"  : "Maj7"  ; intervals.remove("7" );  }

        // Check if the 5 is present
        if     (intervals.contains("b3" )){ chordSymbol += " b3"    ; intervals.remove("b3"  );  }
        else if(intervals.contains("#3" )){ chordSymbol += " #3"    ; intervals.remove("#3"  );  }

        if     (intervals.contains("b5" )){ chordSymbol += " b5"    ;                            }
        else if(intervals.contains("#5" )){ chordSymbol += " #5"    ;                            }

        if     (intervals.contains("b7" )){ chordSymbol += " b7"    ; intervals.remove("b7"  );  }
        else if(intervals.contains("#7" )){ chordSymbol += " #7"    ; intervals.remove("#7"  );  }

        if     (intervals.contains("b9" )){ chordSymbol += " b9"    ; intervals.remove("b9"  );  }
        else if(intervals.contains("#9" )){ chordSymbol += " #9"    ; intervals.remove("#9"  );  }

        if     (intervals.contains("b11")){ chordSymbol += " b11"   ; intervals.remove("b11" );  }
        else if(intervals.contains("#11")){ chordSymbol += " #11"   ; intervals.remove("#11" );  }

        if     (intervals.contains("b13")){ chordSymbol += " b13"   ; intervals.remove("b13" );  }
        else if(intervals.contains("#13")){ chordSymbol += " #13"   ; intervals.remove("#13" );  }


        // Check for no 3rd or 5th
        if(!intervals.containsDegree(1)) chordSymbol += " no1";
        else intervals.removeDegree(1);

        if(!intervals.containsDegree(5)) chordSymbol += " no5";
        else intervals.removeDegree(5);


        // Check added notes
        static std::vector<std::string> addedNotes = {
            "b2" , "2" , "#2" , 
            "b3" , "3" , "#3" ,
            "b4" , "4" , "#4" ,
            // "b5" , "5" , "#5" ,
            "b6" , "6" , "#6" ,
            "b7" , "7" , "#7" ,
            "b9" , "9" , "#9" ,
            "b11", "11", "#11",
            "b13", "13", "#13",
        };
            
        for(const auto& note : addedNotes){
            if(intervals.contains(note)){
                chordSymbol += " add" + note;
                intervals.remove(note);
            }
        }

        // Print the chord symbol
        std::cout << "Chord Symbol: " << chordSymbol << std::endl;
    }

    // Get the chord symbol
    std::string getChordSymbol()
    {
        return chordSymbol;
    }

    const Intervals& getIntervals() const
    {
        return chordIntervals;
    }

    // Get Voicing from a list of degrees in the wanted order
    const std::vector<int> getSemitones() const
    {
        auto root = getRoot();
        std::vector<int> voicing;
        for(auto i : chordIntervals){
            voicing.push_back(i.getSemitones()+root);
        }
        return std::move(voicing);
    }

    // Overload the index operator
    int operator[](int index)
    {   
        while(index < 0)                      index += this->size();
        while(index >= chordIntervals.size()) index -= this->size();

        return chordIntervals[index].getSemitones()+getRoot();
    }


    // Get Voicing from a list of degrees in the wanted order
    std::vector<int> getVoicing(std::vector<int> degrees, bool addBass=false, bool addRest=false)
    {
        auto intervals = this->chordIntervals;
        std::vector<int> voicing;
        if(addBass) voicing.push_back(getBass());
        int last = -1;  
        std::set<int> usedDegrees;
        for(auto d : degrees){ 
            if(intervals.containsDegree(d)){
                usedDegrees.insert(d);
                auto i = intervals.getIntervalFromDegree(d);
                auto n = i.getSemitones()+getRoot();
                while(n < last) n += 12;
                voicing.push_back(n);
                last = n;
            }
        }

        // Remove the used degrees
        for(auto d : usedDegrees){
            intervals.removeDegree(d);
        }

        // Add the rest of the intervals
        if(addRest){
            for(auto i : intervals){
                auto n = i.getSemitones()+getRoot();
                while(n < last) n += 12;
                voicing.push_back(n);
                last = n;
            }
        }

        return std::move(voicing);
    }
    // Get Voicing from a list of degrees in the wanted order
    std::vector<int> getVoicing(bool addBass=false)
    {
        std::vector<int> voicing;
        if(addBass) voicing.push_back(getBass());
        auto root = getRoot();
        for(auto i : chordIntervals){
            voicing.push_back(i.getSemitones()+root);
        }
        return std::move(voicing);
    }

    // Set the chord from a chord symbol - rootNote only used for roman numerals
    void setChord(const std::string& aChordSymbol, int aRoot = 0){
        auto chordSymbol = aChordSymbol;
        std::string rootName = "";
        chordIntervals.clear();

        // Test if the chors symbol is in roman numerals
        const bool isRoman = isRomanChordSymbol(chordSymbol);

        // Get the root note
        int rootNote = 0;

        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(isRoman){
            while(chordSymbol[0] == 'b' || chordSymbol[0] == '#') {
                if      (chordSymbol[0] == 'b') { rootNote -= 1; rootName += "b"; }
                else if (chordSymbol[0] == '#') { rootNote += 1; rootName += "#"; }
                chordSymbol.erase(0,1);
            }
        }

        // Replace start
        if     (replacePrefix(chordSymbol, "Cbm", "cb")){ }
        else if(replacePrefix(chordSymbol, "Cm" , "c" )){ }
        else if(replacePrefix(chordSymbol, "C#m", "c#")){ }
        else if(replacePrefix(chordSymbol, "Dbm", "db")){ }
        else if(replacePrefix(chordSymbol, "Dm" , "d" )){ }
        else if(replacePrefix(chordSymbol, "D#m", "d#")){ }
        else if(replacePrefix(chordSymbol, "Ebm", "eb")){ }
        else if(replacePrefix(chordSymbol, "Em" , "e" )){ }
        else if(replacePrefix(chordSymbol, "E#m", "e#")){ }
        else if(replacePrefix(chordSymbol, "Fbm", "fb")){ }
        else if(replacePrefix(chordSymbol, "Fm" , "f" )){ }
        else if(replacePrefix(chordSymbol, "F#m", "f#")){ }
        else if(replacePrefix(chordSymbol, "Gbm", "gb")){ }
        else if(replacePrefix(chordSymbol, "Gm" , "g" )){ }
        else if(replacePrefix(chordSymbol, "G#m", "g#")){ }
        else if(replacePrefix(chordSymbol, "Abm", "ab")){ }
        else if(replacePrefix(chordSymbol, "Am" , "a" )){ }
        else if(replacePrefix(chordSymbol, "A#m", "a#")){ }
        else if(replacePrefix(chordSymbol, "Bbm", "bb")){ }
        else if(replacePrefix(chordSymbol, "Bm" , "b" )){ }
        else if(replacePrefix(chordSymbol, "B#m", "b#")){ }

        // Test if the first letter of the roman numeral is a lower case letter. If it is then it is a minor chord and the rootNote is lowered by 3 semitones
        // Set chord type
        bool isMajor = isupper(chordSymbol[0]);
        Quality chordQuality = isMajor ? Quality::Major : Quality::Minor;

        // Convert to_lower 
        std::transform(chordSymbol.begin(), chordSymbol.end(), chordSymbol.begin(), ::tolower);

        // Move the rootNote according according to the chord symbol --- Roman Numerals
             if (removePrefix(chordSymbol, "iii" )){ rootNote += 4;  rootName += "III"; }
        else if (removePrefix(chordSymbol, "vii" )){ rootNote += 11; rootName += "VII"; }
        else if (removePrefix(chordSymbol, "ii"  )){ rootNote += 2;  rootName += "II" ; }
        else if (removePrefix(chordSymbol, "iv"  )){ rootNote += 5;  rootName += "IV" ; }
        else if (removePrefix(chordSymbol, "vi"  )){ rootNote += 9;  rootName += "VI" ; }
        else if (removePrefix(chordSymbol, "i"   )){ rootNote += 0;  rootName += "I"  ; }
        else if (removePrefix(chordSymbol, "v"   )){ rootNote += 7;  rootName += "V"  ; }
        // Move the rootNote according according to the chord symbol --- Specific Chords
        else if (removePrefix(chordSymbol, "c#"  )){ rootNote = 1;  rootName = "C#"; }
        else if (removePrefix(chordSymbol, "db"  )){ rootNote = 1;  rootName = "Db"; }
        else if (removePrefix(chordSymbol, "d#"  )){ rootNote = 3;  rootName = "D#"; }
        else if (removePrefix(chordSymbol, "eb"  )){ rootNote = 3;  rootName = "Eb"; }
        else if (removePrefix(chordSymbol, "e#"  )){ rootNote = 5;  rootName = "E#"; }
        else if (removePrefix(chordSymbol, "fb"  )){ rootNote = 5;  rootName = "Fb"; }
        else if (removePrefix(chordSymbol, "f#"  )){ rootNote = 6;  rootName = "F#"; }
        else if (removePrefix(chordSymbol, "gb"  )){ rootNote = 6;  rootName = "Gb"; }
        else if (removePrefix(chordSymbol, "g#"  )){ rootNote = 8;  rootName = "G#"; }
        else if (removePrefix(chordSymbol, "ab"  )){ rootNote = 8;  rootName = "Ab"; }
        else if (removePrefix(chordSymbol, "a#"  )){ rootNote = 10; rootName = "A#"; }
        else if (removePrefix(chordSymbol, "bb"  )){ rootNote = 10; rootName = "Bb"; }
        else if (removePrefix(chordSymbol, "cb"  )){ rootNote = 11; rootName = "Cb"; } 
        else if (removePrefix(chordSymbol, "b#"  )){ rootNote = 0;  rootName = "B#"; }
        else if (removePrefix(chordSymbol, "c"   )){ rootNote = 0;  rootName = "C" ; }
        else if (removePrefix(chordSymbol, "d"   )){ rootNote = 2;  rootName = "D" ; }
        else if (removePrefix(chordSymbol, "e"   )){ rootNote = 4;  rootName = "E" ; }
        else if (removePrefix(chordSymbol, "f"   )){ rootNote = 5;  rootName = "F" ; }
        else if (removePrefix(chordSymbol, "g"   )){ rootNote = 7;  rootName = "G" ; }
        else if (removePrefix(chordSymbol, "a"   )){ rootNote = 9;  rootName = "A" ; }
        else if (removePrefix(chordSymbol, "b"   )){ rootNote = 11; rootName = "B" ; }
    
        // Change notes if the chord is diminished or augmented
        if      (removePrefix(chordSymbol, "°"       )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "dim"     )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "ø"       )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "halfdim" )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "aug"     )){ chordQuality = Quality::Augmented;      }
        else if (removePrefix(chordSymbol, "+"       )){ chordQuality = Quality::Augmented;      }
        else if (removePrefix(chordSymbol, "sus2"    )){ chordQuality = Quality::Sus2;           }
        else if (removePrefix(chordSymbol, "sus4"    )){ chordQuality = Quality::Sus4;           }
        else if (removePrefix(chordSymbol, "5"       )){ chordQuality = Quality::PowerChord;     }

        // Remove stuff from the chord symbol
        const std::string chars = " ^()";
        // Remove the chars
        for (char c: chars) {
            chordSymbol.erase(std::remove(chordSymbol.begin(), chordSymbol.end(), c), chordSymbol.end());
        }

        // Initialize the chord tones vector based on the chord type
        switch (chordQuality)
        {
            case Quality::Major:          chordIntervals     = {Interval(1), Interval(3)   , Interval(5)             }; break;
            case Quality::Minor:          chordIntervals     = {Interval(1), Interval(3,-1), Interval(5)             }; break;
            case Quality::Diminished:     chordIntervals     = {Interval(1), Interval(3,-1), Interval(5,-1)          }; break;
            case Quality::HalfDiminished: chordIntervals     = {Interval(1), Interval(3,-1), Interval(5,-1), Interval(7,-1) }; break;
            case Quality::Augmented:      chordIntervals     = {Interval(1), Interval(3)   , Interval(5, 1)          }; break;
            case Quality::Sus2:           chordIntervals     = {Interval(1), Interval(2)   , Interval(5)             }; break;
            case Quality::Sus4:           chordIntervals     = {Interval(1), Interval(4)   , Interval(5)             }; break;
            case Quality::PowerChord:     chordIntervals     = {Interval(1),          Interval(5)             }; break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            chordIntervals.add(Interval(6));
        }
        else if(removePrefix(chordSymbol, "7")){
            chordIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
        }
        else if(removePrefix(chordSymbol, "9")){ 
            chordIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            chordIntervals.add(Interval(9));
        }
        else if(removePrefix(chordSymbol, "11")){ 
            chordIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            chordIntervals.add(Interval(9),Interval(11));
        }
        else if(removePrefix(chordSymbol, "13")){ 
            chordIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            chordIntervals.add(Interval(9),Interval(11),Interval(13));
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            chordIntervals.add(Interval(7));
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            chordIntervals.add(Interval(7),Interval(9));
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            chordIntervals.add(Interval(7),Interval(9),Interval(11));
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            chordIntervals.add(Interval(7),Interval(9),Interval(11),Interval(13));
        }

        // Handle more complex chords
        bool found = true;
        while(found)
        {   
            found = false;
            // Flatten
            if(removePrefix(chordSymbol, "b3"    )){ chordIntervals.setQuality( 3, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b5"    )){ chordIntervals.setQuality( 5, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b7"    )){ chordIntervals.setQuality( 7, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b9"    )){ chordIntervals.setQuality( 9, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b11"   )){ chordIntervals.setQuality(11, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b13"   )){ chordIntervals.setQuality(13, -1, true); found = true; }
            
            // Sharpen
            if(removePrefix(chordSymbol, "#3"    )){ chordIntervals.setQuality(3 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#5"    )){ chordIntervals.setQuality(5 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#7"    )){ chordIntervals.setQuality(7 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#9"    )){ chordIntervals.setQuality(9 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#11"   )){ chordIntervals.setQuality(11,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#13"   )){ chordIntervals.setQuality(13,  1, true); found = true; }

            // Add notes if required
            if(removePrefix(chordSymbol, "add2"  )){ chordIntervals.add(Interval( 2));        found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ chordIntervals.add(Interval( 4));        found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ chordIntervals.add(Interval( 6));        found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ chordIntervals.add(Interval( 9));        found = true; }
            if(removePrefix(chordSymbol, "add11" )){ chordIntervals.add(Interval(11));        found = true; }
            if(removePrefix(chordSymbol, "add13" )){ chordIntervals.add(Interval(13));        found = true; }

            // Remove notes if required
            if(removePrefix(chordSymbol, "no1"   )){ chordIntervals.removeDegree( 1);         found = true; }
            if(removePrefix(chordSymbol, "no3"   )){ chordIntervals.removeDegree( 3);         found = true; }
            if(removePrefix(chordSymbol, "no5"   )){ chordIntervals.removeDegree( 5);         found = true; }
            if(removePrefix(chordSymbol, "no7"   )){ chordIntervals.removeDegree( 7);         found = true; }
            if(removePrefix(chordSymbol, "no9"   )){ chordIntervals.removeDegree( 9);         found = true; }
            if(removePrefix(chordSymbol, "no11"  )){ chordIntervals.removeDegree(11);         found = true; }
            if(removePrefix(chordSymbol, "no13"  )){ chordIntervals.removeDegree(13);         found = true; }
        }

        // Sort the chordIntervals
        chordIntervals.sort();

        // Print the noteNames
        this->rootNote = rootNote+aRoot;
        this->bassNote = rootNote+aRoot;

        // Handle slash chords
        if(removePrefix(chordSymbol,"/")){
            // Get the note number of the slash note
            bassNote = getNoteNumber(chordSymbol,aRoot);
            chordSymbol.clear();
        }

        // Add the rest of the note names
        for(auto interval : chordIntervals){
            if(interval.getDegree() != 1)
                noteNames.push_back(interval.getNoteName(rootNote, isRoman));
            else 
                noteNames.push_back(rootName);
        }
        
        if(chordSymbol.size() > 0){
            std::cerr << "setChord(): Warning: Error parsing chord symbol: " << aChordSymbol << " - Remaining: " << chordSymbol << std::endl;
        }

    }

    // Get the semitone of the Bass Note, same as root if not a slash chord
    int getBass(int min=0, int max=127) const
    {
        auto note = bassNote - 12 + mOctave*12;
        while(note < min) note += 12;
        while(note > max) note -= 12;

        return note;
    }

    int getRoot() const 
    {
        return rootNote+mOctave*12;
    }

    void printIntervals()
    {
        chordIntervals.print();
    }



    void printSemitones(){
        // Print the chord intervals
        for(auto interval : chordIntervals){
            std::cout << interval.getSemitones() << " ";
        }
        std::cout << std::endl;        
    }

    void printNoteNames()
    {
        // Convert the intervals to chord tones
        std::vector<std::string> noteNames;
        for(auto interval : chordIntervals){
            std::cout << interval.getNoteName(rootNote) << " ";
        }
        std::cout << std::endl;
    }

    void print()
    {
        std::cout << getChordSymbol() << "\t";
        const auto& chordTones = getSemitones();

        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << "BassNote: " << bassNote << "\t";
        std::cout << std::endl;
        printNoteNames();
    }

    // Size function
    size_t size() const
    {
        return chordIntervals.size();
    }

    // Empty function
    bool empty() const
    {
        return chordIntervals.empty();
    }

private:
    // Chord Symbol
    std::string      chordSymbol;
    // Chord Intervals
    Intervals        chordIntervals;
    // Note Names
    std::vector<std::string> noteNames;

    // Root Note
    int rootNote = 0;
    // Bass Note
    int bassNote = 0;
    // Octave
    int mOctave = 3;

};









} // namespace cmtk
