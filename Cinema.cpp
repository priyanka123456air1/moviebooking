#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Screen.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema(string name) {
        this->name = name;
    }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    string getName() const { return name; }
    const vector<Screen>& getScreens() const { return screens; }
};