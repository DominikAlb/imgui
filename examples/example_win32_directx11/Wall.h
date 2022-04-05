//Sciany szyny losujacej
//Towrzy kwadrat, ktory ma za zadanie ograniczyc pole pilek
//Dziedziczy z klasy Object oraz nadpisuje funkcje init

#pragma once
#include <cstddef>
#include <vector>
#include "../imgui.h"
#include "../imgui.h"
#include "examples/example_win32_directx11/Object.h"

#ifndef IMGUI_BALL_H
#define IMGUI_BALL_H

#endif //IMGUI_BALL_H

template<class T = float>
class Wall : public Object<T> {
public:
    Wall(T _x, T _y, T _length, ImVec2& _center, ImU32& _imU32) : Object<T>(_center, _imU32, _x, _y, _length) {}

    Wall(const Wall& other) : x(other.x), y(other.y), center(other.center), col(other.col), length(other.length) {}

    Wall(Wall&& other) {}

    Wall& operator=(const Wall& other) {
        return *this = Engine(other);
    }

    Wall& operator=(Wall&& other) noexcept {
        std::swap(x, other.x);
        std::swap(y, other.y);
        std::swap(center, other.center);
        std::swap(col, other.col);
        std::swap(length, other.length);
        return *this;
    }

    void init(ImDrawList* draw) override {
        ImVec2 c(x, y);
        ImVec2 c2(x + length, y + length);
        ImDrawFlags corners_tl_br = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight;
        col = IM_COL32(255, 0, 0, 255);
        draw->AddRect(c, c2, col, 0, corners_tl_br, 2);
    }

    void initLine(ImDrawList* draw) {
        ImVec2 c(x, y);
        ImVec2 c2(x + length, y);
        col = IM_COL32(222, 55, 0, 222);
        draw->AddLine(c, c2, col, 10);
    }
};
