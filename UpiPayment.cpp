#pragma once
#include <iostream>
#include <string>
#include "Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {
        cout << "[Payment] Processing UPI Payment of ₹" << amount << " via " << upiId << "...\n";
        if (upiId == "invalid@upi") {
            cout << "[Payment Failed] Invalid UPI credentials!\n";
            return false;
        }
        cout << "[Payment Success] UPI Transaction completed successfully.\n";
        return true;
    }
};