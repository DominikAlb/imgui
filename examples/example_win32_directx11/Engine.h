//Dolna czesc maszyny losujacej odpowiada za wprowadzanie pilek w ruch
//Maszyna dziedziczy z klasy Object
//parametr force odpowiada za moc poruszania pilek co zmienia predkosc pilek
//jesli sila bedzie za mala, grawitacja sciagnie pilki w dol

#pragma once
#include <examples/example_win32_directx11/Object.h>
template<class T = float>
class Engine: public Object<T> {
public:
    //konstruktory kopiujace
    Engine(T _x, T _y, ImVec2& _center, ImU32& _imU32, std::shared_ptr<T> _force, T _length): Object<T>(_center, _imU32, _x, _y, _length), force(_force) {}

    Engine(const Engine& other) : Object<T>(other.center, other.imU32, other.x, other.y, other.length) {}

    Engine& operator=(const Engine& other) {
        return *this = Engine(other);
    }

    void init(ImDrawList* draw) override {
        ImVec2 c(x, y);
        ImVec2 c2(x+length, y);
        draw->AddLine(c, c2, col, 10);
    }

    void setForce(T i) {
        force = i;
    }

    T getForce() {
        return *force.get();
    }

private:
    std::shared_ptr<T> force;
};
