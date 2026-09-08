#pragma once
#include <iostream>
#include <string>
#include "Seat.cpp"
using namespace std;

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat(Seat seat) : seat(seat), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }
    bool isBooked() const { return status == SeatStatus::BOOKED; }

    bool lockSeat() {
        if (status == SeatStatus::BOOKED || status == SeatStatus::LOCKED) {
            return false;
        }
        status = SeatStatus::LOCKED;
        return true;
    }

    void confirmSeat() { status = SeatStatus::BOOKED; }
    void releaseSeat() { status = SeatStatus::AVAILABLE; }

    Seat getSeat() const { return seat; }
    SeatStatus getStatus() const { return status; }
};