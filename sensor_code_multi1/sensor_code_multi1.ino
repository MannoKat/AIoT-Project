// Libraries for the sensors
#include <DHT.h>

// Constants for the sensor pins
#define DHT_PIN 2
#define SOIL_MOISTURE_PIN A0
#define LDR_PIN A1

// Constants for the sensor types
#define DHT_TYPE DHT11

// Thresholds for the sensors
#define TEMP_LOWER_LIMIT 10
#define TEMP_UPPER_LIMIT 20
#define HUMIDITY_LOWER_LIMIT 40
#define HUMIDITY_UPPER_LIMIT 60
#define SOIL_MOISTURE_LOWER_LIMIT 55
#define SOIL_MOISTURE_UPPER_LIMIT 70
#define BRIGHTNESS_LOWER_LIMIT 800
#define BRIGHTNESS_UPPER_LIMIT 1300

// Pin numbers for nebulizer, light, and sunshade net
#define NEBULIZER_PIN 3
#define LIGHT_PIN 4
#define SUNSHADE_NET_PIN 5
#define PUMP_PIN 6

// Function prototypes
void checkTemperature(float temperature);
void checkHumidity(float humidity);
void checkSoilMoisture(int soilMoisture);
void checkBrightness(int brightness);
void notifyWarning(String message);

// Initialize the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);


void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize pins for nebulizer, light, and sunshade net
  pinMode(NEBULIZER_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(SUNSHADE_NET_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(A1,INPUT);
  // Start with all actuators turned off
  digitalWrite(NEBULIZER_PIN, LOW);
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(SUNSHADE_NET_PIN, LOW);
  digitalWrite(PUMP_PIN, LOW);
}

void loop() {
  // // Read sensor values
  // float temperature = dht.readTemperature();
  // float humidity = dht.readHumidity();
  // float soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  // float brightness = analogRead(LDR_PIN);

  if(Serial.available()){
    char c = Serial.read();
    if (c == 't'){
      // Check temperature
      float t = dht.readTemperature();
      Serial.print("!1:Temperature:");
      Serial.print(t);   
      Serial.print("#");
      if (t > TEMP_UPPER_LIMIT) {
      digitalWrite(SUNSHADE_NET_PIN, HIGH); // Turn on sunshade net
      } else if (t < TEMP_LOWER_LIMIT) {
      digitalWrite(SUNSHADE_NET_PIN, LOW);  // Turn off sunshade net
      } else {
      digitalWrite(SUNSHADE_NET_PIN, LOW); // Turn off sunshade net
      }
    } 
    else if (c == 'h'){
      // Check humidity
      float h = dht.readHumidity();
      Serial.print("!1:Humidity:");
      Serial.print(h);   
      Serial.print("#");
      if (h < HUMIDITY_LOWER_LIMIT) {
      digitalWrite(NEBULIZER_PIN, HIGH); // Turn on nebulizer
      } else if (h > HUMIDITY_UPPER_LIMIT) {
      digitalWrite(NEBULIZER_PIN, LOW); // Turn off nebulizer
      } else {
      digitalWrite(NEBULIZER_PIN, LOW); // Turn off nebulizer
      }
    }
    else if (c == 's'){
      // Check humidity
      float s = (1200 - analogRead(SOIL_MOISTURE_PIN))/10;
      Serial.print("!1:Soil moisture:");
      Serial.print(s);   
      Serial.print("#");
      if (s < SOIL_MOISTURE_LOWER_LIMIT) {
      digitalWrite(PUMP_PIN, HIGH); // Turn on nebulizer
      } else if (s > SOIL_MOISTURE_UPPER_LIMIT) {
      digitalWrite(PUMP_PIN, LOW); // Turn off nebulizer
      } else {
      digitalWrite(PUMP_PIN, LOW); // Turn off nebulizer
  }
    }
    else if (c == 'b'){
      // Check brightness
      float b = (1500-analogRead(LDR_PIN));
      Serial.print("!1:Brightness:");
      Serial.print(b);   
      Serial.print("#");
      if (b < BRIGHTNESS_LOWER_LIMIT) {
      digitalWrite(LIGHT_PIN, HIGH); // Turn on light
      } else if (b > BRIGHTNESS_UPPER_LIMIT) {
      digitalWrite(LIGHT_PIN, LOW); // Turn off light
      } else {
      digitalWrite(LIGHT_PIN, LOW); // Turn off light
    }
    }
  }
}

// void checkTemperature(float temperature) {
//   Serial.print("Temp: ");
//   Serial.println(temperature);
//   if (temperature > TEMP_UPPER_LIMIT) {
//     digitalWrite(SUNSHADE_NET_PIN, HIGH); // Turn on sunshade net
//     notifyWarning("Temperature is too high!");
//   } 
//   else if (temperature < TEMP_LOWER_LIMIT) {
//     digitalWrite(SUNSHADE_NET_PIN, LOW);  // Turn off sunshade net
//     notifyWarning("Temperature is too low!");
//   }
//   else {
//     digitalWrite(SUNSHADE_NET_PIN, LOW); // Turn off sunshade net
//   }
// }
// void checkHumidity(float humidity) {
//   Serial.print("Humidity: ");
//   Serial.println(humidity);
//   if (humidity < HUMIDITY_LOWER_LIMIT) {
//     digitalWrite(NEBULIZER_PIN, HIGH); // Turn on nebulizer
//     notifyWarning("Humidity is too low!");
//   } else if (humidity > HUMIDITY_UPPER_LIMIT) {
//     digitalWrite(NEBULIZER_PIN, LOW); // Turn off nebulizer
//     notifyWarning("Humidity is too high!");
//   } else {
//     digitalWrite(NEBULIZER_PIN, LOW); // Turn off nebulizer
//   }
// }
// void checkSoilMoisture(int soilMoisture) {
//   Serial.print("Soil Moisture: ");
//   Serial.println(soilMoisture);
//   if (soilMoisture < SOIL_MOISTURE_LOWER_LIMIT) {
//     digitalWrite(PUMP_PIN, LOW); // Turn on nebulizer
//     notifyWarning("Soil Moisture is too high!");
//   } else if (soilMoisture > SOIL_MOISTURE_UPPER_LIMIT) {
//     digitalWrite(PUMP_PIN, HIGH); // Turn off nebulizer
//     notifyWarning("Soil Moisture is too low! Need more water!!!");
//   } else {
//     digitalWrite(PUMP_PIN, LOW); // Turn off nebulizer
//   }
// }

// void checkBrightness(int brightness) {
//   Serial.print("Brightness: ");
//   Serial.println(brightness);
//   if (brightness < BRIGHTNESS_LOWER_LIMIT) {
//     digitalWrite(LIGHT_PIN, LOW); // Turn on light
//     notifyWarning("Brightness is too high!");
//   } else if (brightness > BRIGHTNESS_UPPER_LIMIT) {
//     digitalWrite(LIGHT_PIN, HIGH); // Turn off light
//     notifyWarning("Brightness is too low!");
//   } else {
//     digitalWrite(LIGHT_PIN, LOW); // Turn off light
//   }
// }

// void notifyWarning(String message) {
//   Serial.println("Warning: " + message);
//   // Add code here to send the notification (e.g., via GSM module or Wi-Fi)
// }
