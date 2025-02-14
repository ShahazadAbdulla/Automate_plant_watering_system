#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

#define WIFI_SSID "Sproutify"
#define WIFI_PASSWORD "sproutify"

#define FIREBASE_HOST "https://sproutify-3a23c-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "yxECGsRju1Gp3lOiLETzjzOsfQXpRswFrhZALnIu"  // Firebase Authentication token

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Sensor Pins
#define SOIL_MOISTURE_PIN 34  // HW-103 Soil Sensor (Analog)
#define DHT_PIN 4             // DHT11 Sensor (Digital)
#define DHT_TYPE DHT11

// L298N Motor Driver Pins
#define PUMP1_IN1 18  // Pump 1
#define PUMP1_IN2 19  
#define PUMP2_IN1 22  // Pump 2
#define PUMP2_IN2 23  
#define PUMP3_IN1 25  // Pump 3
#define PUMP3_IN2 26  

DHT dht(DHT_PIN, DHT_TYPE);

const int numReadings = 10;
int moistureThreshold = 40;  // Below 40% -> Turn on pump

unsigned long lastUpdateMillis = 0;
const long updateInterval = 3000;  // Firebase update interval: 3 sec

void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("[WiFi] Connecting...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n[WiFi] Connected!");

    // Firebase Setup
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println("[Firebase] Initialized.");

    // Initialize sensors
    dht.begin();
    pinMode(SOIL_MOISTURE_PIN, INPUT);

    // Set Motor Pins
    pinMode(PUMP1_IN1, OUTPUT);
    pinMode(PUMP1_IN2, OUTPUT);
    pinMode(PUMP2_IN1, OUTPUT);
    pinMode(PUMP2_IN2, OUTPUT);
    pinMode(PUMP3_IN1, OUTPUT);
    pinMode(PUMP3_IN2, OUTPUT);

    // Turn all pumps OFF initially
    stopPump1();
    stopPump2();
    stopPump3();

    Serial.println("[Setup] Initialization complete.");
}

void loop() {
    float totalMoisture = 0, totalTemp = 0, totalHumidity = 0;

    Serial.println("[Reading Sensors] Start");

    for (int i = 0; i < numReadings; i++) {
        totalMoisture += analogRead(SOIL_MOISTURE_PIN);
        totalTemp += dht.readTemperature();
        totalHumidity += dht.readHumidity();
        delay(10);
    }

    float avgMoisture = totalMoisture / numReadings;
    float avgTemp = totalTemp / numReadings;
    float avgHumidity = totalHumidity / numReadings;

    float moisturePercent = map(avgMoisture, 4095, 1150, 0, 100);

    Serial.print("[Sensor Data] Temp: ");
    Serial.print(avgTemp);
    Serial.print("°C | Humidity: ");
    Serial.print(avgHumidity);
    Serial.print("% | Soil Moisture: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    // Update Firebase every 3 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdateMillis >= updateInterval) {
        lastUpdateMillis = currentMillis;

        Serial.println("[Firebase Update] Sending sensor data...");

        if (Firebase.setFloat(firebaseData, "/sensors/Humidity", avgHumidity)) {
            Serial.println("[Firebase Update] Humidity updated.");
        } else {
            Serial.print("[Firebase Error] Humidity: ");
            Serial.println(firebaseData.errorReason());
        }

        if (Firebase.setFloat(firebaseData, "/sensors/Soil_Moisture", moisturePercent)) {
            Serial.println("[Firebase Update] Soil Moisture updated.");
        } else {
            Serial.print("[Firebase Error] Soil Moisture: ");
            Serial.println(firebaseData.errorReason());
        }

        if (Firebase.setFloat(firebaseData, "/sensors/Temperature", avgTemp)) {
            Serial.println("[Firebase Update] Temperature updated.");
        } else {
            Serial.print("[Firebase Error] Temperature: ");
            Serial.println(firebaseData.errorReason());
        }
    }

    // Fetch Pump Control states every 100ms
    bool pump1State = false, pump2State = false, pump3State = false;

    if (Firebase.getBool(firebaseData, "/test/PumpControl/Pump1")) {
        pump1State = firebaseData.boolData();
        Serial.print("[Firebase Fetch] Pump1 State: ");
        Serial.println(pump1State ? "ON" : "OFF");
    } else {
        Serial.print("[Firebase Error] Pump1: ");
        Serial.println(firebaseData.errorReason());
    }

    if (Firebase.getBool(firebaseData, "/test/PumpControl/Pump2")) {
        pump2State = firebaseData.boolData();
        Serial.print("[Firebase Fetch] Pump2 State: ");
        Serial.println(pump2State ? "ON" : "OFF");
    } else {
        Serial.print("[Firebase Error] Pump2: ");
        Serial.println(firebaseData.errorReason());
    }

    if (Firebase.getBool(firebaseData, "/test/PumpControl/Pump3")) {
        pump3State = firebaseData.boolData();
        Serial.print("[Firebase Fetch] Pump3 State: ");
        Serial.println(pump3State ? "ON" : "OFF");
    } else {
        Serial.print("[Firebase Error] Pump3: ");
        Serial.println(firebaseData.errorReason());
    }

    // Control Pumps based on Firebase states
    if (pump1State) startPump1();
    else stopPump1();

    if (pump2State) startPump2();
    else stopPump2();

    if (pump3State) startPump3();
    else stopPump3();

    Serial.println("[Pump Control] Updated from Firebase.");

    delay(100);  // Firebase fetch interval remains 100ms
}

// Control functions for pumps
void startPump1() {
    Serial.println("[Pump1] Starting...");
    digitalWrite(PUMP1_IN1, HIGH);
    digitalWrite(PUMP1_IN2, LOW);
}

void stopPump1() {
    Serial.println("[Pump1] Stopping...");
    digitalWrite(PUMP1_IN1, LOW);
    digitalWrite(PUMP1_IN2, LOW);
}

void startPump2() {
    Serial.println("[Pump2] Starting...");
    digitalWrite(PUMP2_IN1, HIGH);
    digitalWrite(PUMP2_IN2, LOW);
}

void stopPump2() {
    Serial.println("[Pump2] Stopping...");
    digitalWrite(PUMP2_IN1, LOW);
    digitalWrite(PUMP2_IN2, LOW);
}

void startPump3() {
    Serial.println("[Pump3] Starting...");
    digitalWrite(PUMP3_IN1, HIGH);
    digitalWrite(PUMP3_IN2, LOW);
}

void stopPump3() {
    Serial.println("[Pump3] Stopping...");
    digitalWrite(PUMP3_IN1, LOW);
    digitalWrite(PUMP3_IN2, LOW);
}
