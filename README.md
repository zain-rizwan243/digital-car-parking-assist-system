# Digital Car Parking Assist System

An Arduino-based parking assistant that guides a driver into a tight
garage space. An ultrasonic sensor measures the distance to the car,
a set of LEDs shows how close it is, and a buzzer warns when the car
gets too close. If the car stops moving, the system turns itself off to
save power, and it wakes up again when the car moves.


## Features
- Real-time distance measurement with an ultrasonic sensor
- Five distance stages shown with green, yellow, and red LEDs
- Blinking red LEDs and a buzzer when the car is too close
- Automatic power-off after the car has stayed still for a while
- Wakes up automatically when the car moves

## How It Works
The sensor measures the distance to the car, and the Arduino lights the
LEDs according to the distance:

| Distance        | What lights up                                     |
|-----------------|----------------------------------------------------|
| Above 80 cm     | Green LEDs                                         |
| 60 to 80 cm     | Green + yellow LEDs                                |
| 40 to 60 cm     | Green + yellow + first pair of red LEDs            |
| 20 to 40 cm     | Green + yellow + all four red LEDs                 |
| 20 cm or less   | Green + yellow stay on, red LEDs blink, buzzer beeps |

**Power saving:** the Arduino remembers the car's distance. If the
distance stays within about 5 cm for 10 seconds, the system switches
all LEDs and the buzzer off, whichever stage the car stopped at. If the
distance changes by more than 5 cm (the car moves), the system turns
back on. This matches a real garage, where the car is parked for hours
and the system does not need to keep running.

## Components
- Arduino [board, e.g. Uno]
- Ultrasonic distance sensor [model, e.g. HC-SR04] (TRIG on pin 9, ECHO on pin 10)
- 2 green LEDs (pin 2)
- 2 yellow LEDs (pin 3)
- 4 red LEDs (two on pin 4, two on pin 5)
- Buzzer (pin 6)
- [Resistors, breadboard, power supply]

## Software
- Arduino IDE

## Circuit Diagram
[Drag your circuit diagram image here]

## Code
The sketch is in `parking_assist.ino`. Two settings at the top control
the power-saving behavior:
- `PARK_TIMEOUT`: how long the car must stay still before the system
  turns off (10 seconds)
- `MOVE_TOLERANCE`: how much the distance must change to count as
  movement (5 cm)

## Repository Contents
- `parking_assist.ino` - Arduino code

## Author
Zain Rizwan - Electrical Engineer<br>
Personal project (2025)
