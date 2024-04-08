#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
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

// Is the string a chord symbol in arabic numerals
inline bool isArabicChordSymbol(const std::string& chordSymbol)
{
    if(chordSymbol.empty()) return false;

    // If size is 2 then the first character must be an 'b' or '#'
    if(chordSymbol.size() >= 2){
        if(chordSymbol[0] != 'b' && chordSymbol[0] != '#') return false;
        return chordSymbol.find_first_of("1234567") == 1;
    }

    // If size is 1 then the first character must be a number
    return chordSymbol.find_first_of("1234567") == 0;

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
inline
std::string getNoteNameString(std::string& s)
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

        // Check for sharp or flat
        if     (s[0] == 'b'){ result += "b"; s.erase(0,1); }
        else if(s[0] == '#'){ result += "#"; s.erase(0,1); }

        // Return if empty
        if(s.empty()){ return ""; }

        // Loop until no more symbols are found
        bool found = !s.empty();
        while(!s.empty() && found){
            found = false;
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
        if     (s[0] == 'b'){ result += "b"; s.erase(0,1); }
        else if(s[0] == '#'){ result += "#"; s.erase(0,1); }

        // Return if empty
        if(s.empty()){ return ""; }

        // Loop until no more symbols are found
        bool found = !s.empty();
        while(!s.empty() && found){
            found = false;
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

    // Function to get the chord tones from a chord symbol
    void setChord(std::string aChordSymbol, int aRootNote = 0)
    {
        chordSymbol = aChordSymbol;
        chordTones = getChordTones(aChordSymbol, aRootNote);
    }

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
        else if(intervals.contains("2 5"          )){ chordSymbol = "sus2" ; intervals.remove("2")           ; }
        else if(intervals.contains("4 5"          )){ chordSymbol = "sus4" ; intervals.remove("4")           ; }
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

        //if(!intervals.containsDegree(5)) chordSymbol += " no5";
        //else intervals.removeDegree(5);


        // Check added notes - Naturals
        static std::vector<std::string> addedNotes = {
            "b2" , "2" , "#2" , 
            "b3" , "3" , "#3" ,
            "b4" , "4" , "#4" ,
            "b5" , "5" , "#5" ,
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

    // Get the chord tones
    std::vector<int> getChordTones()
    {
        return chordTones;
    }

    const Intervals& getIntervals() const
    {
        return chordIntervals;
    }

    // Get the chord tones with an inversion
    std::vector<int> getChordTones(int inversion)
    {
        inversion = inversion % chordTones.size();

        auto notes = this->chordTones;
        // If the inversion is positive, rotate the notes to the right
        while(inversion > 0){
            std::rotate(notes.begin(), notes.begin() + 1, notes.end());
            inversion--;
            // Add one octave to the last note
            notes.back() += 12;
        }
        // If the inversion is negative, rotate the notes to the left
        while(inversion < 0){
            std::rotate(notes.rbegin(), notes.rbegin() + 1, notes.rend());
            inversion++;
            // Subtract one octave from the first note
            notes.front() -= 12;
        }
        // Sort the notes
        // std::sort(notes.begin(), notes.end());

        return notes;
    }

    // Overload the index operator
    int operator[](int index)
    {   
        if(index >= chordTones.size()){
            std::cerr << "Error: Index out of range" << std::endl;
            return 0;
        }
        return chordTones[index];
    }

    

    // Get the chord tones from a chord symbol
    std::vector<int> getChordTones(const std::string& aChordSymbol, int rootNote = 0){
        auto chordSymbol = aChordSymbol;
        std::string rootName = "";
        chordIntervals.clear();

        // Test if the chors symbol is in roman numerals
        const bool isRoman = isRomanChordSymbol(chordSymbol);

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
        else if (removePrefix(chordSymbol, "c#"  )){ rootNote += 1;  rootName = "C#"; }
        else if (removePrefix(chordSymbol, "db"  )){ rootNote += 1;  rootName = "Db"; }
        else if (removePrefix(chordSymbol, "d#"  )){ rootNote += 3;  rootName = "D#"; }
        else if (removePrefix(chordSymbol, "eb"  )){ rootNote += 3;  rootName = "Eb"; }
        else if (removePrefix(chordSymbol, "e#"  )){ rootNote += 5;  rootName = "E#"; }
        else if (removePrefix(chordSymbol, "fb"  )){ rootNote += 5;  rootName = "Fb"; }
        else if (removePrefix(chordSymbol, "f#"  )){ rootNote += 6;  rootName = "F#"; }
        else if (removePrefix(chordSymbol, "gb"  )){ rootNote += 6;  rootName = "Gb"; }
        else if (removePrefix(chordSymbol, "g#"  )){ rootNote += 8;  rootName = "G#"; }
        else if (removePrefix(chordSymbol, "ab"  )){ rootNote += 8;  rootName = "Ab"; }
        else if (removePrefix(chordSymbol, "a#"  )){ rootNote += 10; rootName = "A#"; }
        else if (removePrefix(chordSymbol, "bb"  )){ rootNote += 10; rootName = "Bb"; }
        else if (removePrefix(chordSymbol, "cb"  )){ rootNote += 11; rootName = "Cb"; } 
        else if (removePrefix(chordSymbol, "b#"  )){ rootNote += 0;  rootName = "B#"; }
        else if (removePrefix(chordSymbol, "c"   )){ rootNote += 0;  rootName = "C" ; }
        else if (removePrefix(chordSymbol, "d"   )){ rootNote += 2;  rootName = "D" ; }
        else if (removePrefix(chordSymbol, "e"   )){ rootNote += 4;  rootName = "E" ; }
        else if (removePrefix(chordSymbol, "f"   )){ rootNote += 5;  rootName = "F" ; }
        else if (removePrefix(chordSymbol, "g"   )){ rootNote += 7;  rootName = "G" ; }
        else if (removePrefix(chordSymbol, "a"   )){ rootNote += 9;  rootName = "A" ; }
        else if (removePrefix(chordSymbol, "b"   )){ rootNote += 11; rootName = "B" ; }
    
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
            if(removePrefix(chordSymbol, "b3"  )){ chordIntervals.setQuality( 3,-1,true); found = true; }
            if(removePrefix(chordSymbol, "b5"  )){ chordIntervals.setQuality( 5,-1,true); found = true; }
            if(removePrefix(chordSymbol, "b7"  )){ chordIntervals.setQuality( 7,-1,true); found = true; }
            if(removePrefix(chordSymbol, "b9"  )){ chordIntervals.setQuality( 9,-1,true); found = true; }
            if(removePrefix(chordSymbol, "b11" )){ chordIntervals.setQuality(11,-1,true); found = true; }
            if(removePrefix(chordSymbol, "b13" )){ chordIntervals.setQuality(13,-1,true); found = true; }
            
            // Sharpen
            if(removePrefix(chordSymbol, "#3"  )){ chordIntervals.setQuality(3 , 1,true); found = true; }
            if(removePrefix(chordSymbol, "#5"  )){ chordIntervals.setQuality(5 , 1,true); found = true; }
            if(removePrefix(chordSymbol, "#7"  )){ chordIntervals.setQuality(7 , 1,true); found = true; }
            if(removePrefix(chordSymbol, "#9"  )){ chordIntervals.setQuality(9 , 1,true); found = true; }
            if(removePrefix(chordSymbol, "#11" )){ chordIntervals.setQuality(11, 1,true); found = true; }
            if(removePrefix(chordSymbol, "#13" )){ chordIntervals.setQuality(13, 1,true); found = true; }
            
            // Remove notes if required
            if(removePrefix(chordSymbol, "no1" )){ chordIntervals.removeDegree( 1); found = true; }
            if(removePrefix(chordSymbol, "no3" )){ chordIntervals.removeDegree( 3); found = true; }
            if(removePrefix(chordSymbol, "no5" )){ chordIntervals.removeDegree( 5); found = true; }
            if(removePrefix(chordSymbol, "no7" )){ chordIntervals.removeDegree( 7); found = true; }
            if(removePrefix(chordSymbol, "no9" )){ chordIntervals.removeDegree( 9); found = true; }
            if(removePrefix(chordSymbol, "no11")){ chordIntervals.removeDegree(11); found = true; }
            if(removePrefix(chordSymbol, "no13")){ chordIntervals.removeDegree(13); found = true; }

            // Add notes if required -TODO: With the I class this should be easier
            if(removePrefix(chordSymbol, "add2"  )){ chordIntervals.add(Interval( 2));    found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ chordIntervals.add(Interval( 4));    found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ chordIntervals.add(Interval( 6));    found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ chordIntervals.add(Interval( 9));    found = true; }
            if(removePrefix(chordSymbol, "add11" )){ chordIntervals.add(Interval(11));    found = true; }
            if(removePrefix(chordSymbol, "add13" )){ chordIntervals.add(Interval(13));    found = true; }
            if(removePrefix(chordSymbol, "addb2" )){ chordIntervals.add(Interval( 2,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb4" )){ chordIntervals.add(Interval( 4,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb6" )){ chordIntervals.add(Interval( 6,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb9" )){ chordIntervals.add(Interval( 9,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb11")){ chordIntervals.add(Interval(11,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb13")){ chordIntervals.add(Interval(13,-1)); found = true; }
            if(removePrefix(chordSymbol, "add#2" )){ chordIntervals.add(Interval( 2, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#4" )){ chordIntervals.add(Interval( 4, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#6" )){ chordIntervals.add(Interval( 6, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#9" )){ chordIntervals.add(Interval( 9, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#11")){ chordIntervals.add(Interval(11, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#13")){ chordIntervals.add(Interval(13, 1)); found = true; }
        }

        // Sort the chordIntervals
        chordIntervals.sort();

        // Print the noteNames
        this->rootNote = rootNote;
        this->bassNote = rootNote;

        // Handle slash chords
        bool slash = false;
        if(removePrefix(chordSymbol,"/")){
            // Get the note name
            std::string slashNoteName = getNoteNameString(chordSymbol);
            std::transform(slashNoteName.begin(), slashNoteName.end(), slashNoteName.begin(), ::tolower);

            // Print Slash Note
            std::cout << "Slash Note: " << slashNoteName << std::endl;

            if(slashNoteName.size() > 0){

                int slashNote = 0;
                bool found = false;
                for(auto interval : chordIntervals){
                    std::string note = interval.getNoteName(rootNote, isRoman);
                    // Note to_lower
                    std::transform(note.begin(), note.end(), note.begin(), ::tolower);

                    if(slashNoteName==note){
                        found = true;
                        break;
                    }
                    slashNote++;
                }

                // Move the slash note to the front. Not by rotating the noteNames vector, just by inserting the slash note at the front and removing it from where it was
                if(found){
                    // Same for chordIntervals
                    chordIntervals.insert(0, chordIntervals[slashNote]);
                    // Set the bass note
                    bassNote = rootNote + slashNote;
                
                }
                else // Add the note if not already present
                {
                    chordIntervals.insert(0,intervalFromNoteName(slashNoteName, rootNote));
                }
                // Set the slash flag
                slash = true;
            }
                
        }        

        // Add the rest of the note names
        for(auto interval : chordIntervals){
            if(interval.getDegree() != 1)
                noteNames.push_back(interval.getNoteName(rootNote, isRoman));
            else 
                noteNames.push_back(rootName);
        }
        
        // Print the noteNames
        // for(auto note : noteNames){
        //     std::cout << note << " ";
        // }
        // std::cout << std::endl;

        // Convert the chordIntervals to int and assign to chordTones
        std::vector<int> chordTones;
        for (auto interval : chordIntervals) {
            chordTones.push_back(interval.getSemitones());
        }

        // Sort the chord tones by shifting down an octave if the next value is lower
        for (int i = 0; i < chordTones.size()-1; i++) {
            if (chordTones[i] > chordTones[i+1]) {
                chordTones[i] -= 12;
            }
        }

        // Add the rootNote to each of the chord tones
        for (int i = 0; i < chordTones.size(); i++) {
            chordTones[i] += rootNote;
        }

        // Store the bassnote to be used after inversion confusion
        if(slash) bassNote = chordTones[0];

        if(chordSymbol.size() > 0){
            std::cerr << "getChordTones(): Warning: Error parsing chord symbol: " << aChordSymbol << " - Remaining: " << chordSymbol << std::endl;
        }

        // Return the chord tones
        return chordTones;

    }

    // Function to find the lowest chord tone
    int lowest()
    {
        int lowest = 1000;
        for(auto note : chordTones){
            if(note < lowest) lowest = note;
        }
        return lowest;
    }

    // highest
    int highest()
    {
        int highest = -1000;
        for(auto note : chordTones){
            if(note > highest) highest = note;
        }
        return highest;
    }

    // Mean
    float mean()
    {
        float sum = 0;
        for(auto note : chordTones){
            sum += note;
        }
        return sum / chordTones.size();
    }

    // Median
    int median(std::vector<int> vec)
    {
        std::sort(vec.begin(), vec.end());
        return vec[vec.size()/2];
    }

    int smallestNoteDistance(std::vector<int> chordTones)
    {
        std::sort(chordTones.begin(), chordTones.end());
        int smallest = 1000;
        for (int i = 1; i < chordTones.size(); i++) {
            int dist = abs(chordTones[i] - chordTones[i-1]);
            // std::cout << "Dist: " << dist << std::endl;
            if (dist < smallest){
                smallest = dist;
            }
        }
        // std::cout << "Smallest: " << smallest << std::endl;
        return smallest;
    }

    // Group in range
    std::vector<int> getGroupRange(int low=0, int high=127, int mindist=0, bool print=false)
    {        
        auto notes = chordTones;
        // Sort the chord tones
        std::sort(notes.begin(), notes.end());

        // Move into the right octave
        while(median(notes) < low){
            for(auto& note : notes){
                note += 12;
                while(note < low ) note += 12;
            }
        }
        
        // If the distance to the previous note is less than 3, move it up an octave
        while(mindist && smallestNoteDistance(notes) < mindist){
            for (int i = 1; i < notes.size(); i++) {
                int dist = notes[i] - notes[i-1];
                // std::cout << "Dist: " << dist << std::endl;
                if (dist < mindist){
                    notes[i] += 12;
                    std::sort(notes.begin(), notes.end());
                    break;
                }
            }
        }

        for(auto& note : notes){
            while(note > high) note -= 12;
        }

        std::sort(notes.begin(), notes.end());

        if(print){
            for(auto note : notes){
                std::cout << note << " ";
            }
            std::cout << std::endl;
        }

        return notes;
    }

    int getBassNote(int min=0, int max=127)
    {
        auto note = bassNote;
        while(note < min) note += 12;
        while(note > max) note -= 12;

        return note;
    }

    const int getRoot() const 
    {
        return rootNote;
    }

    void zeroCollaps(std::vector<int>& chordTones)
    {
        for(auto& note : chordTones){
            if(note >= 6) note -= 12;
        }

        // Sort the chord tones
        std::sort(chordTones.begin(), chordTones.end());
    }

    void moveNthBy(int n, int by)
    {
        chordTones[n] += by;
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

    void print(int inversion = 0)
    {
        std::cout << getChordSymbol() << "_" << inversion << "\t";
        const std::vector<int>& chordTones = getChordTones(inversion);

        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << "BassNote: " << bassNote << "\t";
        std::cout << std::endl;

    }

    // Is the chord expressed in arabic numerals
    bool isArabic(const std::string& chordSymbol)
    {
        return chordSymbol.find_first_of("1234567") < 2;
    }

    Chord& zeroCenter()
    {
        // Zero Distance
        for(auto& note : chordTones){
            if(note > 6) note -= 12;
        }

        return *this;
    }

    // Function to add or subtract an octave to a specific note defined by the interval
    bool moveInterval(Interval interval, int octaves)
    {
        int n = 0;
        for(auto& i : chordIntervals){
            if(i == interval){
                moveNthBy(n, octaves*12);
                return true;
            }
            n++;
        }
        return false;
        // std::sort(chordTones.begin(), chordTones.end());
    }
    bool moveInterval(int deg, int octaves)
    {
        int n = 0;
        for(auto i : chordIntervals){
            if(i.getDegree() == deg){
                moveNthBy(n, octaves*12);
                return true;
            }
            n++;
        }
        return false;
        // std::sort(chordTones.begin(), chordTones.end());
    }


    // Function to open the voicing of the chord
    void openVoicing()
    {
        // Test if the chord has a 3rd
        if     (moveInterval(3 , 1)){}

        // Test if the chord has a 7th
        if     (moveInterval(7 , 1)){}
    }

    // Function to voice lead the chord to another chord
    std::vector<int> voiceLead(Chord other)
    {
        std::vector<int> newNotes;
        std::vector<int> neededNotes = this->getChordTones();
        std::vector<int> otherNotes = other.getChordTones();
        // Sort the possible notes
        std::sort(neededNotes.begin(), neededNotes.end());
        std::sort(otherNotes.begin() , otherNotes.end());
        /* Print the possible notes
        for(auto& note : possibleNotes){
            std::cout << note << " ";
        }
        std::cout << std::endl;
        */

        // Loop through the chord tones
        while(!neededNotes.empty())
        {
            // Get the first note
            int note = neededNotes.front();
            // Remove the note from the needed notes
            neededNotes.erase(neededNotes.begin());
            // Loop through the other notes
            for(int i = 0; i < otherNotes.size(); i++){
                for(int octave=-2; octave<3; octave++){
                    // If the note is within 3 semitones of the other note
                    if(abs(note - otherNotes[i] + octave*12) < 3){
                        // Add the note to the new notes
                        newNotes.push_back(otherNotes[i] + octave*12);
                        // Remove the note from the other notes
                        otherNotes.erase(otherNotes.begin() + i);
                        // Break the loop
                        break;
                    }
                }

            }
        }


        // Sort the new chord tones
        otherNotes = other.getChordTones();
        std::sort(otherNotes.begin(), otherNotes.end());
        // Print the other notes
        for(auto& note : otherNotes){
            std::cout << note << " ";
        }
        std::cout << std::endl;
        // Sort the new chord tones
        std::sort(newNotes.begin(), newNotes.end());
        // Print the new notes
        for(auto& note : newNotes){
            std::cout << note << " ";
        }
        std::cout << std::endl;

        return newNotes;
    }

    // Function to change the order and octave of the chord tones such that no tones are closer than min semitones
    void minDistVoicing(int min=6)
    {
        // Sort the chord tones
        std::sort(chordTones.begin(), chordTones.end());
        again:
        for (int i = 1; i < chordTones.size(); i++) {
            // If the distance between the notes is less than min
            if(chordTones[i] - chordTones[i-1] < min){
                // Move the note up an octave
                chordTones[i] += 12;
                // Sort the chord tones
                std::sort(chordTones.begin(), chordTones.end());
                // Return true
                goto again;
            }
        }
    }

    // Size function
    const size_t size() const
    {
        return chordTones.size();
    }

    // Empty function
    const bool empty() const
    {
        return chordTones.empty();
    }

private:
    // Chord Symbol
    std::string      chordSymbol;
    // Chord Tones
    std::vector<int> chordTones;
    // Chord Intervals
    Intervals chordIntervals;

    // Note Names
    std::vector<std::string> noteNames;

    // Root Note
    int rootNote = 0;
    // Bass Note
    int bassNote = 0;


};









} // namespace cmtk
