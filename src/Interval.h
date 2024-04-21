#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Chords.h"

namespace cmtk {


// ----------------------------------------------------------------------- //
// ----------------------------- Interval Class -------------------------- //
// ----------------------------------------------------------------------- //
class Interval : public CMTK {
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

    static Interval NewFromSemi(int semitones, bool sharp=false)
    {
        Interval res;
        res.setFromSemi(semitones,sharp);
        return std::move(res);
    }

    Interval& clear()
    {
        mDegree    = 0;
        mQuality   = 0;
        mSemitones = 0;
        return *this;
    }

    // Function to set the interval
    Interval& set(std::string aName)
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
        mQuality = 0;

        // While the interval is not empty and starts with a 'b' or '#' character 
        while(!aName.empty() && (aName[0] == 'b' || aName[0] == '#'))
        {
            // If the interval starts with a 'b' character
            if(aName[0] == 'b')
            {
                mQuality--;
            }
            // If the interval starts with a '#' character
            else if(aName[0] == '#')
            {
                mQuality++;
            }
            // Remove the first character from the interval
            aName.erase(0, 1);
        }

        // If the interval is not empty and the first character is a digit
        if(!aName.empty() && std::isdigit(aName[0]))
        {
            // Get the degree of the interval
            mDegree = std::stoi(aName);

            // Calculate the number of semitones
            updateSemitones(mDegree, mQuality);

            // Return
            return *this;
        }

        // If the interval is empty
        throw std::invalid_argument("Invalid interval name - No degree specified");
    }

    Interval& set(int aDegree, int aQuality=0)
    {
        // Make sure the degree is 1 or higher
        while(aDegree < 1) aDegree += 7;

        // Set the degree, quality and semitones
        mDegree = aDegree;
        mQuality = aQuality;
        updateSemitones(mDegree, mQuality);
        return *this;
    }

    // Set from a vector of semitones - The lowest semitone will be treated as the root
    Interval& setFromSemi(int s, bool sharp=false)
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
        return *this;
    }

    // Function to return inverted interval
    Interval getInverted()
    {
        auto inverted = Interval::NewFromSemi(12-mSemitones);
        while(inverted.getDegree() < 1) inverted.shiftOctave(1);
        return std::move(inverted);
    }

    // Function to get the interval as a string
    std::string toString() const
    {
        auto quality = this->mQuality;
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
        res += std::to_string(mDegree);
        return std::move(res);
    }

    // Function to get the interval as a string
    const std::string getName() const
    {
        return std::move(toString());
    }

    // Function to get the number of semitones
    const int getSemi() const
    {
        return mSemitones;
    }

    // Print the interval
    Interval& print()
    {
        std::cout << "(" << toString() << "~" << getSemi() << ")" << std::endl;  
        return *this; 
    }

    // Print name
    Interval& printName()
    {
        std::cout << getName() << std::endl;   
        return *this;
    }

    // Sharpen the interval
    Interval& sharpen()
    {
        mQuality++;
        mSemitones++;
        return *this;
    }

    // Flatten the interval
    Interval& flatten()
    {
        mQuality--;
        mSemitones--;
        return *this;
    }

    // Set quality
    Interval& setQuality(int aQuality)
    {
        int diff = aQuality - mQuality;
        mQuality = aQuality;
        mSemitones += diff;
        return *this;
    }

    // Set quality from string
    Interval& setQuality(std::string aQuality)
    {
        int newQuality = 0;
        for(auto c : aQuality)
        {
            if     (c == 'b') newQuality--;
            else if(c == '#') newQuality++;
        }
        setQuality(newQuality);
        return *this;
    }

    // Set Quality from char
    Interval& setQuality(char aQuality)
    {
        int newQuality = aQuality == 'b' ? -1 : aQuality == '#' ? 1 : 0;
        setQuality(newQuality);
        return *this;
    }

    // Get Quality
    const int getQuality() const
    {
        return mQuality;
    }

    // Get Degree
    const int getDegree() const
    {
        return mDegree;
    }

    // Set Degree
    Interval& setDegree(int aDegree, bool keepSemi=false)
    {
        if(keepSemi) return setDegreeKeepSemi(aDegree);
        mDegree = aDegree;
        updateSemitones(mDegree, mQuality);
        return *this;
    }

    // Set Degree
    Interval& setDegreeKeepSemi(int aDegree)
    {
        mDegree = aDegree;
        auto semiFromMajorDegree = getSemiFromMajorDegree(mDegree);
        mQuality = mSemitones - semiFromMajorDegree;
        return *this;
    }

    // Set Degree and Semi - Quality will be adjusted
    Interval& setDegreeSemi(int aDegree, int aSemi)
    {
        mDegree = aDegree;
        mSemitones = aSemi;
        mQuality = mSemitones - getSemiFromMajorDegree(mDegree);
        return *this;
    }

    // Equality operator
    bool operator==(const Interval& other) const
    {
        return mDegree == other.mDegree && mQuality == other.mQuality;
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
        return mSemitones < other.mSemitones;
    }

    // operator+ for Interval
    Interval operator+(const Interval& other) const
    {
        return Interval::NewFromSemi(mSemitones + other.mSemitones);
    }

    // operator+ for Semitones
    Interval operator+(int n) const
    {
        return Interval::NewFromSemi(mSemitones + n);
    }

    // operator+= for Interval
    Interval& operator+=(const Interval& other)
    {
        setFromSemi(mSemitones + other.mSemitones);
        return *this;
    }

    // operator+= for Semitones
    Interval& operator+=(int n)
    {
        setFromSemi(mSemitones + n);
        return *this;
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Interval& i)
    {
        auto tmp = i;
        os << tmp.toString();
        return os;
    }

    // Function to shift the interval up a number of octaves by manipulating the degree and the quality
    Interval& shiftOctave(int n)
    {   
        // Shift the degree up by 7
        mDegree += 7*n;
        // Shift the quality up by 12
        mSemitones += 12*n;
        return *this;
    }

    // Interval to Note Name
    std::string getNoteName(int rootNote, bool isRoman = false) const
    {
        // Get the note number
        int note = (rootNote + getSemi()) % 12;

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
    Interval getNegativeHarmonic() const
    {
        // This will mirror on the Major <--> Minor axis
        return std::move(Interval::NewFromSemi(7-mSemitones));
    }

    // Function to convert the interval to the negative harmonic by mirroring on the Major <--> Minor axis
    Interval& harmonicNeg()
    {
        // This will mirror on the Major <--> Minor axis
        setFromSemi(7-mSemitones);
        return *this;
    }

    // Transpose
    Interval& transpose(int n)
    {
        setFromSemi(getSemi() + n);
        return *this;
    }

    // ----------------------------- Support for Roman Numerals ----------------------------- //
    // Create a new Interval from a Roman Numeral
    static Interval NewFromRoman(std::string roman)
    {
        Interval res;
        res.setRoman(roman);
        return std::move(res);
    }

    // Set the interval from a Roman Numeral
    Interval& setRoman(std::string aRoman)
    {
        clear();
        // Handle flat and sharp symbols
        while(aRoman.front() == 'b' || aRoman.front() == '#')
        {
            if     (aRoman.front() == 'b') flatten();
            else if(aRoman.front() == '#') sharpen();
            aRoman.erase(0,1);
        }

        // Set Degree
        setDegree(romanToInt(aRoman));
        
        return *this;
    }

    // Get Name as Roman Numeral
    std::string getRoman(bool upperCase) const
    {
        std::string res = "";
        
        // Add the quality
        auto quality = this->mQuality;
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
        res += getDegreeRoman(upperCase);
        
        // Return the result
        return std::move(res);
    }

    // Get Degree as Roman Numeral
    std::string getDegreeRoman(bool upperCase) const
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

    Interval& simplify()
    {
        // Simplify the interval
        while(mDegree > 7)
        {
            mDegree -= 7;
        }
        while(mDegree < 1)
        {
            mDegree += 7;
        }
        // Update the semitones
        updateSemitones(mDegree, mQuality);
        return *this;
    }

private:
    // Function to set the interval
    int mSemitones = 0; // The number of semitones required to reach the interval
    int mDegree = 0;    // The degree is relative to the major scale
    int mQuality = 0;   // -1 for flat, 0 for natural, 1 for sharp, etc.

    // Function to get the number of semitones from the degree and quality
    void updateSemitones(int aDegree, int aQuality)
    {
        mSemitones = aQuality + getSemiFromMajorDegree(aDegree);
    }

    int getSemiFromMajorDegree(int aDegree)
    {
        auto semitones = 0;
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

        return semitones;

    }


 
};



// ------------------------------------------------------------------------------------------------ //
// ---------------------------------------- Intervals Class --------------------------------------- //
// ------------------------------------------------------------------------------------------------ //
using IntervalVector = std::vector<Interval>;
class Intervals : public CMTK, public IntervalVector {
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
    Intervals& set(const IntervalVector& intervals)
    {
        // Clear the intervals
        IntervalVector::clear();

        // Add the intervals
        for(const auto& i : intervals)
        {
            add(i);
        }

        return *this;
    }

    // Set the intervals from a string
    Intervals& set(const std::string& intervals)
    {
        // Clear the intervals
        IntervalVector::clear();

        // Add the intervals
        add(intervals);

        return *this;
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
    
    Intervals& add(const Intervals& interval)
    {
        for(auto& i : interval) add(i);
        return *this;
    }

    Intervals& add(const IntervalVector& interval)
    {
        for(auto& i : interval) add(i);
        return *this;
    }

    Intervals& add(int degree, int quality=0)
    {
        add(Interval(degree, quality));
        return *this;
    }

    Intervals& add(std::string str)
    {
        for(auto& interval : FromString(str)){ add(interval); }
        return *this;
    }

    // Add semitone
    Intervals& addSemi(int semi, bool sharp=false)
    {
        add(Interval::NewFromSemi(semi,sharp));
        return *this;
    }

    // Add semitones
    Intervals& addSemi(std::vector<int> semi, bool sharp=false)
    {
        for(auto s : semi) add(Interval::NewFromSemi(s,sharp));
        return *this;
    }

    // Remove semitone
    Intervals& removeSemi(int semi)
    {
        // Remove the interval if semi is the same
        auto it = std::remove_if(IntervalVector::begin(), IntervalVector::end(), [semi](Interval i){ return i.getSemi() == semi; });
        IntervalVector::erase(it, IntervalVector::end());
        return *this;
    }

    // Remove semitones
    Intervals& removeSemi(std::vector<int> semi)
    {
        for(auto s : semi) removeSemi(s);
        return *this;
    }
    
    // Function to add an interval to the chord
    Intervals& add(const Interval& interval){
        // If an equal interval is already present, then do not add it, but replace it
        for(auto& i : *this){
            if(i == interval){
                i = interval;
                return *this;
            };
        }

        // Add the interval
        IntervalVector::push_back(interval);
        return *this;
    }

    // Function to insert an interval into a specific index
    Intervals& insert(int index, const Interval& n){
        // Test if interval already present
        for(auto& interval : *this){
            if(interval == n){ 
                // Move the interval to the new index
                IntervalVector::erase(std::remove(IntervalVector::begin(), IntervalVector::end(), n), IntervalVector::end());
                IntervalVector::insert(IntervalVector::begin() + index, n);
                return *this;
            }
        }

        // If not, add the interval
        IntervalVector::insert(IntervalVector::begin() + index, n);
        return *this;
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

    // toString
    std::string toString() const
    {
        std::string res = "";
        for(auto& interval : *this)
        {
            if(interval == this->back()) res += interval.toString();
            else                         res += interval.toString() + " ";            
        }

        return std::move(res);
    }

    // Rotate the intervals
    Intervals& rotate(int n)
    {
        // Rotate the intervals
        if(n > 0) std::rotate(IntervalVector::begin() , IntervalVector::begin() + n, IntervalVector::end());
        if(n < 0) std::rotate(IntervalVector::rbegin(), IntervalVector::rbegin() - n, IntervalVector::rend());
        return *this;
    }

    // Remove Interval by string, return true if changed
    bool remove(const std::string& str)
    {
        bool changed = false;

        for(auto& interval : FromString(str))
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

    // Convert a string to a Intervals object
    static Intervals FromString(std::string str)
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


    // Set Quality of the Interval by Degree
    Intervals& setQuality(int aDegree, int aQuality, bool allowAdd = false)
    {
        // Find the Degree and set the quality
        for(auto& interval : *this)
        {
            if(interval.getDegree() == aDegree)
            {
                interval.setQuality(aQuality);
                return *this;
            }
        }
        // If the degree is not found, add it
        if(allowAdd)
        {
            IntervalVector::push_back(Interval(aDegree, aQuality));
        }
        return *this;
    }

    // Print the chord intervals
    Intervals& print(){
        for(auto& interval : *this){
            std::cout << "(" << interval.toString() << "~" << interval.getSemi() << ") ";
        }
        std::cout << std::endl;
        return *this;
    }

    // Print the semitones
    Intervals& printSemi(){
        for(auto& interval : *this){
            std::cout << interval.getSemi() << " ";
        }
        std::cout << std::endl;
        return *this;
    }

    // Sort function
    Intervals& sort()
    {
        std::sort(IntervalVector::begin(), IntervalVector::end());
        return *this;
    }

    // Test if an interval is present
    bool contains(const Interval& n) const
    {
        // Test if interval is present - both Degree and Quality must match
        return std::find_if(IntervalVector::begin(), IntervalVector::end(), [n](Interval i){ return i.getDegree() == n.getDegree() && i.getQuality() == n.getQuality(); }) != IntervalVector::end();
    }

    // Test if an interval is present
    const bool contains(const std::string& yes) const
    {
        for(const auto& interval : FromString(yes))
        {
            if(!contains(interval)) return false;
        }
        return true;        
    }

    // Test if an interval is not present
    const bool containsNot(const std::string& no) const
    {
        for(const auto& interval : FromString(no))
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

    const std::vector<int> getSemi(int offset=0) const
    {
        std::vector<int> res;
        for(auto& interval : *this)
        {
            res.push_back(interval.getSemi()+offset);
        }
        return std::move(res);
    }

    // Get semitones, but ensure that the lowest is zero
    std::vector<int> getSemiNormalized()
    {
        auto semi = getSemi();
        const int min = *std::min_element(semi.begin(), semi.end());
        for(auto& s : semi) s -= min;
        return std::move(semi);
    }

    // Get the minimum Interval
    const Interval& getMin() const
    {
        return *std::min_element(IntervalVector::begin(), IntervalVector::end());
    }

    // Get the minimum semitone
    int getMinSemi() const
    {
        auto semi = getSemi();
        return *std::min_element(semi.begin(), semi.end());
    }

    // Get the maximum Interval
    const Interval& getMax() const
    {
        return *std::max_element(IntervalVector::begin(), IntervalVector::end());
    }

    // Get the maximum semitone
    int getMaxSemi() const
    {
        auto semi = getSemi();
        return *std::max_element(semi.begin(), semi.end());
    }

    // Get the median Interval
    const Interval& getMedian() const
    {
        auto intervals = *this;
        std::sort(intervals.begin(), intervals.end());
        return intervals[intervals.size()/2];
    }

    // Get the median semitone
    int getMedianSemi() const
    {
        auto semi = getSemi();
        std::sort(semi.begin(), semi.end());
        return semi[semi.size()/2];
    }

    // Get the mean semitone
    int getMeanSemi()
    {
        auto semi = getSemi();
        int sum = 0;
        for(auto s : semi) sum += s;
        return sum / semi.size();
    }

    // Create a new Intervals object from the semitones 
    static Intervals NewFromSemi(std::vector<int> semitones, bool normalize=false)
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
            addSemi(s);
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
    Intervals& printChordSymbol()
    {
        std::cout << "Chord Symbol: " << getChordSymbol() << std::endl;
        return *this;
    }

    // Function to get the Intervals normalized
    Intervals getNormalized()
    {
        Intervals res;
        for(auto s : getSemiNormalized())
        {
            res.add(Interval::NewFromSemi(s));
        }
        return std::move(res);
    }

    // Normalize the Intervals
    Intervals& normalize()
    {
        setFromSemi(getSemiNormalized());
        return *this;
    }

    // Simplify
    Intervals& simplify()
    {
        for(auto& interval : *this)
        {
            interval.simplify();
        }

        removeDuplicates();

        return *this;
    }

    // Remove Duplicate Intervals
    Intervals& removeDuplicates()
    {
        std::sort(IntervalVector::begin(), IntervalVector::end());
        IntervalVector::erase(std::unique(IntervalVector::begin(), IntervalVector::end()), IntervalVector::end());
        return *this;
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
    Intervals& harmonicNeg()
    {
        for(auto& interval : *this) interval.harmonicNeg();
        return *this;
    }

    // Transpose this
    Intervals& transpose(int semitones)
    {
        for(auto& interval : *this)
        {
            interval.transpose(semitones);
        }
        return *this;
    }

    // Return a new transposed Intervals object
    Intervals getTransposed(int n)
    {
        auto res = *this;
        res.transpose(n);
        return std::move(res);
    }

    // Get Interval from Degree
    Interval getIntervalFromDegree(int degree)
    {
        for(auto& interval : *this)
        {
            if(interval.getDegree() == degree) return interval;
        }
        // Print error message
        std::cerr << "Error: getIntervalFromDegree(): Degree not found" << std::endl;

        // Return an empty interval
        return Interval(degree);
    }

    // Get a specific inversion
    Intervals getInversion(int n, bool normalize=false) const
    {
        auto intervals = *this;
        if(n > 0){ 
            for(int i=0; i<n; i++){
                intervals.rotate(1);
                intervals.back().shiftOctave(1);
                intervals.sort();
            }
        }
        else if(n < 0){
            for(int i=0; i<-n; i++){
                intervals.rotate(-1);
                intervals.front().shiftOctave(-1);
                intervals.sort();
            }
        }
        if(normalize) intervals.normalize();
        return std::move(intervals);
    }

    // Create a vector with all inversions
    std::vector<Intervals> getAllInversions(bool simplify=true, bool normalize=false) const
    {
        auto intervals = *this;
        if(simplify) intervals.simplify();
        std::vector<Intervals> inversions;
        for(int i=0; i<intervals.size(); i++) {
            intervals.sort();
            inversions.push_back(intervals);
            if(normalize) inversions.back().normalize();
            intervals.front().shiftOctave(1);
            intervals.rotate(1);
            // If the first interval is above 12 then subtract 12 from all intervals
            if(intervals.front().getSemi() >= 12) intervals.shiftOctave(-1);
        }

        // Remove duplicates
        inversions.erase(std::unique(inversions.begin(), inversions.end()), inversions.end());

        return std::move(inversions);
    }

    // Print all inversions
    void printAllInversions(bool simplify=true, bool normalize=false) const
    {
        auto inversions = getAllInversions(simplify,normalize);
        for(auto& inversion : inversions)
        {
            inversion.printSemi();
        }
    }

    // Shift the intervals a number of octaves
    Intervals& shiftOctave(int n)
    {  
        auto it = IntervalVector::begin();
        while(it != IntervalVector::end())
        {
            it->shiftOctave(n);
            it++;
        }

        return *this;
    }

    // Print the intervals as whole and half steps. 
    // This is often used as scale signature. The method getSemiSteps is probably more interesting
    const std::string getWH() const
    {   
        auto intervals = this->getSemi();
        intervals.push_back(intervals[0] + 12);

        // Get a vector with the diff between the intervals
        std::string result = "";
        for (int i = 1; i < intervals.size(); i++)
        {
            auto diff = intervals[i] - intervals[i-1];
            if(diff % 2 == 0) // If the diff is even
            {
                int x = diff / 2;
                result += x == 1 ? "W-" : std::to_string(x) + "W-";
            }
            else
            {
                int x = diff;
                result += x==1 ? "H-" : std::to_string(x) + "H-";
            }
        }
        // If the last char is a '-' remove it
        if(result.back() == '-') result.pop_back();
        
        return std::move(result);
    }

    // Get the scale as semitone steps
    std::vector<int> getSemiSteps()
    {   
        auto intervals = this->getSemi();
        intervals.push_back(intervals[0] + 12);

        // Get a vector with the diff between the intervals
        std::vector<int> result = {};
        for (int i = 1; i < intervals.size(); i++)
        {
            auto diff = intervals[i] - intervals[i-1];
            result.push_back(diff);
        }
        
        return std::move(result);
    }

    // Print the intervals as semitone steps
    Intervals& printSemiSteps()
    {
        for(auto& step : getSemiSteps())
        {
            std::cout << step << " ";
        }
        std::cout << std::endl;
        return *this;
    }

    // Set the Intervals from a Whole-Half step string
    Intervals& setWH(const std::string& str)
    {
        this->clear();
        this->add(1);
        // For each W or H in the string, add the corresponding interval
        int n=1;
        for(auto& c : str)
        {   
            if(isdigit(c)) n = c - '0';
            if(c == 'W'){ addW(n); n=1; }
            if(c == 'H'){ addH(n); n=1; }
        }
        return *this;
    }

    // Print the Intervals as whole and half steps
    Intervals& printWH()
    {
        std::cout << getWH() << std::endl;
        return *this;
    }

    // Add a Whole Step
    Intervals& addW(int n=1)
    {
        addStep(n*2);
        return *this;
    }

    // Add a Whole Step
    Intervals& addH(int n=1)
    {
        addStep(n);
        return *this;
    }

    // Add a Whole Step
    Intervals& addStep(int n)
    {
        std::sort(IntervalVector::begin(), IntervalVector::end());
        auto interval = IntervalVector::back();
        interval.transpose(n);
        add(std::move(interval));
        return *this;
    }

    // Add a step from another interval 
    Intervals& addStep(const Interval& interval)
    {
        addStep(interval.getSemi());

        return *this;
    }

    // Add step from sting
    Intervals& addStep(const std::string& str)
    {
        return *this;
    }

    // If the Intervals represent a scale, then rotate to get the next mode
    Intervals getMode(int n, bool keepDegree=false)
    {
        n -= 1;
        auto semi = getSemiSteps();
        std::rotate(semi.begin(), semi.begin() + n, semi.end());
        auto size = this->size();

        Intervals result;
        int i = 0;
        result.add(at(i++).getDegree());
        for(auto& s : semi)
        {
            if(i == size) break;
            result.addStep(s);
            if(size == 7 || keepDegree) result.back().setDegreeKeepSemi(at(i).getDegree());
            i++;
        }

        return std::move(result);
    }





private:


};








} // namespace cmtk
