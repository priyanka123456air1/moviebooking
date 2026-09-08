#pragma once
#include <iostream>
#include "Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    static void printTicket(const Booking* booking) {
        if (!booking || booking->getStatus() != "CONFIRMED") {
            cout << "[Printer Error] Cannot print ticket for unconfirmed booking.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "           CINEMA TICKET                \n";
        cout << "========================================\n";
        cout << " Booking ID : " << booking->getBookingId() << "\n";
        cout << " Customer   : " << booking->getCustomer().getName() 
             << " (" << booking->getCustomer().getPhone() << ")\n";
        cout << " Movie      : " << booking->getShow()->getMovie()->getTitle() << "\n";
        cout << " Time       : " << booking->getShow()->getShowTime() << "\n";
        cout << " Seats      : ";
        for (auto* ss : booking->getBookedSeats()) {
            cout << ss->getSeat().getSeatNumber() << " ";
        }
        cout << "\n Total Paid : ₹" << booking->getBookingAmount() << "\n";
        cout << " Status     : " << booking->getStatus() << "\n";
        cout << "========================================\n\n";
    }
};