#pragma once
#include <iostream>
#include "Payment.cpp"
using namespace std;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "[Payment] Processing Cash Payment of ₹" << amount << " at counter...\n";
        cout << "[Payment Success] Cash Received.\n";
        return true;
    }
};