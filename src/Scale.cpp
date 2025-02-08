#include "Scale.h"
#include "Chord.h"

namespace cmtk {

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Scale Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
// Constructor to set the scale from a given name and root note
Scale::Scale(std::string aName, Note aRootNote)
{
    setRoot(aRootNote);
    setScale(aName);
}

    // Constructor to set the scale from a given name and root note
    Scale::Scale(std::string aName, std::string aRootNote)
    {
        setRoot(aRootNote);
        setScale(aName);
    }

    // Constructor to set the scale from a combined root and name, e.g. "C-Major", "Eb-Dorian"
    Scale::Scale(const std::string& aName)
    {
        set(aName);
    }

    // Set the Root Note of the Scale from a Note Object
    Scale& Scale::setRoot(const Note& aRootNote)
    {
        mRootNote = aRootNote;
        updateNotes();
        return *this;
    }

    // Set the Root Note of the Scale from a string
    Scale& Scale::setRoot(const std::string& aRootNote)
    {
        mRootNote = Note(aRootNote);
        updateNotes();
        return *this;
    }

    // Set the Root Note of the Scale from a semi-tone value given as an integer
    Scale& Scale::setRoot(int aRootNote)
    {
        mRootNote = Note(aRootNote);
        updateNotes();
        return *this;
    }

    // Function to get the Root Note of the Scale
    const Note& Scale::getRoot() const
    {
        return mRootNote;
    }

    // Function to Clear the Scale
    Scale& Scale::clear()
    {
        mName.clear();
        mNotes.clear();
        mIntervals.clear();
        mStyle.clear();
        return *this;
    }

    // Function to set the scale from a combined root and name, e.g. "C-Major", "Eb-Dorian"
    Scale& Scale::set(const std::string& s)
    {
        // Split the string
        auto vec = split(s, '-');

        // If only one element - Set the scale and default the root to C
        if(vec.size() == 1)
        {
            setScale(vec[0]);
            setRoot("C");
            return *this;
        }
        // If two elements - Set the root and scale
        if(vec.size() >= 2)
        {
            setRoot(vec[0]);
            setScale(vec[1]);
        }

        return *this;
    }

    // Function to set the scale from a string, e.g. "Major", "Dorian"
    Scale& Scale::setScale(std::string aScaleName)
    {
        clear();
        mName = aScaleName; // TODO: Move this to end and set only if everything is ok

        // ----------------------- Major Modes ----------------------- //
        // Ionian Mode - Major Scale 1st Mode {1 2 3 4 5 6 7}
        if (mName == "Ionian" || mName == "Major")
        {
            mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7)};
            mStyle = "Happy,Light,Bright,Positive,Pop,Rock,Jazz,Classical,Happy";
        }
        // Dorian Mode - Major Scale 2nd Mode {1 2 ♭3 4 5 6 ♭7} - Def:Nat6
        // Riders On The Storm by The Doors, Mad World by Tears for Fears, Scarborough Fair, Woodstock by Joni Mitchell, Blue Jeans by Lana Del Rey, Drive by R.E.M., The "Dorian vamp", Pink Floyd and Dorian
        else if (mName == "Dorian") 
        {
            mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
            mStyle = "Jazzy,Bluesy,Rocky,Sophisticated,Adventurous";
        }
        // Phrygian Mode - Major Scale 3rd Mode {1 ♭2 ♭3 4 5 ♭6 ♭7} - Def:b2
        else if (mName == "Phrygian")
        {
            mIntervals = {Interval(1), Interval(2, -1), Interval(3, -1), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
            mStyle = "Exotic,Spanish,Eastern,Flamenco,Latin,Lively";
        }
        // Lydian Mode - Major Scale 4th Mode {1 2 3 ♯4 5 6 7} - Def:#4
        else if (mName == "Lydian")
        {
            mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4, 1), Interval(5), Interval(6), Interval(7)};
            mStyle = "Dreamy,Spacey,Modern,Jazz,Hopeful,Positive,Magical";
            // mProgressions.add("Evanescence" ,"I|iii|I|iii");
        }
        // Mixolydian Mode - Major Scale 5th Mode {1 2 3 4 5 6 ♭7} - Def:b7
        else if (mName == "Mixolydian") 
        {
            mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6), Interval(7, -1)};
            mStyle = "Blues,Rock,Jazz,Folk,Country,Pop";
            // mProgressions.add("MixolydianVamp","I|bVII|IV|I");
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
            // mProgressions.add("PrincessLeia","I|iv6");
        }
        // Dorian b5 - Harmonic Major 2nd Mode {1 2 ♭3 4 ♭5 6 ♭7}
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
            // mProgressions.add("HarmonicVamp"  ,"i|i|bVI|V");
            // mProgressions.add("ChocolateJesus","i|iv|i|V7");
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
        // Valar Morghulis Theme-Game of Thrones, My Iron Lung-Radiohead,Univited-Alanis Morissette,Extraordinary Girl-Green Day, The Simpsons, The Fragile-Nine Inch Nails,  
        // https://youtu.be/GTRDQeiLNck?si=uJKIR-BdlzOaXstT 
        else if (mName == "Mixolydian b6")
        {
            mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4), Interval(5), Interval(6, -1), Interval(7, -1)};
            mStyle = "Sad,Sentimental";
            // mProgressions.add("Vamp","I|iv");
            // mProgressions.add("PrincessLeia","I|iv6");
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
            // mProgressions.add("ClapHands","i|bVI7");
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
            // mProgressions.add("RoyalRoad","I|IV|iii|vi");
        }
        // Super-Locrian Diminished - Neopolitan Minor 7th Mode
        else if (mName == "Super-Locrian Diminished")
        {
            mIntervals = {Interval(1), Interval(2, -1), Interval(3, -2), Interval(4, -1), Interval(5, -1), Interval(6, -1), Interval(7, -2)};
            mStyle = "Latin,Dark";
        }

        // ----------------------- Double Harmonic Modes ----------------------- //
        // Double Harmonic Major - Double Harmonic Major 1st Mode - Dune-Hans Zimmer, Misirlou
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
            // mProgressions.add("HarmonicVamp","i|i|bVI|V");
            // mProgressions.add("ClapHands"   ,"i|bVI7");
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

        // ----------------------- Persian Modes ----------------- //
        else if (mName == "Persian" || mName == "Persian 1st Mode")
        {
            mIntervals = {Interval(1), Interval(2, -1), Interval(3), Interval(4), Interval(5, -1), Interval(6,-1), Interval(7)};
        }
        else if (mName == "Persian 2nd Mode")
        {
            mIntervals = {Interval(1), Interval(2,1), Interval(3), Interval(4), Interval(5), Interval(6,1), Interval(7)};
        }
        else if (mName == "Persian 3rd Mode")
        {
            mIntervals = {Interval(1), Interval(2,-1), Interval(3,-2), Interval(4,-1), Interval(5), Interval(6,1), Interval(7,-2)};
        } 
        else if (mName == "Persian 4th Mode")
        {
            mIntervals = {Interval(1), Interval(2,-1), Interval(3,-1), Interval(4,1), Interval(5), Interval(6,-1), Interval(7)};
        }
        else if (mName == "Persian 5th Mode")
        {
            mIntervals = {Interval(1), Interval(2), Interval(3,1), Interval(4,1), Interval(5), Interval(6,1), Interval(7)};
        }
        else if (mName == "Persian 6th Mode")
        {
            mIntervals = {Interval(1), Interval(2,1), Interval(3), Interval(4), Interval(5,1), Interval(6), Interval(7,-1)};
        }
        else if (mName == "Persian 7th Mode")
        {
            mIntervals = {Interval(1), Interval(2,-1), Interval(3,-2), Interval(4), Interval(5,-1), Interval(6,-2), Interval(7,-2)};
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
            mIntervals = {Interval(1), Interval(2), Interval(3, -1), Interval(4,-1), Interval(5), Interval(6)};
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

        // Enigma {1 b2 3 #4 #5 #6 7}
        // Prometheus {1 2 3 ♯4 6 ♭7}
        // Whole Tone {1 2 3 ♯4 ♯5 ♯6}
        // ----------------------- Bebop Scales ----------------------- //


        // ----------------------- Other Scales ----------------------- //
        // Whole Tone {1 2 3 ♯4 ♯5 ♯6}
        // Octatonic
        else if (mName == "Whole Tone")
        {
            mIntervals = {Interval(1), Interval(2), Interval(3), Interval(4,1), Interval(5,1), Interval(6, 1)};
        }


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

        // Set Notes
        updateNotes();

        // Scale Unknown?
        if(mIntervals.empty())
        {
            // Throw exception for unknown scale
            throw std::runtime_error("Scale::Scale(): Unknown scale: " + mName);
        }

        return *this;

    }

    // Overload the [] operator to get the interval at a given index (degree-1)
    Interval Scale::operator[](int index)
    {
        return intervalAt(index);
    }

    // Function to get the semi-tone of the scale at a given index
    int Scale::semiToneAt(int index) 
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

        res += mIntervals[index].getSemi();
        return res;
    }

    // Function to get a scale that matches the given intervals
    Scale Scale::GetScale(const Intervals& intervals)
    {
        for(auto& scale : GetAllScales())
        {
            if(scale.getIntervals() == intervals)
            {
                return std::move(scale);
            }
        }

        // Throw exception if scale not found
        throw std::runtime_error("Scale::GetScale(): Scale not found with intervals: " + intervals.toString());
    }

    // Function to get the semi-tones of the scale at given indexes
    std::vector<int> Scale::semitoneAt(const std::vector<int> &indexes)
    {
        std::vector<int> semitones;
        for (auto index : indexes)
        {
            semitones.push_back(semiToneAt(index));
        }

        return std::move(semitones);
    }

    // Function to get the interval of the scale at a given index
    const Interval Scale::intervalAt(int index) const 
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

    // Function to get the intervals of the scale at given indexes
    const Intervals Scale::intervalAt(const std::vector<int> &indexes) const 
    {
        Intervals intervals;
        for (auto index : indexes)
        {
            intervals.push_back(intervalAt(index));
        }

        return std::move(intervals);
    }

    // Function to get the chord symbol of the scale at a given index
    std::string Scale::getChordSymbol(int index, int size, bool roman, bool simplify) const
    {
        // Check that size is valid
        if (size < 3 || size > 7)
            throw std::invalid_argument("Scale::getChordSymbol(): Invalid size: " + std::to_string(size) + std::string(" - Size must be between 3 and 7"));

        // Create a vector of indexes for the chord
        Intervals chordIntervals;
        for (int i = 0; i < size; i++)
        {
            auto interval = intervalAt(index + 2 * i);
            chordIntervals.add(interval);
        }

        // Get the normalized semitones
        auto semitones = chordIntervals.getSemiNormalized();

        // String for the chord symbol
        std::string chordSymbol = "";
        std::string toAppend = "";

        // Uppercase Roman
        bool uppercase = true;

        // Triads
        if      (inVec(semitones, {4, 7})){                                           }
        else if (inVec(semitones, {4, 6})){ toAppend = "b5"     ;                     }
        else if (inVec(semitones, {3, 7})){ if(!roman) chordSymbol = "m" ; uppercase = false;  }
        else if (inVec(semitones, {3, 6})){ chordSymbol = "°"   ; uppercase = false;  }
        else if (inVec(semitones, {4, 8})){ chordSymbol = "+"   ;                     }
        else if (inVec(semitones, {2, 7})){ toAppend = "sus2"   ;                     }
        else if (inVec(semitones, {2, 6})){ toAppend = "sus2b5" ; uppercase = false;  }
        else if (inVec(semitones, {5, 7})){ toAppend = "sus4"   ;                     }
        else
        {
            // Throw exception for unknown chord
            throw std::runtime_error("Scale::getChordSymbol(" + std::to_string(index) + "," + std::to_string(size) + "): Unknown chord with Semitones: " + toString(semitones));
        }

        // 7th
        if (size > 3){
            if      (inVec(semitones, Intervals("b7").getSemi())){ if(chordSymbol == "°") chordSymbol = "ø7"; else chordSymbol.append("7"); }
            else if (inVec(semitones, Intervals("7") .getSemi())){ chordSymbol.append("Maj7"); }
            else if (inVec(semitones, Intervals("6") .getSemi())){ chordSymbol.append(chordSymbol == "°" ? "7" : "6"); }
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
        if (size > 4){
            if      (inVec(semitones, Intervals( "9").getSemi())){ chordSymbol.back() = '9'; }
            else if (inVec(semitones, Intervals("b9").getSemi())){ toAppend += "b9";         }
            else if (inVec(semitones, Intervals("#9").getSemi())){ toAppend += "#9";         }
            else
            {
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 9th chord with Semitones: " + toString(semitones));
            }
        }

        // 11th Chords
        if(size > 5){
            if      (inVec(semitones, Intervals("11") .getSemi())){ chordSymbol.back() = '1'; chordSymbol.push_back('1'); }
            else if (inVec(semitones, Intervals("b11").getSemi())){ toAppend += "b11"; }
            else if (inVec(semitones, Intervals("#11").getSemi())){ toAppend += "#11"; }
            else
            {
                // Throw exception for unknown chord
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 11th chord with Semitones: " + toString(semitones));
            }
        }

        // 13th Chords
        if (size > 6){
            if      (inVec(semitones, Intervals("13" ).getSemi())){ replaceBack(chordSymbol, "13", endsWith(chordSymbol, "11") ? 2 : 1); }
            else if (inVec(semitones, Intervals("b13").getSemi())){ toAppend += "b13"; }
            else if (inVec(semitones, Intervals("#13").getSemi())){ toAppend += "#13"; }
            else
            {
                throw std::runtime_error("Scale::getChordSymbol(): Unknown 13th chord with Semitones: " + toString(semitones));
            }
        }

        // Insert the roman numeral at beginning of the chord symbol
        if(roman) chordSymbol.insert(0, chordIntervals.front().getRoman(uppercase));
        else      chordSymbol.insert(0, mRootNote.getNoteAt(chordIntervals.front()).toString(false,simplify));

        // Append
        if (!toAppend.empty())
        {
            chordSymbol.append(toAppend);
        }

        // Print the chord symbol
        return std::move(chordSymbol);
    }

    // Get chord at index
    Chord Scale::getChord(int index, int size)
    {
        index--;
        const auto& chordSymbol = getChordSymbol(index, size);
        auto chord = Chord(chordSymbol);
        return std::move(chord);
    }

    // Get all the chord symbols
    std::vector<std::string> Scale::getChordSymbols(int size, bool roman)
    {
        std::vector<std::string> chordSymbols;
        for (int i = 0; i < mIntervals.size(); i++)
        {
            chordSymbols.push_back(getChordSymbol(i, size));
        }

        return std::move(chordSymbols);
    }

    // Get ChordProg from a vector of indexes
    ChordProg Scale::getChordProg(const std::vector<int>& indexes, int size)
    {
        ChordProg chordProgression;
        for (auto index : indexes)
        {
            chordProgression.addChord(getChord(index, size));
        }
        chordProgression.setTonic(mRootNote);

        return std::move(chordProgression);
    }

    // Get ChordProg from a vector of indexes and sizes
    ChordProg Scale::getChordProg(const std::vector<int>& indexes, const std::vector<int>& aSize)
    {
        ChordProg chordProgression;
        int i=0;
        for (auto index : indexes)
        {
            if(i >= aSize.size()) i = 0;
            chordProgression.addChord(getChord(index-1, aSize[i++]));
        }

        return std::move(chordProgression);
    }
    
    // Get ChordProg from a string of indexes and a size
    ChordProg Scale::getChordProg(const std::string& s, int size)
    {
        std::vector<int> indexes;
        for(char c : s)
        {
            if(isdigit(c))
            {
                int index = c - '0';
                indexes.push_back(index);
            }
        }
        return std::move(getChordProg(indexes,size));
    }

    // Get ChordProg from a combined string of Root, Scale and Degrees, e.g. "C-Major-145" -> ChordProg("C|F|G")
    ChordProg Scale::GetChordProg(const std::string& s, int size)
    {
        ChordProg chordProgression;
        try {
            Scale scale;
            auto tokens = split(s, '-');
            if(tokens.size() == 3)
            {   
                scale = Scale(tokens[1],tokens[0]);
                chordProgression = scale.getChordProg(tokens[2],size);
            }
            else if(tokens.size() == 4)
            {
                size = std::stoi(tokens[3]);
                scale = Scale(tokens[1],tokens[0]);
                chordProgression = scale.getChordProg(tokens[2],size);
            }
            else {
                throw std::runtime_error("Scale::GetChordProg(): Invalid argument: " + s);
            }
        } catch (const std::exception& e) {
            // Handle the exception here
            std::cerr << e.what() << std::endl;
        }

        return std::move(chordProgression);
    }

    // Print the chord symbols
    void Scale::printChordSymbols(int size)
    {
        auto chordSymbols = getChordSymbols(size);
        for (auto chordSymbol : chordSymbols)
        {
            std::cout << chordSymbol << " ";
        }
        std::cout << std::endl;
    }

    // Function to calculate the brightness of the scale
    int Scale::getBrightness()
    {
        int brightness = 0;
        for (auto interval : mIntervals)
        {
            brightness += interval.getQuality();
        }
        return brightness;
    };

    // Size of the scale
    int Scale::size()
    {
        return mIntervals.size();
    }

    // Stream operator to print the scale
    std::ostream &operator<<(std::ostream &os, const Scale &scale)
    {
        os << scale.mName << "(" << scale.mIntervals << ")";

        return os;
    }

    // Get Intervals of the scale
    const Intervals& Scale::getIntervals() const
    {
        return mIntervals;
    }

    // Get Intervals of the scale
    Intervals Scale::getIntervals()
    {
        return mIntervals;
    }

    // Get Notes of the scale
    const Notes& Scale::getNotes() const
    {
        return mNotes;
    }

    // Print the scale
    void Scale::print(int size, bool simplify) const
    {
        std::cout << mRootNote.toString(false,false) << "-" << mName << " : " << getWholeHalfPattern();
        if (!mStyle.empty())
            std::cout << " - " << mStyle;
        std::cout << std::endl;

        int i = 0;
        printf("%-6s%-6s%-6s%-10s\t%-10s\t%-6s\t%-6s\n", "Deg", "Int", "Semi", "Roman", "Chord", "Note", "Midi");
        for (auto interval : mIntervals)
        {
            std::cout << std::left << std::setw(6) << i+1
                        << std::left << std::setw(6) << interval.toString()
                        << std::left << std::setw(6) << interval.getSemi()
                        << std::left << std::setw(10) << getChordSymbol(i, size, true  ) << "\t"
                        << std::left << std::setw(10) << getChordSymbol(i, size, false, simplify ) << "\t" 
                        << mNotes.at(i).toString(true,simplify) << "\t" << mNotes.semiAt(i) 
                        << std::endl;
            i++;
        }
        std::cout << std::endl;
    }

    // Print the scale as whole and half steps
    const std::string Scale::getWholeHalfPattern() const
    {   
        auto intervals = mIntervals.getSemi();
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
    bool Scale::isDiatonic(const Chord &chord) const
    {
        return mNotes.contains(chord.getNotes(), true);
    }

    // Functions to test if a chord progression is diatonic to the scale    
    bool Scale::isDiatonic(const ChordProg& chordProgression) const
    {
        for(const auto& chord : chordProgression)
        {
            if(!isDiatonic(chord)) return false;
        }

        return true;
    }

    // Function to calculate the diatonicity of a set of notes to the scale
    float Scale::diatonicity(const Notes& aChordNotes)
    {   
        // ChordNotes
        auto chordNotes = aChordNotes;
        chordNotes.removeOctave();
        chordNotes.removeDuplicates();
        // ScaleNotes
        auto scaleNotes = mNotes;
        scaleNotes.removeOctave();
        scaleNotes.removeDuplicates();
        // Find Number of notes in the chord that are in the scale
        int numNotesInScale = 0;
        for (const auto& note : chordNotes)
        {
            if(scaleNotes.contains(note)) numNotesInScale++;
        }

        return numNotesInScale / (float) aChordNotes.size();
    }        

    // Function to calculate the diatonicity of a chord to the scale
    float Scale::diatonicity(const Chord &chord)
    {   
        return diatonicity(chord.getNotes());
    }

    // Function to calculate the diatonicity of a chordProgression to the scale
    float Scale::diatonicity(const ChordProg& chordProgression)
    {
        return diatonicity(chordProgression.getNotes().removeOctave());
    }
    
    // Return a vector of all the supported scales, with the given root note
    std::vector<Scale> Scale::GetAllScales(const Note& aRoot)
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
            "Double Harmonic Major", "Lydian #2 #6", "Ultra Phrygian", "Hungarian Minor", "Oriental", "Ionian Augmented #2", "Locrian Diminished bb3",
            // Persian Modes:
            // "Persian", "Persian 2nd Mode", "Persian 3rd Mode", "Persian 4th Mode", "Persian 5th Mode", "Persian 6th Mode", "Persian 7th Mode",
            // Other Scales - TODO: Fix this class so that scales with other number of notes than 7 is supported!
            // "Major Pentatonic"     , "Minor Pentatonic", "Blues", "Octatonic", "Augmented", "Bebop Dominant", "Octatonic Whole-Half", "Octatonic Half-Whole", "Tritone"
        }){
            scales.push_back(Scale(scaleName,aRoot));
        }

        return std::move(scales);
    }

    // Return a vector of all the supported scales, in all keys... A CPU intensive operation
    std::vector<Scale> Scale::GetAllScalesAllKeys()
    {
        std::vector<Scale> scales;
        for(auto& scale : GetAllScales())
        {
            for(auto& root : Notes::AllKeys())
            {
                scale.setRoot(root);
                scales.push_back(scale);
            }
        }
        return std::move(scales);
    }

    // Get the names of the modes of a given scale
    std::vector<std::string> Scale::GetModeNames(std::string s)
    {
        //      Scale Name                       1st Mode                 2nd Mode               3rd Mode                     4th Mode               5th Mode             6th Mode               7th Mode
        if(s == "Major"                ) return {"Ionian"               , "Dorian"             , "Phrygian"                 , "Lydian"             , "Mixolydian"       , "Aeolian"            , "Locrian"                 };
        if(s == "Harmonic Major"       ) return {"Harmonic Major"       , "Dorian b5"          , "Phrygian b4"              , "Lydian b3"          , "Mixolydian b2"    , "Lydian Augmented"   , "Locrian Diminished"      };
        if(s == "Harmonic Minor"       ) return {"Harmonic Minor"       , "Locrian n6"         , "Ionian #5"                , "Dorian #4"          , "Phrygian Dominant", "Lydian #2"          , "Super Locrian"           };
        if(s == "Melodic Minor"        ) return {"Melodic Minor"        , "Dorian b2"          , "Lydian Augmented"         , "Lydian Dominant"    , "Mixolydian b6"    , "Locrian #2"         , "Altered"                 };
        if(s == "Neopolitan Major"     ) return {"Neopolitan Major"     , "Lydian Augmented #6", "Lydian Augmented Dominant", "Lydian b6 Dominant" , "Major Locrian"    , "Super Locrian n2"   , "Super Locrian bb3"       };
        if(s == "Neopolitan Minor"     ) return {"Neopolitan Minor"     , "Lydian #6"          , "Mixolydian Augmented"     , "Hungarian Gypsy"    , "Locrian n3"       , "Ionian #2"          , "Super-Locrian Diminished"};
        if(s == "Double Harmonic Major") return {"Double Harmonic Major", "Lydian #2 #6"       , "Ultra Phrygian"           , "Hungarian Minor"    , "Oriental"         , "Ionian Augmented #2", "Locrian Diminished bb3"  };
        if(s == "Persian"              ) return {"Persian"              , "Persian 2nd Mode"   , "Persian 3rd Mode"         , "Persian 4th Mode"   , "Persian 5th Mode" , "Persian 6th Mode"   , "Persian 7th Mode"        };
        if(s == "Major Pentatonic"     ) return {"Major Pentatonic"     , "Egyptian Pentatonic", "Man Gong Pentatonic"      , "Ritsusen Pentatonic", "Minor Pentatonic" };
        if(s == "Blues"                ) return {"Major Blues"          , "Blues 2nd Mode"     , "Blues 3rd Mode"           , "Blues 4th Mode"     , "Blues 5th Mode"    , "Minor Blues"        };

        // Return empty vector if no scales found
        return {};
    }

    // Get the Modes of a scale
    std::vector<Scale> Scale::GetModes(std::string s, const Note& root)
    {
        std::vector<Scale> modes;
        for(auto modeName : GetModeNames(s))
        {
            modes.push_back(Scale(modeName,root));
        }

        return std::move(modes);
    }

    // Print the names of the modes
    void Scale::PrintModeNames(std::string s, int size)
    {
        if(s.empty()){
            for(auto scaleName : {
                "Major", "Harmonic Major", "Harmonic Minor", "Melodic Minor", "Neopolitan Major", "Neopolitan Minor", "Double Harmonic Major", "Persian", "Major Pentatonic", "Blues"
            }){
                PrintModeNames(scaleName, size);
                std::cout << std::endl;
            }
            return;
        }

        // Print the ModeNames
        int i = 1;
        std::cout << s << " Modes: " << std::endl;
        for(auto mode : GetModeNames(s)){
            std::cout << i++ << ": " << mode << std::endl;
        } 
    }

    // Print the modes
    void Scale::PrintModes(std::string s,  Note root, int size)
    {
        if(s.empty()){
            for(auto scaleName : {
                "Major", "Harmonic Major", "Harmonic Minor", "Melodic Minor", "Neopolitan Major", "Neopolitan Minor", "Double Harmonic Major", "Major Pentatonic", "Blues"
            }){
                PrintModes(scaleName, root, size);
                std::cout << std::endl;
            }
            return;
        }

        // Print the Modes
        int i = 1;
        for(auto mode : GetModes(s,root)){
            std::cout << s << " Mode " << i++ << ": " << std::endl;
            mode.print(size);
        } 

    }

    // Print all the scales
    void Scale::PrintAllScales(int size)
    {
        for (auto scale : GetAllScales())
        {
            scale.print(size);
        }
    }

    // Return a vector with all the scales sorted by brightness
    std::vector<Scale> Scale::GetScalesByBrightness()
    {
        auto scales = GetAllScales();
        std::sort(scales.begin(), scales.end(), [](Scale a, Scale b)
                    { return a.getBrightness() < b.getBrightness(); });
        return std::move(scales);
    }

    // Return a vector with all the scales sorted by Diatonicity to a given chord progression. Only the scales with the given root note are returned
    std::vector<Scale> Scale::GetScalesByDiatonicity(const ChordProg& chordProgression, const Note& aRoot)
    {
        auto scales = GetAllScales(aRoot);
        std::sort(scales.begin(), scales.end(), [&chordProgression](Scale a, Scale b){ 
            return a.diatonicity(chordProgression) > b.diatonicity(chordProgression); 
        });
        return std::move(scales);
    }

    // Return a vector with all the scales sorted by Diatonicity to a given chord progression. All Root notes are considered
    std::vector<Scale> Scale::GetScalesByDiatonicity(const ChordProg& chordProgression)
    {
        if(chordProgression.getTonic().isOk()) return GetScalesByDiatonicity(chordProgression, chordProgression.getTonic());

        auto scales = GetAllScalesAllKeys();
        std::sort(scales.begin(), scales.end(), [&chordProgression](Scale a, Scale b){ 
            float sad = a.diatonicity(chordProgression);
            float sbd = b.diatonicity(chordProgression);
            if(sad > sbd) return true;
            if(sad < sbd) return false;

            auto  sar = a.getRoot();
            auto  sbr = b.getRoot();
            auto  cr  = chordProgression[0].getRoot();
            if(sar == cr && sbr != cr) return true;
            if(sar != cr && sbr == cr) return false;

            return sar == cr && sbr != cr;
        });
        return std::move(scales);
    } 

    // Get the name of the scale
    std::string Scale::getName(bool withRoot) const
    {
        return mRootNote.toString(false,false) + "-" + mName;
    }

    // Print the scales sorted by Diatonicity to a ChordProg
    void Scale::PrintScalesByDiatonicity(const ChordProg& chordProgression, int limit)
    {
        // Collect all scales sorted by Diatonicity
        auto scales = GetScalesByDiatonicity(chordProgression);

        int i=0;
        for (auto scale : scales){

            std::cout << scale.getName() << "\tdiatonicity : " << scale.diatonicity(chordProgression) * 100 << " %" << std::endl;
            if(++i == limit) return;
        }
    }

    // Get a vector of all the diatonic scales to a given chord
    std::vector<Scale> Scale::GetDiatonicScales(const Chord& chord, const Note& aTonic)
    {
        std::vector<Scale> diatonicScales;
        for (auto scale : GetAllScales())
        {
            scale.setRoot(aTonic);
            if (scale.isDiatonic(chord))
            {
                diatonicScales.push_back(scale);
            }
        }

        return std::move(diatonicScales);
    }

    // Get a vector of all the diatonic scales to a given chord progression
    std::vector<Scale> Scale::GetDiatonicScales(const ChordProg& chordProgression, const Note& aTonic)
    {
        std::vector<Scale> diatonicScales;
        for (auto scale : GetAllScales())
        {   
            scale.setRoot(aTonic);
            if (scale.isDiatonic(chordProgression))
            {
                diatonicScales.push_back(scale);
            }
        }

        return std::move(diatonicScales);
    }
    
    // Print all the diatonic scales to a given chord
    void Scale::PrintDiatonicScales(const Chord& chord, const Note& aTonic, int size)
    {
        for(const auto& scale : GetDiatonicScales(chord,aTonic))
        {
            scale.print(size);
        }
    }

    // Print all the diatonic scales to a given chord
    void Scale::PrintDiatonicScales(const Chord& chord, int size)
    {
        for(const auto& key : Notes::AllKeys())
        {
            PrintDiatonicScales(chord, key, size);
        }
    }        

    // Print all the diatonic scales to a given chord progression
    void Scale::PrintDiatonicScales(const ChordProg& chordProgression, const Note& aTonic, int size)
    {
        for(const auto& scale : GetDiatonicScales(chordProgression, aTonic))
        {
            scale.print(size);
        }   
    }

    // Print all the diatonic scales to a given chord progression
    void Scale::PrintDiatonicScales(const ChordProg& chordProgression, int size)
    {
        for(const auto& key : Notes::AllKeys())
        {
            PrintDiatonicScales(chordProgression, key, size);
        }
    }

    // -----PRIVATE FUNCTIONS----- //

    // Function to update the notes of the scale
    void Scale::updateNotes()
    {
        mNotes = mRootNote.getNoteAt(mIntervals);
    }


} // namespace cmtk
