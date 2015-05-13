#ifndef CLIENT_H_
#define CLIENT_H_

#include "Common.h"
#include "Config.h"
#include "Keyboard.h"
#include "PlayerList.h"

#include <Windows.h>
#include <vector>
#include <unordered_map>

class Level;

enum class GunState {
    Tap,
    Constant,
    Off
};

class Client {
public:
    Client() { }
    virtual ~Client() { }

    virtual void Update(DWORD dt) = 0;

    virtual void Bomb() = 0;
    virtual void Gun(GunState state, int energy_percent = 100) = 0;
    virtual void Burst() = 0;
    virtual void Repel() = 0;
	virtual void Decoy() = 0;
    virtual void SetThrust(bool on) = 0;

    virtual void SetXRadar(bool on) = 0;
    virtual void Warp() = 0;
    
    virtual int GetEnergy() = 0;
    virtual int GetRotation() = 0;
    virtual bool InSafe(Vec2 real_pos, const Level& level) = 0;

    virtual void Up(bool val) = 0;
    virtual void Down(bool val) = 0;
    virtual void Left(bool val) = 0;
    virtual void Right(bool val) = 0;

    virtual void Attach() = 0;

    virtual bool InShip() const = 0;
    virtual void EnterShip(int num) = 0;
    virtual void Spec() = 0;

    virtual std::vector<PlayerPtr> GetEnemies(Vec2 real_pos, const Level& level) = 0;
    virtual PlayerPtr GetClosestEnemy(Vec2 real_pos, Vec2 heading, const Level& level, int* dx, int* dy, double* dist) = 0;

    virtual Vec2 GetRealPosition(Vec2 bot_pos, Vec2 target, const Level& level) = 0;

    virtual void ReleaseKeys() = 0;
    virtual void ToggleKeys() = 0;

    virtual int GetFreq() = 0;

    virtual PlayerList GetFreqPlayers(int freq) = 0;
    virtual PlayerList GetPlayers() = 0;

    virtual bool OnSoloFreq() = 0;
    virtual PlayerPtr GetSelectedPlayer() = 0;
    virtual void MoveTicker(Direction dir) = 0;

    virtual std::vector<Vec2> FindMines(Vec2 bot_pixel_pos) = 0;

    virtual void Scan() = 0;

    virtual bool Emped() = 0;

    virtual void SendString(const std::string& str) = 0;
    virtual void UseMacro(short num) = 0;

    virtual void SelectPlayer(const std::string& name) = 0;

    virtual void SetTarget(const std::string& name) = 0;
    virtual void SetPriorityTarget(const std::string& name) = 0;
    virtual std::string GetPriorityTarget() const = 0;
};

namespace Ships {
    class RotationStore;
}

namespace Memory {
    class MemorySensor;
}

class ScreenClient : public Client {
private:
    Config& m_Config;
    Keyboard m_Keyboard;
    HWND m_Window;

    ScreenGrabberPtr m_Screen;
    ScreenAreaPtr m_Radar;
    ScreenAreaPtr m_Ship;
    ScreenAreaPtr m_Player;
    ScreenAreaPtr m_EnergyArea[5];
    PlayerWindow m_PlayerWindow;

    typedef std::function<void(ScreenGrabberPtr, int, int)> PixelHandler;
    std::unordered_map<Pixel, PixelHandler> m_PixelHandlers;

    std::string m_Target;
    std::string m_PriorityTarget;

    Memory::MemorySensor& m_MemorySensor;

    int m_CurrentBulletDelay;

    DWORD m_LastBullet;
    DWORD m_LastBomb;
    DWORD m_EmpEnd;

    bool m_Thrusting;

    Ships::RotationStore* m_Rotations;

    void GrabRadar();
public:
    ScreenClient(HWND hwnd, Config& config, Memory::MemorySensor& memsensor);

    virtual void Update(DWORD dt);

    virtual void Bomb();
    virtual void Gun(GunState state, int energy_percent = 100);
    virtual void Burst();
    virtual void Repel();
	virtual void Decoy();
    virtual void SetThrust(bool on);

    virtual void SetXRadar(bool on);
    virtual void Warp();

    virtual int GetEnergy();
    virtual int GetRotation();
    virtual bool InSafe(Vec2 real_pos, const Level& level);

    virtual void Up(bool val);
    virtual void Down(bool val);
    virtual void Left(bool val);
    virtual void Right(bool val);

    virtual void Attach();

    virtual bool InShip() const;
    virtual void EnterShip(int num);
    virtual void Spec();

    virtual std::vector<PlayerPtr> GetEnemies(Vec2 real_pos, const Level& level);
    virtual PlayerPtr GetClosestEnemy(Vec2 real_pos, Vec2 heading, const Level& level, int* dx, int* dy, double* dist);

    virtual Vec2 GetRealPosition(Vec2 bot_pos, Vec2 target, const Level& level);

    virtual void ReleaseKeys();
    virtual void ToggleKeys();

    virtual int GetFreq();

    virtual PlayerList GetFreqPlayers(int freq);
    virtual PlayerList GetPlayers();

    virtual bool OnSoloFreq();
    virtual PlayerPtr GetSelectedPlayer();
    virtual void MoveTicker(Direction dir);

    ScreenAreaPtr GetRadar() { return m_Radar; }

    virtual std::vector<Vec2> FindMines(Vec2 bot_pixel_pos);

    void EMPPixelHandler(ScreenGrabberPtr screen, int x, int y);
    virtual void Scan();

    virtual bool Emped();

    virtual void SendString(const std::string& str);
    virtual void UseMacro(short num);

    virtual void SelectPlayer(const std::string& name);

    virtual void SetTarget(const std::string& name);
    virtual void SetPriorityTarget(const std::string& name);

    virtual std::string GetPriorityTarget() const {
        return m_PriorityTarget;
    }
};

#endif
