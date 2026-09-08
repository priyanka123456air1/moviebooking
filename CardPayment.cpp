#pragma once
#include <iostream>
#include <string>
#include "Payment.cpp"
using namespace std;

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {
        cout << "[Payment] Processing Card Payment of ₹" << amount << "...\n";
        cout << "[Payment Success] Card Transaction Approved.\n";
        return true;
    }
};