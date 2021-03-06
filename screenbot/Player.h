#ifndef PLAYER_H_
#define PLAYER_H_

#include "Vector.h"
#include "Common.h"

#include <string>
#include <memory>
#include <vector>

class Player : public api::Player {
private:
    std::string m_Name;
    unsigned int m_Freq;
    unsigned short m_Rotation;
    Vec2 m_Position;
    Vec2 m_Velocity;
    unsigned short m_Pid;
    api::Ship m_Ship;
    bool m_InArena;
    unsigned char m_Status;
    
public:
    Player() 
        : m_InArena(true), m_Freq(9999), 
          m_Rotation(0), m_Pid(0), 
          m_Ship(api::Ship::Spectator),
          m_Status(0)
    { }

    Player(const std::string& name) 
        : m_Name(name), m_InArena(true), 
          m_Freq(9999), m_Rotation(0), 
          m_Pid(0), m_Ship(api::Ship::Spectator),
          m_Status(0)
    { }

    Player(const std::string& name, unsigned short freq) 
        : m_Name(name), m_Freq(freq), 
          m_InArena(true), m_Rotation(0), 
          m_Pid(0), m_Ship(api::Ship::Spectator),
          m_Status(0)
    { }

    const std::string& GetName() const { return m_Name; }
    unsigned int GetFreq() const { return m_Freq; }
    unsigned short GetRotation() const { return m_Rotation; }
    // Pixels
    Vec2 GetPosition() const { return m_Position; }
    // Pixels
    Vec2 GetVelocity() const { return m_Velocity; }
    unsigned short GetPid() const { return m_Pid; }
    api::Ship GetShip() const { return m_Ship; }
    bool InArena() const { return m_InArena; }
    unsigned char GetStatus() const { return m_Status; }

    void SetName(const std::string& name) { m_Name = name; }
    void SetFreq(unsigned int freq) { m_Freq = freq; }
    void SetRotation(unsigned short rot) { m_Rotation = rot; }
    // Pixels
    void SetPosition(int x, int y) { m_Position = Vec2(x, y); }
    // Pixels
    void SetPosition(Vec2 pos) { m_Position = pos; }
    // Pixels
    void SetVelocity(int xspeed, int yspeed) { m_Velocity = Vec2(xspeed, yspeed); }
    // Pixels
    void SetVelocity(Vec2 vel) { m_Velocity = vel; }
    void SetPid(unsigned short pid) { m_Pid = pid; }
    void SetShip(api::Ship ship) { m_Ship = ship; }
    void SetInArena(bool inarena) { m_InArena = inarena; }
    void SetStatus(unsigned char status) { m_Status = status; }

    Vec2 GetHeading() const {
        double rad = (((40 - (GetRotation() + 30)) % 40) * 9) * (M_PI / 180);
        return Vec2((float)std::cos(rad), -(float)std::sin(rad));
    }
};

//typedef shared_ptr<api::Player> api::PlayerPtr;
//typedef std::vector<api::PlayerPtr>api::PlayerList;

#endif
