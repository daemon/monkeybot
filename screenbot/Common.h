#ifndef COMMON_H_
#define COMMON_H_

#include "api/Api.h"

#include <cstdint>
#include <memory>
#include <ostream>
#include <functional>
#include <Windows.h>

#include "Vector.h"
#include "MessageQueue.h"

#ifdef UNICODE
#include <io.h>
#include <fcntl.h>
#define tstring std::wstring
#define tstringstream std::wstringstream
#define tcout std::wcout
#define tcin std::wcin
#define tcerr std::wcerr
#define tostream std::wostream
#define tifstream std::wifstream
#define tregex std::wregex
#define tsmatch std::wsmatch
#define tsregex_iterator std::wsregex_iterator

#define to_tstring std::to_wstring
#else
#define tstring std::string
#define tstringstream std::stringstream
#define tcout std::cout
#define tcin std::cin
#define tcerr std::cerr
#define tostream std::ostream
#define tfilebuf std::filebuf
#define tifstream std::ifstream
#define tregex std::regex
#define tsmatch std::smatch
#define tsregex_iterator std::sregex_iterator

#define to_tstring std::to_string
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

class ScreenArea;
class ScreenGrabber;

using std::shared_ptr;
using std::weak_ptr;

typedef shared_ptr<ScreenGrabber> ScreenGrabberPtr;
typedef shared_ptr<ScreenArea> ScreenAreaPtr;

//namespace api { class Client; }
//typedef shared_ptr<api::Client> ClientPtr;

enum class Direction {
    Up, Down, Left, Right, None
};

namespace Ships {
    extern const u64 Rotations[8][40];
}

struct Pixel {
    u8 b;
    u8 g;
    u8 r;
    u8 a;

    Pixel() : b(0), g(0), r(0), a(0) { }
    Pixel(u8 r, u8 g, u8 b, u8 a) : b(b), g(g), r(r), a(a) { }
};


tostream& operator<<(tostream& out, const Pixel& pix);
u64 operator+(const Pixel& pix, u64 a);
bool operator==(const Pixel& first, const Pixel& second);
bool operator!=(const Pixel& first, const Pixel& second);

namespace std {
    template<>
    struct hash <Pixel> {
        size_t operator()(const Pixel& pix) const {
            u32 val = (pix.b << 24) | (pix.g << 16) | (pix.r << 8) | pix.a;
            return val;
        }
    };
}

namespace Colors {
    extern const Pixel RadarColor;
    extern const Pixel RadarEnd;
    extern const Pixel RadarBorder;
    extern const Pixel RadarWall;
    extern const Pixel SafeColor;
    extern const Pixel EnemyColor[2];
    extern const Pixel EnemyBallColor;
    extern const Pixel EnergyColor[2];
    extern const Pixel XRadarOn;
    extern const Pixel XRadarOff;
    extern const Pixel MultiNone;
    extern const Pixel MultiOff;
    extern const Pixel BulletBounceColor;
}

class Font;

namespace Fonts {
    extern Font* TallFont;
}

tostream& operator<<(tostream& out, const Vec2& vec);

#endif
