int PWM_OUT_Pin = 6;  // Output PWM pin
int PWM_IN_Pin = 5;   // Input PWM pin

void setup() {
    pinMode(PWM_OUT_Pin, OUTPUT);
    pinMode(PWM_IN_Pin, INPUT);
    Serial.begin(9600); // Start serial communication
}

void loop() {
    // Read high and low times
    unsigned long highTime = pulseIn(PWM_IN_Pin, HIGH);
    unsigned long lowTime = pulseIn(PWM_IN_Pin, LOW);

    // Compute cycle time
    unsigned long cycleTime = highTime + lowTime;

    // Prevent division by zero
    if (cycleTime == 0) {
      Serial.println("No PWM signal detected!");
      analogWrite(PWM_OUT_Pin, 0);
      return;
    }

    // Compute duty cycle (0.0 - 1.0)
    float dutyCycle = (float)highTime / cycleTime;

    // Amplify duty cycle by 8 and scale to 0-255
    int outputPWM = constrain(dutyCycle * 4 * 255, 0, 255);

    // Output the amplified PWM signal
    Serial.print("%, Amplified Output PWM: ");
    Serial.println(outputPWM);
    analogWrite(PWM_OUT_Pin, outputPWM);

    // Print values for debugging
    Serial.print("Duty Cycle: ");
    Serial.println(dutyCycle * 100);


    delay(800); // Small delay for stability
}
