#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Customer.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"
using namespace std;

class Booking {
private:
    int bookingId;
    Customer customer;
    const Show* show;
    vector<ShowSeat*> bookedSeats;
    double bookingAmount;
    string status;

public:
    static int nextBookingId;

    Booking(Customer customer, const Show* show, vector<ShowSeat*> seats, double amount)
        : customer(customer), show(show), bookedSeats(seats), bookingAmount(amount), status("PENDING") {
        this->bookingId = ++nextBookingId;
    }

    void setStatus(const string& newStatus) {
        this->status = newStatus;
    }

    int getBookingId() const { return bookingId; }
    Customer getCustomer() const { return customer; }
    const Show* getShow() const { return show; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    double getBookingAmount() const { return bookingAmount; }
    string getStatus() const { return status; }
};

int Booking::nextBookingId = 1000;