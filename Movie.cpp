#pragma once
#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int durationMinutes;

public:
    Movie() {
        this->title = "Unknown";
        this->language = "Unknown";
        this->durationMinutes = 0;
    }

    Movie(string title, string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};