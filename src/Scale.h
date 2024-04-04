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

namespace cmtk
{    
    // ----------------------------------------------------------------------- //
    // ----------------------------- Scale Class ----------------------------- //
    // ----------------------------------------------------------------------- //
    class Scale
    {
    public:
        // Constructor
        Scale()
        {
            setScale("Major");
        }

        Scale(std::string aName, int aRootNote = 0)
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
            // Ionian Mode - Major Scale 1st Mode {1 2 3 4 5 6 7}
            if (mName == "Ionian" || mName == "Major")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7)};
                mStyle = "Happy,Light,Bright,Positive,Pop,Rock,Jazz,Classical,Happy";
            }
            // Dorian Mode - Major Scale 2nd Mode {1 2 ♭3 4 5 6 ♭7} 
            else if (mName == "Dorian")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "Jazzy,Bluesy,Rocky,Sophisticated,Adventurous";
            }
            // Phrygian Mode - Major Scale 3rd Mode {1 ♭2 ♭3 4 5 ♭6 ♭7}
            else if (mName == "Phrygian")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "Exotic,Spanish,Eastern,Flamenco,Latin,Lively";
            }
            // Lydian Mode - Major Scale 4th Mode {1 2 3 ♯4 5 6 7}
            else if (mName == "Lydian")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5), Interval(6), Interval(7)};
                mStyle = "Dreamy,Spacey,Modern,Jazz,Hopeful,Positive,Magical";
            }
            // Mixolydian Mode - Major Scale 5th Mode {1 2 3 4 5 6 ♭7}
            else if (mName == "Mixolydian")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "Blues,Rock,Jazz,Folk,Country,Pop";
            }
            // Aeolian Mode (Natural Minor) - Major Scale 6th Mode {1 2 ♭3 4 5 ♭6 ♭7}
            else if (mName == "Aeolian" || mName == "Minor")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "Sad,Dark,Blues,Jazz,Rock,Metal,Emotional,Sentimental,Serious";
            }
            // Locrian Mode - Major Scale 7th Mode {1 ♭2 ♭3 4 ♭5 ♭6 ♭7}
            else if (mName == "Locrian")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Dissonant,Unstable,Dark,Blues,Jazz,Complex,Exotic";
            }

            // ----------------------- Harmonic Major Modes ----------------------- //
            // Harmonic Major - Harmonic Major 1st Mode {1 2 3 4 5 ♭6 7}
            else if (mName == "Harmonic Major")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6, -1), Interval(7)};
                mStyle = "Majestic,Heroic,Powerful,Exotic,Eastern,Classical";
            }
            // Dorian b5 - Harmonic Major 2nd Mode {1 2 ♭3 4 ♭5 6 7}
            else if (mName == "Dorian b5")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6), Interval(7, -1)};
                mStyle = "Mysterious,Dark,Unstable"; 
            }
            // Phrygian b4 - Harmonic Major 3rd Mode {1 2 ♭3 ♭4 5 ♭6 ♭7}
            else if (mName == "Phrygian b4")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4, -1), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "Sentimental,Ambiguous,Exotic,Eastern,Spanish,Flamenco,Latin";
            }
            // Lydian b3 - Harmonic Major 4th Mode {1 2 ♭3 ♯4 5 6 7}
            else if (mName == "Lydian b3")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4, 1), Interval(5), Interval(6), Interval(7)};
                mStyle = "Mysterious,Exotic,Eastern,Spanish,Flamenco,Latin";
            }
            // Mixolydian b2 - Harmonic Major 5th Mode {1 ♭2 3 4 5 6 ♭7}
            else if (mName == "Mixolydian b2")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "Heroic,Majestic,Powerful,Exotic,Eastern,Classical";
            }
            // Lydian Augmented - Harmonic Major 6th Mode {1 ♯2 3 ♯4 ♯5 6 7}
            else if (mName == "Lydian Augmented #2")
            {
                mIntervals = {Interval(1), Interval(2, 1), Interval(3), Interval(4, 1), Interval(5, 1), Interval(6), Interval(7)};
                mStyle = "Majestic,Heroic,Powerful,Exotic,Eastern,Classical";
            }
            // Locrian Diminished - Harmonic Major 7th Mode
            else if (mName == "Locrian Diminished")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -2)};
                mStyle = "Classical,Emotional,Sentimental";
            }

            // ----------------------- Harmonic Minor Modes ----------------------- //
            // Harmonic Minor - Harmonic Minor 1st Mode {1 2 b3 4 5 b6 7}
            else if (mName == "Harmonic Minor")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7)};
                mStyle = "Sad,Epic,Tragic,Classical,Emotional,Dark,Exotic,Eastern,Spanish,Flamenco,Latin";
            }
            // Locrian n6 - Harmonic Minor 2nd Mode
            else if (mName == "Locrian n6")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6), Interval(7, -1)};
                mStyle = "Ancient";
            }
            // Ionian Augmented - Harmonic Minor 3rd Mode
            else if (mName == "Ionian Augmented" || mName == "Ionian #5")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5, 1), Interval(6), Interval(7)};
                mStyle = "Hopeful,Open,Majestic,Heroic";
            }
            // Dorian #4 - Harmonic Minor 4th Mode {1 2 ♭3 ♯4 5 6 ♭7}
            else if (mName == "Dorian #4" || mName == "Ukrainian Dorian")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4, 1), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "World,Gypsy,Eastern European,Mysterious";
            }
            // Phrygian Dominant - Harmonic Minor 5th Mode
            else if (mName == "Phrygian Dominant")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "World,Gypsy,Flamenco,Middle Eastern,Jewish";
            }
            // Lydian #2 - Harmonic Minor 6th Mode
            else if (mName == "Lydian #2")
            {
                mIntervals = {Interval(1), Interval(2, 1), Interval(3), Interval(4, 1), Interval(5), Interval(6), Interval(7)};
                mStyle = "Yearning,Emotional,Serious,Classical,Exotic";
            }
            // Super Locrian - Harmonic Minor 7th Mode
            else if (mName == "Super Locrian")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -2)};
                mStyle = "Latin,Complex,Dissonant,Dark";
            }

            // ----------------------- Melodic Minor Modes ----------------------- //
            // Melodic Minor - Melodic Minor 1st Mode
            else if (mName == "Melodic Minor")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5), Interval(6), Interval(7)};
                mStyle = "Emosional,Classical,Sad,Hopeful,Spy";
            }
            // Dorian b2 - Melodic Minor 2nd Mode
            else if (mName == "Dorian b2")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "Suspeseful,Uneasy,Film Noir";
            }
            // Lydian Augmented - Melodic Minor 3rd Mode
            else if (mName == "Lydian Augmented")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5, 1), Interval(6), Interval(7)};
                mStyle = "Positive,Magical,Mysterious,Jazzy,Ethnic";
            }
            // Lydian Dominant - Melodic Minor 4th Mode
            else if (mName == "Lydian Dominant" || mName == "Acoustic")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5), Interval(6), Interval(7, -1)};
                mStyle = "Positive,Folk,World,Jazzy";
            }
            // Mixolydian b6 - Melodic Minor 5th Mode
            else if (mName == "Mixolydian b6")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "Sad,Sentimental";
            }
            // Locrian #2 - Melodic Minor 6th Mode
            else if (mName == "Half Diminished" || mName == "Locrian #2")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Jazz,Rock,Sad,Complex";
            }
            // Altered - Melodic Minor 7th Mode
            else if (mName == "Altered" || mName == "Super Locrian")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Jazz,Sophisticated";
            }

            // ----------------------- Neopolitan Major ----------------------- //
            // Neopolitan Major - Neopolitan Major 1st Mode
            else if (mName == "Neopolitan Major")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6), Interval(7)};
                mStyle = "Complex,Latin,Melancholic,Sentimental";
            }
            // Lydian Augmented #6 - Neopolitan Major 2nd Mode
            else if (mName == "Lydian Augmented #6")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5, 1), Interval(6, 1), Interval(7)};
                mStyle = "Mysterious,Unstable";
            }
            // Lydian Augmented Dominant - Neopolitan Major 3rd Mode
            else if (mName == "Lydian Augmented Dominant")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5, 1), Interval(6), Interval(7, -1)};
                mStyle = "Unstable,Complex";
            }
            // Lydian b6 Dominant - Neopolitan Major 4th Mode
            else if (mName == "Lydian b6 Dominant")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "Mysterious,Unstable";
            }
            // Major Locrian - Neopolitan Major 5th Mode
            else if (mName == "Major Locrian")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Positive,World,Mysterious,Middle Eastern";
            }
            // Super Locrian n2 - Neopolitan Major 6th Mode
            else if (mName == "Super Locrian n2")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Complex,Unstable";
            }
            // Super Locrian bb3 - Neopolitan Major 7th Mode
            else if (mName == "Super Locrian bb3")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -2), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Heroic,Mysterious";
            }

            // ----------------------- Neopolitan Minor ----------------------- //
            // Neopolitan Minor - Neopolitan Minor 1st Mode
            else if (mName == "Neopolitan Minor")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7)};
                mStyle = "Complex,Latin,Melancholic,Sentimental";
            }
            // Lydian #6 - Neopolitan Minor 2nd Mode
            else if (mName == "Lydian #6")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5), Interval(6, 1), Interval(7)};
                mStyle = "Ethereal,Dreamy";
            }
            // Mixolydian Augmented - Neopolitan Minor 3rd Mode
            else if (mName == "Mixolydian Augmented")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5, 1), Interval(6), Interval(7, -1)};
                mStyle = "Serious,Ambiguous";
            }
            // Hungarian Gypsy - Neopolitan Minor 4th Mode
            else if (mName == "Hungarian Gypsy")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4, 1), Interval(5), Interval(6, -1), Interval(7, -1)};
                mStyle = "World,Flamenco,Gypsy,Eastern European,Middle Eastern";
            }
            // Locrian n3 - Neopolitan Minor 5th Mode
            else if (mName == "Locrian n3")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -1)};
                mStyle = "Complex,Jazz";
            }
            // Ionian #2 - Neopolitan Minor 6th Mode
            else if (mName == "Ionian #2")
            {
                mIntervals = {Interval(1), Interval(2, 1), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7)};
                mStyle = "Unstable,Complex";
            }
            // Super-Locrian Diminished - Neopolitan Minor 7th Mode
            else if (mName == "Super-Locrian Diminished")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -2), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -2)};
                mStyle = "Latin,Dark";
            }

            // ----------------------- Double Harmonic Modes ----------------------- //
            // Double Harmonic Major - Double Harmonic Major 1st Mode
            else if (mName == "Double Harmonic Major")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5), Interval(6, -1), Interval(7)};
            }
            // Lydian #2 #6 - Double Harmonic Major 2nd Mode
            else if (mName == "Lydian #2 #6")
            {
                mIntervals = {Interval(1), Interval(2, 1), Interval(3), Interval(4, 1), Interval(5), Interval(6, 1), Interval(7)};
            }
            // Ultra Phrygian - Double Harmonic Major 3rd Mode
            else if (mName == "Ultra Phrygian")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4, -1), Interval(5), Interval(6, -1), Interval(7, -2)};
            }
            // Hungarian Minor - Double Harmonic Major 4rd Mode
            else if (mName == "Hungarian Minor")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4, 1), Interval(5), Interval(6, -1), Interval(7)};
            }
            // Oriental - Double Harmonic Major 5th Mode
            else if (mName == "Oriental")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5, -1), Interval(6), Interval(7, -1)};
            }
            // Ionian Augmented #2 - Double Harmonic Major 6th Mode
            else if (mName == "Ionian Augmented #2")
            {
                mIntervals = {Interval(1), Interval(2, 1), Interval(3), Interval(4), Interval(5, 1), Interval(6), Interval(7)};
            }
            // Locrian Diminished bb3 - Double Harmonic Major 7th Mode
            else if (mName == "Locrian Diminished bb3")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -2), Interval(4), Interval(5, -1), Interval(6, -1), Interval(7, -2)};
            }

            // ----------------------- Pentatonic Modes -------------- //
            // Major Pentatonic - Pentatonic 1st Mode
            else if (mName == "Major Pentatonic")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(5), Interval(6)};
            }
            // Egyptian Pentatonic - Pentatonic 2nd Mode
            else if (mName == "Egyptian Pentatonic")
            {
                mIntervals = {Interval(1), Interval(2), Interval(4), Interval(5), Interval(7, -1)};
            }
            // Man Gong Pentatonic - Pentatonic 3rd Mode
            else if (mName == "Man Gong Pentatonic")
            {
                mIntervals = {Interval(1), Interval(3, -1), Interval(4), Interval(6, -1), Interval(7, -1)};
            }
            // Ritsusen Pentatonic - Pentatonic 4rd Mode
            else if (mName == "Ritsusen Pentatonic")
            {
                mIntervals = {Interval(1), Interval(2), Interval(4), Interval(5), Interval(6)};
            }
            // Minor Pentatonic - Pentatonic 5th Mode
            else if (mName == "Minor Pentatonic")
            {
                mIntervals = {Interval(1), Interval(3, -1), Interval(4), Interval(5), Interval(7, -1)};
            }

            // ----------------------- Blues Scale Modes ------------------ //
            // Major Blues - Blues 1st Mode
            else if (mName == "Major Blues" || mName == "Gospel" || mName == "Blues 1st Mode")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(3), Interval(5), Interval(6)};
            }
            // Blues 2nd Mode
            else if (mName == "Blues 2nd Mode")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(2), Interval(4), Interval(5), Interval(7, -1)};
            }
            // Blues 3rd Mode
            else if (mName == "Blues 3rd Mode")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(5, -1), Interval(6), Interval(7)};
            }
            // Blues 4th Mode
            else if (mName == "Blues 4th Mode")
            {
                mIntervals = {Interval(1), Interval(3, -1), Interval(4), Interval(5, 1), Interval(6, 1), Interval(7)};
            }
            // Blues 5th Mode
            else if (mName == "Blues 5th Mode")
            {
                mIntervals = {Interval(1), Interval(2), Interval(4), Interval(5), Interval(6, -1), Interval(6)};
            }
            // Minor Blues - Blues 6th Mode
            else if (mName == "Minor Blues" || mName == "Blues 6th Mode")
            {
                mIntervals = {Interval(1), Interval(3, -1), Interval(4), Interval(5, -1), Interval(5), Interval(7, -1)};
            }

            // ----------------------- Other Scales ----------------------- //

            // Octatonic
            else if (mName == "Octatonic")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1), Interval(7)};
            }
            // Augmented Scale
            else if (mName == "Augmented")
            {
                mIntervals = {Interval(1), Interval(3, -1), Interval(3), Interval(5), Interval(5, 1), Interval(7)};
            }
            // Bebop Dominant
            else if (mName == "Bebop Dominant")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7, -1), Interval(7)};
            }
            // Octatonic Half-Whole
            else if (mName == "Octatonic Whole-Half")
            {
                mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5, -1), Interval(6, -1), Interval(6), Interval(7)};
            }
            else if (mName == "Octatonic Half-Whole")
            {
                mIntervals = {Interval(1), Interval(2 - 1), Interval(3, -1), Interval(3), Interval(4, 1), Interval(5), Interval(6), Interval(7, -1)};
            }
            // Tritone
            else if (mName == "Tritone")
            {
                mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(5, -1), Interval(5), Interval(7, -1)};
            }

            else
            {
                std::cerr << "Error: Unrecognized scale name" << std::endl;
            }
        }

        // Overload the [] operator to get the semi-tone of the scale
        Interval operator[](int index)
        {
            return intervalAt(index);
        }

        // Function to get the scale name
        int semiToneAt(int index)
        {
            int res = mRootNote;
            while (index < 0)
            {
                index += mIntervals.size();
                res -= 12;
            }
            while (index >= mIntervals.size())
            {
                index -= mIntervals.size();
                res += 12;
            }

            res += mIntervals[index].getSemitones();
            return res;
        }

        Interval intervalAt(int index)
        {
            int octave = 0;
            while (index < 0)
            {
                index += mIntervals.size();
                octave--;
            }
            while (index >= mIntervals.size())
            {
                index -= mIntervals.size();
                octave++;
            }

            auto interval = mIntervals[index];
            interval.shiftOctave(octave);

            return std::move(interval);
        }

        Intervals intervalAt(const std::vector<int> &indexes)
        {
            Intervals intervals;
            for (auto index : indexes)
            {
                intervals.push_back(intervalAt(index));
            }

            return std::move(intervals);
        }

        std::string getChordSymbol(int index, int size = 3)
        {
            // Check that size is valid
            if (size < 3 || size > 7)
            {
                throw std::invalid_argument("Scale::getChordSymbol(): Invalid size: " + std::to_string(size) + std::string(" - Size must be between 3 and 7"));
            }

            // std::cout << "--- Chord @ Index: --- " << index << std::endl;

            // Create a vector of indexes for the chord
            Intervals chordIntervals;
            for (int i = 0; i < size; i++)
            {
                auto interval = intervalAt(index + 2 * i);
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
            if (inVec(semitones, {4, 7}))
            {
            }
            else if (inVec(semitones, {4, 6}))
            {
                toAppend = "b5";
            }
            else if (inVec(semitones, {3, 7}))
            {
                uppercase = false;
            }
            else if (inVec(semitones, {3, 6}))
            {
                chordSymbol = "°";
                uppercase = false;
            }
            else if (inVec(semitones, {4, 8}))
            {
                chordSymbol = "+";
            }
            else if (inVec(semitones, {2, 7}))
            {
                toAppend = "sus2";
            }
            else if (inVec(semitones, {2, 6}))
            {
                toAppend = "sus2b5";
                uppercase = false;
            }
            else if (inVec(semitones, {5, 7}))
            {
                toAppend = "sus4";
            }
            else
            {
                // String with the semitones:
                std::string semitonesString = "";
                for (auto semitone : semitones)
                    semitonesString += std::to_string(semitone) + " ";

                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(" + std::to_string(index) + "," + std::to_string(size) + "): Unknown chord with Semitones: " + semitonesString);
            }

            // 7th
            if (size > 3)
            {
                if (inVec(semitones, Intervals("b7").getSemitones()))
                {
                    if (chordSymbol == "°")
                        chordSymbol = "ø7";
                    else
                        chordSymbol.append("7");
                }
                else if (inVec(semitones, Intervals("7").getSemitones()))
                {
                    chordSymbol.append("Maj7");
                }
                else if (inVec(semitones, Intervals("6").getSemitones()))
                {
                    chordSymbol.append(chordSymbol == "°" ? "7" : "6");
                }
                else
                {
                    // String with the semitones:
                    std::string semitonesString = "";
                    for (auto semitone : semitones)
                        semitonesString += std::to_string(semitone) + " ";
                    // Throw exception for unknown chord
                    throw std::runtime_error("Scale::getChordSymbol(): Unknown extension with Semitones: " + semitonesString);
                }
            }

            // 9th Chords
            if (size > 4)
            {
                if (inVec(semitones, Intervals("9").getSemitones()))
                {
                    chordSymbol.back() = '9';
                }
                else if (inVec(semitones, Intervals("b9").getSemitones()))
                {
                    toAppend += "b9";
                }
                else if (inVec(semitones, Intervals("#9").getSemitones()))
                {
                    toAppend += "#9";
                }
                else
                {
                    // String with the semitones:
                    std::string semitonesString = "";
                    for (auto semitone : semitones)
                        semitonesString += std::to_string(semitone) + " ";
                    // Throw exception for unknown chord
                    throw std::runtime_error("Scale::getChordSymbol(): Unknown 9th chord with Semitones: " + semitonesString);
                }
            }

            // 11th Chords
            if (size > 5)
            {
                if (inVec(semitones, Intervals("11").getSemitones()))
                {
                    chordSymbol.back() = '1';
                    chordSymbol.push_back('1');
                }
                else if (inVec(semitones, Intervals("b11").getSemitones()))
                {
                    toAppend += "b11";
                }
                else if (inVec(semitones, Intervals("#11").getSemitones()))
                {
                    toAppend += "#11";
                }
                else
                {
                    // String with the semitones:
                    std::string semitonesString = "";
                    for (auto semitone : semitones)
                        semitonesString += std::to_string(semitone) + " ";
                    // Throw exception for unknown chord
                    throw std::runtime_error("Scale::getChordSymbol(): Unknown 11th chord with Semitones: " + semitonesString);
                }
            }

            // 13th Chords
            if (size > 6)
            {
                if (inVec(semitones, Intervals("13").getSemitones()))
                {
                    replaceBack(chordSymbol, "13", endsWith(chordSymbol, "11") ? 2 : 1);
                }
                else if (inVec(semitones, Intervals("b13").getSemitones()))
                {
                    toAppend += "b13";
                }
                else if (inVec(semitones, Intervals("#13").getSemitones()))
                {
                    toAppend += "#13";
                }
                else
                {
                    // String with the semitones:
                    std::string semitonesString = "";
                    for (auto semitone : semitones)
                        semitonesString += std::to_string(semitone) + " ";
                    // Throw exception for unknown chord
                    throw std::runtime_error("Scale::getChordSymbol(): Unknown 13th chord with Semitones: " + semitonesString);
                }
            }

            // Insert the roman numeral at beginning of the chord symbol
            chordSymbol.insert(0, chordIntervals.front().getRomanName(uppercase));

            // Append
            if (!toAppend.empty())
            {
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
        Chord getChord(int index, int size = 3)
        {
            const auto& chordSymbol = getChordSymbol(index, size);
            auto chord = Chord(chordSymbol);
            return std::move(chord);
        }

        std::vector<std::string> getChordSymbols(int size = 3)
        {
            std::vector<std::string> chordSymbols;
            for (int i = 0; i < mIntervals.size(); i++)
            {
                chordSymbols.push_back(getChordSymbol(i, size));
            }

            return std::move(chordSymbols);
        }

        // Print the chord symbols
        void printChordSymbols(int size = 3)
        {
            auto chordSymbols = getChordSymbols(size);
            for (auto chordSymbol : chordSymbols)
            {
                std::cout << chordSymbol << " ";
            }
            std::cout << std::endl;
        }

        // Function to calculate the brightness of the scale
        int getBrightness()
        {
            int brightness = 0;
            for (auto interval : mIntervals)
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
        friend std::ostream &operator<<(std::ostream &os, const Scale &scale)
        {
            os << scale.mName << "(" << scale.mIntervals << ")";

            return os;
        }

        // Print the scale
        void print(int size = 3)
        {
            std::cout << "Scale: " << mName << " : " << getWholeHalfPattern();
            if (!mStyle.empty())
                std::cout << " - " << mStyle;
            std::cout << std::endl;

            int i = 0;
            std::cout << "Int\tSemi\tChord\n";
            for (auto interval : mIntervals)
            {
                std::cout << interval.getString() << "\t" << interval.getSemitones() << "\t" << getChordSymbol(i++, size) << "\n";
            }
            std::cout << std::endl;
        }

        // Print the scale as whole and half steps
        std::string getWholeHalfPattern()
        {   
            auto intervals = mIntervals.getSemitones();
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

        // Function to test if a chord is diatonic to the scale
        bool isChordDiatonic(const Chord &chord)
        {
            std::vector<int> chordNotes;
            for (auto interval : chord.getIntervals())
            {
                auto semitones = interval.getSemitones() % 12;
                // Check if the interval is in the scale
                if (std::find_if(mIntervals.begin(), mIntervals.end(), [semitones, this](Interval i)
                                 { return i.getSemitones() == semitones; }) == mIntervals.end())
                {
                    return false;
                }
            }

            return true;
        }

        // Function to calculate the diatonicity of a chord to the scale
        float diatonicity(const Chord &chord)
        {
            int diatonicNotes = 0;
            for (auto interval : chord.getIntervals())
            {
                auto semitones = interval.getSemitones() % 12;
                // Check if the interval is in the scale
                if (std::find_if(mIntervals.begin(), mIntervals.end(), [semitones, this](Interval i)
                                 { return i.getSemitones() == semitones; }) != mIntervals.end())
                {
                    diatonicNotes++;
                }
            }

            return static_cast<float>(diatonicNotes) / chord.size();
        }

        static std::vector<Scale> getAllScales()
        {
            std::vector<Scale> scales;
            for (auto scaleName : {
                // TODO: Add more scales - https://en.wikipedia.org/wiki/List_of_musical_scales_and_modes
                // Major Modes:
                "Major", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian",
                // Harmonic Major Modes:
                "Harmonic Major", "Dorian b5", "Phrygian b4", "Lydian b3", "Mixolydian b2", "Lydian Augmented", "Locrian Diminished",
                // Harmonic Minor Modes:
                "Harmonic Minor", "Locrian n6", "Ionian #5", "Dorian #4", "Phrygian Dominant", "Lydian #2", "Super Locrian",
                // Melodic Minor Modes:
                "Melodic Minor", "Dorian b2", "Lydian Augmented", "Lydian Dominant", "Mixolydian b6", "Locrian #2", "Altered",
                // Neopolitan Major Modes:
                "Neopolitan Major", "Lydian Augmented #6", "Lydian Augmented Dominant", "Lydian b6 Dominant", "Major Locrian", "Super Locrian n2", "Super Locrian bb3",
                // Neopolitan Major Modes:
                "Neopolitan Minor", "Lydian #6", "Mixolydian Augmented", "Hungarian Gypsy", "Locrian n3", "Ionian #2", "Super-Locrian Diminished",
                // Double Harmonic Major Modes:
                "Double Harmonic Major", "Lydian #2 #6", "Ultra Phrygian", "Hungarian Minor", "Oriental", "Ionian Augmented #2", "Locrian Diminished bb3"
                // Other Scales - TODO: Fix this class so that scales with other number of notes than 7 is supported!
                // "Major Pentatonic"     , "Minor Pentatonic", "Blues", "Octatonic", "Augmented", "Bebop Dominant", "Octatonic Whole-Half", "Octatonic Half-Whole", "Tritone"
            }){
                scales.push_back(Scale(scaleName));
            }

            return std::move(scales);
        }

        static void printAllScales(int size = 3)
        {
            for (auto scale : getAllScales())
            {
                scale.print(size);
            }
        }

        static std::vector<Scale> getScalesByBrightness()
        {
            auto scales = getAllScales();
            std::sort(scales.begin(), scales.end(), [](Scale a, Scale b)
                      { return a.getBrightness() < b.getBrightness(); });
            return std::move(scales);
        }

        static std::vector<Scale> getDiatonicScales(const Chord &chord)
        {
            std::vector<Scale> diatonicScales;
            for (auto scale : getAllScales())
            {
                if (scale.isChordDiatonic(chord))
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
        // The styles of music the mode is usually used for
        std::string mStyle = "";
        // Some useful progressions for the scale
        std::vector<std::string> mProgressions;

        // Function to test is a vector contains the values given in the arguments
        bool inVec(const std::vector<int> &vec, const std::vector<int> &values)
        {
            return std::all_of(values.begin(), values.end(), [&vec](int value)
                               { return std::find(vec.begin(), vec.end(), value) != vec.end(); });
        }

        void replaceBack(std::string &str, const std::string &toReplace, int size = 1)
        {
            str.replace(str.end() - size, str.end(), toReplace);
        }

        // Test is a string ens with another string
        bool endsWith(const std::string &str, const std::string &ending)
        {
            if (str.length() >= ending.length())
            {
                return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
            }
            return false;
        }
    };

} // namespace cmtk
