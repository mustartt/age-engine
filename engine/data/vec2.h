//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_DATA_VEC2_H_
#define FINAL_PROJECT_ENGINE_DATA_VEC2_H_

namespace AGE {

template<typename T>
class vec2 {
    T x;
    T y;
    vec2() : x{0}, y{0} {}
    vec2(T x, T y) : x{x}, y{y} {}
    vec2(const vec2 &v) : x(v.x), y(v.y) {}

    vec2 &operator=(const vec2 &v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    vec2 operator+(vec2 &v) {
        return vec2(x + v.x, y + v.y);
    }
    vec2 operator-(vec2 &v) {
        return vec2(x - v.x, y - v.y);
    }

    template<typename D>
    vec2 operator+(D s) {
        return vec2(x + s, y + s);
    }
    template<typename D>
    vec2 operator-(D s) {
        return vec2(x - s, y - s);
    }
    template<typename D>
    vec2 operator*(D s) {
        return vec2(x * s, y * s);
    }
    template<typename D>
    vec2 operator/(D s) {
        return vec2(x / s, y / s);
    }
};

}

#endif //FINAL_PROJECT_ENGINE_DATA_VEC2_H_
