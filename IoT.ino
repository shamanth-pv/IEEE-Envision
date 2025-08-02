#include <LiquidCrystal.h>

// Wind speed measurement variables
float V_wind = 0;
float Windspeedfloat;
int Windspeedint;   
float temp; 
int gas_sensor_port = A1;
int gas_sensor_value = 0;

// Rainfall measurement variables
float rain;
const int triggerPin = 10;
const int echoPin = 9;
long duration;
LiquidCrystal lcd(8, 2, 6, 5, 4, 3); // LCD setup



void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(A2, INPUT); // Set pin A2 as input for wind speed measurement
  Serial.println("Setup done");// Debugging statement
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(7,OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2); // Initialize LCD
}

void loop() {
  Serial.println("Looping..."); // Debugging statement
  
  // Read wind speed
  float V_wind = analogRead(A2) * (5.0 / 1023.0);
  temp=((analogRead(A0)*0.0048828125)-0.5)*100;
  // Convert voltage to MPH
  Windspeedint = (V_wind - 0.4) * 10 * 2.025 * 2.237;
  Windspeedfloat = (V_wind - 0.4) * 10 * 2.025 * 2.237;
  
  // Output wind speed to serial monitor
  Serial.print("Wind Speed: ");
  if (Windspeedfloat <= 0) {
    Serial.print("0.0");
  } else {
    Serial.print(Windspeedfloat);
  }
  Serial.println(" MPH");
  
  // Output anemometer voltage to serial monitor
  Serial.print("Anemometer Voltage: ");
  if (V_wind > 2) {
    Serial.println("Out of range!");
  } else if (V_wind < 0.4) {
    Serial.println("Out of range!");
  } else {
    Serial.print(V_wind);
    Serial.println(" V");
    Serial.print("Current temperature: ");
    Serial.println(temp);
     gas_sensor_value = analogRead(gas_sensor_port);
  Serial.println("Gas sensor value: " + String(gas_sensor_value));
  if (gas_sensor_value > 200)
  {
    tone(7,523,1000);
  }

  }
   // For rainfall measurement
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  rain = 0.01723 * duration;

  // Display rainfall on LCD
  lcd.setCursor(0, 0);
  lcd.print("Rainfall: ");
  lcd.print(rain);
  lcd.print("mm");
  
  // Print rainfall to serial monitor
  Serial.print("Rainfall: ");
  Serial.print(rain);
  Serial.println(" mm");  
  
  delay(1000); // Delay for 1 second before the next reading
}