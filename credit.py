from cs50 import get_int

# Prompt for card number
while True:
    credit = get_int("Number: ")
    if credit > 0:
        break

# Define function: Checksum Algorithm
def luhn_checksum(credit):
    # Define function: Convert string digits to int digits as a list/array
    def convert_digits(n):
        return [int(d) for d in str(n)]
    # Initiate Convert-Digits function for entire string
    digits = convert_digits(credit)
    # Starting from the end of list/array, go to every other number and add it to new list/array called "odd"
    odd = digits[-1::-2]
    # Do same as above but for even, starting from second-to-last digit
    even = digits[-2::-2]
    # Initialize checksum variable from 0, add all odd numbers together
    checksum = 0
    checksum += sum(odd)
    # Do same as above but multiply digits by 2 before adding together
    for d in even:
        checksum += sum(convert_digits(d * 2))
        # Retrun checksum mode 10
    return checksum % 10

# Initialize variables
amex = credit
visa = credit
master = credit
length = 0

# Check length for credit card
length = len(str(credit))

# 10 to the power of...
while amex >= 10 ** 13:
    amex = int(amex / 10 ** 13)

while visa >= 10:
    visa = int(visa / 10)

while master >= 10 ** 14:
    master = int(master / 10 ** 14)

# Initialize checksum algorithm, and keep doing it until == 0
# When checksum == 0, check length and corresponding bank institution to see a match
if luhn_checksum(credit) == 0:
    if length == 15 and (amex == 34 or amex == 37):
        print("AMEX")
    elif visa == 4 and (length == 13 or length == 16):
        print("VISA")
    elif length == 16 and (51 <= master <= 55):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")