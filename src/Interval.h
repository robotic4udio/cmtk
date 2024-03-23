#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>
#include "Chords.h"

namespace cmtk {


// ----------------------------------------------------------------------- //
// ----------------------------- Interval Class -------------------------- //
// ----------------------------------------------------------------------- //

class I {
public:
    // Constructor
    I() = default;
    I(std::string interval)
    {
        setIval(interval);
    }

    // Function to set the interval
    void setIval(std::string aName)
    {
        // Test that the string only contains valid characters
        for(auto c : aName)
        {
            if(c != 'b' && c != '#' && !std::isdigit(c))
            {
                throw std::invalid_argument("Invalid interval name");
            }
        }
        // Test that the string is not empty
        if(aName.empty())
        {
            throw std::invalid_argument("Invalid interval name");
        }


        mName = aName;
        quality = 0;

        // While the interval is not empty and starts with a 'b' or '#' character 
        while(!mName.empty() && (mName[0] == 'b' || mName[0] == '#'))
        {
            // If the interval starts with a 'b' character
            if(mName[0] == 'b')
            {
                quality--;
            }
            // If the interval starts with a '#' character
            else if(mName[0] == '#')
            {
                quality++;
            }
            // Remove the first character from the interval
            mName.erase(0, 1);
        }

        // If the interval is not empty and the first character is a digit
        if(!mName.empty() && std::isdigit(mName[0]))
        {
            // Get the number of semitones
            natural = std::stoi(mName);
            
            // Get the octave number
            semitones = quality;
            int intervalNumber = natural;
            while(intervalNumber > 7)
            {
                intervalNumber -= 7;
                semitones += 12;
            }
            
            // Get the semitones from the interval number with the major scale as reference
            switch(intervalNumber)
            {
                case 1: semitones += 0; break;
                case 2: semitones += 2; break;
                case 3: semitones += 4; break;
                case 4: semitones += 5; break;
                case 5: semitones += 7; break;
                case 6: semitones += 9; break;
                case 7: semitones += 11; break;
                default: break;
            }

        }

    }

    std::string getString()
    {
        auto quality = this->quality;
        std::string res = "";
        while(quality < 0)
        {
            res += "b";
            quality++;
        }
        while(quality > 0)
        {
            res += "#";
            quality--;
        }
        res += std::to_string(natural);
        return std::move(res);
    }

    // Function to get the number of semitones
    int getSemitones()
    {
        return semitones;
    }

    // Print the interval
    void print()
    {
        std::cout << getString() << ": " << getSemitones() << std::endl;   
    }

private:
    std::string mName;

    // Function to set the interval
    int semitones = 0;
    int natural = 0;
    int quality = 0;


};









} // namespace cmtk
