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
    return chordSymbol.find_first_of("ivIV") != std::string::npos;
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



} // namespace cmtk
