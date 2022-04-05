
//
// Created by 01156962 on 3/17/2022.
//

//Logika kolektora
//Odpowiada za wszystkie sytuacje zwiazane z kolizjami obiektow, grawitacja, sila oraz zmiane rotacji
//Funkcje z klasy Collision zostaly przeniesione do klasy Logic
//Logic zapamietuje pilki w kolektorze oraz wyswietla je za pomoca funkcji init
//Klasa Logic zapamietuje rowniez liczby zlapane przez Collector
//Klasa posiada rowniez parametry x, y aby wyswietlic pilki w trakcie restartu gry

#pragma once
#include <memory>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "imgui.h"
#include "examples/example_win32_directx11/Engine.h"
#include "examples/example_win32_directx11/Ball.h"
#include "examples/example_win32_directx11/Collector.h"

template<class T = float>
class Logic {

private:

    static std::vector<std::shared_ptr<Ball<T>>> arr;
    static std::shared_ptr<T> gravity;
    static T x;
    static T y;
    static Engine<T> engine;
    static Collector<T> collector;
    static Wall<T> wall;

public:
    Logic() {}
    Logic(const Logic& other) {}
    Logic(Logic&& other) {}

    Logic& operator=(const Logic& other) {
        return *this = Logic(other);
    }

    static void restart() {
        x = 170;
        y = 170;
        arr.clear();
        wonNumbers.clear();
    }

    void move() {
        for (auto it = begin(arr); it != end(arr); ++it) {
            randomMove((*it).get());
        }
    }

    static void checkRotation(Ball<T>* ball, Wall<T>& wall) {

        int wallCollision = checkWallCollision(*ball, wall, engine.getForce());
        if (wallCollision == 1) {
            changeRotation(ball, 1, -1);
        }
        else if (wallCollision == -1) {
            changeRotation(ball, -1, 1);
        }
        for (auto it = begin(arr); it != end(arr); ++it) {
            if (checkBallCollision(*ball, *(*it).get())) {
                bounceBall(ball, (*it).get());
            }
        }
    }

    static void bounceBall(Ball<T>* ball1, Ball<T>* ball2) {
        T x1 = ball1->getX();
        T y1 = ball1->getY();
        T x2 = ball2->getX();
        T y2 = ball2->getY();
        if (x1 == x2 && y1 == y2) {
            return;
        }
        T r1 = randomNumber(-1, 1);
        T r2 = randomNumber(-1, 1);
        T r3 = randomNumber(-1, 1);
        T r4 = randomNumber(-1, 1);
        T angleX1 = r1;
        T angleY1 = r2;
        T angleX2 = r3;
        T angleY2 = r4;
        ball1->setAngleX(angleX1);
        ball1->setAngleY(angleY1);
        ball1->setAngle(ImVec2(angleX1, angleY1));
        ball2->setAngleX(angleX2);
        ball2->setAngleY(angleY2);
        ball2->setAngle(ImVec2(angleX2, angleY2));
    }

    static T randomNumber(float Min, float Max) {
        return ((T(rand()) / T(RAND_MAX)) * (Max - Min)) + Min;
    }

    static void moveWithCollision() {

        for (auto it = arr.begin(); it != arr.end(); ++it) {
            gravityRun((*it).get(), wall);
            engineRun((*it).get());
            checkRotation((*it).get(), wall);

            if (checkCollectorCollision(*(*it).get(), collector, engine.getForce())) {
                Ball<float>* b = std::move((*it).get());
                wonNumbers.push_back(b->getNumber());
                arr.erase(std::remove(arr.begin(), arr.end(), *it));
                if (wonNumbers.size() == 6) {
                    return;
                }
            }
        }
    }

    static void changeRotation(Ball<T>* ball, T rotationX, T rotationY) {
        T angleBallX = ball->getAngleX();
        T angleBallY = ball->getAngleY();
        x = angleBallX * rotationX;
        y = angleBallY * rotationY;
        ImVec2 iv(x, y);
        ball->setAngle(iv);
        ball->setAngleX(x);
        ball->setAngleY(y);
    }

    static void gravityRun(Ball<T>* ball, Wall<T>& wall) {
        ImVec2 ballPosition = ball->getCenter();
        T x = ball->getX();
        T y = ball->getY();
        if (y + *gravity.get() - ball->getAngleY() * engine.getForce() >= wall.getY()) {
            y += *gravity.get();
        } else {
            y += *gravity.get() - ball->getAngleY() * engine.getForce();
        }
        
        ImVec2 iv(x, y);
        ball->setY(y);
        ball->setCenter(iv);
    }

    static void engineRun(Ball<T>* ball) {

        T engineX = engine.getX() + engine.getLength();
        T engineY = engine.getY();

        T x = ball->getX();
        T y = ball->getY();

        T angleX = ball->getAngleX();
        T angleY = ball->getAngleY();
        T angleSinX = sin(x / engineX);
        T angleSinY = sin(y / engineY);
        if (ball->getX() - ball->getRadius() <= wall.getX()) {
            x += (wall.getLength() * 3) / 4;
        }
        if (ball->getX() + ball->getRadius() >= wall.getX() + wall.getLength()) {
            x -= (wall.getLength() * 3) / 4;
        }
        if (ball->getY() + ball->getRadius() >= wall.getY() + wall.getLength()) {
            y -= (wall.getLength() * 3) / 4;
        }
        x -= fabsf(engine.getForce() * angleSinX) * angleX;
        y -= fabsf(engine.getForce() * angleSinY) * angleY;

        //ball->setX(x1);
        ImVec2 iv(x, y);
        ball->setY(y);
        ball->setX(x);
        ball->setCenter(iv);
    }

    void init(ImDrawList* draw, T* size) {

        if (arr.size() == 0) {
            ImU32 col = IM_COL32(255, 0, 0, 255);
            int num_segments = 100;
            T thickness = 1;
            T radius = *size;
            T weight = 1;
            ImVec2 center(x, y);

            for (int i = 1; i < 50; i++) {
                center = ImVec2(x, y);
                ImVec2 angle = ImVec2(0, 0);
                std::shared_ptr<Ball<T>> b = std::shared_ptr<Ball<T>>(new Ball<T>(center, col, num_segments, thickness, radius, weight, i, x, y, angle, 0.6, 1, 1));
                draw->AddCircleFilled(b->getCenter(), b->getRadius(), b->getCol(), b->getNumSegments());
                arr.push_back(std::move(b));
                x = x + 30;

                if (i % 5 == 0) {
                    y = y + 20;
                    x = x - 150;
                }
            }
            std::random_shuffle(arr.begin(), arr.end());
        }
        else {
            for (auto it = begin(arr); it != end(arr); ++it) {
                ImVec2 center((*it).get()->getX(), (*it).get()->getY());
                draw->AddCircleFilled(center, *size, col);
            }
        }
    }

    static bool checkBallCollision(const Ball<T>& ball1, const Ball<T>& ball2) {

        T dx = ball1.getX() - ball2.getX();
        T dy = ball1.getY() - ball2.getY();
        T distance = sqrt(dx * dx + dy * dy);

        return distance < ball1.getRadius() + ball2.getRadius();
    }

    static int checkWallCollision(Ball<T>& ball, Wall<T>& wall, T speed) {
        if (ball.getY() + speed + ball.getRadius() >= wall.getY() + wall.getLength() ||
            ball.getY() - ball.getRadius() - speed <= wall.getY()) {
            return 1;
        }
        else if (
            ball.getX() + speed + ball.getRadius() >= wall.getX() + wall.getLength() ||
            ball.getX() - ball.getRadius() - speed <= wall.getX()) {
            return -1;
        }
        return 0;
    }

    static bool checkCollectorCollision(Ball<T>& ball, Collector<T>& collector, T speed) {
        return (ball.getY() - speed - ball.getRadius() <= collector.getY() &&
            ball.getX() - speed - ball.getRadius() <= collector.getX() + collector.getLength() &&
            ball.getX() + ball.getRadius() + speed >= collector.getX());
    }
    
    static std::vector<int> wonNumbers;
};
