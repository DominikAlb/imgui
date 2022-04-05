#pragma once
//
// Created by 01156962 on 3/17/2022.
//
//Klasa Menu posiada parametry, ktore odpowiadaja za sterowanie interfejsem
//W ten sposob pozbyto sie parametrow w klasie Interfejs
//surowe wskazniki zastaly zastapione std::shared_ptr

#include <vector>
#include <memory>

class Menu {

private:
    std::shared_ptr<bool> lottoInterface;
    std::shared_ptr<bool> runGame;
    std::shared_ptr<bool> gameWindow;
    std::shared_ptr<bool> win;
    std::shared_ptr<bool> endGame;
    std::shared_ptr<std::vector<int>> inputNumbers;
    std::shared_ptr<float> force;
    std::shared_ptr<float> ballsSize;
    std::shared_ptr<float> gravity;

public:
    Menu(bool _lottoInterface, bool _runGame, bool _gameWindow, bool _win, bool _endGame, std::vector<int>& _inputNumbers, float _force, float _gravity, float _ballsSize):
        lottoInterface(std::make_shared<bool>(_lottoInterface)), runGame(std::make_shared<bool>(_runGame)), gameWindow(std::make_shared<bool>(_gameWindow)),
        win(std::make_shared<bool>(_win)), endGame(std::make_shared<bool>(_endGame)), inputNumbers(std::make_shared<std::vector<int>>(_inputNumbers)),
        force(std::make_shared<float>(_force)), ballsSize(std::make_shared<float>(_ballsSize)), gravity(std::make_shared<float>(_gravity)) {};

    bool* getLottoInterface() {
        return lottoInterface.get();
    }

    bool* getRunGame() {
        return runGame.get();
    }

    bool* getWin() {
        return win.get();
    }

    bool* getEndGame() {
        return endGame.get();
    }

    bool* getGameWindow() {
        return gameWindow.get();
    }


    std::shared_ptr<std::vector<int>> getInputNumbersPtr() {
        return inputNumbers;
    }

    int getInputNumber(int i) {
        return (*inputNumbers.get()).at(i);
    }

    void pushBackInputNumber(int i) {
        (*inputNumbers.get()).push_back(i);
    }

    float* getForce() {
        return force.get();
    }

    float* getGravity() {
        return gravity.get();
    }

    float* getBallsSize() {
        return ballsSize.get();
    }

    void setLottoInterface(bool b) {
        *lottoInterface.get() = b;
    }

    void setRunGame(bool b) {
        *runGame.get() = b;
    }

    void setGameWindow(bool b) {
        *gameWindow.get() = b;
    }

    void setWin(bool b) {
        *win.get() = b;
    }

    void setEndGame(bool b) {
        *endGame.get() = b;
    }

    void setForce(float f) {
        *force.get() = f;
    }

    void setGravity(float f) {
        *gravity.get() = f;
    }

    void setBallsSize(float f) {
        *ballsSize.get() = f;
    }

    std::shared_ptr<float> getForcePtr() {
        return force;
    }

    std::shared_ptr<float> getGravityPtr() {
        return gravity;
    }
};
