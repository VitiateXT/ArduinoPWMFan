int PWM_OUT_PIN = 6; // Output PWM pin
int PWM_IN_PIN = 5; // Input PWM pin
int PWM_FAN_STOP = 0; // PWM Duty Cycle to 0
int PWM_FAN_MAX_SPEED = 255; // PWM duty cycle to maximum
int AMPLIFY_POWER = 2; // Power of 2 to amplify
double AMPLIFY_FACTOR = 0.0625; // Factor to amplify
int DELAY_TIME = 511; // Delay time in milliseconds

void setup() {
    pinMode(PWM_OUT_PIN, OUTPUT);
    pinMode(PWM_IN_PIN, INPUT);
    Serial.begin(9600); // Start serial communication
}

void loop() {
    // Read high and low times
    unsigned long highTime = pulseIn(PWM_IN_PIN, HIGH);
    unsigned long lowTime = pulseIn(PWM_IN_PIN, LOW);

    // Compute cycle time
    unsigned long cycleTime = highTime + lowTime;

    // Prevent division by zero and set PWM Fan to stop
    if (cycleTime == 0) {
      Serial.println("No PWM signal detected!");
      analogWrite(PWM_OUT_PIN, PWM_FAN_STOP);
      return;
    }

    // Compute duty cycle (0.0 - 1.0)
    double dutyCycle = (float)highTime / cycleTime;

    // Amplify duty cycle with a function and scale to 0-255
    int outputPWM = constrain(AMPLIFY_FACTOR * pow((dutyCycle * PWM_FAN_MAX_SPEED), AMPLIFY_POWER), PWM_FAN_STOP, PWM_FAN_MAX_SPEED);

    // Output the amplified PWM signal
    Serial.print("%, Amplified Output PWM: ");
    Serial.println(outputPWM);
    analogWrite(PWM_OUT_PIN, outputPWM);

    // Print values for debugging
    Serial.print("Duty Cycle: ");
    Serial.println(dutyCycle * 100);

    delay(DELAY_TIME); // Small delay for stability
}
