# 🚦 Smart Traffic Management System

## 📌 Overview
The **Smart Traffic Management System** is an IoT-based solution designed to optimize traffic flow using real-time data from sensors and cameras. This system dynamically adjusts traffic signals to reduce congestion, improve emergency response times, and enhance road safety.

## ✨ Features
- **Real-time Traffic Monitoring**: Uses ESP32 Cam & WiFi modules to capture and transmit live traffic data.
- **Dynamic Signal Control**: Adjusts signal timings based on traffic density.
- **Emergency Vehicle Detection**: Prioritizes emergency vehicles by adjusting signal timing.
- **Web Dashboard**: Displays live traffic data and analytics.
- **Scalability**: Can be integrated with smart city infrastructure.

## 🛠️ Tech Stack
- **Hardware**: ESP32-CAM, ESP8266, Ultrasonic Sensors
- **Software**: Python, Arduino C, OpenCV, Flask (for backend)
- **Cloud Services**: Firebase (for real-time data storage & analysis)

## 🚀 Installation & Setup

### 1️⃣ Clone the Repository
```bash
 git clone https://github.com/yourusername/smart-traffic-management.git
 cd smart-traffic-management
```

### 2️⃣ Hardware Setup
- Connect **ESP32-CAM** for video streaming.
- Integrate **ESP8266 WiFi Module** for cloud connectivity.
- Attach **Ultrasonic Sensors** to detect vehicle density.

### 3️⃣ Update Configuration Variables
Before running the system, update the following variables in the `config.py` or Arduino script:

- **WiFi Credentials**
  ```cpp
  #define WIFI_SSID "Your_WiFi_Name"
  #define WIFI_PASSWORD "Your_WiFi_Password"
  ```
- **Firebase Credentials** (if used)
  ```python
  FIREBASE_URL = "https://your-firebase-app.firebaseio.com/"
  ```
- **Camera Stream URL**
  ```python
  CAMERA_IP = "http://your-esp32-ip:81/stream"
  ```

### 4️⃣ Install Dependencies
```bash
pip install -r requirements.txt
```

### 5️⃣ Run the System
```bash
python main.py
```

## 📊 How It Works
1. **ESP32-CAM** captures traffic images and streams them to the system.
2. **Ultrasonic sensors** measure traffic density at different junctions.
3. **Data Processing**: The Python backend analyzes traffic and adjusts signal timings dynamically.
4. **Real-time Dashboard** displays the current traffic conditions.
5. **Emergency Mode** is activated when an ambulance is detected, adjusting signals accordingly.

## 🔧 Troubleshooting
- **ESP32 not connecting?**
  - Check WiFi credentials.
  - Ensure ESP32 is flashed with the correct firmware.
- **No live stream from ESP32-CAM?**
  - Verify IP address in the script.
  - Restart ESP32 and recheck the serial monitor.
- **Firebase not updating?**
  - Check API keys and database rules.

## 📜 License
This project is open-source under the MIT License.

## 🤝 Contributing
We welcome contributions! Feel free to fork, raise issues, or submit pull requests.

## 📧 Contact
For queries, contact [Your Name](mailto:your-email@example.com).
