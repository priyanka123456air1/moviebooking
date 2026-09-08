#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Seat.cpp"
#include "Screen.cpp"
#include "Movie.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Cinema.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "BookingService.cpp"
#include "TicketPrinter.cpp"

using namespace std;

// Helper function to split comma-separated seat inputs (e.g., "A1,B2")
vector<string> parseSeats(const string& input) {
    vector<string> seats;
    stringstream ss(input);
    string seat;
    while (getline(ss, seat, ',')) {
        // Remove leading/trailing spaces if any
        size_t start = seat.find_first_not_of(" ");
        size_t end = seat.find_last_not_of(" ");
        if (start != string::npos && end != string::npos) {
            seats.push_back(seat.substr(start, end - start + 1));
        }
    }
    return seats;
}

int main() {
    // --- Setup Initial Cinema Data ---
    Cinema cinema("HJCINEMA");
    
    Screen screen1("Screen-1");
    screen1.addSeat(Seat("A1", "SILVER"));
    screen1.addSeat(Seat("A2", "SILVER"));
    screen1.addSeat(Seat("A3", "SILVER"));
    screen1.addSeat(Seat("A4", "SILVER"));
    screen1.addSeat(Seat("B1", "GOLD"));
    screen1.addSeat(Seat("B2", "GOLD"));
    screen1.addSeat(Seat("B3", "GOLD"));
    screen1.addSeat(Seat("C1", "PLATINUM"));
    screen1.addSeat(Seat("C2", "PLATINUM"));

    Screen screen2("Screen-2");
    screen2.addSeat(Seat("A1", "SILVER"));
    screen2.addSeat(Seat("A2", "SILVER"));
    screen2.addSeat(Seat("B1", "GOLD"));

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Movie m1("3 Idiots", "Hindi", 170);
    Movie m2("Interstellar", "English", 169);

    Show show1(101, &m1, &screen1, "06:00 PM");
    Show show2(102, &m2, &screen2, "09:00 PM");

    vector<Movie> movies = {m1, m2};
    vector<Show> shows = {show1, show2};

    BookingService service(&cinema);
    vector<Booking*> myTickets;

    int choice;
    do {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies   2. Book   3. Cancel   4. My tickets   0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- AVAILABLE MOVIES ---\n";
                for (size_t i = 0; i < movies.size(); ++i) {
                    cout << "[" << i + 1 << "] " << movies[i].getTitle() 
                         << "\t" << movies[i].getLanguage() 
                         << " " << movies[i].getDurationMinutes() << " min\n";
                }
                break;
            }

            case 2: {
                // Step 1: Select Movie
                cout << "\n";
                for (size_t i = 0; i < movies.size(); ++i) {
                    cout << "[" << i + 1 << "] " << movies[i].getTitle() 
                         << "\t" << movies[i].getLanguage() 
                         << " " << movies[i].getDurationMinutes() << " min\n";
                }
                cout << "\nChoose movie: ";
                int movieChoice;
                cin >> movieChoice;

                if (movieChoice < 1 || movieChoice > (int)movies.size()) {
                    cout << "Invalid movie choice!\n";
                    break;
                }

                // Step 2: Select Show
                cout << "\n[1] Screen-1   06:00 PM\n";
                cout << "[2] Screen-2   09:00 PM\n";
                cout << "Choose show: ";
                int showChoice;
                cin >> showChoice;

                Show* selectedShow = (showChoice == 1) ? &shows[0] : &shows[1];

                // Step 3: Display Layout
                cout << "\nSCREEN-1   " << selectedShow->getShowTime() 
                     << "  |  " << selectedShow->getMovie()->getTitle() << "\n";
                
                cout << "SILVER    ";
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "SILVER") {
                        cout << ss.getSeat().getSeatNumber() 
                             << (ss.isBooked() ? "[X] " : "[ ] ");
                    }
                }
                cout << "\nGOLD      ";
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "GOLD") {
                        cout << ss.getSeat().getSeatNumber() 
                             << (ss.isBooked() ? "[X] " : "[ ] ");
                    }
                }
                cout << "\nPLATINUM  ";
                for (auto& ss : selectedShow->getShowSeats()) {
                    if (ss.getSeat().getCategory() == "PLATINUM") {
                        cout << ss.getSeat().getSeatNumber() 
                             << (ss.isBooked() ? "[X] " : "[ ] ");
                    }
                }
                cout << "\n\n( [ ] = available   [X] = booked )\n\n";

                // Step 4: Choose Seats
                cout << "Seats (e.g. A1,B2): ";
                string seatsInput;
                cin >> seatsInput;

                vector<string> chosenSeats = parseSeats(seatsInput);
                Customer customer("Himanshu", "9876543210");

                Booking* booking = service.createBooking(customer, selectedShow, chosenSeats);
                if (!booking) break;

                // Display Price Breakdown
                double total = 0;
                for (auto* ss : booking->getBookedSeats()) {
                    double price = (ss->getSeat().getCategory() == "PLATINUM") ? 350 :
                                  (ss->getSeat().getCategory() == "GOLD") ? 250 : 150;
                    cout << ss->getSeat().getSeatNumber() << " " 
                         << ss->getSeat().getCategory() << " Rs." << price << "\n";
                    total += price;
                }
                cout << "TOTAL          Rs." << total << "\n\n";

                // Step 5: Payment Method
                cout << "Pay by: 1.UPI   2.Card   3.Cash > ";
                int payChoice;
                cin >> payChoice;

                Payment* payment = nullptr;
                if (payChoice == 1) payment = new UpiPayment("user@upi");
                else if (payChoice == 2) payment = new CardPayment("4111-XXXX-XXXX-1111");
                else payment = new CashPayment();

                if (service.processPayment(booking, payment)) {
                    myTickets.push_back(booking);
                    TicketPrinter::printTicket(booking);
                }
                delete payment;
                break;
            }

            case 3: {
                if (myTickets.empty()) {
                    cout << "\nNo bookings found to cancel.\n";
                    break;
                }
                cout << "\n--- CANCEL BOOKING ---\n";
                cout << "Enter Booking ID: ";
                int bId;
                cin >> bId;

                for (auto* b : myTickets) {
                    if (b->getBookingId() == bId) {
                        service.cancelBooking(b);
                        break;
                    }
                }
                break;
            }

            case 4: {
                cout << "\n--- MY TICKETS ---\n";
                if (myTickets.empty()) {
                    cout << "No tickets booked yet.\n";
                } else {
                    for (auto* b : myTickets) {
                        TicketPrinter::printTicket(b);
                    }
                }
                break;
            }

            case 0:
                cout << "\nExiting System. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    } while (choice != 0);

    // Dynamic Cleanup
    for (auto* b : myTickets) delete b;

    return 0;
}