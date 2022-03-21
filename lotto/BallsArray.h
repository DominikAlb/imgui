//
// Created by 01156962 on 3/17/2022.
//
/*#include <vector>
#include <cstddef>
#include <memory>

#ifndef IMGUI_BALLS_H
#define IMGUI_BALLS_H

#endif //IMGUI_BALLS_H

template<class T> class BallsArray {

    //typedef std::vector<std::unique_ptr<T>> ball_type;
    typedef std::vector<T> ball_type;
protected:
    ball_type balls{};
    
public:
    void deallocate(){
        for (auto it = balls.begin(); it != std::end(balls); ++it) {
            delete it;
        }
    };
    int size() const {return balls->size() ;};
    virtual void addBall(T ball) = 0;
    virtual void init() = 0;
};
*/
