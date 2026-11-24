#define TRIG_PIN 9
#define ECHO_PIN 10

#define GREEN_LED 2   // Controls both Green LEDs
#define YELLOW_LED 3  // Controls both Yellow LEDs
#define RED_LED_1 4   // Controls first two Red LEDs
#define RED_LED_2 5   // Controls last two Red LEDs
#define Buzzer 6

const unsigned long PARK_TIMEOUT = 10000; // ms without movement before turning off
const int MOVE_TOLERANCE = 5;             // cm change that counts as "car moved"

bool systemActive = true;       // System ON/OFF flag
unsigned long lastMoveTime = 0; // when the car last moved
long lastDistance = 0;          // reference distance for detecting movement

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED_1, OUTPUT);
    pinMode(RED_LED_2, OUTPUT);
    pinMode(Buzzer, OUTPUT);

    lastDistance = getDistance();
    lastMoveTime = millis();
}

long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2;  // Convert to cm
    return distance;
}

void allOff() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED_1, LOW);
    digitalWrite(RED_LED_2, LOW);
    digitalWrite(Buzzer, LOW);
}

void loop() {
    long distance = getDistance();

    // Did the car move since the reference reading?
    if (abs(distance - lastDistance) > MOVE_TOLERANCE) {
        lastDistance = distance;
        lastMoveTime = millis();
        systemActive = true;   // wake the system up if it was off
    }

    // Car has not moved for the timeout -> turn the system off (any stage)
    if (systemActive && millis() - lastMoveTime >= PARK_TIMEOUT) {
        systemActive = false;
        allOff();
    }

    // If system is off, keep watching the distance but do nothing else
    if (!systemActive) {
        delay(100);
        return;
    }

    if (distance > 80) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED_1, LOW);
        digitalWrite(RED_LED_2, LOW);
        digitalWrite(Buzzer, LOW);
    }
    else if (distance > 60 && distance <= 80) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED_1, LOW);
        digitalWrite(RED_LED_2, LOW);
        digitalWrite(Buzzer, LOW);
    }
    else if (distance > 40 && distance <= 60) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED_1, HIGH);
        digitalWrite(RED_LED_2, LOW);
        digitalWrite(Buzzer, LOW);
    }
    else if (distance > 20 && distance <= 40) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED_1, HIGH);
        digitalWrite(RED_LED_2, HIGH);
        digitalWrite(Buzzer, LOW);
    }
    else {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, HIGH);

        // Blink Red LEDs & Buzzer when too close
        digitalWrite(RED_LED_1, HIGH);
        digitalWrite(RED_LED_2, HIGH);
        digitalWrite(Buzzer, HIGH);
        delay(200);
        digitalWrite(RED_LED_1, LOW);
        digitalWrite(RED_LED_2, LOW);
        digitalWrite(Buzzer, LOW);
        delay(200);
    }

    delay(100); // Small delay for stability
}
