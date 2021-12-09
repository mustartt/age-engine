//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_DATA_VEC2_H_
#define FINAL_PROJECT_ENGINE_DATA_VEC2_H_

#include <ostream>
namespace AGE {

template<typename T>
class vec2 {
  public:
    T x;
    T y;
    vec2() : x{0}, y{0} {}
    vec2(T x, T y) : x{x}, y{y} {}
    vec2(const vec2 &v) : x(v.x), y(v.y) {}
    vec2<T> &operator=(const vec2<T> &v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    vec2<T> operator+(const vec2<T> &v) const {
        return vec2(x + v.x, y + v.y);
    }
    vec2<T> operator-(const vec2<T> &v) const {
        return vec2(x - v.x, y - v.y);
    }
    vec2<T> operator+(T s) const {
        return vec2(x + s, y + s);
    }
    vec2<T> operator-(T s) const {
        return vec2(x - s, y - s);
    }
    vec2<T> operator*(T s) {
        return vec2(x * s, y * s);
    }
    vec2<T> operator/(T s) {
        return vec2(x / s, y / s);
    }
    friend std::ostream &operator<<(std::ostream &os, const vec2 &vec2) {
        os << "(x: " << vec2.x << ", y: " << vec2.y << ")";
        return os;
    }
};

}

#endif //FINAL_PROJECT_ENGINE_DATA_VEC2_H_
