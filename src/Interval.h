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
        set(interval);
    }
    I(int degree, int quality=0)
    {
        set(degree, quality);
    }

    // Function to set the interval
    void set(std::string aName)
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

        // Initialize the quality of the interval
        quality = 0;

        // While the interval is not empty and starts with a 'b' or '#' character 
        while(!aName.empty() && (aName[0] == 'b' || aName[0] == '#'))
        {
            // If the interval starts with a 'b' character
            if(aName[0] == 'b')
            {
                quality--;
            }
            // If the interval starts with a '#' character
            else if(aName[0] == '#')
            {
                quality++;
            }
            // Remove the first character from the interval
            aName.erase(0, 1);
        }

        // If the interval is not empty and the first character is a digit
        if(!aName.empty() && std::isdigit(aName[0]))
        {
            // Get the degree of the interval
            degree = std::stoi(aName);

            // Calculate the number of semitones
            updateSemitones(degree, quality);

            // Return
            return;
        }

        // If the interval is empty
        throw std::invalid_argument("Invalid interval name");
    }

    void set(int aDegree, int aQuality)
    {
        // Test if the degree is below 1
        if(aDegree < 1)
        {
            throw std::invalid_argument("Invalid interval degree");
        }
        // Set the degree, quality and semitones
        degree = aDegree;
        quality = aQuality;
        updateSemitones(degree, quality);
    }

    // Function to get the interval as a string
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
        res += std::to_string(degree);
        return std::move(res);
    }

    // Function to get the interval as a string
    std::string getName()
    {
        return std::move(getString());
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

    // Sharpen the interval
    void sharpen()
    {
        quality++;
        semitones++;
    }

    // Flatten the interval
    void flatten()
    {
        quality--;
        semitones--;
    }

    // Set quality
    void setQuality(int aQuality)
    {
        int diff = aQuality - quality;
        quality = aQuality;
        semitones += diff;
    }

    // Set quality from string
    void setQuality(std::string aQuality)
    {
        int newQuality = 0;
        for(auto c : aQuality)
        {
            if     (c == 'b') newQuality--;
            else if(c == '#') newQuality++;
        }
        setQuality(newQuality);
    }

    // Set Quality from char
    void setQuality(char aQuality)
    {
        int newQuality = aQuality == 'b' ? -1 : aQuality == '#' ? 1 : 0;
        setQuality(newQuality);
    }

    // Get Quality
    int getQuality()
    {
        return quality;
    }

    // Get Degree
    int getDegree()
    {
        return degree;
    }

    // Set Degree
    void setDegree(int aDegree)
    {
        degree = aDegree;
        updateSemitones(degree, quality);
    }
    
    // Equality operator
    bool operator==(const I& other) const
    {
        return semitones == other.semitones;
    }

    // Add a function to be used in std::sort
    bool operator<(const I& other) const
    {
        return semitones < other.semitones;
    }



private:
    // Function to set the interval
    int semitones = 0; // The number of semitones required to reach the interval
    int degree = 0;    // The degree is relative to the major scale
    int quality = 0;   // -1 for flat, 0 for natural, 1 for sharp

    // Function to get the number of semitones from the degree and quality
    void updateSemitones(int aDegree, int aQuality)
    {
        semitones = aQuality;
        while(aDegree > 7)
        {
            aDegree -= 7;
            semitones += 12;
        }
        while(aDegree < 1)
        {
            aDegree += 7;
            semitones -= 12;
        }
    
        // Add the number of semitones for the degree
        switch(aDegree)
        {
            case 1: semitones +=  0; break;
            case 2: semitones +=  2; break;
            case 3: semitones +=  4; break;
            case 4: semitones +=  5; break;
            case 5: semitones +=  7; break;
            case 6: semitones +=  9; break;
            case 7: semitones += 11; break;
            default: break;
        }

    }

};









} // namespace cmtk
