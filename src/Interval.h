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
class Interval {
public:
    // Constructor
    Interval() = default;
    Interval(std::string interval)
    {
        set(interval);
    }
    Interval(int degree, int quality=0)
    {
        set(degree, quality);
    }

    static Interval newFromSemi(int semitones, bool sharp=false)
    {
        Interval res;
        res.setFromSemi(semitones,sharp);
        return std::move(res);
    }

    // Function to set the interval
    void set(std::string aName)
    {
        // Test that the string only contains valid characters
        for(auto c : aName)
        {
            if(c != 'b' && c != '#' && !std::isdigit(c))
            {
                throw std::invalid_argument("Invalid interval name - Invalid character " + std::string(1, c));
            }
        }
        // Test that the string is not empty
        if(aName.empty())
        {
            throw std::invalid_argument("Invalid interval name - Empty string");
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
        throw std::invalid_argument("Invalid interval name - No degree specified");
    }

    void set(int aDegree, int aQuality=0)
    {
        // Make sure the degree is 1 or higher
        while(aDegree < 1) aDegree += 7;

        // Set the degree, quality and semitones
        degree = aDegree;
        quality = aQuality;
        updateSemitones(degree, quality);
    }

       // Set from a vector of semitones - The lowest semitone will be treated as the root
    void setFromSemi(int s, bool sharp=false)
    {
        int octave = 0;
        while(s >= 12)
        {
            s -= 12;
            octave++;
        }
        while(s < 0)
        {
            s += 12;
            octave--;
        }

        switch(s)
        {
            case  0: set(octave*7 + 1)   ; break;
            case  1: sharp ? set(octave*7 + 1, 1) : set(octave*7 + 2,-1); break;
            case  2: set(octave*7 + 2)   ; break;
            case  3: sharp ? set(octave*7 + 2, 1) : set(octave*7 + 3,-1); break;
            case  4: set(octave*7 + 3)   ; break;
            case  5: set(octave*7 + 4)   ; break;
            case  6: sharp ? set(octave*7 + 4, 1) : set(octave*7 + 5,-1); break;
            case  7: set(octave*7 + 5)   ; break;
            case  8: sharp ? set(octave*7 + 5, 1) : set(octave*7 + 6,-1); break;
            case  9: set(octave*7 + 6)   ; break;
            case 10: sharp ? set(octave*7 + 6, 1) : set(octave*7 + 7,-1); break;
            case 11: set(octave*7 + 7)   ; break;
        }        
    }

    // Function to get the interval as a string
    const std::string getString() const
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
    const std::string getName() const
    {
        return std::move(getString());
    }

    // Function to get the number of semitones
    const int getSemitones() const
    {
        return semitones;
    }

    // Print the interval
    void print()
    {
        std::cout << "(" << getString() << "~" << getSemitones() << ")" << std::endl;   
    }

    // Print name
    void printName()
    {
        std::cout << getName() << std::endl;   
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
    const int getQuality() const
    {
        return quality;
    }

    // Get Degree
    const int getDegree() const
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
    bool operator==(const Interval& other) const
    {
        return degree == other.degree && quality == other.quality;
    }

    // Equality operator for string
    const bool operator==(const std::string& intervalString) const
    {
        return intervalString == getName();
    }

    // Inequality operator
    bool operator!=(const Interval& other) const
    {
        return !((*this) == other);
    }

    // Add a function to be used in std::sort
    bool operator<(const Interval& other) const
    {
        return semitones < other.semitones;
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Interval& i)
    {
        auto tmp = i;
        os << tmp.getString();
        return os;
    }

    // Function to shift the interval up a number of octaves by manipulating the degree and the quality
    void shiftOctave(int n)
    {   
        // Shift the degree up by 7
        degree += 7*n;
        // Shift the quality up by 12
        semitones += 12*n;
    }

    // Get Name as Roman Numeral
    std::string getRomanName(bool upperCase) 
    {
        std::string res = "";
        
        // Add the quality
        auto quality = this->quality;
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

        // Add the degree
        res += getRomanDegree(upperCase);
        
        // Return the result
        return std::move(res);

    }

    // Interval to Note Name
    std::string getNoteName(int rootNote, bool isRoman = false)
    {
        // Get the note number
        int note = (rootNote + getSemitones()) % 12;

        // Get the quality of the interval
        auto sharpFlat = getQuality();
        bool isSharp = sharpFlat > 0;
        bool isFlat  = sharpFlat < 0;

        if(isRoman){
            // Return the note name
            switch(note){
                case 0:  return "I";
                case 1:  return isSharp ? "#I" : "bII";
                case 2:  return "II";
                case 3:  return isSharp ? "#II" : "bIII";
                case 4:  return "III";
                case 5:  return "IV";
                case 6:  return isSharp ? "#IV" : "bV";
                case 7:  return "V";
                case 8:  return isSharp ? "#V" : "bVI";
                case 9:  return "VI";
                case 10: return isSharp ? "#VI" : "bVII";
                case 11: return "VII";
            }
        }
        else {
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
        }
        // Print error message
        std::cerr << "Error: intervalToNoteName(): Note not found note" << std::endl;
        return "C";
    }

    // Function to return the negative harmonic to the interval
    Interval getNegativeHarmonic()
    {
        // This will mirror on the Major <--> Minor axis
        return std::move(Interval::newFromSemi(7-semitones));
    }

    // Function to convert the interval to the negative harmonic by mirroring on the Major <--> Minor axis
    void negHarmonic()
    {
        // This will mirror on the Major <--> Minor axis
        setFromSemi(7-semitones);
    }

    // Transpose
    void transpose(int semitones)
    {
        setFromSemi(getSemitones() + semitones);
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

    // Get Degree as Roman Numeral
    std::string getRomanDegree(bool upperCase)
    {
        auto degree = this->getDegree();
        while(degree > 7)
        {
            degree -= 7;
        }
        while(degree < 1)
        {
            degree += 7;
        }
        switch(degree)
        {
            case 1: return upperCase ? "I"   : "i"  ;
            case 2: return upperCase ? "II"  : "ii" ;
            case 3: return upperCase ? "III" : "iii";
            case 4: return upperCase ? "IV"  : "iv" ;
            case 5: return upperCase ? "V"   : "v"  ;
            case 6: return upperCase ? "VI"  : "vi" ;
            case 7: return upperCase ? "VII" : "vii";
            default: return "";
        }
    }
 
};



// ------------------------------------------------------------------------------------------------ //
// ---------------------------------------- Intervals Class --------------------------------------- //
// ------------------------------------------------------------------------------------------------ //
using IntervalVector = std::vector<Interval>;
class Intervals : public IntervalVector {
public:
    // Constructor
    Intervals() = default;

    // Constructor
    Intervals(IntervalVector intervals)
    {
        set(intervals);
    }

    // Constructor
    Intervals(std::string intervals)
    {
        set(intervals);
    }

    // Function to set the intervals
    void set(const IntervalVector& intervals)
    {
        // Clear the intervals
        IntervalVector::clear();

        // Add the intervals
        for(const auto& i : intervals)
        {
            add(i);
        }
    }

    // Set the intervals from a string
    void set(const std::string& intervals)
    {
        // Clear the intervals
        IntervalVector::clear();

        // Add the intervals
        add(intervals);
    }

    // Overload the assignment operator
    Intervals& operator=(const IntervalVector& intervals)
    {
        set(intervals);
        return *this;
    }

    // Overload the assignment operator
    Intervals& operator=(const std::string& intervals)
    {
        set(intervals);
        return *this;
    }

    void add(int degree, int quality=0)
    {
        add(Interval(degree, quality));
    }

    void add(std::string str)
    {
        for(auto& interval : fromString(str))
        {
            add(interval);
        }
    }

    // Function to add an interval to the chord
    void add(const Interval& interval){
        // If an equal interval is already present, then do not add it, but replace it
        for(auto& i : *this){
            if(i == interval){
                i = interval;
                return;
            };
        }

        // Add the interval
        IntervalVector::push_back(interval);
    }

    // Template function to add an interval to the chord
    template<typename... Args>
    void add(const Interval& interval, Args... args){
        add(interval);
        add(args...);
    }

    // Template function to set the intervals
    template<typename... Args>
    void set(const Interval& interval, Args... args){
        set(interval);
        add(args...);
    }

    // Function to insert an interval into a specific index
    void insert(int index, const Interval& n){
        // Test if interval already present
        for(auto& interval : *this){
            if(interval == n){ 
                // Move the interval to the new index
                IntervalVector::erase(std::remove(IntervalVector::begin(), IntervalVector::end(), n), IntervalVector::end());
                IntervalVector::insert(IntervalVector::begin() + index, n);
                return;
            }
        }

        // If not, add the interval
        IntervalVector::insert(IntervalVector::begin() + index, n);
    }

    // Remove Interval, return true if removed
    bool remove(const Interval& n)
    {
        // Remove the interval if Degree and Quality are the same
        auto it = std::remove_if(IntervalVector::begin(), IntervalVector::end(), [n](Interval i){ return i.getDegree() == n.getDegree() && i.getQuality() == n.getQuality();});
        if(it == IntervalVector::end()) return false;
        IntervalVector::erase(it, IntervalVector::end());
        return true;
    }

    static Intervals fromString(std::string str)
    {
        // Replace double spaces with single spaces
        str.erase(std::unique(str.begin(), str.end(), [](char a, char b){ return a == ' ' && b == ' '; }), str.end());
        // Remove spaces at the beginning and end of the string
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch){ return !std::isspace(ch); }));
        str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch){ return !std::isspace(ch); }).base(), str.end());

        // Create the Intervals object
        Intervals res;

        size_t pos = 0;
        while((pos = str.find(" ")) != std::string::npos)
        {
            res.add(Interval(str.substr(0, pos)));
            str.erase(0, pos + 1);
        }
        res.add(Interval(str));

        return std::move(res);
    }

    // Remove Interval by string, return true if changed
    bool remove(const std::string& str)
    {
        bool changed = false;

        for(auto& interval : fromString(str))
        {
            if(remove(interval)) changed = true;
        }

        return changed; 
    }

    // Remove Interval by Degree and Quality
    void remove(int degree, int quality)
    {
        IntervalVector::erase(std::remove_if(IntervalVector::begin(), IntervalVector::end(), [degree, quality](Interval i){ return (i.getDegree() == degree) && (i.getQuality() == quality); }), IntervalVector::end());
    }

    // Remove Interval by Degree related to the Major Scale
    void removeDegree(int aDegree)
    {
        IntervalVector::erase(std::remove_if(IntervalVector::begin(), IntervalVector::end(), [aDegree](Interval i){ return i.getDegree() == aDegree; }), IntervalVector::end());
    }

    // Set Quality
    void setQuality(int aDegree, int aQuality, bool allowAdd = false)
    {
        // Find the Degree and set the quality
        for(auto& interval : *this)
        {
            if(interval.getDegree() == aDegree)
            {
                interval.setQuality(aQuality);
                return;
            }
        }
        // If the degree is not found, add it
        if(allowAdd)
        {
            IntervalVector::push_back(Interval(aDegree, aQuality));
        }
    }

    // Print the chord intervals
    void print(){
        for(auto& interval : *this){
            std::cout << "(" << interval.getString() << "~" << interval.getSemitones() << ") ";
        }
        std::cout << std::endl;
    }

    // Sort function
    void sort()
    {
        std::sort(IntervalVector::begin(), IntervalVector::end());
    }

    // Test if an interval is present
    const bool contains(const Interval& n) const
    {
        // Test if interval is present - both Degree and Quality must match
        return std::find_if(IntervalVector::begin(), IntervalVector::end(), [n](Interval i){ return i.getDegree() == n.getDegree() && i.getQuality() == n.getQuality(); }) != IntervalVector::end();
    }

    // Test if an interval is present
    const bool contains(const std::string& yes) const
    {
        for(const auto& interval : fromString(yes))
        {
            if(!contains(interval)) return false;
        }
        return true;        
    }

    // Test if an interval is not present
    const bool containsNot(const std::string& no) const
    {
        for(const auto& interval : fromString(no))
        {
            if(contains(interval)) return false;
        }

        return true;
    }

    // Test if an interval is present and another is not
    const bool contains(const std::string& yes, const std::string& no) const
    {
        return contains(yes) && containsNot(no);
    }

    // Contains Degree
    const bool containsDegree(int degree) const
    {
        return std::find_if(IntervalVector::begin(), IntervalVector::end(), [degree](Interval i){ return i.getDegree() == degree; }) != IntervalVector::end();
    }

    // Equality operator
    bool operator==(const Intervals& other) const
    {
        if(size() != other.size()) return false;
        for(int i = 0; i < size(); i++)
        {
            if(at(i) != other.at(i)) return false;
        }
        return true;
    }


    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Intervals& intervals)
    {
        for(const auto& interval : intervals)
        {
            if(interval == intervals.back()) os << interval;
            else                             os << interval << " ";
        } 


        return os;
    }

    const std::vector<int> getSemitones(int offset=0) const
    {
        std::vector<int> res;
        for(auto& interval : *this)
        {
            res.push_back(interval.getSemitones()+offset);
        }
        return std::move(res);
    }

    // Get semitones, but ensure that the lowest is zero
    std::vector<int> getSemitonesNormalized()
    {
        auto semitones = getSemitones();
        const int min = *std::min_element(semitones.begin(), semitones.end());
        for(auto& s : semitones)
        {
            s -= min;
        }
        return std::move(semitones);
    }

    // Get the minimum Interval
    Interval getMin()
    {
        return *std::min_element(IntervalVector::begin(), IntervalVector::end());
    }

    // Get the minimum semitone
    int getMinSemi()
    {
        return *std::min_element(getSemitones().begin(), getSemitones().end());
    }

    // Get the maximum Interval
    Interval getMax()
    {
        return *std::max_element(IntervalVector::begin(), IntervalVector::end());
    }

    // Get the maximum semitone
    int getMaxSemi()
    {
        return *std::max_element(getSemitones().begin(), getSemitones().end());
    }

    // Get the median Interval
    Interval getMedian()
    {
        auto intervals = *this;
        std::sort(intervals.begin(), intervals.end());
        return intervals[intervals.size()/2];
    }

    // Get the median semitone
    int getMedianSemi()
    {
        auto semitones = getSemitones();
        std::sort(semitones.begin(), semitones.end());
        return semitones[semitones.size()/2];
    }

    // Get the mean semitone
    int getMeanSemi()
    {
        auto semitones = getSemitones();
        int sum = 0;
        for(auto s : semitones)
        {
            sum += s;
        }
        return sum / semitones.size();
    }



    // Create a new Intervals object from the semitones 
    static Intervals newFromSemi(std::vector<int> semitones, bool normalize=false)
    {
        Intervals res;
        res.setFromSemi(semitones, normalize);
        return std::move(res);
    }

    // Set from a vector of semitones - The lowest semitone will be treated as the root
    void setFromSemi(std::vector<int> semitones, bool normalize=false)
    {
        // Sort the semitones
        std::sort(semitones.begin(), semitones.end());

        // Normalize the semitones
        if(normalize)
        {
            int min = *std::min_element(semitones.begin(), semitones.end());
            for(auto& s : semitones){ s -= min; }
        }

        // Clear the intervals
        clear();

        // Add the intervals
        for(auto s : semitones)
        {
            int octave = 0;
            while(s >= 12)
            {
                s -= 12;
                octave++;
            }

            switch(s)
            {
                case  0: add(octave*7 + 1)   ; break;
                case  1: add(octave*7 + 2,-1); break;
                case  2: add(octave*7 + 2)   ; break;
                case  3: add(octave*7 + 3,-1); break;
                case  4: add(octave*7 + 3)   ; break;
                case  5: add(octave*7 + 4)   ; break;
                case  6: add(octave*7 + 5,-1); break;
                case  7: add(octave*7 + 5)   ; break;
                case  8: add(octave*7 + 6,-1); break;
                case  9: add(octave*7 + 6)   ; break;
                case 10: add(octave*7 + 7,-1); break;
                case 11: add(octave*7 + 7)   ; break;
            }

        }
    }

    std::string getChordSymbol()
    {   
        auto intervals = this->getNormalized();
        std::string chordSymbol = "";
        bool maj = false;
        std::string toAppend = "";

        if     (intervals.contains("3 b7", "#5 b6")){ chordSymbol = "dom"  ; intervals.remove("3")           ; }
        else if(intervals.contains("3 #5", "b3 5" )){ chordSymbol = "aug"  ; intervals.remove("3")           ; }
        else if(intervals.contains("b3 b5","3 5"  )){ chordSymbol = "dim"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("3"            )){ chordSymbol = "maj"  ; intervals.remove("3"); maj=true ; }
        else if(intervals.contains("b3"           )){ chordSymbol = "min"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("2 5"          )){ chordSymbol = "sus2" ; intervals.remove("2")           ; }
        else if(intervals.contains("4 5"          )){ chordSymbol = "sus4" ; intervals.remove("4")           ; }
        else if(intervals.contains("5"            )){ chordSymbol = "5"    ;                                 ; }

        // Add Extension
        if     (intervals.contains("b7 9 11 13"  )){ chordSymbol += "13"      ; intervals.remove("b7 9 11 13"   );  }
        else if(intervals.contains("b7 b9 11 13" )){ chordSymbol += "13 b9"   ; intervals.remove("b7 b9 11 13"  );  }
        else if(intervals.contains("b7 9 b11 13" )){ chordSymbol += "13 b11"  ; intervals.remove("b7 9 b11 13"  );  }
        else if(intervals.contains("b7 b9 b11 13")){ chordSymbol += "13 b9b11"; intervals.remove("b7 b9 b11 13" );  }
        else if(intervals.contains("b7 9 11"     )){ chordSymbol += "11"      ; intervals.remove("b7 9 11" );  }
        else if(intervals.contains("b7 b9 11"    )){ chordSymbol += "11 b9"   ; intervals.remove("b7 b9 11");  }
        else if(intervals.contains("b7 9"        )){ chordSymbol += "9"       ; intervals.remove("b7 9" );  }
        else if(intervals.contains("b7"          )){ chordSymbol += "7"       ; intervals.remove("b7" );  }
        else if(intervals.contains("7 9 11 13"   )){ chordSymbol += maj ? "13" : "Maj13" ; intervals.remove("7 9 11 13" );  }
        else if(intervals.contains("7 b9 11 13"  )){ chordSymbol += maj ? "13 b9" : "Maj13 b9" ; intervals.remove("7 b9 11 13" );  }
        else if(intervals.contains("7 9 b11 13"  )){ chordSymbol += maj ? "13 b11" : "Maj13 b11" ; intervals.remove("7 9 b11 13" );  }
        else if(intervals.contains("7 b9 b11 13" )){ chordSymbol += maj ? "13 b9b11" : "Maj13 b9b11" ; intervals.remove("7 b9 b11 13" );  }
        else if(intervals.contains("7 9 11"      )){ chordSymbol += maj ? "11" : "Maj11" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 b9 11"     )){ chordSymbol += maj ? "11 b9" : "Maj11 b9" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 9"         )){ chordSymbol += maj ? "9"  : "Maj9"  ; intervals.remove("7 9" );  }
        else if(intervals.contains("7"           )){ chordSymbol += maj ? "7"  : "Maj7"  ; intervals.remove("7" );  }

        // Check if the 5 is present
        if     (intervals.contains("b3" )){ chordSymbol += " b3"    ; intervals.remove("b3"  );  }
        else if(intervals.contains("#3" )){ chordSymbol += " #3"    ; intervals.remove("#3"  );  }

        if     (intervals.contains("b5" )){ chordSymbol += " b5"    ;                            }
        else if(intervals.contains("#5" )){ chordSymbol += " #5"    ;                            }

        if     (intervals.contains("b7" )){ chordSymbol += " b7"    ; intervals.remove("b7"  );  }
        else if(intervals.contains("#7" )){ chordSymbol += " #7"    ; intervals.remove("#7"  );  }

        if     (intervals.contains("b9" )){ chordSymbol += " b9"    ; intervals.remove("b9"  );  }
        else if(intervals.contains("#9" )){ chordSymbol += " #9"    ; intervals.remove("#9"  );  }

        if     (intervals.contains("b11")){ chordSymbol += " b11"   ; intervals.remove("b11" );  }
        else if(intervals.contains("#11")){ chordSymbol += " #11"   ; intervals.remove("#11" );  }

        if     (intervals.contains("b13")){ chordSymbol += " b13"   ; intervals.remove("b13" );  }
        else if(intervals.contains("#13")){ chordSymbol += " #13"   ; intervals.remove("#13" );  }


        // Check for no 3rd or 5th
        if(!intervals.containsDegree(1)) chordSymbol += " no1";
        else intervals.removeDegree(1);

        //if(!intervals.containsDegree(5)) chordSymbol += " no5";
        //else intervals.removeDegree(5);


        // Check added notes - Naturals
        std::vector<std::string> addedNotes = {
            "b2" , "2" , "#2" , 
            "b3" , "3" , "#3" ,
            "b4" , "4" , "#4" ,
            "b5" , "5" , "#5" ,
            "b6" , "6" , "#6" ,
            "b7" , "7" , "#7" ,
            "b9" , "9" , "#9" ,
            "b11", "11", "#11",
            "b13", "13", "#13",
        };
            
        for(const auto& note : addedNotes){
            if(intervals.contains(note)){
                chordSymbol += " add" + note;
                intervals.remove(note);
            }
        }

        return chordSymbol;
    }

    // Print the ChordSymbol
    void printChordSymbol()
    {
        std::cout << "Chord Symbol: " << getChordSymbol() << std::endl;
    }

    // Function to get the Intervals normalized
    Intervals getNormalized()
    {
        Intervals res;
        for(auto s : getSemitonesNormalized())
        {
            res.add(Interval::newFromSemi(s));
        }
        return std::move(res);
    }

    // Normalize the Intervals
    void normalize()
    {
        setFromSemi(getSemitonesNormalized());
    }
    
    // Get negative harmonic 
    Intervals getNegativeHarmonic()
    {
        Intervals res;
        for(auto& interval : *this)
        {
            res.add(interval.getNegativeHarmonic());
        }
        // Sort the intervals
        res.sort();

        return std::move(res);
    }

    // Convert to Negative Harmonic by mirroring on the Major <--> Minor axis
    void negHarmonic()
    {
        for(auto& interval : *this) interval.negHarmonic();
    }

    // Transpose this
    void transpose(int semitones)
    {
        for(auto& interval : *this)
        {
            interval.transpose(semitones);
        }
    }

    // Return a new transposed Intervals object
    Intervals getTransposed(int semitones)
    {
        auto res = *this;
        res.transpose(semitones);
        return std::move(res);
    }

    // Get Interval from Degree
    Interval getIntervalFromDegree(int degree)
    {
        for(auto& interval : *this)
        {
            if(interval.getDegree() == degree) return interval;
        }
        return Interval();
    }

private:


};








} // namespace cmtk
