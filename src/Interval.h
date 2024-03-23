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
            semitones = semitonesFromDegree(degree, quality);

            // Return
            return;
        }

        // If the interval is empty
        throw std::invalid_argument("Invalid interval name");
    }

    void set(int aDegree, int aQuality)
    {
        degree = aDegree;
        quality = aQuality;
        semitones = semitonesFromDegree(degree, quality);
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

    // Get Degree
    int getDegree()
    {
        return degree;
    }

    // Set Degree
    void setDegree(int aDegree)
    {
        degree = aDegree;
        semitones = semitonesFromDegree(degree, quality);
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
    int semitones = 0;
    int degree = 0;  
    int quality = 0; // -1 for flat, 0 for natural, 1 for sharp

    int semitonesFromDegree(int aDegree, int aQuality=0)
    {
        int tmp_semitones = aQuality;
        while(aDegree > 7)
        {
            aDegree -= 7;
            tmp_semitones += 12;
        }
        
        switch(degree)
        {
            case 1: tmp_semitones += 0; break;
            case 2: tmp_semitones += 2; break;
            case 3: tmp_semitones += 4; break;
            case 4: tmp_semitones += 5; break;
            case 5: tmp_semitones += 7; break;
            case 6: tmp_semitones += 9; break;
            case 7: tmp_semitones += 11; break;
            default: break;
        }

        return tmp_semitones;
    }

};









} // namespace cmtk
