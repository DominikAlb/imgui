//Gorna czesc maszyny odpowiadajaca za wylapywanie pilek
//Dziedziczy za klasy Wall oraz nadpisuje funkcje init

#pragma once
#include <examples/example_win32_directx11/Wall.h>
template<class T = float>
class Collector: public Wall<T> {
public:
    void init(ImDrawList* draw) override {
        Wall<T>::initLine(draw);
    }
    Collector(T _x, T _y, T _length, ImVec2 _center, ImU32 _imU32) : Wall<T>(_x, _y, _length, _center, _imU32){}

    Collector(const Collector& other) : Wall<T>(other) {}

    Collector(Collector&& other) {}

    Collector& operator=(const Collector& other) {
        return *this = Engine(other);
    }

    Collector& operator=(Collector&& other) noexcept {
        std::swap(center, other.center);
        std::swap(col, other.col);
        return *this;
    }

};
