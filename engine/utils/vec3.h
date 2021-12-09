//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_DATA_VEC3_H_
#define FINAL_PROJECT_ENGINE_DATA_VEC3_H_

namespace AGE {

template<typename T>
class vec3 {
  public:
    T x;
    T y;
    T z;
    vec3() : x{0}, y{0}, z{0} {}
    vec3(T x, T y, T z) : x{x}, y{y}, z{z} {}
    vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}
    vec3 &operator=(const vec3 &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    vec3 operator+(const vec3 &v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }
    vec3 &operator+=(const vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    vec3 operator-(const vec3 &v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }
    vec3 &operator-=(const vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
};

}

#endif //FINAL_PROJECT_ENGINE_DATA_VEC3_H_
