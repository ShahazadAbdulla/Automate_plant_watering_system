﻿# Automated Plant Watering & Nutrition System
Sproutify is a smart, automated plant care system that monitors soil and environmental conditions to provide optimal water and nutrition to plants. It uses real-time sensor data and machine learning models to predict water and nutrient requirements, ensuring efficient and sustainable plant growth.

﻿# 🚀 Project Overview
This system automates the process of watering plants and delivering essential nutrients like Nitrogen (N), Phosphorus (P), and Potassium (K) by analyzing sensor data and applying predictive models.

﻿# How It Works
Sensor Data Collection:

🌿 NPK Sensor: Measures nitrogen, phosphorus, and potassium levels in the soil.
💧 Soil Moisture Sensor (HW-103): Monitors soil moisture to prevent over/under-watering.
🌡️ DHT11 Sensor: Captures temperature and humidity data to adjust water needs based on environmental factors.
Data Analysis & Prediction:

Sensor data is processed to predict water and nutrient requirements.
Machine learning models can be integrated for better accuracy.
Automated Watering & Nutrition:

Based on predictions, water pumps are activated via an ESP32-controlled motor driver.
Real-time monitoring and control through Firebase.
Remote Control:

Users can view sensor data and control pumps via a mobile app integrated with Firebase.
🔍 Potential Machine Learning Models
You can integrate these models to predict water and nutrient requirements:

﻿# 🌾 Soil Moisture Prediction:
LSTM (Long Short-Term Memory) for time-series moisture forecasting.
🍃 Nutrient Requirement Prediction:
Random Forest or XGBoost using NPK levels and plant type as features.
☀️ Environmental Impact Analysis:
Linear Regression to assess humidity and temperature impacts.
🌱 Plant Growth Optimization:
KNN (K-Nearest Neighbors) to predict nutrient needs based on historical data.
🛠️ Tech Stack
ESP32: Microcontroller for sensor interfacing and control.
Firebase: Real-time database for monitoring and control.
DHT11: Temperature and humidity sensing.
HW-103 Soil Sensor: Soil moisture measurement.
Motor Driver (L298N): Controls pumps for water and nutrient delivery.
C++ (Arduino): Embedded programming.
﻿# 🔧 Installation & Usage
 
Clone the repository:
git clone "link"
Install necessary libraries in Arduino IDE:

WiFi.h
FirebaseESP32
DHT.h
Upload Code to ESP32:

Open MainCode.ino in Arduino IDE.
Adjust Wi-Fi credentials and Firebase config if needed.
Upload to ESP32.
Monitor System:

Open Firebase Realtime Database to view live sensor readings.
Control pumps remotely via Firebase.
📊 Real-Time Data Insights
Parameter	Sensor	Unit	Usage
Soil Moisture	HW-103	%	Triggers watering if below threshold.
Temperature	DHT11	°C	Adjusts watering based on conditions.
Humidity	DHT11	%	Adjusts watering based on conditions.
NPK Levels	NPK Sensor	mg/kg	Predicts nutrient needs for growth.
🌿 Sustainability Focus
Water Conservation: Provides only the required water amount.
Precision Agriculture: Tailors nutrition based on real-time analysis.
Remote Monitoring: Reduces manual intervention.
⚙️ Future Improvements
🌾 Plant-Specific Watering Models.
🧠 AI-based Growth Pattern Recognition.
📱 Mobile App Interface for better user experience.
☀️ Solar Power Integration for energy efficiency.
🧠 Contributing
We welcome contributions to improve this project! Feel free to fork the repo and submit pull requests.

🌱 Happy Growing! 🌏
