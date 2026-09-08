#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Screen.cpp"
#include "Movie.cpp"
#include "ShowSeat.cpp"
using namespace std;

class Show {
private:
    int showId;
    string showTime;
    const Movie* movie;
    const Screen* screen;
    vector<ShowSeat> showSeats;

public:
    Show(int showId, const Movie* movie, const Screen* screen, string showTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->showTime = showTime;

        for (const auto& seat : screen->getSeats()) {
            showSeats.push_back(ShowSeat(seat));
        }
    }

    int getShowId() const { return showId; }
    const Movie* getMovie() const { return movie; }
    string getShowTime() const { return showTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    ShowSeat* findShowSeat(const string& seatNumber) {
        for (auto& ss : showSeats) {
            if (ss.getSeat().getSeatNumber() == seatNumber) {
                return &ss;
            }
        }
        return nullptr;
    }
};

