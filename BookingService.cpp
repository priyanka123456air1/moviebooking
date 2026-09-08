#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cinema.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
using namespace std;

class BookingService {
private:
    const Cinema* cinema;

public:
    BookingService(const Cinema* cinema) {
        this->cinema = cinema;
    }

    Booking* createBooking(Customer customer, Show* show, vector<string> seatNumbers) {
        vector<ShowSeat*> selectedSeats;

        for (const auto& sNo : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(sNo);

            if (!ss) {
                cout << "[Error] Invalid seat number: " << sNo << "! Operation aborted.\n";
                return nullptr;
            }

            if (!ss->lockSeat()) {
                cout << "[Error] Seat " << sNo << " is already BOOKED or Unavailable! Selection rejected.\n";
                for (auto* lockedSs : selectedSeats) {
                    lockedSs->releaseSeat();
                }
                return nullptr;
            }
            selectedSeats.push_back(ss);
        }

        double totalAmount = selectedSeats.size() * 250.0;
        return new Booking(customer, show, selectedSeats, totalAmount);
    }

    bool processPayment(Booking* booking, Payment* paymentMethod) {
        if (!booking) return false;

        bool success = paymentMethod->pay(booking->getBookingAmount());

        if (success) {
            booking->setStatus("CONFIRMED");
            for (auto* ss : booking->getBookedSeats()) {
                ss->confirmSeat();
            }
            cout << "[Booking Confirmed] Booking ID #" << booking->getBookingId() << " is confirmed!\n";
            return true;
        } else {
            cout << "[Payment Failed] Payment declined! Booking NOT confirmed. Releasing locked seats...\n";
            booking->setStatus("FAILED");
            for (auto* ss : booking->getBookedSeats()) {
                ss->releaseSeat();
            }
            return false;
        }
    }

    void cancelBooking(Booking* booking) {
        if (!booking || booking->getStatus() != "CONFIRMED") {
            cout << "[Cancel Error] Cannot cancel an unconfirmed or invalid booking!\n";
            return;
        }

        booking->setStatus("CANCELLED");
        for (auto* ss : booking->getBookedSeats()) {
            ss->releaseSeat();
        }
        cout << "[Cancel Success] Booking #" << booking->getBookingId() 
             << " cancelled successfully. Seats are now AVAILABLE again.\n";
    }
};