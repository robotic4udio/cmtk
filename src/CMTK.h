#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>

namespace cmtk {

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Constants ---------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
static constexpr const int C0 = 24;
static constexpr const int C1 = C0+12;
static constexpr const int C2 = C0+24;
static constexpr const int C3 = C0+36;
static constexpr const int C4 = C0+48;
static constexpr const int C5 = C0+60;
static constexpr const int C6 = C0+72;
static constexpr const int C7 = C0+84;
static constexpr const int C8 = C0+96;
static constexpr const int C9 = C0+108;

static constexpr const int OCTAVES_BELOW_ZERO = C0/12;


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

// Same as removePrefix but case insensitive option
inline bool removePrefix(std::string& s, const std::string& prefix, bool caseSensitive)
{
    if(caseSensitive) return removePrefix(s, prefix);
    std::string s1 = s;
    std::string s2 = prefix;
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.size() >= s2.size() && s1.compare(0, s2.size(), s2) == 0){
        s.erase(0,s2.size());
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

// Same as replacePrefix but case insensitive option
inline bool replacePrefix(std::string& s, const std::string& prefix, const std::string& to, bool caseSensitive)
{
    if(caseSensitive) return replacePrefix(s, prefix, to);
    std::string s1 = s;
    std::string s2 = prefix;
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.size() >= s2.size() && s1.compare(0, s2.size(), s2) == 0){
        s.replace(0, s2.length(), to);
        return true;
    }
    return false;
}

// If a string contains another string, then remove it and return true
inline bool removeSubstring(std::string& s, const std::string& sub)
{
    size_t pos = s.find(sub);
    if(pos != std::string::npos){
        s.erase(pos, sub.size());
        return true;
    }
    return false;
}

// Same as removeSubstring but case insensitive option
inline bool removeSubstring(std::string& s, const std::string& sub, bool caseSensitive)
{
    if(caseSensitive) return removeSubstring(s, sub);
    std::string s1 = s;
    std::string s2 = sub;
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    size_t pos = s1.find(s2);
    if(pos != std::string::npos){
        s.erase(pos, s2.size());
        return true;
    }
    return false;
}

inline bool isNumber(const std::string& s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

// Starts with a number
inline bool startsWithNumber(const std::string& s)
{
    return !s.empty() && std::isdigit(s[0]);
}

// Remove all instances of the characters from a string
inline bool removeChars(std::string& s, const std::string& chars)
{
    auto size = s.size();
    // Remove the chars
    for (char c: chars) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    // Return true if the size has changed
    if(size != s.size()) return true;
    return false;
}

// Function to convert a roman numeral to an integer
int romanToInt(std::string romanNumeral)
{
    // Convert the roman numeral to uppercase
    std::transform(romanNumeral.begin(), romanNumeral.end(), romanNumeral.begin(), ::toupper);

    // Create a map of the roman numerals
    std::map<char, int> romanMap;
    romanMap['I'] = 1;
    romanMap['V'] = 5;
    romanMap['X'] = 10;
    romanMap['L'] = 50;
    romanMap['C'] = 100;
    romanMap['D'] = 500;
    romanMap['M'] = 1000;

    // Initialize the result
    int result = 0;

    // Loop through the roman numeral
    for (int i = 0; i < romanNumeral.size(); i++) {
        // Get the value of the current roman numeral
        int value = romanMap[romanNumeral[i]];

        // If the next roman numeral is greater, subtract the current value
        if (i + 1 < romanNumeral.size() && romanMap[romanNumeral[i + 1]] > value) {
            result -= value;
        }
        // Otherwise, add the current value
        else {
            result += value;
        }
    }

    return result;
};

// Function to convert an integer to a roman numeral
std::string intToRoman(int num, bool upperCase = true)
{
    // Create a map of the roman numerals
    std::map<int, std::string> romanMap;
    romanMap[1] = "I";
    romanMap[4] = "IV";
    romanMap[5] = "V";
    romanMap[9] = "IX";
    romanMap[10] = "X";
    romanMap[40] = "XL";
    romanMap[50] = "L";
    romanMap[90] = "XC";
    romanMap[100] = "C";
    romanMap[400] = "CD";
    romanMap[500] = "D";
    romanMap[900] = "CM";
    romanMap[1000] = "M";

    // Initialize the result
    std::string result = "";

    // Loop through the roman numerals
    for (auto it = romanMap.rbegin(); it != romanMap.rend(); it++) {
        // Get the value of the current roman numeral
        int value = it->first;
        // Get the symbol of the current roman numeral
        std::string symbol = it->second;

        // Add the symbol to the result while the value is less than the number
        while (num >= value) {
            result += symbol;
            num -= value;
        }
    }

    // Convert the result to lowercase
    if (!upperCase) {
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    }

    return std::move(result);
};

// Function to convert a pitch expressed as a roman numeral to a semitone value
int romanPitchToSemitone(std::string romanPitch, int root=0)
{
    int semitone = root;

    // Handle flat and sharp symbols
    while(romanPitch.front() == 'b' || romanPitch.front() == '#')
    {
        if     (romanPitch.front() == 'b') semitone--;
        else if(romanPitch.front() == '#') semitone++;
        romanPitch.erase(0,1);
    }

    // Convert the roman pitch to uppercase
    std::transform(romanPitch.begin(), romanPitch.end(), romanPitch.begin(), ::toupper);

    // Get roman numeral value
    auto romanValue = romanToInt(romanPitch);

    // While the roman numeral is greater than 7, subtract 7
    while(romanValue > 7){ 
        romanValue -= 7;
        semitone += 12;
    }

    // Convert the roman pitch to an integer
    switch(romanValue)
    {
        case 1: semitone +=  0; break;
        case 2: semitone +=  2; break;
        case 3: semitone +=  4; break;
        case 4: semitone +=  5; break;
        case 5: semitone +=  7; break;
        case 6: semitone +=  9; break;
        case 7: semitone += 11; break;
    }

    return semitone;
};

// Is the string a chord symbol in roman numerals
inline bool isRomanChordSymbol(const std::string& chordSymbol)
{
    return chordSymbol.find_first_of("ivIVXL") != std::string::npos;
}

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Arabic Numerals ----------------------------------------- //
// -------------------------------------------------------------------------------------------- //

// Is the string a chord symbol in arabic numerals
inline bool isArabicChordSymbol(std::string chordSymbol)
{
    if(chordSymbol.empty()) return false;

    // While the first character is a 'b' or '#' remove it
    while(chordSymbol[0] == 'b' || chordSymbol[0] == '#'){
        chordSymbol.erase(0,1);
    }

    // Now the first character must be a number
    return chordSymbol.find_first_of("123456789") == 0;
}

// Function to convert a pitch expressed as an arabic numeral to a semitone value
int arabicPitchToSemitone(std::string arabicPitch, int root=0)
{
    int semitone = root;

    // Handle flat and sharp symbols
    while(arabicPitch.front() == 'b' || arabicPitch.front() == '#')
    {
        if     (arabicPitch.front() == 'b') semitone--;
        else if(arabicPitch.front() == '#') semitone++;
        arabicPitch.erase(0,1);
    }

    // Convert the arabic pitch to an integer
    int arabicValue = std::stoi(arabicPitch);

    // While the arabic numeral is greater than 7, subtract 7
    while(arabicValue > 7){ 
        arabicValue -= 7;
        semitone += 12;
    }

    // Convert the arabic pitch to an integer
    switch(arabicValue)
    {
        case 1: semitone +=  0; break;
        case 2: semitone +=  2; break;
        case 3: semitone +=  4; break;
        case 4: semitone +=  5; break;
        case 5: semitone +=  7; break;
        case 6: semitone +=  9; break;
        case 7: semitone += 11; break;
    }

    return semitone;
};


// Create a static std::map<std::vector<Notes>> with all the above notes:
static std::map<std::string, std::vector<std::string>> MajorNoteMap = {
    {"C" , { "C"  , "D"  , "E"  , "F"  , "G"  , "A"  , "B"   }},
    {"C#", { "C#" , "D#" , "E#" , "F#" , "G#" , "A#" , "B#"  }},
    {"Db", { "Db" , "Eb" , "F"  , "Gb" , "Ab" , "Bb" , "C"   }},
    {"D" , { "D"  , "E"  , "F#" , "G"  , "A"  , "B"  , "C#"  }},
    {"D#", { "D#" , "E#" , "F##", "G#" , "A#" , "B#" , "C##" }},
    {"Eb", { "Eb" , "F"  , "G"  , "Ab" , "Bb" , "C"  , "D"   }},
    {"E" , { "E"  , "F#" , "G#" , "A"  , "B"  , "C#" , "D#"  }},
    {"F" , { "F"  , "G"  , "A"  , "Bb" , "C"  , "D"  , "E"   }},
    {"F#", { "F#" , "G#" , "A#" , "B"  , "C#" , "D#" , "E#"  }},
    {"Gb", { "Gb" , "Ab" , "Bb" , "Cb" , "Db" , "Eb" , "F"   }},
    {"G" , { "G"  , "A"  , "B"  , "C"  , "D"  , "E"  , "F#"  }},
    {"G#", { "G#" , "A#" , "B#" , "C#" , "D#" , "E#" , "F##" }},
    {"Ab", { "Ab" , "Bb" , "C"  , "Db" , "Eb" , "F"  , "G"   }},
    {"A" , { "A"  , "B"  , "C#" , "D"  , "E"  , "F#" , "G#"  }},
    {"A#", { "A#" , "B#" , "C##", "D#" , "E#" , "F##", "G##" }},
    {"Bb", { "Bb" , "C"  , "D"  , "Eb" , "F"  , "G"  , "A"   }},
    {"B" , { "B"  , "C#" , "D#" , "E"  , "F#" , "G#" , "A#"  }},
    {"Cb", { "Cb" , "Db" , "Eb" , "Fb" , "Gb" , "Ab" , "Bb"  }}
};

inline static std::string MajorNoteMapAt(std::string key, int index) 
{
    while(index <  0) index += 6;
    while(index >  6) index -= 6;
    return MajorNoteMap[key][index];
}

inline void simplifyNoteName(std::string& note)
{
    // Flats that can be replaced with note
    bool found = true;
    while(found){
        found = false;
        if(replacePrefix(note, "Cb" , "B")) found = true;
        if(replacePrefix(note, "Dbb", "C")) found = true;
        if(replacePrefix(note, "Ebb", "D")) found = true;
        if(replacePrefix(note, "Fb" , "E")) found = true;
        if(replacePrefix(note, "Gbb", "F")) found = true;
        if(replacePrefix(note, "Abb", "G")) found = true;
        if(replacePrefix(note, "Bbb", "A")) found = true;

        // Sharps that can be replaced with note
        if(replacePrefix(note, "C##", "D")) found = true;
        if(replacePrefix(note, "D##", "E")) found = true;
        if(replacePrefix(note, "E#" , "F")) found = true;
        if(replacePrefix(note, "F##", "G")) found = true;
        if(replacePrefix(note, "G##", "A")) found = true;
        if(replacePrefix(note, "A##", "B")) found = true;
        if(replacePrefix(note, "B#" , "C")) found = true;

        if(removeSubstring(note, "b#")) found = true;
        if(removeSubstring(note, "#b")) found = true;
    
    }
}



// Base Class for all CMTK Objects
class CMTK
{
public:

    


    bool mPreferSharp = false;


};








};