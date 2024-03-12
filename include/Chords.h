#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>

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

// ----------------------------------------------------------------------- //
// ----------------------------- Interval Functions ---------------------- //
// ----------------------------------------------------------------------- //

// Enum class to represent the intervals
enum class Interval {
     _R = 0, // Root 
    _b2,     // Flat 2nd
     _2,     // 2nd
    _s2,     // Sharp 2nd
    _b3,     // Flat 3rd
     _3,     // 3rd
    _s3,     // Sharp 3rd
    _b4,     // Flat 4th
     _4,     // 4th
    _s4,     // Sharp 4th
    _b5,     // Flat 5th
     _5,     // 5th
    _s5,     // Sharp 5th
    _b6,     // Flat 6th
     _6,     // 6th
    _s6,     // Sharp 6th
    _b7,     // Flat 7th
     _7,     // 7th
    _s7,     // Sharp 7th
    _b9,     // Flat 9th
     _9,     // 9th
    _s9,     // Sharp 9th
   _b11,     // Flat 11th
    _11,     // 11th
   _s11,     // Sharp 11th
   _b13,     // Flat 13th
    _13,     // 13th
   _s13,     // Sharp 13th
   COUNT
};

enum class NoteName {
    C = 0,
    Cs,
    Db,
    D,
    Ds,
    Eb,
    E,
    Es,
    Fb,
    F,
    Fs,
    Gb,
    G,
    Gs,
    Ab,
    A,
    As,
    Bb,
    B,
    Bs,
    Cb,
    I,
    II,
    III,
    IV,
    V,
    VI,
    VII,
    bI,
    bII,
    bIII,
    bIV,
    bV,
    bVI,
    bVII,
    sI,
    sII,
    sIII,
    sIV,
    sV,
    sVI,
    sVII,
    NA
};

// Get NoteName from beginnign of string
inline
NoteName getNoteName(std::string& s)
{
    auto copy = s;
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);

    if(s.empty()){
        // Print error message
        std::cerr << "Error: Unrecognized note" << std::endl;

        return NoteName::NA;
    }

    auto s0 = tolower(s[0]);

    if(s.size() >= 2){
        if(s[1] == '#'){
            if(s0 == 'c') return NoteName::Cs;
            if(s0 == 'd') return NoteName::Ds;
            if(s0 == 'e') return NoteName::Es;
            if(s0 == 'f') return NoteName::Fs;
            if(s0 == 'g') return NoteName::Gs;
            if(s0 == 'a') return NoteName::As;
            if(s0 == 'b') return NoteName::Bs;
        }
        else if(s[1] == 'b'){
            if(s0 == 'c') return NoteName::Cb;
            if(s0 == 'd') return NoteName::Db;
            if(s0 == 'e') return NoteName::Eb;
            if(s0 == 'f') return NoteName::Fb;
            if(s0 == 'g') return NoteName::Gb;
            if(s0 == 'a') return NoteName::Ab;
            if(s0 == 'b') return NoteName::Bb;
        }
    }
    else if(s.size() >= 1){
        if(s0 == 'c') return NoteName::C;
        if(s0 == 'd') return NoteName::D;
        if(s0 == 'e') return NoteName::E;
        if(s0 == 'f') return NoteName::F;
        if(s0 == 'g') return NoteName::G;
        if(s0 == 'a') return NoteName::A;
        if(s0 == 'b') return NoteName::B;
    }
    return NoteName::NA;
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

    char s0 = tolower(s[0]);
    char s1 = tolower(s[1]);

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
    // Print error message
    std::cerr << "Error: getNoteNameString(): Unrecognized note" << std::endl;
    return "";
}

// Convert the interval to a integer semi tone
inline
int toInt(Interval interval)
{   
    // Return the interval as an integer
    switch(interval){
        case Interval::_R:   return  0;
        case Interval::_b2:  return  1;
        case Interval::_2:   return  2;
        case Interval::_s2:  return  3;
        case Interval::_b3:  return  3;
        case Interval::_3:   return  4;
        case Interval::_s3:  return  5;
        case Interval::_b4:  return  4;
        case Interval::_4:   return  5;
        case Interval::_s4:  return  6;
        case Interval::_b5:  return  6;
        case Interval::_5:   return  7;
        case Interval::_s5:  return  8;
        case Interval::_b6:  return  8;
        case Interval::_6:   return  9;
        case Interval::_s6:  return 10;
        case Interval::_b7:  return 10;
        case Interval::_7:   return 11;
        case Interval::_s7:  return 12;
        case Interval::_b9:  return 13;
        case Interval::_9:   return 14;
        case Interval::_s9:  return 15;
        case Interval::_b11: return 16;
        case Interval::_11:  return 17;
        case Interval::_s11: return 18;
        case Interval::_b13: return 20;
        case Interval::_13:  return 21;
        case Interval::_s13: return 22;
        case Interval::COUNT: return -1;
    }

    return -1;
}

// Convert the interval to a integer semi tone
inline
int shapFlat(Interval interval)
{   
    // Return the interval as an integer
    switch(interval){
        case Interval::_R:   return   0;
        case Interval::_b2:  return  -1;
        case Interval::_2:   return   0;
        case Interval::_s2:  return   1;
        case Interval::_b3:  return  -1;
        case Interval::_3:   return   0;
        case Interval::_s3:  return   1;
        case Interval::_b4:  return  -1;
        case Interval::_4:   return   0;
        case Interval::_s4:  return   1;
        case Interval::_b5:  return  -1;
        case Interval::_5:   return   0;
        case Interval::_s5:  return   1;
        case Interval::_b6:  return  -1;
        case Interval::_6:   return   0;
        case Interval::_s6:  return   1;
        case Interval::_b7:  return  -1;
        case Interval::_7:   return   0;
        case Interval::_s7:  return   1;
        case Interval::_b9:  return  -1;
        case Interval::_9:   return   0;
        case Interval::_s9:  return   1;
        case Interval::_b11: return  -1;
        case Interval::_11:  return   0;
        case Interval::_s11: return   1;
        case Interval::_b13: return  -1;
        case Interval::_13:  return   0;
        case Interval::_s13: return   1;
        case Interval::COUNT: return  0;
    }
}

// Covert the interval to a string
inline
std::string intervalToString(Interval interval)
{
    switch(interval){
        case Interval::_R:   return "R";
        case Interval::_b2:  return "b2";
        case Interval::_2:   return "2";
        case Interval::_s2:  return "s2";
        case Interval::_b3:  return "b3";
        case Interval::_3:   return "3";
        case Interval::_s3:  return "s3";
        case Interval::_b4:  return "b4";
        case Interval::_4:   return "4";
        case Interval::_s4:  return "s4";
        case Interval::_b5:  return "b5";
        case Interval::_5:   return "5";
        case Interval::_s5:  return "s5";
        case Interval::_b6:  return "b6";
        case Interval::_6:   return "6";
        case Interval::_s6:  return "s6";
        case Interval::_b7:  return "b7";
        case Interval::_7:   return "7";
        case Interval::_s7:  return "s7";
        case Interval::_b9:  return "b9";
        case Interval::_9:   return "9";
        case Interval::_s9:  return "s9";
        case Interval::_b11: return "b11";
        case Interval::_11:  return "11";
        case Interval::_s11: return "s11";
        case Interval::_b13: return "b13";
        case Interval::_13:  return "13";
        case Interval::_s13: return "s13";
        case Interval::COUNT: return "NA";
    }
    // Print error message
    std::cerr << "Error: Unrecognized interval" << std::endl;

    return "NA";
}

// Map to convert the string to an interval
inline
Interval intervalFromString(const std::string& interval){
    if(interval == "R")  return Interval::_R;
    if(interval == "b2") return Interval::_b2;
    if(interval == "2")  return Interval::_2;
    if(interval == "s2") return Interval::_s2;
    if(interval == "b3") return Interval::_b3;
    if(interval == "3")  return Interval::_3;
    if(interval == "s3") return Interval::_s3;
    if(interval == "b4") return Interval::_b4;
    if(interval == "4")  return Interval::_4;
    if(interval == "s4") return Interval::_s4;
    if(interval == "b5") return Interval::_b5;
    if(interval == "5")  return Interval::_5;
    if(interval == "s5") return Interval::_s5;
    if(interval == "b6") return Interval::_b6;
    if(interval == "6")  return Interval::_6;
    if(interval == "s6") return Interval::_s6;
    if(interval == "b7") return Interval::_b7;
    if(interval == "7")  return Interval::_7;
    if(interval == "s7") return Interval::_s7;
    if(interval == "b9") return Interval::_b9;
    if(interval == "9")  return Interval::_9;
    if(interval == "s9") return Interval::_s9;
    if(interval == "b11")return Interval::_b11;
    if(interval == "11") return Interval::_11;
    if(interval == "s11")return Interval::_s11;
    if(interval == "b13")return Interval::_b13;
    if(interval == "13") return Interval::_13;
    if(interval == "s13")return Interval::_s13;
    
    // Print error message
    std::cerr << "Error: Unrecognized interval: " << interval << std::endl;
    // Return the root note
    return Interval::_R;
}

// Interval to Note Name
inline
std::string intervalToNoteName(Interval interval, int rootNote)
{
    // Get the note number
    int note = (rootNote + toInt(interval)) % 12;

    auto sharpFlat = shapFlat(interval);
    bool isSharp = sharpFlat > 0;
    bool isFlat  = sharpFlat < 0;

    // print note and sharp/flat
    std::cout << "Note: " << note << " sharpFlat: " << sharpFlat << " isSharp: " << isSharp << " isFlat: " << isFlat << std::endl;


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

    // Print error message
    std::cerr << "Error: intervalToNoteName(): Note not found note" << std::endl;
    return "C";
}

// Interval between two notes
inline
Interval intervalFromNoteName(std::string n, int rootNote)
{   
    // Convert to lower case
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);

    // Get the note number
    switch(rootNote){
        case 0:{
            if(n == "c") return Interval::_R;
            if(n == "d") return Interval::_2;
            if(n == "e") return Interval::_3;
            if(n == "f") return Interval::_4;
            if(n == "g") return Interval::_5;
            if(n == "a") return Interval::_6;
            if(n == "b") return Interval::_7;
            if(n == "cb") return Interval::_7;
            if(n == "c#") return Interval::_b2;
            if(n == "db") return Interval::_b2;
            if(n == "d#") return Interval::_s2;
            if(n == "eb") return Interval::_b3;
            if(n == "e#") return Interval::_4;
            if(n == "fb") return Interval::_3;
            if(n == "f#") return Interval::_s4;
            if(n == "gb") return Interval::_b5;
            if(n == "g#") return Interval::_s5;
            if(n == "ab") return Interval::_b6;
            if(n == "a#") return Interval::_s6;
            if(n == "bb") return Interval::_b7;
            if(n == "b#") return Interval::_R;
        }
        break;
        case 1:{ // The key of C# or Db
            if(n == "c#") return Interval::_R;
            if(n == "db") return Interval::_R;
            if(n == "d")  return Interval::_b2;
            if(n == "d#") return Interval::_2;
            if(n == "eb") return Interval::_2;
            if(n == "e")  return Interval::_b3;
            if(n == "fb") return Interval::_b3;
            if(n == "e#") return Interval::_3;
            if(n == "f")  return Interval::_3;
            if(n == "f#") return Interval::_4;
            if(n == "gb") return Interval::_4;
            if(n == "g")  return Interval::_b5;
            if(n == "g#") return Interval::_5;
            if(n == "ab") return Interval::_5;
            if(n == "a")  return Interval::_b6;
            if(n == "a#") return Interval::_6;
            if(n == "bb") return Interval::_6;
            if(n == "b")  return Interval::_b7;
            if(n == "b#") return Interval::_7;
            if(n == "c")  return Interval::_7;








        }
    }





    // Print note and sharp/flat


    // Print error message
    std::cerr << "Error: intervalFromNoteName(): Unrecognized note" << std::endl;

    // Return the root note
    return Interval::_R;

}


// ----------------------------------------------------------------------- //
// ----------------------------- Scale Class ----------------------------- //
// ----------------------------------------------------------------------- //

class Scale {
public:
    // Constructor
    Scale() = default;
    Scale(std::string scaleName)
    {
        setScale(scaleName);
    }

    // Function to set the scale
    void setScale(std::string aScaleName)
    {
        scaleName = aScaleName;
        if(scaleName == "Major"){ 
            scaleIntervals = {Interval::_R, Interval::_2, Interval::_3, Interval::_4, Interval::_5, Interval::_6, Interval::_7};  
            scaleTones  = {0, 2, 4, 5, 7, 9, 11}; 
            scaleChords = {"I","ii","iii","IV","V","vi","vii°"};
        }
        else if(scaleName == "Minor"){
            scaleIntervals = {Interval::_R, Interval::_2, Interval::_b3, Interval::_4, Interval::_5, Interval::_b6, Interval::_b7};
            scaleTones  = {0, 2, 3, 5, 7, 8, 10};
            scaleChords = {"i","ii°","bIII","iv","v","bVI","bVII"};
        }
        else if(scaleName == "Dorian"){
            scaleIntervals = {Interval::_R, Interval::_2, Interval::_b3, Interval::_4, Interval::_5, Interval::_6, Interval::_b7};
            scaleTones  = {0, 2, 3, 5, 7, 9, 10};
            scaleChords = {"i","ii","bIII","IV","v","vi°","bVII"};
        }
    }


private:
    // The scale name
    std::string scaleName;
    // The scale intervals
    std::vector<Interval> scaleIntervals;
    // The scale tones
    std::vector<int> scaleTones;
    // The scale chords
    std::vector<std::string> scaleChords;

};


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

    // Interval between root and another note
    Interval intervalFromRoot(std::string note, int rootNote)
    {
        return intervalFromNoteName(note, rootNote);
    }

    // Get the chord tones from a chord symbol
    std::vector<int> getChordTones(const std::string& aChordSymbol, int rootNote = 0){
        auto chordSymbol = aChordSymbol;
        std::string rootName = "";
        chordIntervals.clear();
        noteNames_.clear();
        noteNames_.push_back(NoteName::I);
        bool sharp = false;
        bool flat  = false;

        
        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(isRoman(chordSymbol)){
            while(chordSymbol[0] == 'b' || chordSymbol[0] == '#') {
                if      (chordSymbol[0] == 'b') { rootNote -= 1; rootName += "b"; flat =  true;}
                else if (chordSymbol[0] == '#') { rootNote += 1; rootName += "#"; sharp = true;}
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
             if (removePrefix(chordSymbol, "iii" )){ rootNote += 4;  rootName += "III"; noteNames_[0] = flat ? NoteName::bIII : sharp ? NoteName::sIII : NoteName::III; }
        else if (removePrefix(chordSymbol, "vii" )){ rootNote += 11; rootName += "VII"; noteNames_[0] = flat ? NoteName::bVII : sharp ? NoteName::sVII : NoteName::VII; }
        else if (removePrefix(chordSymbol, "ii"  )){ rootNote += 2;  rootName += "II" ; noteNames_[0] = flat ? NoteName::bII  : sharp ? NoteName::sII  : NoteName::II;  }
        else if (removePrefix(chordSymbol, "iv"  )){ rootNote += 5;  rootName += "IV" ; noteNames_[0] = flat ? NoteName::bIV  : sharp ? NoteName::sIV  : NoteName::IV;  }
        else if (removePrefix(chordSymbol, "vi"  )){ rootNote += 9;  rootName += "VI" ; noteNames_[0] = flat ? NoteName::bVI  : sharp ? NoteName::sVI  : NoteName::VI;  }
        else if (removePrefix(chordSymbol, "i"   )){ rootNote += 0;  rootName += "I"  ; noteNames_[0] = flat ? NoteName::bI   : sharp ? NoteName::sI   : NoteName::I;   }
        else if (removePrefix(chordSymbol, "v"   )){ rootNote += 7;  rootName += "V"  ; noteNames_[0] = flat ? NoteName::bV   : sharp ? NoteName::sV   : NoteName::V;   }
        // Move the rootNote according according to the chord symbol --- Specific Chords
        else if (removePrefix(chordSymbol, "c#"  )){ rootNote += 1;  rootName = "C#"; noteNames_[0] = NoteName::Cs; }
        else if (removePrefix(chordSymbol, "db"  )){ rootNote += 1;  rootName = "Db"; noteNames_[0] = NoteName::Db; }
        else if (removePrefix(chordSymbol, "d#"  )){ rootNote += 3;  rootName = "D#"; noteNames_[0] = NoteName::Ds; }
        else if (removePrefix(chordSymbol, "eb"  )){ rootNote += 3;  rootName = "Eb"; noteNames_[0] = NoteName::Eb; }
        else if (removePrefix(chordSymbol, "e#"  )){ rootNote += 5;  rootName = "E#"; noteNames_[0] = NoteName::Es; }
        else if (removePrefix(chordSymbol, "fb"  )){ rootNote += 5;  rootName = "Fb"; noteNames_[0] = NoteName::Fb; }
        else if (removePrefix(chordSymbol, "f#"  )){ rootNote += 6;  rootName = "F#"; noteNames_[0] = NoteName::Fs; }
        else if (removePrefix(chordSymbol, "gb"  )){ rootNote += 6;  rootName = "Gb"; noteNames_[0] = NoteName::Gb; }
        else if (removePrefix(chordSymbol, "g#"  )){ rootNote += 8;  rootName = "G#"; noteNames_[0] = NoteName::Gs; }
        else if (removePrefix(chordSymbol, "ab"  )){ rootNote += 8;  rootName = "Ab"; noteNames_[0] = NoteName::Ab; }
        else if (removePrefix(chordSymbol, "a#"  )){ rootNote += 10; rootName = "A#"; noteNames_[0] = NoteName::As; }
        else if (removePrefix(chordSymbol, "bb"  )){ rootNote += 10; rootName = "Bb"; noteNames_[0] = NoteName::Bb; }
        else if (removePrefix(chordSymbol, "cb"  )){ rootNote += 11; rootName = "Cb"; noteNames_[0] = NoteName::Cb; } 
        else if (removePrefix(chordSymbol, "b#"  )){ rootNote += 0;  rootName = "B#"; noteNames_[0] = NoteName::Bs; }
        else if (removePrefix(chordSymbol, "c"   )){ rootNote += 0;  rootName = "C" ; noteNames_[0] = NoteName::C;  }
        else if (removePrefix(chordSymbol, "d"   )){ rootNote += 2;  rootName = "D" ; noteNames_[0] = NoteName::D;  }
        else if (removePrefix(chordSymbol, "e"   )){ rootNote += 4;  rootName = "E" ; noteNames_[0] = NoteName::E;  }
        else if (removePrefix(chordSymbol, "f"   )){ rootNote += 5;  rootName = "F" ; noteNames_[0] = NoteName::F;  }
        else if (removePrefix(chordSymbol, "g"   )){ rootNote += 7;  rootName = "G" ; noteNames_[0] = NoteName::G;  }
        else if (removePrefix(chordSymbol, "a"   )){ rootNote += 9;  rootName = "A" ; noteNames_[0] = NoteName::A;  }
        else if (removePrefix(chordSymbol, "b"   )){ rootNote += 11; rootName = "B" ; noteNames_[0] = NoteName::B;  }

    
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
            case Quality::Major:          chordIntervals = {Interval::_R, Interval::_3,  Interval::_5};  break;
            case Quality::Minor:          chordIntervals = {Interval::_R, Interval::_b3, Interval::_5};  break;
            case Quality::Diminished:     chordIntervals = {Interval::_R, Interval::_b3, Interval::_b5}; break;
            case Quality::HalfDiminished: chordIntervals = {Interval::_R, Interval::_b3, Interval::_b5, Interval::_b7}; break;
            case Quality::Augmented:      chordIntervals = {Interval::_R, Interval::_3,  Interval::_s5}; break;
            case Quality::Sus2:           chordIntervals = {Interval::_R, Interval::_2,  Interval::_5};  break;
            case Quality::Sus4:           chordIntervals = {Interval::_R, Interval::_4,  Interval::_5};  break;
            case Quality::PowerChord:     chordIntervals = {Interval::_R,                Interval::_5};  break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            add(Interval::_6);
        }
        else if(removePrefix(chordSymbol, "7")){
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
        }
        else if(removePrefix(chordSymbol, "9")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
        }
        else if(removePrefix(chordSymbol, "11")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
            add(Interval::_11);
        }
        else if(removePrefix(chordSymbol, "13")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
            add(Interval::_11);
            add(Interval::_13);
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            add(Interval::_7);
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            add(Interval::_7);
            add(Interval::_9);
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            add(Interval::_7);
            add(Interval::_9);
            add(Interval::_11);
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            add(Interval::_7);
            add(Interval::_9);
            add(Interval::_11);
            add(Interval::_13);
        }

        // Handle more complex chords
        bool found = true;
        while(found)
        {   
            found = false;
            // Flatten
            if(removePrefix(chordSymbol, "b3"  )){ remove(Interval::_3);  remove(Interval::_s3);  add(Interval::_b3);  found = true; }
            if(removePrefix(chordSymbol, "b5"  )){ remove(Interval::_5);  remove(Interval::_s5);  add(Interval::_b5);  found = true; }
            if(removePrefix(chordSymbol, "b7"  )){ remove(Interval::_7);  remove(Interval::_s7);  add(Interval::_b7);  found = true; }
            if(removePrefix(chordSymbol, "b9"  )){ remove(Interval::_9);  remove(Interval::_s9);  add(Interval::_b9);  found = true; }
            if(removePrefix(chordSymbol, "b11" )){ remove(Interval::_11); remove(Interval::_s11); add(Interval::_b11); found = true; }
            if(removePrefix(chordSymbol, "b13" )){ remove(Interval::_13); remove(Interval::_s13); add(Interval::_b13); found = true; }
            
            // Sharpen
            if(removePrefix(chordSymbol, "#3"  )){ remove(Interval::_3);  remove(Interval::_b3);  add(Interval::_s3);  found = true; }
            if(removePrefix(chordSymbol, "#5"  )){ remove(Interval::_5);  remove(Interval::_b5);  add(Interval::_s5);  found = true; }
            if(removePrefix(chordSymbol, "#7"  )){ remove(Interval::_7);  remove(Interval::_b7);  add(Interval::_s7);  found = true; }
            if(removePrefix(chordSymbol, "#9"  )){ remove(Interval::_9);  remove(Interval::_b9);  add(Interval::_s9);  found = true; }
            if(removePrefix(chordSymbol, "#11" )){ remove(Interval::_11); remove(Interval::_b11); add(Interval::_s11); found = true; }
            if(removePrefix(chordSymbol, "#13" )){ remove(Interval::_13); remove(Interval::_b13); add(Interval::_s13); found = true; }
            
            // Remove notes if required
            if(removePrefix(chordSymbol, "no1" )){ remove(Interval::_R);  found = true; }
            if(removePrefix(chordSymbol, "no3" )){ remove(Interval::_3);  remove(Interval::_b3);  remove(Interval::_s3); found = true;}
            if(removePrefix(chordSymbol, "no5" )){ remove(Interval::_5);  remove(Interval::_b5);  remove(Interval::_s5); found = true;}
            if(removePrefix(chordSymbol, "no7" )){ remove(Interval::_7);  remove(Interval::_b7);  remove(Interval::_s7); found = true;}
            if(removePrefix(chordSymbol, "no9" )){ remove(Interval::_9);  remove(Interval::_b9);  remove(Interval::_s9); found = true;}
            if(removePrefix(chordSymbol, "no11")){ remove(Interval::_11); remove(Interval::_b11); remove(Interval::_s11);found = true;}
            if(removePrefix(chordSymbol, "no13")){ remove(Interval::_13); remove(Interval::_b13); remove(Interval::_s13);found = true;}

            // Add notes if required
            if(removePrefix(chordSymbol, "add2"  )){ add(Interval::_2);   found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ add(Interval::_4);   found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ add(Interval::_6);   found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ add(Interval::_9);   found = true; }
            if(removePrefix(chordSymbol, "add11" )){ add(Interval::_11);  found = true; }
            if(removePrefix(chordSymbol, "add13" )){ add(Interval::_13);  found = true; }
            if(removePrefix(chordSymbol, "addb2" )){ add(Interval::_b2);  found = true; }
            if(removePrefix(chordSymbol, "addb4" )){ add(Interval::_b4);  found = true; }
            if(removePrefix(chordSymbol, "addb6" )){ add(Interval::_b6);  found = true; }
            if(removePrefix(chordSymbol, "addb9" )){ add(Interval::_b9);  found = true; }
            if(removePrefix(chordSymbol, "addb11")){ add(Interval::_b11); found = true; }
            if(removePrefix(chordSymbol, "addb13")){ add(Interval::_b13); found = true; }
            if(removePrefix(chordSymbol, "add#2" )){ add(Interval::_s2);  found = true; }
            if(removePrefix(chordSymbol, "add#4" )){ add(Interval::_s4);  found = true; }
            if(removePrefix(chordSymbol, "add#6" )){ add(Interval::_s6);  found = true; }
            if(removePrefix(chordSymbol, "add#9" )){ add(Interval::_s9);  found = true; }
            if(removePrefix(chordSymbol, "add#11")){ add(Interval::_s11); found = true; }
            if(removePrefix(chordSymbol, "add#13")){ add(Interval::_s13); found = true; }
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


            if(slashNoteName.size() > 0){

                int slashNote = 0;
                bool found = false;
                for(auto interval : chordIntervals){
                    std::string note = intervalToNoteName(interval, rootNote);
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
            if(interval != Interval::_R)
                noteNames.push_back(intervalToNoteName(interval, rootNote));
            else 
                noteNames.push_back(rootName);
        }
        
        // Print the noteNames
        for(auto note : noteNames){
            std::cout << note << " ";
        }
        std::cout << std::endl;

        // Cast the chordIntervals to int and assign to chordTones
        std::vector<int> chordTones;
        for (auto interval : chordIntervals) {
            chordTones.push_back(toInt(interval));
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
            std::cerr << "Warning: Unrecognized chord symbol: " << aChordSymbol << " : " << chordSymbol << std::endl;
        }

        // Return the chord tones
        return chordTones;

    }

    // Function to flatten an interval
    void flatten(Interval n)
    {
        for(auto& interval : chordIntervals){
            if(interval == n){
                interval = static_cast<Interval>(static_cast<int>(interval) - 1);
            }
        }
    }

    // Function to add an interval
    void add(Interval n)
    {   
        // Test if interval already present
        for(auto& interval : chordIntervals){
            if(toInt(interval) == toInt(n)) return;
        }
        // If not, add the interval
        chordIntervals.push_back(n);
    }

    void insert(int index, Interval n)
    {
        // Test if interval already present
        for(auto& interval : chordIntervals){
            if(toInt(interval) == toInt(n)){ 
                // If it is the move it the the new index
                chordIntervals.erase(std::remove(chordIntervals.begin(), chordIntervals.end(), interval), chordIntervals.end());
                chordIntervals.insert(chordIntervals.begin() + index, n);
                return;
            }
        }

        // If not, add the interval
        chordIntervals.insert(chordIntervals.begin() + index, n);
    }

    // Remove Interval
    void remove(Interval n)
    {
        chordIntervals.erase(std::remove(chordIntervals.begin(), chordIntervals.end(), n), chordIntervals.end());
        chordTones.erase(std::remove(chordTones.begin(), chordTones.end(), toInt(n)), chordTones.end());
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
        std::cout << "Smallest: " << smallest << std::endl;
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
                std::cout << "Dist: " << dist << std::endl;
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
        for(const auto& interval : chordIntervals){
            std::cout << intervalToString(interval) << " ";
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

    // Is the chord expressed in roman numerals
    bool isRoman(const std::string& chordSymbol)
    {
        return chordSymbol.find_first_of("ivIV") != std::string::npos;
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

    bool hasInterval(Interval interval)
    {
        for(auto& i : chordIntervals){
            if(i == interval) return true;
        }
        return false;
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

    // Function to open the voicing of the chord
    void openVoicing()
    {
        // Test if the chord has a 3rd
        if     (moveInterval(Interval::_3 , 1)){}
        else if(moveInterval(Interval::_b3, 1)){}
        else if(moveInterval(Interval::_s3, 1)){}

        // Test if the chord has a 7th
        if     (moveInterval(Interval::_7 , 1)){}
        else if(moveInterval(Interval::_b7, 1)){}
        else if(moveInterval(Interval::_s7, 1)){}
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
    std::vector<Interval> chordIntervals;
    // Note Names
    std::vector<std::string> noteNames;
    std::vector<NoteName> noteNames_;

    // Root Note
    int rootNote = 0;
    // Bass Note
    int bassNote = 0;


};

// ----------------------------------------------------------------------- //
// ----------------------- ChordProgression Class ----------------------- //
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
