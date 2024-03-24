#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>
#include "Interval.h"

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

// Is the string a chord symbol in roman numerals
inline bool isRomanChordSymbol(const std::string& chordSymbol)
{
    return chordSymbol.find_first_of("ivIV") != std::string::npos;
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

// Interval to Note Name
inline std::string intervalToNoteName(I interval, int rootNote, bool isRoman = false)
{
    // Get the note number
    int note = (rootNote + interval.getSemitones()) % 12;

    // Get the quality of the interval
    auto sharpFlat = interval.getQuality();
    bool isSharp = sharpFlat > 0;
    bool isFlat  = sharpFlat < 0;

    if(isRoman){
        // Return the note name
        switch(note){
            case 0:  return "I";
            case 1:  return isSharp ? "#I" : "bII";
            case 2:  return "II";
            case 3:  return isSharp ? "#II" : "bIII";
            case 4:  return "III";
            case 5:  return "IV";
            case 6:  return isSharp ? "#IV" : "bV";
            case 7:  return "V";
            case 8:  return isSharp ? "#V" : "bVI";
            case 9:  return "VI";
            case 10: return isSharp ? "#VI" : "bVII";
            case 11: return "VII";
        }
    }
    else {
        // Return the note name
        switch(note){
            case 0:  return "C";
            case 1:  return isSharp ? "C#" : "Db";
            case 2:  return "D";
            case 3:  return isSharp ? "D#" : "Eb";
            case 4:  return "E";
            case 5:  return "F";
            case 6:  return isSharp ? "F#" : "Gb";
            case 7:  return "G";
            case 8:  return isSharp ? "G#" : "Ab";
            case 9:  return "A";
            case 10: return isSharp ? "A#" : "Bb";
            case 11: return "B";
        }
    }
    // Print error message
    std::cerr << "Error: intervalToNoteName(): Note not found note" << std::endl;
    return "C";
}

// Interval between two notes
inline 
I intervalFromNoteName(std::string n, int rootNote)
{   
    // Convert to lower case
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);

    // Get the note number
    switch(rootNote){
        case 0:{ // The key of C
            if(n == "c")  return I(1);
            if(n == "d")  return I(2);
            if(n == "e")  return I(3);
            if(n == "f")  return I(4);
            if(n == "g")  return I(5);
            if(n == "a")  return I(6);
            if(n == "b")  return I(7);
            if(n == "cb") return I(7);
            if(n == "c#") return I(1, 1);
            if(n == "db") return I(2,-1);
            if(n == "d#") return I(2, 1);
            if(n == "eb") return I(3,-1);
            if(n == "e#") return I(4);
            if(n == "fb") return I(3);
            if(n == "f#") return I(4, 1);
            if(n == "gb") return I(5,-1);
            if(n == "g#") return I(5, 1);
            if(n == "ab") return I(6,-1);
            if(n == "a#") return I(6, 1);
            if(n == "bb") return I(7,-1);
            if(n == "b#") return I(7, 1);
        }
        break;
        case 1:{ // The key of C# or Db
            if(n == "c#") return I(1);
            if(n == "db") return I(1);
            if(n == "d")  return I(2,-1);
            if(n == "d#") return I(2);
            if(n == "eb") return I(2);
            if(n == "e")  return I(3,-1);
            if(n == "fb") return I(3,-1);
            if(n == "e#") return I(3);
            if(n == "f")  return I(3);
            if(n == "f#") return I(4);
            if(n == "gb") return I(4);
            if(n == "g")  return I(5,-1);
            if(n == "g#") return I(5);
            if(n == "ab") return I(5);
            if(n == "a")  return I(6,-1);
            if(n == "a#") return I(6);
            if(n == "bb") return I(6);
            if(n == "b")  return I(7,-1);
            if(n == "b#") return I(7);
            if(n == "c")  return I(7);
            if(n == "cb") return I(7,-1);
        }
        break;
        case 2:{ // The key of D
            if(n == "d")  return I(1);
            if(n == "e")  return I(2);
            if(n == "f#") return I(3);
            if(n == "g")  return I(4);
            if(n == "a")  return I(5);
            if(n == "b")  return I(6);
            if(n == "c#") return I(7);
            if(n == "db") return I(7);
            if(n == "d#") return I(1, 1);
            if(n == "eb") return I(2,-1);
            if(n == "e#") return I(2, 1);
            if(n == "f")  return I(3,-1);
            if(n == "fb") return I(2);
            if(n == "gb") return I(3);
            if(n == "g#") return I(4, 1);
            if(n == "ab") return I(5,-1);
            if(n == "a#") return I(5, 1);
            if(n == "bb") return I(6,-1);
            if(n == "b#") return I(6, 1);
            if(n == "c")  return I(7,-1);
            if(n == "cb") return I(6);
        }
        break;
        case 3:{ // The key of D# or Eb
            if(n == "d#") return I(1);
            if(n == "eb") return I(1);
            if(n == "e")  return I(2,-1);
            if(n == "f")  return I(2);
            if(n == "f#") return I(3,-1);
            if(n == "gb") return I(3,-1);
            if(n == "g")  return I(3);
            if(n == "g#") return I(4, 1);
            if(n == "ab") return I(5,-1);
            if(n == "a")  return I(5);
            if(n == "a#") return I(5, 1);
            if(n == "bb") return I(6,-1);
            if(n == "b")  return I(6);
            if(n == "b#") return I(6, 1);
            if(n == "c")  return I(7,-1);
            if(n == "c#") return I(7);
            if(n == "db") return I(7);
            if(n == "d")  return I(1, 1);
            if(n == "fb") return I(2,-1);
        }

    }

    // Print error message
    std::cerr << "Error: intervalFromNoteName(): Unrecognized note: " << n << ", with root: " << rootNote << std::endl;

    // Return the root note
    return I(1);

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
    Chord(std::string chordSymbol, int rootNote = 0)
    {
        setChord(chordSymbol, rootNote);
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

    const std::vector<I>& getIntervals() const
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
            case Quality::Major:          chordIntervals     = {I(1), I(3)   , I(5)             }; break;
            case Quality::Minor:          chordIntervals     = {I(1), I(3,-1), I(5)             }; break;
            case Quality::Diminished:     chordIntervals     = {I(1), I(3,-1), I(5,-1)          }; break;
            case Quality::HalfDiminished: chordIntervals     = {I(1), I(3,-1), I(5,-1), I(7,-1) }; break;
            case Quality::Augmented:      chordIntervals     = {I(1), I(3)   , I(5, 1)          }; break;
            case Quality::Sus2:           chordIntervals     = {I(1), I(2)   , I(5)             }; break;
            case Quality::Sus4:           chordIntervals     = {I(1), I(4)   , I(5)             }; break;
            case Quality::PowerChord:     chordIntervals     = {I(1),          I(5)             }; break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            add(I(6));
        }
        else if(removePrefix(chordSymbol, "7")){
            add(chordQuality == Quality::Diminished ? I(6) : I(7,-1));
        }
        else if(removePrefix(chordSymbol, "9")){ 
            add(chordQuality == Quality::Diminished ? I(6) : I(7,-1));
            add(I(9));
        }
        else if(removePrefix(chordSymbol, "11")){ 
            add(chordQuality == Quality::Diminished ? I(6) : I(7,-1));
            add(I(9));
            add(I(11));
        }
        else if(removePrefix(chordSymbol, "13")){ 
            add(chordQuality == Quality::Diminished ? I(6) : I(7,-1));
            add(I(9));
            add(I(11));
            add(I(13));
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            add(I(7));
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            add(I(7));
            add(I(9));
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            add(I(7));
            add(I(9));
            add(I(11));
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            add(I(7));
            add(I(9));
            add(I(11));
            add(I(13));
        }

        // Handle more complex chords
        bool found = true;
        while(found)
        {   
            found = false;
            // Flatten
            if(removePrefix(chordSymbol, "b3"  )){ setQuality( 3,-1); found = true; }
            if(removePrefix(chordSymbol, "b5"  )){ setQuality( 5,-1); found = true; }
            if(removePrefix(chordSymbol, "b7"  )){ setQuality( 7,-1); found = true; }
            if(removePrefix(chordSymbol, "b9"  )){ setQuality( 9,-1); found = true; }
            if(removePrefix(chordSymbol, "b11" )){ setQuality(11,-1); found = true; }
            if(removePrefix(chordSymbol, "b13" )){ setQuality(13,-1); found = true; }
            
            // Sharpen
            if(removePrefix(chordSymbol, "#3"  )){ setQuality(3 , 1); found = true; }
            if(removePrefix(chordSymbol, "#5"  )){ setQuality(5 , 1); found = true; }
            if(removePrefix(chordSymbol, "#7"  )){ setQuality(7 , 1); found = true; }
            if(removePrefix(chordSymbol, "#9"  )){ setQuality(9 , 1); found = true; }
            if(removePrefix(chordSymbol, "#11" )){ setQuality(11, 1); found = true; }
            if(removePrefix(chordSymbol, "#13" )){ setQuality(13, 1); found = true; }
            
            // Remove notes if required
            if(removePrefix(chordSymbol, "no1" )){ removeDegree( 1); found = true; }
            if(removePrefix(chordSymbol, "no3" )){ removeDegree( 3); found = true; }
            if(removePrefix(chordSymbol, "no5" )){ removeDegree( 5); found = true; }
            if(removePrefix(chordSymbol, "no7" )){ removeDegree( 7); found = true; }
            if(removePrefix(chordSymbol, "no9" )){ removeDegree( 9); found = true; }
            if(removePrefix(chordSymbol, "no11")){ removeDegree(11); found = true; }
            if(removePrefix(chordSymbol, "no13")){ removeDegree(13); found = true; }

            // Add notes if required -TODO: With the I class this should be easier
            if(removePrefix(chordSymbol, "add2"  )){ add(I( 2));    found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ add(I( 4));    found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ add(I( 6));    found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ add(I( 9));    found = true; }
            if(removePrefix(chordSymbol, "add11" )){ add(I(11));    found = true; }
            if(removePrefix(chordSymbol, "add13" )){ add(I(13));    found = true; }
            if(removePrefix(chordSymbol, "addb2" )){ add(I( 2,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb4" )){ add(I( 4,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb6" )){ add(I( 6,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb9" )){ add(I( 9,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb11")){ add(I(11,-1)); found = true; }
            if(removePrefix(chordSymbol, "addb13")){ add(I(13,-1)); found = true; }
            if(removePrefix(chordSymbol, "add#2" )){ add(I( 2, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#4" )){ add(I( 4, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#6" )){ add(I( 6, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#9" )){ add(I( 9, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#11")){ add(I(11, 1)); found = true; }
            if(removePrefix(chordSymbol, "add#13")){ add(I(13, 1)); found = true; }
        }

        // Sort the chordIntervals
        std::sort(chordIntervals.begin(), chordIntervals.end());

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
                    std::string note = intervalToNoteName(interval, rootNote, isRoman);
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
                    // Same for chordIntervals_old
                    chordIntervals.insert(chordIntervals.begin(), chordIntervals[slashNote]);
                    chordIntervals.erase(chordIntervals.begin() + slashNote + 1);
                    // Set the bass note
                    bassNote = rootNote + slashNote;
                
                }
                else // Add the note if not already present
                {
                    insert(0,intervalFromNoteName(slashNoteName, rootNote));
                }
                // Set the slash flag
                slash = true;
            }
                
        }        


        // Add the rest of the note names
        for(auto interval : chordIntervals){
            if(interval.getDegree() != 1)
                noteNames.push_back(intervalToNoteName(interval, rootNote, isRoman));
            else 
                noteNames.push_back(rootName);
        }
        
        // Print the noteNames
        for(auto note : noteNames){
            std::cout << note << " ";
        }
        std::cout << std::endl;

        // Convert the chordIntervals to int and assign to chordTones
        std::vector<int> chordTones;
        for (auto& interval : chordIntervals) {
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

    void setQuality(int aDegree, int aQuality)
    {
        // Find the Degree and set the quality
        for(auto& interval : chordIntervals)
        {
            if(interval.getDegree() == aDegree)
            {
                interval.setQuality(aQuality);
                return;
            }
        }
        // If the degree is not found, add it
        chordIntervals.push_back(I(aDegree, aQuality));
    }

    void add(I interval)
    {
        // If an equal interval is already present, then do not add it
        for(auto& i : chordIntervals){
            if(i == interval) return;
        }

        // Add the interval
        chordIntervals.push_back(interval);
    }

    void insert(int index, I n){
        // Test if interval already present
        for(auto& interval : chordIntervals){
            if(interval == n){ 
                // If it is the move it the the new index
                chordIntervals.erase(std::remove(chordIntervals.begin(), chordIntervals.end(), n), chordIntervals.end());
                chordIntervals.insert(chordIntervals.begin() + index, n);
                return;
            }
        }

        // If not, add the interval
        chordIntervals.insert(chordIntervals.begin() + index, n);
    }

    // Remove Interval
    void remove(I n)
    {
        chordIntervals.erase(std::remove(chordIntervals.begin(), chordIntervals.end(), n), chordIntervals.end());
    }

    void removeDegree(int aDegree)
    {
        chordIntervals.erase(std::remove_if(chordIntervals.begin(), chordIntervals.end(), [aDegree](I i){ return i.getDegree() == aDegree; }), chordIntervals.end());
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

    void printIntervals(){
        // Print the chord intervals
        for(auto& interval : chordIntervals){
            std::cout << interval.getString() << " ";
        }
        std::cout << std::endl;
    }

    void printSemitones(){
        // Print the chord intervals
        for(auto& interval : chordIntervals){
            std::cout << interval.getSemitones() << " ";
        }
        std::cout << std::endl;        
    }

    void printNoteNames()
    {
        // Convert the intervals to chord tones
        std::vector<std::string> noteNames;
        for(auto interval : chordIntervals){
            std::cout << intervalToNoteName(interval, rootNote) << " ";
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

    void zeroCenter()
    {
        // Zero Distance
        for(auto& note : chordTones){
            if(note > 6) note -= 12;
        }
        
    }

    bool hasInterval(I interval)
    {
        for(auto& i : chordIntervals){
            if(i == interval) return true;
        }
        return false;
    }

    // Function to add or subtract an octave to a specific note defined by the interval
    bool moveInterval(I interval, int octaves)
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
        for(auto& i : chordIntervals){
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


private:
    // Size function
    size_t size()
    {
        return chordTones.size();
    }

    // Empty function
    bool empty()
    {
        return chordTones.empty();
    }

    // Chord Symbol
    std::string      chordSymbol;
    // Chord Tones
    std::vector<int> chordTones;
    // Chord Intervals
    std::vector<I> chordIntervals;

    // Note Names
    std::vector<std::string> noteNames;

    // Root Note
    int rootNote = 0;
    // Bass Note
    int bassNote = 0;


};

// ----------------------------------------------------------------------- //
// ----------------------- ChordProgression Class ------------------------ //
// ----------------------------------------------------------------------- //
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
        chords.clear();
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

    // Size function
    size_t size()
    {
        return chords.size();
    }

    // Empty function
    bool empty()
    {
        return chords.empty();
    }

private:
    std::vector<Chord> chords;
};

// ----------------------------------------------------------------------- //
// ----------------------- ChordSequencer Class -------------------------- //
// ----------------------------------------------------------------------- //
class ChordSequencer {
public:
    // Constructor
    ChordSequencer() = default;

    // Function to set the chord progression
    void setChordProgression(const ChordProgression& aChordProgression)
    {
        chordProgression = aChordProgression;
        rewind();
    }

    std::vector<int> next(int min=0, int max=127, int mindist=0)
    {
        // If the chord progression is empty then return an empty vector
        if(chordProgression.empty()) return {};
        // Loop through the chord progression
        if(++index >= chordProgression.size()) index = 0;
        // Return the chord tones
        current = chordProgression[index].getGroupRange(min,max,mindist);
        return current;
    }

    int getBassNote(int min=0, int max=127)
    {
        return chordProgression[index].getBassNote(min,max);
    }

    // Function to reset the sequencer
    void rewind()
    {
        index = -1;
    }

private:
    ChordProgression chordProgression;
    int index = -1;
    std::vector<int> current = {};
};


// ----------------------------------------------------------------------- //
// ----------------------- ChordProgressions Class ----------------------- //
// ----------------------------------------------------------------------- //
class ChordProgressions {
public:
    // Constructor
    ChordProgressions()
    {
        // Create the chord progressions
        createChordProgressions();
    };

    // Function to create the chord progressions
    void createChordProgressions()
    {
        // Major Chord Progressions
        chordProgressions["2-5-1"]               = ChordProgression("ii7|V7|I7");
        chordProgressions["Axis"]                = ChordProgression("I|V|vi|iv");
        chordProgressions["Axis2"]               = ChordProgression("vi|IV|I|V");
        chordProgressions["Andalusian"]          = ChordProgression("i|bVII|bVI|V");
        chordProgressions["AeolianVamp"]         = ChordProgression("i|bVII|bVI|bVII");
        chordProgressions["DooWop"]              = ChordProgression("I|vi|IV|V");
        chordProgressions["MixolydianVamp"]      = ChordProgression("I|bVII|IV|I");
        chordProgressions["PlagelCascade"]       = ChordProgression("i|bIII|bVII|IV");
        chordProgressions["RedHot1"]             = ChordProgression("i|bVII|v|bVI");
        chordProgressions["RedHot2"]             = ChordProgression("I|V|ii|IV");
        chordProgressions["RedHot3"]             = ChordProgression("IV|I|V|vi");
        chordProgressions["RedHot4"]             = ChordProgression("I|V|vi|IV");
        chordProgressions["RoyalRoad"]           = ChordProgression("I|IV|iii|vi");
        chordProgressions["KissFromARose"]       = ChordProgression("bVI|bVII|I");
        chordProgressions["SuperMarioCadence"]   = ChordProgression("I|bVI|bVII|I");
        chordProgressions["AugmentedClimb"]      = ChordProgression("I|I+|I6no5|I7no5|IV");
        chordProgressions["LastNightOnEarth"]    = ChordProgression("I|I+|I6no5|I7no5|IV|iv|I|I");
        chordProgressions["Ghibli"]              = ChordProgression("IV|V7|iii|vi");
        // Sad Chord Progressions from https://www.pianote.com/blog/sad-chord-progressions/
        chordProgressions["PopProgression"]      = ChordProgression("vi|IV|I|V");
        chordProgressions["HarmonicMinorAxis"]   = ChordProgression("vi|IV|I|bIII");
        chordProgressions["Creep"]               = ChordProgression("I|III|IV|iv");
        chordProgressions["HarmonicVamp"]        = ChordProgression("i|i|VI|V");
        chordProgressions["HouseOfTheRisingSun"] = ChordProgression("i|III|IV|VI");
        chordProgressions["Harmonic Shift"]      = ChordProgression("i|iv|III|V");
        chordProgressions["AeolianClosedLoop"]   = ChordProgression("i|bVII|iv|i");
        chordProgressions["LanaProgression"]     = ChordProgression("i|III|v|VI");
        chordProgressions["Emotional"]           = ChordProgression("vi|IV|V|iii");
        chordProgressions["MoonlightSonata"]     = ChordProgression("i|VI|ii|V");
        chordProgressions["Sting"]               = ChordProgression("i|VII|iv|V");
        chordProgressions["MinorMysteryClimb"]   = ChordProgression("IV|V|vi");
        // The 5 Sad Piano Chord Progressions https://pianowithjonny.com/piano-lessons/5-sad-piano-chord-progressions/
        chordProgressions["Evanescence"]         = ChordProgression("I|iii|I|iii");
        chordProgressions["PrincessLeia"]        = ChordProgression("I|iv6");
        chordProgressions["Sentimental"]         = ChordProgression("i|V|i|vi7b5"); // Normally arranged with decending bass line i | V/7 | i/b7 | vi7b5
        chordProgressions["LoveProgression"]     = ChordProgression("I|V|vi|iii|IV|I|ii7|V"); // I | V/7 | vi | iii/5 | IV | I/3 | ii7 | V
        // The 12 bar blues progression
        chordProgressions["Blues"]               = ChordProgression("I7|IV7|I7|I7|IV7|IV7|I7|I7|V7|IV7|I7|V7");
        // Jazz Progressions
        chordProgressions["RhythmChanges"]       = ChordProgression("I|vi|ii|V");
        // Cadence
        chordProgressions["PlagalCadence"]       = ChordProgression("IV|I");
        chordProgressions["PerfectCadence"]      = ChordProgression("V7|I");
    }

    // Function to add a chord progression to the map
    void addChordProgression(const std::string& chordProgression, const ChordProgression& progression)
    {
        chordProgressions[chordProgression] = progression;
    }

    // Overload index operator to get the chord progression
    ChordProgression& operator[](const std::string& chordProgression)
    {
        return chordProgressions[chordProgression];
    }

    // Print all the chord progressions
    void print()
    {
        for (auto& chordProgression : chordProgressions) {
            std::cout << chordProgression.first << ":\n";
            chordProgression.second.print();
        }
    }

private:
    std::map<std::string, ChordProgression> chordProgressions; // TODO: Make this into a static private member
};












} // namespace cmtk
