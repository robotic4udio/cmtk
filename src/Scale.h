#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>
#include "Chords.h"
#include "Interval.h"


namespace cmtk {


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
        // Ionian Mode (Major)
        if(scaleName == "Ionian" || scaleName == "Major"){ 
            scaleIntervals = {I("1"), I("2"), I("3"), I("4"), I("5"), I("6"), I("7")};  
            chordSymbols = {"I","ii","iii","IV","V","vi","vii°"};
        }
        // Dorian Mode
        else if(scaleName == "Dorian"){
            scaleIntervals = {I("1"), I("2"), I("b3"), I("4"), I("5"), I("6"), I("b7")};  
            chordSymbols = {"i","ii","bIII","IV","v","vi°","bVII"};
        }
        // Phrygian Mode
        else if(scaleName == "Phrygian"){
            scaleIntervals = {I("1"), I("b2"), I("b3"), I("4"), I("5"), I("b6"), I("b7")};  
            chordSymbols = {"i","bII","bIII","iv","v°","bVI","bvii"};
        }
        // Lydian Mode
        else if(scaleName == "Lydian"){
            scaleIntervals = {I("1"), I("2"), I("3"), I("#4"), I("5"), I("6"), I("7")};  
            chordSymbols = {"I","II","iii","#iv°","V","vi","vii"};
        }
        // Mixolydian Mode
        else if(scaleName == "Mixolydian"){
            scaleIntervals = {I("1"), I("2"), I("3"), I("4"), I("5"), I("6"), I("b7")};  
            chordSymbols = {"I","ii","iii°","IV","v","vi","bVII"};
        }
        // Aeolian Mode (Natural Minor)
        else if(scaleName == "Aeolian" || scaleName == "Minor"){
            scaleIntervals = {I("1"), I("2"), I("b3"), I("4"), I("5"), I("b6"), I("b7")};  
            chordSymbols = {"i","ii°","bIII","iv","v","bVI","bVII"};
        }
        // Locrian Mode
        else if(scaleName == "Locrian"){
            scaleIntervals = {I("1"), I("b2"), I("b3"), I("4"), I("b5"), I("b6"), I("b7")};  
            chordSymbols = {"i°","bII","biii","iv","bV","bVI","bvii"};
        }

        else{
            std::cerr << "Error: Unrecognized scale name" << std::endl;
        }
    }

    // Print the scale
    void print()
    {
        std::cout << "Scale: " << scaleName << std::endl;
        for(auto interval : scaleIntervals)
        {
            std::cout << interval.getString() << "\t" << interval.getSemitones() << "\n";
        }
        std::cout << std::endl;
    }






private:
    // The scale name
    std::string scaleName;
    // The scale intervals
    std::vector<I> scaleIntervals;
    // The scale chords
    std::vector<std::string> chordSymbols;

};









} // namespace cmtk
