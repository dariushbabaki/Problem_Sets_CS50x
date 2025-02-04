-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1: Find the crime scene report on Humphrey Street on July 28, 2021
SELECT *
FROM crime_scene_reports
WHERE street = "Humphrey Street" AND year = 2021 AND month = 7 AND day = 28;

-- Step 2: Check the interviews conducted on the same day
SELECT *
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

-- Step 3: Identify initial suspects based on parking lot cameras, ATM transactions, and phone calls
WITH suspects AS (
    SELECT p.*
    FROM people p
    JOIN bakery_security_logs b ON p.license_plate = b.license_plate
    WHERE b.activity = "exit" AND b.year = 2021 AND b.month = 7 AND b.day = 28
    AND b.hour = 10 AND b.minute BETWEEN 15 AND 40
)
SELECT *
FROM suspects
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE bank_accounts.account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28
        AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
    )
);

-- Step 4: Identify possible accomplices by checking recipients of short-duration phone calls
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    AND caller IN ("(286) 555-6063", "(770) 555-1861", "(367) 555-5533")
);

-- Step 5: Check flight details for departures from Fiftyville on July 29, 2021
SELECT f.*, a.city AS destination_city
FROM flights f
JOIN airports a ON f.destination_airport_id = a.id
WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
AND f.hour BETWEEN 00 AND 12
AND f.origin_airport_id IN (
    SELECT id FROM airports WHERE city = "Fiftyville"
)
ORDER BY f.hour, f.minute;

-- Step 6: Identify passengers of suspicious flights whose names match the suspects
SELECT p.name, p.passport_number, f.destination_airport_id, f.hour, f.minute
FROM people p
JOIN passengers pa ON p.passport_number = pa.passport_number
JOIN flights f ON pa.flight_id = f.id
JOIN airports a ON f.origin_airport_id = a.id
WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
AND f.hour BETWEEN 00 AND 12
AND a.city = "Fiftyville"
AND f.destination_airport_id IN (
    SELECT id FROM airports WHERE city IN ("New York City", "Chicago", "San Francisco")
)
AND p.name IN ("Bruce", "Taylor", "Diana", "James", "Philip", "Robin");

-- Step 7: Final conclusion - match confirmed flights with suspect names and identify the main thief and accomplice
SELECT p.name AS thief, accomplice.name AS accomplice, f.destination_airport_id, f.hour, f.minute
FROM people p
JOIN passengers pa ON p.passport_number = pa.passport_number
JOIN flights f ON pa.flight_id = f.id
JOIN airports a ON f.origin_airport_id = a.id
JOIN phone_calls pc ON p.phone_number = pc.caller
JOIN people accomplice ON pc.receiver = accomplice.phone_number
WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
AND f.hour BETWEEN 00 AND 12
AND a.city = "Fiftyville"
AND f.destination_airport_id IN (
    SELECT id FROM airports WHERE city IN ("New York City", "Chicago", "San Francisco")
)
AND p.name IN ("Bruce", "Taylor")
AND accomplice.name IN ("James", "Robin");
