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
        }
        // Dorian Mode - Major Scale 2nd Mode
        else if(mName == "Dorian"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6), I(7,-1)};  
        }
        // Phrygian Mode - Major Scale 3rd Mode
        else if(mName == "Phrygian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
        }
        // Lydian Mode - Major Scale 4th Mode
        else if(mName == "Lydian"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5), I(6), I(7)};  
        }
        // Mixolydian Mode - Major Scale 5th Mode
        else if(mName == "Mixolydian"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6), I(7,-1)};  
        }
        // Aeolian Mode (Natural Minor) - Major Scale 6th Mode
        else if(mName == "Aeolian" || mName == "Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6,-1), I(7,-1)};  
        }
        // Locrian Mode - Major Scale 7th Mode
        else if(mName == "Locrian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5,-1), I(6,-1), I(7,-1)};  
        }

        // ----------------------- Melodic Minor Modes ----------------------- //
        // Melodic Minor - Melodic Minor 1st Mode
        else if(mName == "Melodic Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6), I(7)};  
        }
        // Dorian b2 - Melodic Minor 2nd Mode
        else if(mName == "Dorian b2"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5), I(6), I(7,-1)};  
        }
        // Lydian Augmented - Melodic Minor 3rd Mode
        else if(mName == "Lydian Augmented"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5,1), I(6), I(7)};  
        }
        // Lydian Dominant - Melodic Minor 4th Mode
        else if(mName == "Lydian Dominant" || mName == "Acoustic"){
            mIntervals = {I(1), I(2), I(3), I(4,1), I(5), I(6), I(7,-1)};  
        }
        // Mixolydian b6 - Melodic Minor 5th Mode
        else if(mName == "Mixolydian b6"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5), I(6,-1), I(7,-1)};  
        }
        // Locrian #2 - Melodic Minor 6th Mode
        else if(mName == "Half Diminished" || mName == "Locrian #2"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5,-1), I(6,-1), I(7,-1)};  
        }
        // Altered - Melodic Minor 7th Mode
        else if(mName == "Altered"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5,-1), I(6,-1), I(7,-1)};  
        }

        // ----------------------- Harmonic Minor Modes ----------------------- //
        // Harmonic Minor - Harmonic Minor 1st Mode {1 2 b3 4 5 b6 7}
        else if(mName == "Harmonic Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4), I(5), I(6,-1), I(7)};  
        }
        // Locrian n6 - Harmonic Minor 2nd Mode
        else if(mName == "Locrian n6"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4), I(5,-1), I(6), I(7,-1)};  
        }
        // Ionian #5 - Harmonic Minor 3rd Mode
        else if(mName == "Ionian #5"){
            mIntervals = {I(1), I(2), I(3), I(4), I(5,1), I(6), I(7)};  
        }
        // Dorian #4 - Harmonic Minor 4th Mode
        else if(mName == "Dorian #4" || mName == "Ukrainian Dorian"){
            mIntervals = {I(1), I(2), I(3,-1), I(4,1), I(5), I(6), I(7,-1)};  
        }
        // Phrygian Dominant - Harmonic Minor 5th Mode
        else if(mName == "Phrygian Dominant"){
            mIntervals = {I(1), I(2,-1), I(3), I(4), I(5), I(6,-1), I(7,-1)};  
        }
        // Lydian #2 - Harmonic Minor 6th Mode
        else if(mName == "Lydian #2"){
            mIntervals = {I(1), I(2,1), I(3), I(4,1), I(5), I(6), I(7)};  
        }
        // Super Locrian - Harmonic Minor 7th Mode
        else if(mName == "Super Locrian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5,-1), I(6,-1), I(7,-2)};  
        }

        // ----------------------- Double Harmonic Modes ----------------------- //
        // Double Harmonic Major - Double Harmonic Major 1st Mode
        else if(mName == "Double Harmonic Major"){
            mIntervals = {I(1), I(2,-1), I(3), I(4), I(5), I(6,-1), I(7)};  
        }
        // Lydian #2 #6 - Double Harmonic Major 2nd Mode
        else if(mName == "Lydian #2 #6"){
            mIntervals = {I(1), I(2,1), I(3), I(4,1), I(5), I(6,1), I(7)};  
        }
        // Ultra Phrygian - Double Harmonic Major 3rd Mode
        else if(mName == "Ultra Phrygian"){
            mIntervals = {I(1), I(2,-1), I(3,-1), I(4,-1), I(5), I(6,-1), I(7,-2)};  
        }
        // Hungarian Minor - Double Harmonic Major 4rd Mode
        else if(mName == "Hungarian Minor"){
            mIntervals = {I(1), I(2), I(3,-1), I(4,1), I(5), I(6,-1), I(7)};  
        }

        else{
            std::cerr << "Error: Unrecognized scale name" << std::endl;
        }
    }

    // Overload the [] operator to get the semi-tone of the scale
    I operator[](int index)
    {
        return intervalAt(index);
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
        int octave = 0;
        while(index < 0)
        {
            index += mIntervals.size();
            octave--;
        }
        while(index >= mIntervals.size())
        {
            index -= mIntervals.size();
            octave++;
        }

        auto interval = mIntervals[index];
        interval.shiftOctave(octave);

        return std::move(interval);
    }

    Intervals intervalAt(const std::vector<int>& indexes)
    {
        Intervals intervals;
        for(auto index : indexes)
        {
            intervals.push_back(intervalAt(index));
        }

        return std::move(intervals);
    }


    std::string getChordSymbol(int index, int size=3)
    {
        // Check that size is valid
        if(size < 3 || size > 7)
        {
            throw std::invalid_argument("Scale::getChordSymbol(): Invalid size: " + std::to_string(size) + std::string(" - Size must be between 3 and 7"));
        }
        
        // std::cout << "--- Chord @ Index: --- " << index << std::endl;

        // Create a vector of indexes for the chord
        Intervals chordIntervals;
        for(int i=0; i<size; i++)
        {
            auto interval = intervalAt(index + 2*i);
            chordIntervals.add(interval);
        }
        // Get the normalized semitones
        auto semitones = chordIntervals.getSemitonesNormalized();

        /*
        // Print chord intervals for debugging
        std::cout << "Chord Intervals: ";
        for(auto interval : chordIntervals)
        {
            std::cout << interval.getString() << " ";
        }
        std::cout << std::endl;

        // Print chord semitones for debugging
        std::cout << "Chord Semitones: ";
        for(auto interval : chordIntervals)
        {
            std::cout << interval.getSemitones() << " ";
        }
        std::cout << std::endl;
        
        // Print normalized semitones for debugging
        std::cout << "Normalized Semitones: ";
        for(auto semitone : semitones)
        {
            std::cout << semitone << " ";
        }
        std::cout << std::endl;

        */

        // String for the chord symbol
        std::string chordSymbol = "";
        std::string toAppend = "";

        // Uppercase Roman
        bool uppercase = true;

        // Triads
        if     (inVec(semitones, {4,7})){ chordSymbol = ""    ;                    }
        else if(inVec(semitones, {4,6})){ chordSymbol = ""    ; toAppend = "b5"  ; }
        else if(inVec(semitones, {3,7})){ chordSymbol = ""    ; uppercase = false; }
        else if(inVec(semitones, {3,6})){ chordSymbol = "°"   ; uppercase = false; }
        else if(inVec(semitones, {4,8})){ chordSymbol = "+"   ;                    }
        else if(inVec(semitones, {2,7})){ chordSymbol = ""    ; toAppend = "sus2"; }
        else if(inVec(semitones, {2,6})){ chordSymbol = ""    ; toAppend = "sus2b5"; uppercase = false; }
        else if(inVec(semitones, {5,7})){ chordSymbol = ""    ; toAppend = "sus4";                       }
        else { 
            // String with the semitones:
            std::string semitonesString = "";
            for(auto semitone : semitones) semitonesString += std::to_string(semitone) + " ";
            // Throw exception for unknown chord
            throw std::runtime_error("Scale::getChordSymbol(): Unknown chord with Semitones: " + semitonesString);
        }
        
        // 7th
        if(size > 3){
            if     (inVec(semitones, Intervals("b7").getSemitones())){ if(chordSymbol == "°") chordSymbol = "ø7"; else chordSymbol.append("7" ); }
            else if(inVec(semitones, Intervals("7") .getSemitones())){ chordSymbol.append("Maj7"); }
            else if(inVec(semitones, Intervals("6") .getSemitones())){ chordSymbol.append(chordSymbol == "°" ? "7" : "6"); }
            else {
                // String with the semitones:
                std::string semitonesString = "";
                for(auto semitone : semitones) semitonesString += std::to_string(semitone) + " ";
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown extension with Semitones: " + semitonesString);
            }
        }

        // 9th Chords
        if(size > 4){
            if     (inVec(semitones, Intervals("9") .getSemitones())){ chordSymbol.back() = '9'; }
            else if(inVec(semitones, Intervals("b9").getSemitones())){ toAppend += "b9"; }
            else if(inVec(semitones, Intervals("#9").getSemitones())){ toAppend += "#9"; }
            else {
                // String with the semitones:
                std::string semitonesString = "";
                for(auto semitone : semitones) semitonesString += std::to_string(semitone) + " ";
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 9th chord with Semitones: " + semitonesString);
            }
        }

        // 11th Chords
        if(size > 5){
            if     (inVec(semitones, Intervals("11") .getSemitones())){ chordSymbol.back() = '1'; chordSymbol.push_back('1'); }
            else if(inVec(semitones, Intervals("b11").getSemitones())){ toAppend += "b11"; }
            else if(inVec(semitones, Intervals("#11").getSemitones())){ toAppend += "#11"; }
            else {
                // String with the semitones:
                std::string semitonesString = "";
                for(auto semitone : semitones) semitonesString += std::to_string(semitone) + " ";
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 11th chord with Semitones: " + semitonesString);
            }
        }

        // 13th Chords
        if(size > 6){
            if     (inVec(semitones, Intervals("13") .getSemitones())){ replaceBack(chordSymbol,"13",endsWith(chordSymbol,"11") ? 2 : 1); }
            else if(inVec(semitones, Intervals("b13").getSemitones())){ toAppend += "b13"; }
            else if(inVec(semitones, Intervals("#13").getSemitones())){ toAppend += "#13"; }
            else {
                // String with the semitones:
                std::string semitonesString = "";
                for(auto semitone : semitones) semitonesString += std::to_string(semitone) + " ";
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 13th chord with Semitones: " + semitonesString);
            }
        }

        // Insert the roman numeral at beginning of the chord symbol
        chordSymbol.insert(0, chordIntervals.front().getRomanName(uppercase));

        // Append
        if(!toAppend.empty()){
            // toAppend.insert(0, "^");
            chordSymbol.append(toAppend);
        }

        // Print the chord symbol
        // std::cout << "Chord Symbol: " << chordSymbol << std::endl;
        // Replace part of string at the end with another string 
        // chordSymbol.replace(chordSymbol.end()-1, chordSymbol.end(), "b5");






        return std::move(chordSymbol);

    }

    // Get chord at index
    Chord getChord(int index, int size=3)
    {   
        const auto& chordSymbol = getChordSymbol(index, size);
        auto chord = Chord(chordSymbol);
        return std::move(chord);
    }


    std::vector<std::string> getChordSymbols(int size=3)
    {
        std::vector<std::string> chordSymbols;
        for(int i=0; i<mIntervals.size(); i++)
        {
            chordSymbols.push_back(getChordSymbol(i,size));
        }

        return std::move(chordSymbols);
    }

    // Print the chord symbols
    void printChordSymbols(int size=3)
    {
        auto chordSymbols = getChordSymbols(size);
        for(auto chordSymbol : chordSymbols)
        {
            std::cout << chordSymbol << " ";
        }
        std::cout << std::endl;
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

    // Size of the scale
    int size()
    {
        return mIntervals.size();
    }

    // Stream operator to print the scale
    friend std::ostream& operator<<(std::ostream& os, const Scale& scale)
    {
        os << scale.mName << "(" << scale.mIntervals << ")";
        
        return os;
    }

    // Print the scale
    void print(int size=3)
    {
        std::cout << "Scale: " << mName << std::endl;
        int i = 0;
        std::cout << "Int\tSemi\tChord\n";
        for(auto interval : mIntervals)
        {
            std::cout << interval.getString() << "\t" << interval.getSemitones() << "\t" << getChordSymbol(i++,size) << "\n";
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
            //"Melodic Minor"        , "Dorian b2"   , "Lydian Augmented", "Lydian Dominant", "Mixolydian b6"    , "Locrian #2", "Altered",
            //"Harmonic Minor"       , "Locrian n6"  , "Ionian #5"       , "Dorian #4"      , "Phrygian Dominant", "Lydian #2" , "Super Locrian",
            //"Double Harmonic Major", "Lydian #2 #6", "Ultra Phrygian"  , "Hungarian Minor"
            })
        {
            scales.push_back(Scale(scaleName));
        }

        return std::move(scales);
    }

    static void printAllScales(int size=3)
    {
        for(auto scale : getAllScales())
        {
            scale.print(size);
        }
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
    Intervals mIntervals;
    // The scale root note
    int mRootNote = 0;


    // Function to test is a vector contains the values given in the arguments
    bool inVec(const std::vector<int>& vec, const std::vector<int>& values)
    {
        return std::all_of(values.begin(), values.end(), [&vec](int value){return std::find(vec.begin(), vec.end(), value) != vec.end();});
    }

    void replaceBack(std::string& str, const std::string& toReplace, int size=1)
    {
        str.replace(str.end()-size, str.end(), toReplace);
    }

    // Test is a string ens with another string
    bool endsWith(const std::string& str, const std::string& ending)
    {
        if(str.length() >= ending.length())
        {
            return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
        }
        return false;
    }



};









} // namespace cmtk
