//
// Created by galex on 7/17/2020.
//

#ifndef OPENGL_SANDBOX_VECTOR_H
#define OPENGL_SANDBOX_VECTOR_H

#include <array>

struct Vector2D {
    float& r() { return values[0]; }
    float& g() { return values[1]; }

    float& u() { return values[0]; }
    float& v() { return values[1]; }

    float& x() { return values[0]; }
    float& y() { return values[1]; }

    float r() const { return values[0]; }
    float g() const { return values[1]; }

    float u() const { return values[0]; }
    float v() const { return values[1]; }

    float x() const { return values[0]; }
    float y() const { return values[1]; }

    Vector2D(float x, float y) {
        values[0] = x;
        values[1] = y;
    }

private:
    std::array<float,2> values;
};

struct Vector2DInt {
    int& r() { return values[0]; }
    int& g() { return values[1]; }

    int& u() { return values[0]; }
    int& v() { return values[1]; }

    int& x() { return values[0]; }
    int& y() { return values[1]; }

    int r() const { return values[0]; }
    int g() const { return values[1]; }

    int u() const { return values[0]; }
    int v() const { return values[1]; }

    int x() const { return values[0]; }
    int y() const { return values[1]; }

    Vector2DInt(int x, int y) {
        values[0] = x;
        values[1] = y;
    }

private:
    std::array<int,2> values;
};

struct Vector3D {
    float& r() { return values[0]; }
    float& g() { return values[1]; }
    float& b() { return values[2]; }

    float& x() { return values[0]; }
    float& y() { return values[1]; }
    float& z() { return values[2]; }

    float r() const { return values[0]; }
    float g() const { return values[1]; }
    float b() const { return values[2]; }

    float x() const { return values[0]; }
    float y() const { return values[1]; }
    float z() const { return values[2]; }

    Vector3D(float x, float y, float z) {
        values[0] = x;
        values[1] = y;
        values[2] = z;
    }

private:
    std::array<float,3> values;
};

struct Vector3DInt {
    int& r() { return values[0]; }
    int& g() { return values[1]; }
    int& b() { return values[2]; }

    int& x() { return values[0]; }
    int& y() { return values[1]; }
    int& z() { return values[2]; }

    int r() const { return values[0]; }
    int g() const { return values[1]; }
    int b() const { return values[2]; }

    int x() const { return values[0]; }
    int y() const { return values[1]; }
    int z() const { return values[2]; }

    Vector3DInt(int x, int y, int z) {
        values[0] = x;
        values[1] = y;
        values[2] = z;
    }

private:
    std::array<int,3> values;
};

struct Vector4D {
    float& r() { return values[0]; }
    float& g() { return values[1]; }
    float& b() { return values[2]; }
    float& a() { return values[3]; }

    float& x() { return values[0]; }
    float& y() { return values[1]; }
    float& z() { return values[2]; }
    float& w() { return values[3]; }

    float& u() { return values[2]; }
    float& v() { return values[3]; }

    float r() const { return values[0]; }
    float g() const { return values[1]; }
    float b() const { return values[2]; }
    float a() const { return values[3]; }

    float x() const { return values[0]; }
    float y() const { return values[1]; }
    float z() const { return values[2]; }
    float w() const { return values[3]; }

    float u() const { return values[2]; }
    float v() const { return values[3]; }

    Vector4D(float x, float y, float z, float w) {
        values[0] = x;
        values[1] = y;
        values[2] = z;
        values[3] = w;
    }

private:
    std::array<float,4> values;
};

struct Vector4DInt {
    int& r() { return values[0]; }
    int& g() { return values[1]; }
    int& b() { return values[2]; }
    int& a() { return values[3]; }

    int& x() { return values[0]; }
    int& y() { return values[1]; }
    int& z() { return values[2]; }
    int& w() { return values[3]; }

    int& u() { return values[2]; }
    int& v() { return values[3]; }

    int r() const { return values[0]; }
    int g() const { return values[1]; }
    int b() const { return values[2]; }
    int a() const { return values[3]; }

    int x() const { return values[0]; }
    int y() const { return values[1]; }
    int z() const { return values[2]; }
    int w() const { return values[3]; }

    int u() const { return values[2]; }
    int v() const { return values[3]; }

    Vector4DInt(int x, int y, int z, int w) {
        values[0] = x;
        values[1] = y;
        values[2] = z;
        values[3] = w;
    }

private:
    std::array<int,4> values;
};

#endif //OPENGL_SANDBOX_VECTOR_H
