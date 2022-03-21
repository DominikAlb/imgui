//
// Created by 01156962 on 3/17/2022.
//

#include <memory>
#include <vector>
#include "lotto/Ball.h"
#include <iostream>

class BallLogic {

private:

    static std::vector<std::unique_ptr<Ball<float>>> arr;

    void randomMove(Ball<float>* ball) {
        float _x = ball->getX() + -1 + (rand() % 3);
        ball->setX(_x);

        float _y = ball->getX() + -1 + (rand() % 3);
        ball->setX(_y);

        ImVec2 iv(_x, _y);
        ball->setCenter(iv);
    }

public:
    void move() {
        for (auto it = begin(arr); it != end(arr); ++it) {
            randomMove((*it).get());
        }
    }

    void init(float _x, float _y, float _interface_x, float _interface_y) {
        x = _x;
        y = _y;
        interface_x = _interface_x;
        interface_y = _interface_y;
    }

    static void fun(ImDrawList* draw, float* size) {

        ImU32 col = IM_COL32(255, 0, 0, 255);
        int num_segments = 100;
        float thickness = 1;
        float radius = *size;
        float weight = 1;
        ImVec2 center(x, y);

        
        for (int i = 1; i < 50; i++) {
            center = ImVec2(x, y);
            std::unique_ptr<Ball<float>> b = std::unique_ptr<Ball<float>>(new Ball<float>(center, col, num_segments, thickness, radius, weight, i, x, y));
            draw->AddCircleFilled(b->getCenter(), b->getRadius(), b->getCol(), b->getNumSegments());
            arr.push_back(std::move(b));
            std::cout << arr.size() << std::endl;
            x = x + 20;

            if (i % 5 == 0) {
                y = y + 20;
                x = x - 100;
            }
        }
    }

    static float x;
    static float y;
    static float interface_x;
    static float interface_y;
};
