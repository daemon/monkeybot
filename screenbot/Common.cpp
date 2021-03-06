#include "Common.h"

#include "Font.h"

namespace Fonts {

Font* TallFont = nullptr;

} // ns

tostream& operator<<(tostream& out, const Pixel& pix) {
    out << "(" << (int)pix.r << ", " << (int)pix.g << ", " << (int)pix.b << ", " << (int)pix.a << ")";
    return out;
}

u64 operator+(const Pixel& pix, u64 a) {
    return ((pix.r << 16) | (pix.g << 8) | (pix.b)) + a;
}

bool operator==(const Pixel& first, const Pixel& second) {
    return first.r == second.r && first.g == second.g &&
        first.b == second.b;
}

bool operator!=(const Pixel& first, const Pixel& second) {
    return !(first == second);
}

tostream& operator<<(tostream& out, const Vec2& vec) {
    return out << "(" << vec.x << ", " << vec.y << ")";
}
