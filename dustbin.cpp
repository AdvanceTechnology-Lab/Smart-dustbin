#include <Servo.h>
Servo servo;    
int trigPin = 5;   
int echoPin = 6;  
int servoPin = 7;
int led = 10;
long duration, dist;  

void setup() {      
    Serial.begin(9600);
    servo.attach(servoPin); 
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    pinMode(led, OUTPUT);  
    servo.write(0);  // Lid closed
    delay(100);
    servo.detach();
}

long measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30 ms
    if (duration == 0) {
        return 999;  // No object detected
    }
    return (duration / 2) / 29.1;  // Convert to cm
}

void loop() {
    dist = measureDistance();
    Serial.print("Distance: ");
    Serial.println(dist);

    if (dist < 50) {  // Object detected within 50 cm
        digitalWrite(led, HIGH); // Turn on LED
        servo.attach(servoPin);
        servo.write(0);  // Open lid
        delay(3000);     // Keep lid open for 3 seconds
        servo.write(150); // Close lid
        delay(1000);      // Wait for lid to close
        servo.detach();
        digitalWrite(led, LOW); // Turn off LED
    }
    delay(100);  // Small delay before next measurement
}
