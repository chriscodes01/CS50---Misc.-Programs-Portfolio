#include <iostream>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickles(int cents);
int calculate_pennies(int cents);

int main(void) {
    // Ask how many cents customer is owed
    int cents = get_cents();

    // Calculate number of quarters to give to customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate number of dimes to give to customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate number of nickles to give to customer
    int nickles = calculate_nickles(cents);
    cents = cents - nickles * 5;

    // Calculate number of pennies to give to customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickles + pennies;

    // Print total coins to give to customer
    std::cout << "Customer needs " << coins << "coins" std::endl;
}