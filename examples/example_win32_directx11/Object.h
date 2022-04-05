#pragma once
//
// Created by 01156962 on 3/17/2022.
//
//Podstawowy obiekt - jesli cos ma zostac wyswietlone na ekranie, powinno byc dziedziczone przez klase Object
//Posiada klase wirtualna init do wyswietlania obiektu
//ImVec2 - to polozenie (x, y) do sterowania w bibliotece ImGUI
//ImU32 - kolor obiektu
//length - dlugosc (lub promien obiektu)
//x, y - parametry do polozenia na osi (x, y)

#include <cstddef>
#include <vector>
#include "../imgui.h"

#ifndef IMGUI_BALL_H
#define IMGUI_BALL_H

#endif //IMGUI_BALL_H

template<class T = float> class Object {

protected:
    ImVec2& center;
    ImU32& col;
    T length;
    T x;
    T y;

public:
    Object(ImVec2& _imVec2, ImU32& _col, T _x, T _y, T _length) : center(_imVec2), col(_col), x(_x), y(_y), length(_length) {}

    virtual void init(ImDrawList* draw) = 0;

    const ImVec2& getCenter() const {
        return center;
    }

    void setCenter(const ImVec2& imVec2) {
        center = imVec2;
    }

    ImU32 getCol() const {
        return col;
    }

    void setCol(ImU32 u32) {
        col = u32;
    }

    T getLength() const {
        return length;
    }

    void setLength(T size) {
        length = size;
    }

    T getX() const {
        return x;
    }

    void setX(T i) {
        x = i;
    }

    T getY() const {
        return y;
    }

    void setY(T i) {
        y = i;
    }
};
