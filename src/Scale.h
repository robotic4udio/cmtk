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
    Scale(std::string aName)
    {
        setScale(aName);
    }

    // Function to set the scale
    void setScale(std::string aScaleName)
    {
        mName = aScaleName;
        // Ionian Mode (Major)
        if(mName == "Ionian" || mName == "Major"){ 
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6), I(7)};  
            chordSymbols = {"I","ii","iii","IV","V","vi","vii°"};
        }
        // Dorian Mode
        else if(mName == "Dorian"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6), I(7,-1)};  
            chordSymbols = {"i","ii","bIII","IV","v","vi°","bVII"};
        }
        // Phrygian Mode
        else if(mName == "Phrygian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"i","bII","bIII","iv","v°","bVI","bvii"};
        }
        // Lydian Mode
        else if(mName == "Lydian"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5), I(6), I(7)};  
            chordSymbols = {"I","II","iii","#iv°","V","vi","vii"};
        }
        // Mixolydian Mode
        else if(mName == "Mixolydian"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6), I(7,-1)};  
            chordSymbols = {"I","ii","iii°","IV","v","vi","bVII"};
        }
        // Aeolian Mode (Natural Minor)
        else if(mName == "Aeolian" || mName == "Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"i","ii°","bIII","iv","v","bVI","bVII"};
        }
        // Locrian Mode
        else if(mName == "Locrian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5,-1), I(6,-1), I(7,-1)};  
            chordSymbols = {"i°","bII","biii","iv","bV","bVI","bvii"};
        }

        else{
            std::cerr << "Error: Unrecognized scale name" << std::endl;
        }
    }

    // Print the scale
    void print()
    {
        std::cout << "Scale: " << mName << std::endl;
        for(auto interval : mIntervals)
        {
            std::cout << interval.getString() << "\t" << interval.getSemitones() << "\n";
        }
        std::cout << std::endl;
    }






private:
    // The scale name
    std::string mName;
    // The scale intervals
    std::vector<I> mIntervals;
    // The scale chords
    std::vector<std::string> chordSymbols;

};









} // namespace cmtk
