#pragma once
#include "CMTK.h"

namespace cmtk {

// ----------------------------------------------------------------------- //
// ----------------------------- Interval Class -------------------------- //
// ----------------------------------------------------------------------- //
class Interval : public CMTK {
public:
    // Constructor
    Interval() = default;

    Interval(std::string interval);
    Interval(int degree, int quality=0);

    static Interval NewFromSemi(int semitones, bool sharp=false);

    Interval& clear();

    // Function to set the interval from a string
    Interval& set(std::string aName);

    // Function to set the interval from a degree and a quality
    Interval& set(int aDegree, int aQuality=0);

    // Set from a vector of semitones
    Interval& setFromSemi(int s, bool sharp=false);

    // Function to return inverted interval
    Interval getInverted();

    // Function to get the interval as a string
    std::string toString() const;

    // Function to get the interval as a string
    const std::string getName() const;

    // Function to get the number of semitones
    const int getSemi() const;

    // Print the interval
    Interval& print();

    // Print name
    Interval& printName();

    // Sharpen the interval
    Interval& sharpen();

    // Flatten the interval
    Interval& flatten();

    // Set quality
    Interval& setQuality(int aQuality);

    // Set quality from string
    Interval& setQuality(std::string aQuality);

    // Set Quality from char
    Interval& setQuality(char aQuality);

    // Get Quality
    const int getQuality() const;

    // Get Degree
    const int getDegree() const;

    // Set Degree
    Interval& setDegree(int aDegree, bool keepSemi=false);

    // Set Degree without changing the semitones
    Interval& setDegreeKeepSemi(int aDegree);

    // Set Degree and Semi - Quality will be adjusted
    Interval& setDegreeSemi(int aDegree, int aSemi);

    // Equality operator
    bool operator==(const Interval& other) const;

    // Equality operator for string
    const bool operator==(const std::string& intervalString) const;

    // Inequality operator
    bool operator!=(const Interval& other) const;

    // Add a function to be used in std::sort
    bool operator<(const Interval& other) const;

    // operator+ for Interval
    Interval operator+(const Interval& other) const;

    // operator+ for Semitones
    Interval operator+(int n) const;

    // operator+= for Interval
    Interval& operator+=(const Interval& other);

    // operator+= for Semitones
    Interval& operator+=(int n);

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Interval& i);
    
    // Function to shift the interval up a number of octaves by manipulating the degree and the quality
    Interval& shiftOctave(int n);

    // Interval to Note Name
    std::string getNoteName(int rootNote, bool isRoman = false) const;

    // Function to return the negative harmonic to the interval
    Interval getNegativeHarmonic() const;

    // Function to convert the interval to the negative harmonic by mirroring on the Major <--> Minor axis
    Interval& harmonicNeg();

    // Transpose
    Interval& transpose(int n);

    // ----------------------------- Support for Roman Numerals ----------------------------- //
    // Create a new Interval from a Roman Numeral
    static Interval NewFromRoman(std::string roman);

    // Set the interval from a Roman Numeral
    Interval& setRoman(std::string aRoman);

    // Get Name as Roman Numeral
    std::string getRoman(bool upperCase) const;

    // Get Degree as Roman Numeral
    std::string getDegreeRoman(bool upperCase) const;

    Interval& simplify();

private:
    // Function to set the interval
    int mSemitones = 0; // The number of semitones required to reach the interval
    int mDegree = 0;    // The degree is relative to the major scale
    int mQuality = 0;   // -1 for flat, 0 for natural, 1 for sharp, etc.

    // Function to get the number of semitones from the degree and quality
    void updateSemitones(int aDegree, int aQuality);

    // Function to get the number of semitones for a degree disregarding the quality
    int getSemiFromMajorDegree(int aDegree);
 
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
    Intervals(IntervalVector intervals);
    Intervals(std::string intervals);

    // Function to set the intervals
    Intervals& set(const IntervalVector& intervals);

    // Set the intervals from a string
    Intervals& set(const std::string& intervals);

    // Overload the assignment operator
    Intervals& operator=(const IntervalVector& intervals);

    // Overload the assignment operator
    Intervals& operator=(const std::string& intervals);
    
    // Add Interval(s)
    Intervals& add(const Interval& interval);
    Intervals& add(const IntervalVector& interval);
    Intervals& add(const Intervals& interval);
    Intervals& add(int degree, int quality=0);
    Intervals& add(std::string str);

    // Add semitone
    Intervals& addSemi(int semi, bool sharp=false);
    Intervals& addSemi(std::vector<int> semi, bool sharp=false);

    // Remove semitone
    Intervals& removeSemi(int semi);
    Intervals& removeSemi(std::vector<int> semi);
    
    // Function to insert an interval into a specific index
    Intervals& insert(int index, const Interval& n);

    // Remove Interval, return true if removed
    bool remove(const Interval& n);

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Intervals& intervals);

    // toString
    std::string toString() const;

    // Rotate the intervals
    Intervals& rotate(int n);

    // Remove Interval by string, return true if changed
    bool remove(const std::string& str);

    // Remove Interval by Degree and Quality
    void remove(int degree, int quality);

    // Remove Interval by Degree related to the Major Scale
    void removeDegree(int aDegree);

    // Convert a string to a Intervals object
    static Intervals FromString(std::string str);

    // Set Quality of the Interval by Degree
    Intervals& setQuality(int aDegree, int aQuality, bool allowAdd = false);

    // Print the chord intervals
    Intervals& print();

    // Print the semitones
    Intervals& printSemi();

    // Sort function
    Intervals& sort();

    // Test if an interval is present
    bool contains(const Interval& n) const;

    // Test if an interval is present
    const bool contains(const std::string& yes) const;

    // Test if an interval is not present
    const bool containsNot(const std::string& no) const;

    // Test if an interval is present and another is not
    const bool contains(const std::string& yes, const std::string& no) const;

    // Contains Degree
    const bool containsDegree(int degree) const;

    // Equality operator
    bool operator==(const Intervals& other) const;

    const std::vector<int> getSemi(int offset=0) const;

    // Get semitones, but ensure that the lowest is zero
    std::vector<int> getSemiNormalized();

    // Get the minimum Interval
    const Interval& getMin() const;

    // Get the minimum semitone
    int getMinSemi() const;

    // Get the maximum Interval
    const Interval& getMax() const;

    // Get the maximum semitone
    int getMaxSemi() const;

    // Get the median Interval
    const Interval& getMedian() const;

    // Get the median semitone
    int getMedianSemi() const;

    // Get the mean semitone
    int getMeanSemi();

    // Create a new Intervals object from the semitones 
    static Intervals NewFromSemi(std::vector<int> semitones, bool normalize=false);

    // Set from a vector of semitones - The lowest semitone will be treated as the root
    void setFromSemi(std::vector<int> semitones, bool normalize=false);

    std::string getChordSymbol();

    // Print the ChordSymbol
    Intervals& printChordSymbol();

    // Function to get the Intervals normalized
    Intervals getNormalized();

    // Normalize the Intervals
    Intervals& normalize();

    // Simplify
    Intervals& simplify();

    // Remove Duplicate Intervals
    Intervals& removeDuplicates();
    
    // Get negative harmonic 
    Intervals getNegativeHarmonic();

    // Convert to Negative Harmonic by mirroring on the Major <--> Minor axis
    Intervals& harmonicNeg();

    // Transpose this
    Intervals& transpose(int semitones);

    // Return a new transposed Intervals object
    Intervals getTransposed(int n);

    // Get Interval from Degree
    Interval getIntervalFromDegree(int degree);
    
    // Get a specific inversion
    Intervals getInversion(int n, bool normalize=false) const;

    // Create a vector with all inversions
    std::vector<Intervals> getAllInversions(bool simplify=true, bool normalize=false) const;

    // Print all inversions
    void printAllInversions(bool simplify=true, bool normalize=false) const;

    // Shift the intervals a number of octaves
    Intervals& shiftOctave(int n);

    // Print the intervals as whole and half steps. 
    // This is often used as scale signature. The method getSemiSteps is probably more interesting
    const std::string getWH() const;

    // Get the scale as semitone steps
    std::vector<int> getSemiSteps();

    // Print the intervals as semitone steps
    Intervals& printSemiSteps();

    // Set the Intervals from a Whole-Half step string
    Intervals& setWH(const std::string& str);

    // Print the Intervals as whole and half steps
    Intervals& printWH();

    // Add a Whole Step
    Intervals& addW(int n=1);

    // Add a Half Step
    Intervals& addH(int n=1);

    // Add a Whole Step
    Intervals& addStep(int n);

    // Add a step from another interval 
    Intervals& addStep(const Interval& interval);

    // Add step from sting
    Intervals& addStep(const std::string& str);

    // If the Intervals represent a scale, then rotate to get the next mode
    Intervals getMode(int n, bool keepDegree=false);


private:


};








} // namespace cmtk
