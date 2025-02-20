#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Chord.h"
// Include std::pair
#include <utility>

namespace cmtk {


class ChordArp {
public:
    enum class Style {
        Up,
        Down,
        UpDown
    };

    ChordArp(){
        mChordPtr = nullptr;
    };

    ChordArp(Chord* chordPtr) {
        mChordPtr = chordPtr;
    }

    void reset()
    {
        mStep = 0;
        mCounter = 0;
        switch(mStyle) {
            case Style::Up:
                mUp = true;
                break;
            case Style::Down:
                mUp = false;
                break;
            case Style::UpDown:
                mUp = true;
                break;
        }
    };

    Note next() {
        if(!mChordPtr) return Note();

        Note note;
        bool restart = false;
        auto steps = mSteps > 0 ? mSteps : mChordPtr->size();

        switch(mStyle) {
            case Style::Up:{
                if(mStep >= steps) mStep = 0;
                restart = (mStep == 0);
                note = mChordPtr->getNoteAt(mStep*mJump);
                mStep++;
            }
            break;
            case Style::Down:{
                if(mStep >= steps) mStep = 0;
                restart = (mStep == 0);
                note = mChordPtr->getNoteAt((steps-mStep-1)*mJump);
                mStep++;
            }
            break;
            case Style::UpDown:{
                if(mStep == steps-1) mUp = false;
                restart = (mStep == 0);
                if(restart) mUp = true;
                note = mChordPtr->getNoteAt(mStep * mJump);
                if(mUp) mStep++;
                else    mStep--;
            }
            break;
        }
        // Update the Restart Counter
        if(restart) mCounter++;

        // Update the Octave
        note.setOctave(note.getOctave() + getOctave());

        return note;
    }

    Note next(Chord& chord) {
        setChordPtr(&chord);
        return next();
    }

    ChordArp& setStyle(std::string aStyle){
        if     (aStyle == "Up"    ) mStyle = Style::Up;
        else if(aStyle == "Down"  ) mStyle = Style::Down;
        else if(aStyle == "UpDown") mStyle = Style::UpDown;
        return *this;
    }

    std::string getStyle() const {
        switch(mStyle) {
            case Style::Up:     return "Up";
            case Style::Down:   return "Down";
            case Style::UpDown: return "UpDown";
        }
        return "";
    }

    ChordArp& setStyle(Style aStyle) {
        this->mStyle = aStyle;
        return *this;
    }

    void getStyle(Style& aStyle) {
        aStyle = mStyle;
    }

    ChordArp& setSteps(int aSteps) {
        this->mSteps = aSteps;
        return *this;
    }

    int getSteps() const {
        return mSteps;
    }

    ChordArp& setJump(int aJump) {
        this->mJump = aJump;
        return *this;
    }

    int getJump() const {
        return mJump;
    }

    ChordArp& setOctaves(int aOctaves) {
        this->mOctaves = aOctaves;
        return *this;
    }

    int getOctaves() const {
        return mOctaves;
    }

    Note operator++() {
        return next();
    }

    // SetChord
    ChordArp& setChordPtr(Chord* chordPtr) {
        mChordPtr = chordPtr;
        return *this;
    }

    Chord* getChordPtr() {
        return mChordPtr;
    }

protected:
    int getOctave() const {
        if(mOctaves > 0) return  (mCounter-1)%(mOctaves+1);
        if(mOctaves < 0) return -(mCounter-1)%(1-mOctaves); 
        return 0;
    }

    Style mStyle = Style::Up;
    int mJump = 1;
    int mSteps = 0;
    int mOctaves = 0;
    
    // State Variables
    Chord* mChordPtr = nullptr;
    int mStep = 0;
    int mCounter = 0;
    bool mUp = true;

};


} // namespace cmtk