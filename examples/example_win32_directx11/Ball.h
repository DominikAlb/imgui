#pragma once
//
// Created by 01156962 on 3/17/2022.
//
//Podstawowy obiekt Ball jest pilka w grze
//Kazda pilka posiada swoje polozenie
//Pilka dziedziczy z Object, klasa init jest nadpisana
//Pilka posiada swoja elastycznosc, wage i promien

#include <cstddef>
#include <vector>
#include "../imgui.h"
#include <examples/example_win32_directx11/Object.h>

#ifndef IMGUI_BALL_H
#define IMGUI_BALL_H

#endif //IMGUI_BALL_H

template<class T = float> class Ball: public Object<T> {

private:
    int num_segments;
    T thickness;
    T radius;
    T weight;
    int number;
    T elasticity;
    T angleX;
    T angleY;
    ImVec2& angle;
    Ball() = default;

public:
    Ball(ImVec2& imVec2_, ImU32& col_, int num_segments_, T thickness_, T radius_, T weight_, int number_, T x_, T y_, ImVec2& _angle, T _elasticity, T _angleX, T _angleY) : num_segments(num_segments_), thickness(thickness_),
        radius(radius_), weight(weight_), number(number_), angle(_angle), elasticity(_elasticity), angleX(_angleX), angleY(_angleY), Object<T>(imVec2_, col_, x_, y_, radius_) {}

    void init(ImDrawList* draw) override {
        draw->AddCircleFilled(center, radius, col, num_segments);
    }

    int getNumSegments() const {
        return num_segments;
    }

    void setNumSegments(int numSegments) {
        num_segments = numSegments;
    }

    T getThickness() const {
        return thickness;
    }

    void setThickness(T size) {
        Ball::thickness = size;
    }

    T getRadius() const {
        return radius;
    }

    void setRadius(T size) {
        Ball::radius = size;
    }

    T getWeight() const {
        return weight;
    }

    void setWeight(T size) {
        Ball::weight = size;
    }

    int getNumber() const {
        return number;
    }

    void setNumber(int size) {
        Ball::number = size;
    }

    T getElasticity() const {
        return elasticity;
    }

    void setElasticity(T i) {
        Ball::elasticity = i;
    }

    T getAngleX() const {
        return angleX;
    }

    void setAngleX(T i) {
        Ball::angleX = i;
    }

    T getAngleY() const {
        return angleY;
    }

    void setAngleY(T i) {
        Ball::angleY = i;
    }

    const ImVec2& getAngle() const {
        return angle;
    }

    void setAngle(ImVec2& i) {
        Ball::angle = i;
    }
};
