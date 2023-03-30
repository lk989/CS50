-- Keep a log of any SQL queries you execute as you solve the mystery.


-- 1- REPORT OF THE CRIME
SELECT *
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND description LIKE '%CS50%';
-- >> it says there are 3 witnesses. their interviews contain the word 'bakery'


-- 2- FIND THE INTERVIEWS OF THE WITNESSES
SELECT name, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- >> the theft did 4 things (1/ he escaped with a car. 2/ he made a phone call that is less than a minute.
-- >> 3/ he told the receiver to book the first flight from Fiftyville tomorrow. 4/ he withdrew money from the Leggett Street ATM)


-- 3- NAMES OF THE PEOPLE WHO LEFT THE BAKERY WITH CAR
SELECT name
FROM people
JOIN bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit'
ORDER BY name;
-- >> [Alice, Amanda, Andrew, Barry, Brandon, Bruce, Carolyn, Daniel, Debra, Denis, Diana, Donna, Ethan, Frank, George, Iman,
-- >> Jeremy, John, Jordan, Joshua, Judith, Kelsey, Luca, Martha, Mary, Micheal, Peter, Rachel, Ralph, Robin, Sofia, Sophia,
-- >> Taylor, Thomas, Vanessa, Vincent, Wayne]


-- 4- NAMES OF THE PEOPLE WHO MADE A PHONE CALL THAT MORNING THAT IS LESS THAN A MINUTE
SELECT name
FROM people
JOIN phone_calls
WHERE people.phone_number = phone_calls.caller AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
ORDER BY name;
-- >> [Benista, Bruce, Carina, Diana, Kelsey 'twice', Sofia, Taylor]


-- 5- INTERSECTION OF THE 2 LISTS ABOVE
SELECT name
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND activity = 'exit'
JOIN phone_calls
ON people.phone_number = phone_calls.caller AND phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28 AND duration < 60
ORDER BY name;
-- >> [Bruce, Diana, Kelsey 'twice', Sofia, Taylor]


-- 6- NAMES OF THE PEOPLE WHO WITHDREW MONEY THIS MORNING
SELECT name
FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number AND atm_transactions.year = 2021
AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
ORDER BY name;


-- 7- INTERSECTION OF THE LISTS ABOVE
SELECT name
FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number AND atm_transactions.year = 2021
AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND activity = 'exit'
JOIN phone_calls
ON people.phone_number = phone_calls.caller AND phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28 AND duration < 60
ORDER BY name;
-- >> [Bruce, Diana, Taylor]


-- 8- NAMES OF THE PASSENGERS IN THE FIRST FLIGHT TOMORROW
SELECT name
FROM people
JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN
(SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour
LIMIT 1);


-- 9- INTERSECTION OF THE LISTS ABOVE
SELECT name
FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number AND atm_transactions.year = 2021
AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 5 AND 25 AND activity = 'exit'
JOIN phone_calls
ON people.phone_number = phone_calls.caller AND phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28 AND duration < 60
JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN
(SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour
LIMIT 1)
ORDER BY name;
-- >> [Bruce] >> THE THEFT


-- 10- NAMES OF THE PEOPLE WHO RECIEVED A PHONE CALL THAT MORNING THAT IS LESS THAN A MINUTE
SELECT name
FROM people
JOIN phone_calls
WHERE people.phone_number = phone_calls.receiver AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
ORDER BY name;
-- >> [Anna, Doris, Jack, Jacqueline, James, Larry, Melissa, Philip, Robin]


-- 11- NAME OF THE PERSON THAT THE THEFT HAS CALLED
SELECT name
FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE name = 'Bruce')
AND day = 28 AND duration < 60);
-- >> [Robin] >> THE HELPER


-- 12- FIND THE DESTINATION OF THE FLIGHT HE TOOK
SELECT city
FROM airports
WHERE id IN
(SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour
LIMIT 1);
-- >> [New York City] IS WHERE HE ESCAPED
