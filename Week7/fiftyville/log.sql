-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE street LIKE "Humphrey Street" AND year = 2021 AND month = 7 AND day = 28;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript like "%bakery%";
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT name, passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND year = 2021 AND month = 7 AND day = 28));

SELECT id FROM people WHERE license_plate in (SELECT license_plate FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25);

SELECT name, id FROM people WHERE id in (SELECT id FROM people WHERE license_plate in (SELECT license_plate FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND year = 2021 AND month = 7 AND day = 28));

SELECT * FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;

-- People who are on the flight which were leaving the bakery at the time of the robbery: Luca and Bruce
SELECT name, id FROM people WHERE id in (SELECT id FROM people WHERE license_plate in (SELECT license_plate FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND year = 2021 AND month = 7 AND day = 28))
AND passport_number in (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1));

-- Destination of first flight on the next day out of the city: New York City
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);

-- Phone numbers of Caller and Receiver of the call: (367) 555-5533 and (375) 555-8161
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE id in (SELECT id FROM people WHERE id in (SELECT id FROM people WHERE license_plate in (SELECT license_plate FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND year = 2021 AND month = 7 AND day = 28))
AND passport_number in (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1))));

-- Caller's name: Bruce (Thief)
SELECT name FROM people WHERE phone_number = "(367) 555-5533";
-- Receiver's name: Robin (Accomplice)
SELECT name FROM people WHERE phone_number = "(375) 555-8161";