#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

namespace cmtk {

// ----------------------------------------------------------------------- //
// ----------------------------- Scale Class ----------------------------- //
// ----------------------------------------------------------------------- //

class Scale {
public:
    // Constructor
    Scale() = default;
    Scale(std::string scaleName, int rootNote = 0)
    {
        setScale(scaleName, rootNote);
    }

    // Function to set the scale
    void setScale(std::string aScaleName, int aRootNote = 0)
    {
        scaleName = aScaleName;
        if     (scaleName == "Major"        ){ scaleTones = {0, 2, 4, 5, 7, 9, 11}; ;   }
        else if(scaleName == "NaturalMinor" ){ scaleTones = {0, 2, 3, 5, 7, 8, 10}; scaleChords = {"i","ii°","bIII","iv","v","bVI","bVII"};   }
        else if(scaleName == "HarmonicMinor"){ scaleTones = {0, 2, 3, 5, 7, 8, 11}; scaleChords = {"i","ii°","III+","iv","V","VI" ,"vii°"}; }
        else if(scaleName == "MelodicMinor" ){ scaleTones = {0, 2, 3, 5, 7, 9, 11}; scaleChords = {"i","ii","III+","IV","V","vi°","vii°"}; }
        else if(scaleName == "Dorian"       ){ scaleTones = {0, 2, 3, 5, 7, 9, 10}; scaleChords = {"i","ii","III","IV","v","VI","vii°"};   }
        else if(scaleName == "Phrygian"     ){ scaleTones = {0, 1, 3, 5, 7, 8, 10}; scaleChords = {"i","II","III","iv","v","VI","vii°"};   }
        else if(scaleName == "Lydian"       ){ scaleTones = {0, 2, 4, 6, 7, 9, 11}; scaleChords = {"I","ii","iii°","IV+","V","vi","vii"};  }
        else if(scaleName == "Mixolydian"   ){ scaleTones = {0, 2, 4, 5, 7, 9, 10}; scaleChords = {"I","ii°","iii","IV","v","VI","vii°"};  }
        else if(scaleName == "Locrian"      ){ scaleTones = {0, 1, 3, 5, 6, 8, 10}; scaleChords = {"i","II","iii","iv","v","VI","VII"};    }
    }


    // Get the scale name

    
private:
    // The scale name
    std::string scaleName;
    // The scale tones
    std::vector<int> scaleTones;
    // The scale chords
    std::vector<std::string> scaleChords;

};


// ----------------------------------------------------------------------- //
// ----------------------------- Chord Class ----------------------------- //
// ----------------------------------------------------------------------- //
class Chord {
public:
    // Constructor
    Chord() = default;
    Chord(std::string chordSymbol, int rootNote = 0)
    {
        setChord(chordSymbol, rootNote);
    }

    // Enum class to represent the quality of the chord
    enum class Quality {
        Major,
        Minor,
        Diminished,
        HalfDiminished,
        Augmented,
        Sus2,
        Sus4,
        PowerChord,
    };

    // Enum class to represent the intervals
    enum class Interval {
         _R = 0, // Root
        _sR,     // Sharp Root
        _b2,     // Flat 2nd
         _2,     // 2nd
        _s2,     // Sharp 2nd
        _b3,     // Flat 3rd
         _3,     // 3rd
        _s3,     // Sharp 3rd
        _b4,     // Flat 4th
         _4,     // 4th
        _s4,     // Sharp 4th
        _b5,     // Flat 5th
         _5,     // 5th
        _s5,     // Sharp 5th
        _b6,     // Flat 6th
         _6,     // 6th
        _s6,     // Sharp 6th
        _b7,     // Flat 7th
         _7,     // 7th
        _s7,     // Sharp 7th
        _b9,     // Flat 9th
         _9,     // 9th
        _s9,     // Sharp 9th
       _b11,     // Flat 11th
        _11,     // 11th
       _s11,     // Sharp 11th
       _b13,     // Flat 13th
        _13,     // 13th
       _s13      // Sharp 13th
    };

    // Convert the interval to a integer semi tone
    int toInt(Interval interval)
    {   
        // Return the interval as an integer
        switch(interval){
            case Interval::_R:   return  0;
            case Interval::_sR:  return  1;
            case Interval::_b2:  return  1;
            case Interval::_2:   return  2;
            case Interval::_s2:  return  3;
            case Interval::_b3:  return  3;
            case Interval::_3:   return  4;
            case Interval::_s3:  return  5;
            case Interval::_b4:  return  4;
            case Interval::_4:   return  5;
            case Interval::_s4:  return  6;
            case Interval::_b5:  return  6;
            case Interval::_5:   return  7;
            case Interval::_s5:  return  8;
            case Interval::_b6:  return  8;
            case Interval::_6:   return  9;
            case Interval::_s6:  return 10;
            case Interval::_b7:  return 10;
            case Interval::_7:   return 11;
            case Interval::_s7:  return 12;
            case Interval::_b9:  return 13;
            case Interval::_9:   return 14;
            case Interval::_s9:  return 15;
            case Interval::_b11: return 16;
            case Interval::_11:  return 17;
            case Interval::_s11: return 18;
            case Interval::_b13: return 20;
            case Interval::_13:  return 21;
            case Interval::_s13: return 22;
        }

    }

    // Covert the interval to a string
    std::string intervalToString(Interval interval)
    {
        switch(interval){
            case Interval::_R:   return "R";
            case Interval::_sR:  return "sR";
            case Interval::_b2:  return "b2";
            case Interval::_2:   return "2";
            case Interval::_s2:  return "s2";
            case Interval::_b3:  return "b3";
            case Interval::_3:   return "3";
            case Interval::_s3:  return "s3";
            case Interval::_b4:  return "b4";
            case Interval::_4:   return "4";
            case Interval::_s4:  return "s4";
            case Interval::_b5:  return "b5";
            case Interval::_5:   return "5";
            case Interval::_s5:  return "s5";
            case Interval::_b6:  return "b6";
            case Interval::_6:   return "6";
            case Interval::_s6:  return "s6";
            case Interval::_b7:  return "b7";
            case Interval::_7:   return "7";
            case Interval::_s7:  return "s7";
            case Interval::_b9:  return "b9";
            case Interval::_9:   return "9";
            case Interval::_s9:  return "s9";
            case Interval::_b11: return "b11";
            case Interval::_11:  return "11";
            case Interval::_s11: return "s11";
            case Interval::_b13: return "b13";
            case Interval::_13:  return "13";
            case Interval::_s13: return "s13";
        }
        // Print error message
        std::cerr << "Error: Unrecognized interval" << std::endl;

        return "R";
    }

    // Map to convert the string to an interval
    Interval intervalFromString(const std::string& interval){
        if(interval == "R"  ) return  Interval::_R;
        if(interval == "2"  ) return  Interval::_2;
        if(interval == "b3" ) return  Interval::_b3;
        if(interval == "3"  ) return  Interval::_3;
        if(interval == "s3" ) return  Interval::_s3;
        if(interval == "4"  ) return  Interval::_4;
        if(interval == "s4" ) return  Interval::_s4;
        if(interval == "b5" ) return  Interval::_b5;
        if(interval == "5"  ) return  Interval::_5;
        if(interval == "s5" ) return  Interval::_s5;
        if(interval == "b6" ) return  Interval::_b6;
        if(interval == "6"  ) return  Interval::_6;
        if(interval == "b7" ) return  Interval::_b7;
        if(interval == "7"  ) return  Interval::_7;
        if(interval == "b9" ) return  Interval::_b9;
        if(interval == "9"  ) return  Interval::_9;
        if(interval == "b11") return  Interval::_b11;
        if(interval == "11" ) return  Interval::_11;
        if(interval == "b13") return  Interval::_b13;
        if(interval == "13" ) return  Interval::_13;
        // Print error message
        std::cerr << "Error: Unrecognized interval: " << interval << std::endl;
        // Return the root note
        return Interval::_R;
    }

    

    // Function to get the chord tones from a chord symbol
    void setChord(std::string aChordSymbol, int aRootNote = 0)
    {
        chordSymbol = aChordSymbol;
        chordTones = getChordTones(aChordSymbol, aRootNote);
    }

    // Get the chord symbol
    std::string getChordSymbol()
    {
        return chordSymbol;
    }

    // Get the chord tones
    std::vector<int> getChordTones()
    {
        return chordTones;
    }

    // Get the chord tones with an inversion
    std::vector<int> getChordTones(int inversion)
    {
        inversion = inversion % chordTones.size();

        auto notes = this->chordTones;
        // If the inversion is positive, rotate the notes to the right
        while(inversion > 0){
            std::rotate(notes.begin(), notes.begin() + 1, notes.end());
            inversion--;
            // Add one octave to the last note
            notes.back() += 12;
        }
        // If the inversion is negative, rotate the notes to the left
        while(inversion < 0){
            std::rotate(notes.rbegin(), notes.rbegin() + 1, notes.rend());
            inversion++;
            // Subtract one octave from the first note
            notes.front() -= 12;
        }


        return notes;
    }

    // Overload the index operator
    int operator[](int index)
    {   
        if(index >= chordTones.size()){
            std::cerr << "Error: Index out of range" << std::endl;
            return 0;
        }
        return chordTones[index];
    }

    // Get the chord tones from a chord symbol
    std::vector<int> getChordTones(const std::string& aChordSymbol, int rootNote = 0){
        auto chordSymbol = aChordSymbol;

        // Add octave if the chord symbol starts with a number
        while (chordSymbol[0] == '-' || chordSymbol[0] == '+') {
            if      (chordSymbol[0] == '-') { rootNote -= 12; }
            else if (chordSymbol[0] == '+') { rootNote += 12; }
            chordSymbol.erase(0,1);
        }

        // Chech if the roman numeral contains 'i', 'v', 'I' or 'V'
        bool skip = false;
        if(chordSymbol[0] == 'b' && !isRoman(chordSymbol))
        {
            skip = true;
        }

        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(!skip){
            while (chordSymbol[0] == 'b' || chordSymbol[0] == '#') {
                if      (chordSymbol[0] == 'b') { rootNote -= 1; }
                else if (chordSymbol[0] == '#') { rootNote += 1; }
                chordSymbol.erase(0,1);
            }
        }

        // Replace start
        replacePrefix(chordSymbol, "Cbm", "cb");
        replacePrefix(chordSymbol, "Cm" , "c" );
        replacePrefix(chordSymbol, "C#m", "c#");
        replacePrefix(chordSymbol, "Dbm", "db");
        replacePrefix(chordSymbol, "Dm" , "d" );
        replacePrefix(chordSymbol, "D#m", "d#");
        replacePrefix(chordSymbol, "Ebm", "eb");
        replacePrefix(chordSymbol, "Em" , "e" );
        replacePrefix(chordSymbol, "E#m", "e#");
        replacePrefix(chordSymbol, "Fbm", "fb");
        replacePrefix(chordSymbol, "Fm" , "f" );
        replacePrefix(chordSymbol, "F#m", "f#");
        replacePrefix(chordSymbol, "Gbm", "gb");
        replacePrefix(chordSymbol, "Gm" , "g" );
        replacePrefix(chordSymbol, "G#m", "g#");
        replacePrefix(chordSymbol, "Abm", "ab");
        replacePrefix(chordSymbol, "Am" , "a" );
        replacePrefix(chordSymbol, "A#m", "a#");
        replacePrefix(chordSymbol, "Bbm", "bb");
        replacePrefix(chordSymbol, "Bm" , "b" );
        replacePrefix(chordSymbol, "B#m", "b#");

        // Test if the first letter of the roman numeral is a lower case letter. If it is then it is a minor chord and the rootNote is lowered by 3 semitones
        // Set chord type
        bool isMajor = isupper(chordSymbol[0]);
        Quality chordQuality = isMajor ? Quality::Major : Quality::Minor;

        // Convert to_lower 
        std::transform(chordSymbol.begin(), chordSymbol.end(), chordSymbol.begin(), ::tolower);

        // Move the rootNote according to the roman numeral
             if (removePrefix(chordSymbol, "iii")){  rootNote += 4;  }
        else if (removePrefix(chordSymbol, "vii")){  rootNote += 11; }
        else if (removePrefix(chordSymbol, "ii" )){  rootNote += 2;  }
        else if (removePrefix(chordSymbol, "iv" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "vi" )){  rootNote += 9;  }
        else if (removePrefix(chordSymbol, "i"  )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "v"  )){  rootNote += 7;  }
        else if (removePrefix(chordSymbol, "c#" )){  rootNote += 1;  }
        else if (removePrefix(chordSymbol, "db" )){  rootNote += 1;  }
        else if (removePrefix(chordSymbol, "d#" )){  rootNote += 3;  }
        else if (removePrefix(chordSymbol, "eb" )){  rootNote += 3;  }
        else if (removePrefix(chordSymbol, "e#" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "fb" )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "f#" )){  rootNote += 6;  }
        else if (removePrefix(chordSymbol, "gb" )){  rootNote += 6;  }
        else if (removePrefix(chordSymbol, "g#" )){  rootNote += 8;  }
        else if (removePrefix(chordSymbol, "ab" )){  rootNote += 8;  }
        else if (removePrefix(chordSymbol, "a#" )){  rootNote += 10; }
        else if (removePrefix(chordSymbol, "bb" )){  rootNote += 10; }
        else if (removePrefix(chordSymbol, "cb" )){  rootNote += -1; }
        else if (removePrefix(chordSymbol, "b#" )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "c"  )){  rootNote += 0;  }
        else if (removePrefix(chordSymbol, "d"  )){  rootNote += 2;  }
        else if (removePrefix(chordSymbol, "e"  )){  rootNote += 4;  }
        else if (removePrefix(chordSymbol, "f"  )){  rootNote += 5;  }
        else if (removePrefix(chordSymbol, "g"  )){  rootNote += 7;  }
        else if (removePrefix(chordSymbol, "a"  )){  rootNote += 9;  }
        else if (removePrefix(chordSymbol, "b"  )){  rootNote += 11; }

    
        // Change notes if the chord is diminished or augmented
        if      (removePrefix(chordSymbol, "°"       )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "dim"     )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "ø"       )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "halfdim" )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "+"       )){ chordQuality = Quality::Augmented;      }
        else if (removePrefix(chordSymbol, "sus2"    )){ chordQuality = Quality::Sus2;           }
        else if (removePrefix(chordSymbol, "sus4"    )){ chordQuality = Quality::Sus4;           }
        else if (removePrefix(chordSymbol, "5"       )){ chordQuality = Quality::PowerChord;     }

        // Remove stuff from the chord symbol
        const std::string chars = " ^()";
        // Remove the chars
        for (char c: chars) {
            chordSymbol.erase(std::remove(chordSymbol.begin(), chordSymbol.end(), c), chordSymbol.end());
        }

        // Initialize the chord tones vector based on the chord type
        switch (chordQuality)
        {
            case Quality::Major:          chordIntervals = {Interval::_R, Interval::_3,  Interval::_5};  break;
            case Quality::Minor:          chordIntervals = {Interval::_R, Interval::_b3, Interval::_5};  break;
            case Quality::Diminished:     chordIntervals = {Interval::_R, Interval::_b3, Interval::_b5}; break;
            case Quality::HalfDiminished: chordIntervals = {Interval::_R, Interval::_b3, Interval::_b5, Interval::_b7}; break;
            case Quality::Augmented:      chordIntervals = {Interval::_R, Interval::_3,  Interval::_s5}; break;
            case Quality::Sus2:           chordIntervals = {Interval::_R, Interval::_2,  Interval::_5};  break;
            case Quality::Sus4:           chordIntervals = {Interval::_R, Interval::_4,  Interval::_5};  break;
            case Quality::PowerChord:     chordIntervals = {Interval::_R,                Interval::_5};  break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            add(Interval::_6);
        }
        else if(removePrefix(chordSymbol, "7")){
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
        }
        else if(removePrefix(chordSymbol, "9")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
        }
        else if(removePrefix(chordSymbol, "11")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
            add(Interval::_11);
        }
        else if(removePrefix(chordSymbol, "11")){ 
            add(chordQuality == Quality::Diminished ? Interval::_6 : Interval::_b7);
            add(Interval::_9);
            add(Interval::_11);
            add(Interval::_13);
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            add(Interval::_7);
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            add(Interval::_7);
            add(Interval::_9);
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            add(Interval::_7);
            add(Interval::_9);
            add(Interval::_11);
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            add(Interval::_7);
            add(Interval::_9);
            add(Interval::_11);
            add(Interval::_13);
        }

        // Handle more complex chords
        bool found = true;
        while(found)
        {   
            found = false;
            // Flatten
            if(removePrefix(chordSymbol, "b3"  )){ remove(Interval::_3);  remove(Interval::_s3);  add(Interval::_b3);  found = true; }
            if(removePrefix(chordSymbol, "b5"  )){ remove(Interval::_5);  remove(Interval::_s5);  add(Interval::_b5);  found = true; }
            if(removePrefix(chordSymbol, "b7"  )){ remove(Interval::_7);  remove(Interval::_s7);  add(Interval::_b7);  found = true; }
            if(removePrefix(chordSymbol, "b9"  )){ remove(Interval::_9);  remove(Interval::_s9);  add(Interval::_b9);  found = true; }
            if(removePrefix(chordSymbol, "b11" )){ remove(Interval::_11); remove(Interval::_s11); add(Interval::_b11); found = true; }
            if(removePrefix(chordSymbol, "b13" )){ remove(Interval::_13); remove(Interval::_s13); add(Interval::_b13); found = true; }
            // Sharpen
            if(removePrefix(chordSymbol, "#3"  )){ remove(Interval::_3);  remove(Interval::_b3);  add(Interval::_s3);  found = true; }
            if(removePrefix(chordSymbol, "#5"  )){ remove(Interval::_5);  remove(Interval::_b5);  add(Interval::_s5);  found = true; }
            if(removePrefix(chordSymbol, "#7"  )){ remove(Interval::_7);  remove(Interval::_b7);  add(Interval::_s7);  found = true; }
            if(removePrefix(chordSymbol, "#9"  )){ remove(Interval::_9);  remove(Interval::_b9);  add(Interval::_s9);  found = true; }
            if(removePrefix(chordSymbol, "#11" )){ remove(Interval::_11); remove(Interval::_b11); add(Interval::_s11); found = true; }
            if(removePrefix(chordSymbol, "#13" )){ remove(Interval::_13); remove(Interval::_b13); add(Interval::_s13); found = true; }
            
            // Remove notes if required
            if(removePrefix(chordSymbol, "no1" )){ remove(Interval::_R);  found = true; }
            if(removePrefix(chordSymbol, "no3" )){ remove(Interval::_3);  remove(Interval::_b3);  remove(Interval::_s3); found = true;}
            if(removePrefix(chordSymbol, "no5" )){ remove(Interval::_5);  remove(Interval::_b5);  remove(Interval::_s5); found = true;}
            if(removePrefix(chordSymbol, "no7" )){ remove(Interval::_7);  remove(Interval::_b7);  remove(Interval::_s7); found = true;}
            if(removePrefix(chordSymbol, "no9" )){ remove(Interval::_9);  remove(Interval::_b9);  remove(Interval::_s9); found = true;}
            if(removePrefix(chordSymbol, "no11")){ remove(Interval::_11); remove(Interval::_b11); remove(Interval::_s11);found = true;}
            if(removePrefix(chordSymbol, "no13")){ remove(Interval::_13); remove(Interval::_b13); remove(Interval::_s13);found = true;}

            // Add notes if required
            if(removePrefix(chordSymbol, "add2"  )){ add(Interval::_2);   found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ add(Interval::_4);   found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ add(Interval::_6);   found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ add(Interval::_9);   found = true; }
            if(removePrefix(chordSymbol, "add11" )){ add(Interval::_11);  found = true; }
            if(removePrefix(chordSymbol, "add13" )){ add(Interval::_13);  found = true; }
            if(removePrefix(chordSymbol, "addb2" )){ add(Interval::_b2);  found = true; }
            if(removePrefix(chordSymbol, "addb4" )){ add(Interval::_b4);  found = true; }
            if(removePrefix(chordSymbol, "addb6" )){ add(Interval::_b6);  found = true; }
            if(removePrefix(chordSymbol, "addb9" )){ add(Interval::_b9);  found = true; }
            if(removePrefix(chordSymbol, "addb11")){ add(Interval::_b11); found = true; }
            if(removePrefix(chordSymbol, "addb13")){ add(Interval::_b13); found = true; }
            if(removePrefix(chordSymbol, "add#2" )){ add(Interval::_s2);  found = true; }
            if(removePrefix(chordSymbol, "add#4" )){ add(Interval::_s4);  found = true; }
            if(removePrefix(chordSymbol, "add#6" )){ add(Interval::_s6);  found = true; }
            if(removePrefix(chordSymbol, "add#9" )){ add(Interval::_s9);  found = true; }
            if(removePrefix(chordSymbol, "add#11")){ add(Interval::_s11); found = true; }
            if(removePrefix(chordSymbol, "add#13")){ add(Interval::_s13); found = true; }
        }
        // Erase all that is below zero
        // chordTones.erase(std::remove_if(chordTones.begin(), chordTones.end(), [](int i){ return i < 0; }), chordTones.end());

        // Cast the chordIntervals to int and assign to chordTones
        std::vector<int> chordTones;
        for (auto interval : chordIntervals) {
            chordTones.push_back(toInt(interval));
        }

        // Add the rootNote to each of the chord tones
        for (int i = 0; i < chordTones.size(); i++) {
            chordTones[i] += rootNote;
        }

        if(chordSymbol.size() > 0){
            std::cerr << "Warning: Unrecognized chord symbol: " << aChordSymbol << " : " << chordSymbol << std::endl;
        }

        // Return the chord tones
        return chordTones;

    }

    // Function to flatten an interval
    void flatten(Interval n)
    {
        for(auto& interval : chordIntervals){
            if(interval == n){
                interval = static_cast<Interval>(static_cast<int>(interval) - 1);
            }
        }
    }

    void add(Interval n)
    {   
        // Test if interval already present
        for(auto& interval : chordIntervals){
            if(interval == n) return;
        }
        // If not, add the interval
        chordIntervals.push_back(n);
        // Sort the chord intervals
        std::sort(chordIntervals.begin(), chordIntervals.end());
    }

    // Remove Interval
    void remove(Interval n)
    {
        chordIntervals.erase(std::remove(chordIntervals.begin(), chordIntervals.end(), n), chordIntervals.end());
    }


    void zeroCollaps(std::vector<int>& chordTones)
    {
        for(auto& note : chordTones){
            if(note >= 6) note -= 12;
        }

        // Sort the chord tones
        std::sort(chordTones.begin(), chordTones.end());
    }

    void moveNthBy(std::vector<int>& chordTones, int n, int by)
    {
        chordTones[n] += by;
        std::sort(chordTones.begin(), chordTones.end());
    }

    void printIntervals(){
        // Print the chord intervals
        for(const auto& interval : chordIntervals){
            std::cout << intervalToString(interval) << " ";
        }
        std::cout << std::endl;
    }

    void print(const std::string& chordSymbol)
    {
        std::cout << chordSymbol << "\t";
        std::vector<int> chordTones = getChordTones(chordSymbol);
        // minimizeZeroDistances(chordTones);
        // moveNthBy(chordTones, 2, -12);
        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << std::endl;
    }

    void print(int inversion = 0)
    {
        std::cout << getChordSymbol() << "_" << inversion << "\t";
        const std::vector<int>& chordTones = getChordTones(inversion);

        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << std::endl;
    }

    void printProgression(const std::vector<std::string>& progression)
    {
        for (int i = 0; i < progression.size(); i++) {
            print(progression[i]);
        }
    }

    // Is the chord expressed in roman numerals
    bool isRoman(const std::string& chordSymbol)
    {
        return chordSymbol.find_first_of("ivIV") != std::string::npos;
    }

private:
    // Function to test if string starts with anoter string. If it does then remove the prefix from the string
    static bool removePrefix(std::string& s, const std::string& prefix)
    {
        const bool test = s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
        if(test) s.erase(0,prefix.size());
        return test;
    }

    // Function to replace a substring with another substring, but only if the substring is found at the beginning of the string
    static bool replacePrefix(std::string& str, std::string from, std::string to)
    {
        if (str.find(from) == 0) {
            str.replace(0, from.length(), to);
            return true;
        }
        return false;
    }

    // Function to replace a substring with another substring, but only if the substring is found at the beginning of the string
    static bool removeAt(std::string& str, std::string from, std::string to)
    {
        if (str.find(from) == 0) {
            str.replace(0, from.length(), to);
            return true;
        }
        return false;
    }

    // Size function
    size_t size()
    {
        return chordTones.size();
    }

    // Empty function
    bool empty()
    {
        return chordTones.empty();
    }

    // Chord Symbol
    std::string      chordSymbol;
    // Chord Tones
    std::vector<int> chordTones;
    // Chord Intervals
    std::vector<Interval> chordIntervals;

    // Root Note
    int rootNote = 0;

};

// ----------------------------------------------------------------------- //
// ----------------------- ChordProgression Class ----------------------- //
// ----------------------------------------------------------------------- //
class ChordProgression 
{
public:
    ChordProgression() = default;
    // Constructor to create a chord progression from a vector of chords
    ChordProgression(const std::vector<Chord>& chords)
    {
        this->setChordProgression(chords);
    }
    // Constructor to create a chord progression from a vector of chord symbols
    ChordProgression(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        this->setChordProgression(chordSymbols, rootNote);
    }
    // Constructor to create a chord progression from a string of chord symbols
    ChordProgression(const std::string& chordSymbols, const int rootNote = 0)
    {
        this->setChordProgression(chordSymbols, rootNote);
    }

    // Function to set the chord progression from a vector of chords
    void setChordProgression(const std::vector<Chord>& chords)
    {
        this->chords = chords;
    }

    // Function to set the chord progression from a vector of chord symbols
    void setChordProgression(const std::vector<std::string>& chordSymbols, const int rootNote = 0)
    {
        chords.clear();
        for (int i = 0; i < chordSymbols.size(); i++) {
            chords.push_back(Chord(chordSymbols[i], rootNote));
        }
    }

    // Function to set the chord progression from string of chord symbols
    void setChordProgression(std::string chordSymbols, const int rootNote = 0)
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
        if(chordSymbol.size() > 0)
            chordSymbolsVector.push_back(chordSymbol);
        setChordProgression(chordSymbolsVector, rootNote);
    }

    // Function to add a chord to the progression
    void addChord(const Chord& chord)
    {
        chords.push_back(chord);
    }

    // Function to add a chord to the progression
    void addChord(const std::string& chordSymbol, int rootNote = 0)
    {
        chords.push_back(Chord(chordSymbol, rootNote));
    }

    // Function clear the progression
    void clear()
    {
        chords.clear();
    }

    // Print the chord progression
    void print()
    {
        for(auto& chord : chords) chord.print();
    }

    // Index Operator Overload
    Chord& operator[](int index)
    {
        return chords[index];
    }

    // Size function
    size_t size()
    {
        return chords.size();
    }

    // Empty function
    bool empty()
    {
        return chords.empty();
    }

private:
    std::vector<Chord> chords;
};

// ----------------------------------------------------------------------- //
// ----------------------- ChordSequencer Class -------------------------- //
class ChordSequencer {
public:
    // Constructor
    ChordSequencer() = default;

    // Function to set the chord progression
    void setChordProgression(const ChordProgression& aChordProgression)
    {
        chordProgression = aChordProgression;
        rewind();
    }

    std::vector<int> next()
    {
        // If the chord progression is empty then return an empty vector
        if(chordProgression.empty()) return {};
        // Loop through the chord progression
        if(++index >= chordProgression.size()) index = 0;
        // Return the chord tones
        return chordProgression[index].getChordTones();
    }

    // Function to reset the sequencer
    void rewind()
    {
        index = -1;
    }

private:
    ChordProgression chordProgression;
    int index = -1;
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
        createChordProgressions();
    };

    // Function to create the chord progressions
    void createChordProgressions()
    {
        // Major Chord Progressions
        chordProgressions["2-5-1"]               = ChordProgression("ii7|V7|I7");
        chordProgressions["Axis"]                = ChordProgression("I|V|vi|iv");
        chordProgressions["Axis2"]               = ChordProgression("vi|IV|I|V");
        chordProgressions["Andalusian"]          = ChordProgression("i|bVII|bVI|V");
        chordProgressions["AeolianVamp"]         = ChordProgression("i|bVII|bVI|bVII");
        chordProgressions["DooWop"]              = ChordProgression("I|vi|IV|V");
        chordProgressions["MixolydianVamp"]      = ChordProgression("I|bVII|IV|I");
        chordProgressions["PlagelCascade"]       = ChordProgression("i|bIII|bVII|IV");
        chordProgressions["RedHot1"]             = ChordProgression("i|bVII|v|bVI");
        chordProgressions["RedHot2"]             = ChordProgression("I|V|ii|IV");
        chordProgressions["RedHot3"]             = ChordProgression("IV|I|V|vi");
        chordProgressions["RedHot4"]             = ChordProgression("I|V|vi|IV");
        chordProgressions["RoyalRoad"]           = ChordProgression("I|IV|iii|vi");
        chordProgressions["KissFromARose"]       = ChordProgression("bVI|bVII|I");
        chordProgressions["SuperMarioCadence"]   = ChordProgression("I|bVI|bVII|I");
        chordProgressions["AugmentedClimb"]      = ChordProgression("I|I+|I6no5|I7no5|IV");
        chordProgressions["LastNightOnEarth"]    = ChordProgression("I|I+|I6no5|I7no5|IV|iv|I|I");
        chordProgressions["Ghibli"]              = ChordProgression("IV|V7|iii|vi");
        // Sad Chord Progressions from https://www.pianote.com/blog/sad-chord-progressions/
        chordProgressions["PopProgression"]      = ChordProgression("vi|IV|I|V");
        chordProgressions["HarmonicMinorAxis"]   = ChordProgression("vi|IV|I|III");
        chordProgressions["Creep"]               = ChordProgression("I|III|IV|iv");
        chordProgressions["HarmonicVamp"]        = ChordProgression("i|i|VI|V");
        chordProgressions["HouseOfTheRisingSun"] = ChordProgression("i|III|IV|VI");
        chordProgressions["Harmonic Shift"]      = ChordProgression("i|iv|III|V");
        chordProgressions["AeolianClosedLoop"]   = ChordProgression("i|bVII|iv|i");
        chordProgressions["LanaProgression"]     = ChordProgression("i|III|v|VI");
        chordProgressions["Emotional"]           = ChordProgression("vi|IV|V|iii");
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
    }

    // Function to add a chord progression to the map
    void addChordProgression(const std::string& chordProgression, const ChordProgression& progression)
    {
        chordProgressions[chordProgression] = progression;
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

private:
    std::map<std::string, ChordProgression> chordProgressions; // TODO: Make this into a static private member
};












} // namespace cmtk
