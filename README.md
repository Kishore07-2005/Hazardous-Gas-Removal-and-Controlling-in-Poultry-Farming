# IoT Hazardous Gas Monitoring and Control System in Poultry Farming 🐓🌍

This project monitors hazardous gases (like ammonia) in poultry farms using an **ESP8266 WiFi module** and an **MQ2 gas sensor**.  
When unsafe gas levels are detected, the system **automatically turns on a ventilator** for circulation, while a **buzzer and LED indicators** provide local alerts.  
The project also integrates with the **Blynk IoT platform** for real-time monitoring and notifications.

---

## 🚀 Features
- Real-time detection of hazardous gases
- Automatic ventilator control for safety
- Buzzer + LED indicators for local alerts
- Remote monitoring via **Blynk mobile dashboard**
- Scalable design for larger poultry setups

---

## 🛠️ Components Used
- ESP8266 WiFi Module  
- MQ2 Gas Sensor  
- Ventilator (fan)  
- Buzzer & LED indicators  
- Blynk IoT Platform  

---

## ⚙️ How It Works (Step by Step)

1. **Power & Warm-Up**  
   MQ2 sensor powers on and warms up (~20–30 s) for stable readings.

2. **Connect to Network**  
   ESP8266 connects to Wi-Fi and authenticates with the Blynk project. If it drops, it keeps trying in the background.

3. **Read & Smooth Sensor Data**  
   Analog value from MQ2 (A0) is sampled every N ms and passed through a small moving average to reduce noise.

4. **Compare with Threshold + Hysteresis**  
   The smoothed value is compared against a user-defined **gas_threshold**.  
   A small **hysteresis** (e.g., 5–10%) prevents rapid ON/OFF flicker.

5. **Trigger Safety Actions (High Gas)**  
   - Turn **VENTILATOR = ON** (GPIO)  
   - Activate **BUZZER + LED** for local alert  
   - Push live value and status to **Blynk** (gauge, status text, and event/notification)

6. **While Levels Stay High**  
   Ventilator remains ON; buzzer can beep in intervals. Readings and status continue to update on Blynk.

7. **Recovery (Safe Levels Restored)**  
   When value < (threshold − hysteresis) for a few consecutive samples:  
   - **Buzzer + LED = OFF**  
   - Keep **ventilator ON** for a short **cool-down** (e.g., 10–30 s), then **OFF**  
   - Update Blynk widgets to “Normal”

8. **Manual Override from App (Optional)**  
   A Blynk switch can **force ventilator ON/OFF**. While override is active, auto control is paused.

9. **Failsafe Logic**  
   If Wi-Fi/Blynk is unavailable, local control (sensor → ventilator/buzzer/LED) **continues offline**; data syncs once reconnected.
 

---

## 🚀 Future Enhancements

- **Ammonia-specific sensing:** Add MQ-135/MQ-137 or an electrochemical NH₃ sensor for higher accuracy and easier calibration.  
- **Environment context:** Add **DHT22** (temp/humidity) and use it to adjust thresholds based on conditions.  
- **Cloud data logging & dashboards:** Stream to **Blynk history**, Google Sheets, ThingSpeak, or **InfluxDB + Grafana** for trends and reports.  
- **Multi-channel alerts:** Push notifications + **email/SMS/WhatsApp/Telegram** for critical events.  
- **Adaptive thresholds (AI/TinyML):** Learn a rolling baseline, auto-tune setpoints by time of day/season, and flag anomalies.  
- **PWM speed control:** Drive the **ventilator** with a MOSFET + PWM for variable speed instead of just ON/OFF.  
- **Multi-node expansion:** Use **MQTT + Node-RED** to monitor multiple sheds/zones from a single dashboard.  
- **OTA updates & remote config:** Update ESP8266 firmware and tweak thresholds **over-the-air** from the app.  
- **Power & reliability:** Add a small UPS/battery, surge protection, watchdog timer, and brown-out handling.  
- **Calibration & self-test:** Guided calibration flow from the app (clean-air baseline), plus periodic reminders and a sensor-health check.
 

---

## 📸 Project Demo
**Blynk DashBoard** 
<img width="907" height="585" alt="image" src="https://github.com/user-attachments/assets/d4348c82-4f2d-4468-94b6-64509d704edf" />

**Project Setup video**
<img width="1362" height="766" alt="image" src="https://github.com/user-attachments/assets/d675ec23-f19f-458b-8b8d-801ccb463424" />



---

## ✍️ Author
- **KishoreKumar C**  
Electronics & Communication Engineering Student | IoT & Embedded Systems Enthusiast  
