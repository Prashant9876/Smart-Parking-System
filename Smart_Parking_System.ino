#include <Servo.h>

const int arraySize = 3;
const int irSensorPin1 = 2;
const int irSensorPin2 = 3;
const int irSensorPin3 = 4;
const int irSensorPin4 = 5;
const int irSensorPin5 = 7;

Servo servoMotor;

void setup() {
 Serial.begin(9600);
  Serial.println("Smart Parking System");
 pinMode(irSensorPin1, INPUT);
 pinMode(irSensorPin2, INPUT);
 pinMode(irSensorPin3, INPUT);
 pinMode(irSensorPin4, INPUT);
 pinMode(irSensorPin5, INPUT);
 servoMotor.attach(6);

}

void loop() {
  int placed_Occupied = 0 ;
  int placed_Vaccant = 0 ;
  int parking_no = 0;
  int sensorState1 = digitalRead(irSensorPin1);
  int sensorState2 = digitalRead(irSensorPin2);
  int sensorState3 = digitalRead(irSensorPin3);
  int sensorState4 = digitalRead(irSensorPin4);
  int sensorState5 = digitalRead(irSensorPin5);
  int numbers[arraySize] ={sensorState1, sensorState2, sensorState3};
  for (int i = 0; i < arraySize; i++) {
      if (numbers[i]  == HIGH) {
        placed_Occupied++;
      }
      else{
        placed_Vaccant++;
      }
  }
  Serial.print("Number of Space Occupied: ");
  Serial.println(placed_Occupied);
  Serial.print("Number of Space Vaccant: ");
  Serial.println(placed_Vaccant);

  if (sensorState4 == HIGH){
    Serial.println("Wait,a vehicle is coming out.");
    servoMotor.write(90);
  }
  else{
    servoMotor.write(0);
  }
  if (sensorState4 == HIGH && placed_Vaccant != 0 ){
     for (int i = 0; i < arraySize; i++) {
      if (numbers[i]  == LOW) {
        parking_no =  numbers[i];
        break;
      }
      Serial.print("Parking No for your vehicle is:- ");
      Serial.println(parking_no);
      servoMotor.write(90);
    }
  }
  else{
    servoMotor.write(0);
  }
  delay(1000);


}
