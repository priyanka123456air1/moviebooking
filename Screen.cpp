#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Seat.cpp"
using namespace std;

class Screen {
private:
    string screenName;
    vector<Seat> seats;

public:
    Screen(string screenName) {
        this->screenName = screenName;
    }

    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    string getScreenName() const { return screenName; }
    const vector<Seat>& getSeats() const { return seats; }
};