//
// Created by 01156962 on 3/17/2022.
//

#include <cstddef>
#include <vector>
#include "../imgui.h"

#ifndef IMGUI_BALL_H
#define IMGUI_BALL_H

#endif //IMGUI_BALL_H

template<class T = float> class Ball {

private:
    ImVec2& center;
    ImU32& col;
    int num_segments;
    T thickness;
    T radius;
    T weight;
    int number;
    T x;
    T y;
    Ball() = default;

public:
    Ball(ImVec2& imVec2_, ImU32& col_, int num_segments_, T thickness_, T radius_, T weight_, int number_, T x_, T y_): center(imVec2_), col(col_), num_segments(num_segments_), thickness(thickness_),
    radius(radius_), weight(weight_), number(number_), x(x_), y(y_) {}
    const ImVec2 &getCenter() const {
        return center;
    }

    void setCenter(const ImVec2 &imVec2) {
        Ball::center = imVec2;
    }

    ImU32 getCol() const {
        return col;
    }

    void setCol(ImU32 u32) {
        Ball::col = u32;
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

    T getX() const {
        return x;
    }

    void setX(T i) {
        Ball::x = i;
    }

    T getY() const {
        return y;
    }

    void setY(T i) {
        Ball::y = i;
    }
};
