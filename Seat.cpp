#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class SeatStatus { AVAILABLE, LOCKED, BOOKED };

class Seat {
private:
    string seatNumber;
    string category; // GOLD, SILVER, VIP

public:
    Seat(string seatNumber, string category) {
        this->seatNumber = seatNumber;
        this->category = category;
    }

    string getSeatNumber() const { return seatNumber; }
    string getCategory() const { return category; }
};