// This file is part of Dust Racing 2D.
// Copyright (C) 2015 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef AI_HPP
#define AI_HPP

#include "../common/targetnodebase.hpp"
#include <MCVector2d>
#include <memory>

class Car;
class Race;
class Track;
class TrackTile;

//! Class that implements the artificial intelligence of the computer players.
class AI
{
public:
    enum class State 
    { 
        FollowRoute,   //! Normāla braukšana pa ceļu
        AvoidCollision,  //! Sadursmes novēršana
        Brake, //! Bremzēšana 
        Recover//! Atkopšanās pēc kontroles zaudēšanas
    };

    //! Constructor.
    AI(Car & car, std::shared_ptr<Race> race);

    //! Update.
    void update(bool isRaceCompleted);

    //! Set the current race track.
    void setTrack(std::shared_ptr<Track> track);

    //! Get associated car.
    Car & car() const;

    //! Iegūt pašreizējo MI stāvokli
    State getCurrentState() const;

private:
    
    //! Stāvokļa mašīnas atjaunināšana (pašreizējais stāvoklis)
    void updateState();
    
    //! FollowRoute stāvoklis
    void handleFollowRoute(TargetNodeBasePtr targetNode, TrackTile & currentTile, bool isRaceCompleted);

    //! AvoidCollision stāvoklis
    void handleAvoidCollision(TargetNodeBasePtr targetNode);
    
    //! Bremzēšanas stāvoklis
    void handleBraking(TargetNodeBasePtr targetNode, TrackTile & currentTile);
    
    //! Atkopšanas stāvoklis
    void handleRecovering(TargetNodeBasePtr targetNode);
    
    //! Pāreja uz jaunu stāvokli
    void transitionTo(State newState);

    //! Uzlabota ātruma kontrole dažādiem stāvokļiem
    void speedControlByState(TrackTile & currentTile, bool isRaceCompleted);

    //! Steering logic.
    void steerControl(TargetNodeBasePtr tnode);

    //! Brake/accelerate logic.
    void speedControl(TrackTile & currentTile, bool isRaceCompleted);

    void setRandomTolerance();

    Car & m_car;

    std::shared_ptr<Race> m_race;

    std::shared_ptr<Track> m_track;

    float m_lastDiff;

    size_t m_lastTargetNodeIndex;

    MCVector2dF m_randomTolerance;

    //! Mākslīgā intelekta pašreizējais stāvoklis
    State m_currentState;

    //! Stāvokļa taimeris stāvokļa pārejām
    float m_stateTimer;

    //! Sadursmju noteikšanas slieksnis
    float m_collisionThreshold;

    //! Atkopšanas skaitītājs
    int m_recoveryCounter;
};

typedef std::shared_ptr<AI> AIPtr;

#endif // AI_HPP
