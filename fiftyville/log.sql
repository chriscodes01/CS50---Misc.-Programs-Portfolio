-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Theft took place July 28, 2021 on Humphrey Street.
-- .tables will list all tables
-- .schema TABLE_NAME will show all columns related to that table


-- Start with crime_scene_reports table. Look for report IDs that matches crime date and location.
SELECT id FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- !!! Two IDs: 295 and 297. I should look at their descriptions and narrow our search.
SELECT description FROM crime_scene_reports
WHERE id = 295 OR id = 297;
-- !!! ID 295 describes theft of CS50 duck. Time: 10:15am at the bakery. Interviews with three witnesses who were present, and each interview mentions bakery.
-- I should view tables: interviews and bakery_security_logs
-- It looks like I can pull up interview transcripts by date and activity + license_plates from security logs
-- Let's view all IDs by the date and possibly hour/minute in regards to security logs.
SELECT id, transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;
-- ! ID 161: Within 10 minutes of theft, theif got into car and escaped.
-- ! ID 162: Bakery belongs to Emma. Also, theif withdrew money at ATM on Leggett Street before theft.
-- ! ID 163: As thief left bakery, they made phone call for less than a minute. Said they were planning on taking earliest flgith out of Fiftyville the next day. Thief asked person on phone to purchase flight ticket.
-- I have three leads here. I'll start with ID 161 and look for license plate from security log.
SELECT license_plate, activity, minute FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- ! Returned 8 license plates within 10 minutes of 10:15am. I may be able to link these to people.
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- ! Returned 8 names: Iman, Bruce, Diana, Kelsey, Luca, Vanessa, Barry, Sofia.
-- Let's see what I can find out about the ATM of Leggett Street.
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";
-- ! Only thing of interest were account numbers and amount. Account number -> bank_accounts; amount -> ?
-- Time to see if any names match the ATM/bank accounts from Legget Str. on that date and also match the license plates from security.
-- name FROM people JOIN atm.account_number = bank.account_number JOIN bakery.license = people.license
-- WHERE bank.account_number IN (account_number from both atm.account_number AND bank.account_number)
-- AND bakery.license IN (bakery.license from specific date)
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street")
    AND bakery_security_logs.license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- ! Returned same 8 names. Dead end.
-- I can try checking the earliest flights out of Fiftyville on 7/29/2021
SELECT id, destination_airport_id, hour, minute FROM flights
WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour ASC;
-- ! Earliest flight: ID 36, destination ID: 4, 8:20 AM.
-- Connect earliest flight to airports to discover destination.
SELECT abbreviation, full_name, city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE destination_airport_id IN (
    SELECT destination_airport_id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20);
-- !!!!! Destination: New York City
-- See if passengers.passport_number matches people.passport_number FROM 8 names
SELECT DISTINCT(passengers.passport_number) FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- Got 7 numbers back... not really narrowing it down
-- I guess I'll try checking phone calls that were less than a minute on that date
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Sofia, Kelsey, Bruce, Taylor, Diana, Carina, Kenny, Benista
-- 1st Narrow: Compared to the license plate names, we only match Sofia, Kelsey, Bruce, and Diana
-- See what names match passengers for earliest flight.
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN (
    SELECT id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN (
        SELECT id FROM airports WHERE city = "Fiftyville")
    ORDER BY hour, minute LIMIT 1);
-- Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca
-- 2nd Narrow: Compared to our 1st Narrow, we only match Sofia, Kelsey, Bruce
-- I could specify who withdrew money from ATM.
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
-- 3rd Narrow: Compared to our 2nd Narrow, we only match Bruce!

-- Finally, we need to determine who the accomplice is. We can do this by tracing the phone call from Bruce's phone to the receiver.
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.receiver IN (
    SELECT phone_number FROM people
    WHERE name = "Bruce");
-- !!! Bruce: (367) 555-5533
-- Now we trace using his number and the details of call
SELECT name FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533");
-- !!! Only one name: Robin