#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>
#include "Interval.h"
#include "Chords.h"

namespace cmtk {


// ----------------------------------------------------------------------- //
// ----------------------- ChordProgression Class ------------------------ //
// ----------------------------------------------------------------------- //
using ChordVector = std::vector<Chord>;
class ChordProgression : public ChordVector {
public:
    ChordProgression() = default;
    // Constructor to create a chord progression from a vector of chords
    ChordProgression(const ChordVector& chords)
    {
        this->set(chords);
    }
    // Constructor to create a chord progression from a vector of chord symbols
    ChordProgression(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        this->set(chordSymbols, rootNote);
    }
    // Constructor to create a chord progression from a string of chord symbols
    ChordProgression(const std::string& chordSymbols, const int rootNote = 0)
    {
        this->set(chordSymbols, rootNote);
    }

    // Function to set the chord progression from a vector of chords
    void set(const ChordVector& chords)
    {
        *this = chords; // TODO: Access in a different way
    }

    // Function to set the chord progression from a vector of chord symbols
    void set(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        this->clear();
        for (int i = 0; i < chordSymbols.size(); i++) {
            this->push_back(Chord(chordSymbols[i], rootNote));
        }
    }

    // Function to set the chord progression from string of chord symbols
    void set(std::string chordSymbols, const int rootNote = 0)
    {
        // Remove all spaces from the chord symbols
        chordSymbols.erase(std::remove(chordSymbols.begin(), chordSymbols.end(), ' '), chordSymbols.end());

        std::vector<std::string> chordSymbolsVector;
        std::string chordSymbol;
        for (int i = 0; i < chordSymbols.size(); i++) {
            auto c = chordSymbols[i];
            if (c == '|' || c == ','){
                if(chordSymbol.size() > 0){
                    chordSymbolsVector.push_back(chordSymbol);
                    chordSymbol = "";
                }
            } 
            else {
                chordSymbol += chordSymbols[i];
            }
        }
        // If a chordSymbol is still present push it to the vector
        if(chordSymbol.size() > 0) chordSymbolsVector.push_back(chordSymbol);

        // Use the vector-based set function
        set(chordSymbolsVector, rootNote);
    }

    // Function to add a chord to the progression
    void addChord(const Chord& chord)
    {
        ChordVector::push_back(chord);
    }

    // Function to add a chord to the progression
    void addChord(const std::string& chordSymbol, int rootNote = 0)
    {
        ChordVector::push_back(Chord(chordSymbol, rootNote));
    }

    // Function to clear the progression
    void clear()
    {
        ChordVector::clear();
    }

    // Print the chord progression
    void print()
    {
        for(auto& chord : *this) chord.print(); // TODO: Use iterator
    }

private:


};

// ----------------------------------------------------------------------- //
// ----------------------- ChordSequencer Class -------------------------- //
// ----------------------------------------------------------------------- //
class ChordSequencer {
public:
    // Constructor
    ChordSequencer() = default;

    // Function to set the chord progression
    void set(const ChordProgression& aChordProgression)
    {
        chordProgression = aChordProgression;
        rewind();
    }

    std::vector<int> next(int min=0, int max=127, int mindist=0)
    {
        // If the chord progression is empty then return an empty vector
        if(chordProgression.empty()) return {};
        // Loop through the chord progression
        if(++index >= chordProgression.size()) index = 0;
        // Return the chord tones
        current = chordProgression[index].getGroupRange(min,max,mindist);
        return current;
    }

    int getBassNote(int min=0, int max=127)
    {
        return chordProgression[index].getBassNote(min,max);
    }

    // Function to reset the sequencer
    void rewind()
    {
        index = -1;
    }

private:
    ChordProgression chordProgression;
    int index = -1;
    std::vector<int> current = {};
};


// ----------------------------------------------------------------------- //
// ----------------------- ChordProgressions Class ----------------------- //
// ----------------------------------------------------------------------- //
class ChordProgressions {
public:
    // Constructor
    ChordProgressions()
    {
        // Create the chord progressions
        // createChordProgressions();
    };

    // Function to create the chord progressions
    void createChordProgressions()
    {
        // Major Chord Progressions
        chordProgressions["2-5-1"]               = ChordProgression("ii7|V7|I7");   
        chordProgressions["Axis"]                = ChordProgression("I|V|vi|iv");    // Added to Scale
        chordProgressions["Axis2"]               = ChordProgression("vi|IV|I|V");    // Added to Scale
        chordProgressions["Andalusian"]          = ChordProgression("i|bVII|bVI|V");
        chordProgressions["AeolianVamp"]         = ChordProgression("i|bVII|bVI|bVII"); // Added to Scale
        chordProgressions["DooWop"]              = ChordProgression("I|vi|IV|V");    // Added to Scale
        chordProgressions["MixolydianVamp"]      = ChordProgression("I|bVII|IV|I");  // Added to Scale
        chordProgressions["PlagelCascade"]       = ChordProgression("i|bIII|bVII|IV"); // Added to Dorian
        chordProgressions["RedHot1"]             = ChordProgression("i|bVII|v|bVI");   // Added to Aeolian
        chordProgressions["RedHot2"]             = ChordProgression("I|V|ii|IV");      // Added to Major
        chordProgressions["RedHot3"]             = ChordProgression("IV|I|V|vi");      // Added to Major
        chordProgressions["RedHot4"]             = ChordProgression("I|V|vi|IV");      // Added to Major
        chordProgressions["RoyalRoad"]           = ChordProgression("I|IV|iii|vi");    // Added to Major & Ionian #2
        chordProgressions["KissFromARose"]       = ChordProgression("bVI|bVII|I");     
        chordProgressions["SuperMarioCadence"]   = ChordProgression("I|bVI|bVII|I");   
        chordProgressions["AugmentedClimb"]      = ChordProgression("I|I+|I6no5|I7no5|IV");
        chordProgressions["LastNightOnEarth"]    = ChordProgression("I|I+|I6no5|I7no5|IV|iv|I|I");
        chordProgressions["Ghibli"]              = ChordProgression("IV|V7|iii|vi");  // Added to Major
        // Sad Chord Progressions from https://www.pianote.com/blog/sad-chord-progressions/
        chordProgressions["PopProgression"]      = ChordProgression("vi|IV|I|V");
        chordProgressions["HarmonicMinorAxis"]   = ChordProgression("vi|IV|I|bIII");  // Check this progression - Not Harmonic minor
        chordProgressions["Creep"]               = ChordProgression("I|III|IV|iv");
        chordProgressions["HarmonicVamp"]        = ChordProgression("i|i|bVI|V");
        chordProgressions["HouseOfTheRisingSun"] = ChordProgression("i|III|IV|VI");
        chordProgressions["Harmonic Shift"]      = ChordProgression("i|iv|III|V");
        chordProgressions["AeolianClosedLoop"]   = ChordProgression("i|bVII|iv|i");   // Added to Aeolian
        chordProgressions["LanaProgression"]     = ChordProgression("i|III|v|VI");
        chordProgressions["Emotional"]           = ChordProgression("vi|IV|V|iii");   // Added to Major
        chordProgressions["MoonlightSonata"]     = ChordProgression("i|VI|ii|V");     
        chordProgressions["Sting"]               = ChordProgression("i|VII|iv|V");
        chordProgressions["MinorMysteryClimb"]   = ChordProgression("IV|V|vi");
        // The 5 Sad Piano Chord Progressions https://pianowithjonny.com/piano-lessons/5-sad-piano-chord-progressions/
        chordProgressions["Evanescence"]         = ChordProgression("I|iii|I|iii");
        chordProgressions["PrincessLeia"]        = ChordProgression("I|iv6");
        chordProgressions["Sentimental"]         = ChordProgression("i|V|i|vi7b5"); // Normally arranged with decending bass line i | V/7 | i/b7 | vi7b5
        chordProgressions["LoveProgression"]     = ChordProgression("I|V|vi|iii|IV|I|ii7|V"); // I | V/7 | vi | iii/5 | IV | I/3 | ii7 | V
        // The 12 bar blues progression
        chordProgressions["Blues"]               = ChordProgression("I7|IV7|I7|I7|IV7|IV7|I7|I7|V7|IV7|I7|V7");
        // Jazz Progressions
        chordProgressions["RhythmChanges"]       = ChordProgression("I|vi|ii|V");
        // Cadence
        chordProgressions["PlagalCadence"]       = ChordProgression("IV|I");
        chordProgressions["PerfectCadence"]      = ChordProgression("V7|I");

        // Tom Waits
        chordProgressions["JockeyFullOfBourbon"]  = ChordProgression("i|V");
        chordProgressions["Jockey"] = ChordProgression("i|iv|i|V");
        // Clap Hands
        chordProgressions["??"] = ChordProgression("i|V|iv|V");
        chordProgressions["ClapHands"] = ChordProgression("i|bVI7"); // 
        chordProgressions["ChocolateJesus"] = ChordProgression("i|iv|i|V7"); // Harmonic Minor


    }

    // Function to add a chord progression to the map
    void add(const std::string& name, const std::string& progression)
    {
        chordProgressions[name] = ChordProgression(progression);
    }

    // Function to add a chord progression to the map
    void add(const std::string& name, const ChordProgression& progression)
    {
        chordProgressions[name] = progression;
    }

    // Overload index operator to get the chord progression
    ChordProgression& operator[](const std::string& chordProgression)
    {
        return chordProgressions[chordProgression];
    }

    // Print all the chord progressions
    void print()
    {
        for (auto& chordProgression : chordProgressions) {
            std::cout << chordProgression.first << ":\n";
            chordProgression.second.print();
        }
    }

    void clear()
    {
        chordProgressions.clear();
    }

private:
    std::map<std::string, ChordProgression> chordProgressions; // TODO: Make this into a static private member
};












} // namespace cmtk
