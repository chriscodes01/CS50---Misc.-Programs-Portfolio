#include <iostream>

//int get_cents(void);
//int calculate_quarters(int cents);
//int calculate_dimes(int cents);
//int calculate_nickles(int cents);
//int calculate_pennies(int cents);

class Calculator {
    public:
        int get_cents() {
            int cents;
            do {
                std::cout << "Change owed: ";
                std::cin >> cents;
            }
            while (cents < 0);
            return cents;
        }
        int quarters(int cents) {
            int quarters = 0;
            while (cents >= 25) {
                cents = cents - 25;
                quarters++;
            }
            return quarters;
        }
        int dimes(int cents) {
            int dimes = 0;
            while (cents >= 10) {
                cents = cents - 10;
                dimes++;
            }
            return dimes;
        }
        int nickles(int cents) {
            int nickles = 0;
            while (cents >= 5) {
                cents = cents - 5;
                nickles++;
            }
            return nickles;
        }
        int pennies(int cents) {
            int pennies = 0;
            while (cents >= 1) {
                cents = cents - 1;
                pennies++;
            }
            return pennies;
        }
};

int main(void) {
    Calculator calculate;
    
    
    // Ask how many cents customer is owed
    int cents = calculate.get_cents();

    // Calculate number of quarters to give to customer
    int quarters = calculate.quarters(cents);
    cents = cents - quarters * 25;

    // Calculate number of dimes to give to customer
    int dimes = calculate.dimes(cents);
    cents = cents - dimes * 10;

    // Calculate number of nickles to give to customer
    int nickles = calculate.nickles(cents);
    cents = cents - nickles * 5;

    // Calculate number of pennies to give to customer
    int pennies = calculate.pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickles + pennies;

    // Print total coins to give to customer
    std::cout << "Customer needs " << coins << " coins" << std::endl;
}