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
    Scale()
    {
        setScale("Major");
    }

    Scale(std::string aName, int aRootNote=0)
    {
        setRoot(aRootNote);
        setScale(aName);
    }

    void setRoot(int aRootNote)
    {
        mRootNote = aRootNote;
    }

    int getRoot()
    {
        return mRootNote;
    }

    // Function to set the scale
    void setScale(std::string aScaleName)
    {
        mName = aScaleName;
        // ----------------------- Major Modes ----------------------- //
        // Ionian Mode - Major Scale 1st Mode
        if(mName == "Ionian" || mName == "Major"){ 
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6), I(7)};
            chordSymbols = {"I","ii","iii","IV","V","vi","vii°"};
        }
        // Dorian Mode - Major Scale 2nd Mode
        else if(mName == "Dorian"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6), I(7,-1)};  
            chordSymbols = {"i","ii","bIII","IV","v","vi°","bVII"};
        }
        // Phrygian Mode - Major Scale 3rd Mode
        else if(mName == "Phrygian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"i","bII","bIII","iv","v°","bVI","bvii"};
        }
        // Lydian Mode - Major Scale 4th Mode
        else if(mName == "Lydian"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5), I(6), I(7)};  
            chordSymbols = {"I","II","iii","#iv°","V","vi","vii"};
        }
        // Mixolydian Mode - Major Scale 5th Mode
        else if(mName == "Mixolydian"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6), I(7,-1)};  
            chordSymbols = {"I","ii","iii°","IV","v","vi","bVII"};
        }
        // Aeolian Mode (Natural Minor) - Major Scale 6th Mode
        else if(mName == "Aeolian" || mName == "Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"i","ii°","bIII","iv","v","bVI","bVII"};
        }
        // Locrian Mode - Major Scale 7th Mode
        else if(mName == "Locrian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5,-1), I(6,-1), I(7,-1)};  
            chordSymbols = {"i°","bII","biii","iv","bV","bVI","bvii"};
        }

        // ----------------------- Melodic Minor Modes ----------------------- //
        // Melodic Minor - Melodic Minor 1st Mode
        else if(mName == "Melodic Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6), I(7)};  
            chordSymbols = {"i","ii","bIII+","IV","V","vi°","vii°"};
        }
        // Dorian b2 - Melodic Minor 2nd Mode
        else if(mName == "Dorian b2"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5), I(6), I(7,-1)};  
            chordSymbols = {"i","bii aug","bIII","IV","v°","vi°","bvii"};
        }
        // Lydian Augmented - Melodic Minor 3rd Mode
        else if(mName == "Lydian Augmented"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5,1), I(6), I(7)};  
            chordSymbols = {"I+","II","III","#iv°","#5°","vi","vii"};
        }
        // Lydian Dominant - Melodic Minor 4th Mode
        else if(mName == "Lydian Dominant" || mName == "Acoustic"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5), I(6), I(7,-1)};  
            chordSymbols = {"I","II","iii°","#iv°","v","vi","bVII+"};
        }
        // Mixolydian b6 - Melodic Minor 5th Mode
        else if(mName == "Mixolydian b6"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"I","ii°","iii°","iv","v","bVI+","bVII"};
        }
        // Locrian #2 - Melodic Minor 6th Mode
        else if(mName == "Half Diminished" || mName == "Locrian #2"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5,-1), I(6,-1), I(7,-1)};  
            chordSymbols = {"i°","ii°","biii","iv","bV+","bVI","bVII"};
        }
        // Altered - Melodic Minor 7th Mode
        else if(mName == "Altered"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5,-1), I(6,-1), I(7,-1)};  
            chordSymbols = {"i°","bii","biii","bIV+","bV","bVI","bvii°"};
        }

        // ----------------------- Harmonic Minor Modes ----------------------- //
        // Harmonic Minor - Harmonic Minor 1st Mode
        else if(mName == "Harmonic Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6,-1), I(7)};  
            chordSymbols = {"i","ii°","bIII+","iv","V","bVI","vii°"};
        }
        // Locrian n6 - Harmonic Minor 2nd Mode
        else if(mName == "Locrian n6"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5,-1), I(6), I(7,-1)};  
            chordSymbols = {"i°","bII+","biii","IV","bV","vi°","bvii"};
        }
        // Ionian #5 - Harmonic Minor 3rd Mode
        else if(mName == "Ionian #5"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5,1), I(6), I(7)};  
            chordSymbols = {"I+","ii","III","IV","bv°","vi","vii°"};
        }
        // Dorian #4 - Harmonic Minor 4th Mode
        else if(mName == "Dorian #4" || mName == "Ukrainian Dorian"){
            mIntervals = {I(1), I(2), I(3,-1), I(4,1), I(5), I(6), I(7,-1)};  
            chordSymbols = {"i","II","bIII","#iv°","v","vi°","bVII+"};
        }
        // Phrygian Dominant - Harmonic Minor 5th Mode
        else if(mName == "Phrygian Dominant"){
            mIntervals = {I(1), I(2,-1), I(3), I(4), I(5), I(6,-1), I(7,-1)};  
            chordSymbols = {"I","bII","iii°","iv","v°","bVI+","bvii"};
        }
        // Lydian #2 - Harmonic Minor 6th Mode
        else if(mName == "Lydian #2"){
            mIntervals = {I(1), I(2,1), I(3), I(4,1), I(5), I(6), I(7)};  
            chordSymbols = {"I","#ii°","iii","#iv°","V+","vi","VII"};
        }
        // Super Locrian - Harmonic Minor 7th Mode
        else if(mName == "Super Locrian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5,-1), I(6,-1), I(7,-2)};  
            chordSymbols = {"i°","bii","biii°","bIV+","bv","bVI","bbvii"};
        }

        // ----------------------- Double Harmonic Modes ----------------------- //
        // Double Harmonic Major - Double Harmonic Major 1st Mode
        else if(mName == "Double Harmonic Major"){
            mIntervals = {I(1), I(2,-1), I(3), I(4), I(5), I(6,-1), I(7)};  
            chordSymbols = {"I","bII","iii","iv","V b5","VI+","vii sus2 b5"};
        }
        // Lydian #2 #6 - Double Harmonic Major 2nd Mode
        else if(mName == "Lydian #2 #6"){
            mIntervals = {I(1), I(2,1), I(3), I(4,1), I(5), I(6,1), I(7)};  
            chordSymbols = {"I","#ii","iii","#IV b5","V+","#VI sus2 b5","VII"};
        }
        // Ultra Phrygian - Double Harmonic Major 3rd Mode
        else if(mName == "Ultra Phrygian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5), I(6,-1), I(7,-2)};  
            chordSymbols = {"i","bii","bIII b5","bIV+","V sus2 b5","bVI","bbVII"};
        }
        // Hungarian Minor - Double Harmonic Major 4rd Mode
        else if(mName == "Hungarian Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4,1), I(5), I(6,-1), I(7)};  
            chordSymbols = {"i","II b5","bIII+","#iv sus2 b5","V","bVI","vii"};
        }

        else{
            std::cerr << "Error: Unrecognized scale name" << std::endl;
        }
    }

    // Overload the [] operator to get the semi-tone of the scale
    int operator[](int index)
    {
        return semiToneAt(index);
    }
    
    // Function to get the scale name
    int semiToneAt(int index)
    {
        int res=mRootNote;
        while(index < 0)
        {
            index += mIntervals.size();
            res -= 12;
        }
        while(index >= mIntervals.size())
        {
            index -= mIntervals.size();
            res += 12;
        }

        res += mIntervals[index].getSemitones();
        return res;
    }

    I intervalAt(int index)
    {
        while(index < 0)
        {
            index += mIntervals.size();
        }
        while(index >= mIntervals.size())
        {
            index -= mIntervals.size();
        }

        return mIntervals[index];
    }



    // Function to calculate the brightness of the scale
    int getBrightness()
    {
        int brightness = 0;
        for(auto interval : mIntervals)
        {
            brightness += interval.getQuality();
        }
        return brightness;
    };

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

    // Function to test if a chord is diatonic to the scale
    bool isChordDiatonic(const Chord& chord)
    {
        std::vector<int> chordNotes;
        for(auto interval : chord.getIntervals())
        {
            auto semitones = interval.getSemitones() % 12;
            // Check if the interval is in the scale
            if(std::find_if(mIntervals.begin(), mIntervals.end(), [semitones,this](I i){return i.getSemitones() == semitones;}) == mIntervals.end())
            {
                return false;
            }
        }

        return true;
    }

    static std::vector<Scale> getAllScales()
    {
        std::vector<Scale> scales;
        for(auto scaleName : {
            "Major"                , "Dorian"      , "Phrygian"        , "Lydian"         , "Mixolydian"       , "Aeolian"   , "Locrian", 
            "Melodic Minor"        , "Dorian b2"   , "Lydian Augmented", "Lydian Dominant", "Mixolydian b6"    , "Locrian #2", "Altered",
            "Harmonic Minor"       , "Locrian n6"  , "Ionian #5"       , "Dorian #4"      , "Phrygian Dominant", "Lydian #2" , "Super Locrian",
            "Double Harmonic Major", "Lydian #2 #6", "Ultra Phrygian"  , "Hungarian Minor"})
        {
            scales.push_back(Scale(scaleName));
        }

        return std::move(scales);
    }

    static std::vector<Scale> getScalesByBrightness()
    {
        auto scales = getAllScales();
        std::sort(scales.begin(), scales.end(), [](Scale a, Scale b){return a.getBrightness() < b.getBrightness();});
        return std::move(scales);
    }

    static std::vector<Scale> getDiatonicScales(const Chord& chord)
    {
        std::vector<Scale> diatonicScales;
        for(auto scale : getAllScales())
        {
            if(scale.isChordDiatonic(chord))
            {
                diatonicScales.push_back(scale);
            }
        }

        return std::move(diatonicScales);
    }


private:
    // The scale name
    std::string mName;
    // The scale intervals
    std::vector<I> mIntervals;
    // The scale chords
    std::vector<std::string> chordSymbols;
    // The scale root note
    int mRootNote = 0;

};









} // namespace cmtk
