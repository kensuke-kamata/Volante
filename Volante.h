#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Volante {
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat2 = glm::mat2;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;
    using Quat = glm::quat;

    constexpr float PI = glm::pi<float>();
    constexpr float TWO_PI = 2.0f * PI;
    constexpr float HALF_PI = PI / 2.0f;
    constexpr float GRAVITY = 9.81f;

    inline Vec3 cross(const Vec3& a, const Vec3& b) {
        return glm::cross(a, b);
    }

    inline float dot(const Vec3& a, const Vec3& b) {
        return glm::dot(a, b);
    }

    inline Vec3 normalize(const Vec3& v) {
        return glm::normalize(v);
    }

    inline float length(const Vec3& v) {
        return glm::length(v);
    }

    inline float distance(const Vec3& a, const Vec3& b) {
        return glm::distance(a, b);
    }
}