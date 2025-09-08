#define BLYNK_TEMPLATE_ID "TMPL3kWX8VQ69"
#define BLYNK_TEMPLATE_NAME "Hazardous Gas Monitor"
#define BLYNK_AUTH_TOKEN "0SquEN1OC4lu9VIShWU5SINCZbLHWWCZ"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "your wifi name";
char pass[] = "your password";

#define MQ2_PIN A0
#define BUZZER_PIN D5
#define LED_PIN D6  // Optional physical LED
#define RELAY_PIN D7  // Relay control for the fan

BlynkTimer timer;
int threshold = 30;

void sendSensor() {
  int mq2Value = analogRead(MQ2_PIN);
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value);  // Print the MQ2 sensor reading to the Serial Monitor

  Blynk.virtualWrite(V0, mq2Value); // Send sensor value to Blynk gauge/chart

  if (mq2Value > threshold) {
    digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON
    digitalWrite(LED_PIN, HIGH);     // LED ON (optional)
    digitalWrite(RELAY_PIN, HIGH);   // Fan ON (Relay triggered)
    Blynk.virtualWrite(V1, "🚨 Danger");
    Blynk.virtualWrite(V2, 255);     // LED widget ON in Blynk
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Buzzer OFF
    digitalWrite(LED_PIN, LOW);      // LED OFF
    digitalWrite(RELAY_PIN, LOW);    // Fan OFF (Relay turned off)
    Blynk.virtualWrite(V1, "✅ Safe");
    Blynk.virtualWrite(V2, 0);       // LED widget OFF in Blynk
  }
}

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as output

  digitalWrite(BUZZER_PIN, LOW);  // Start with buzzer OFF
  digitalWrite(LED_PIN, LOW);     // Start with LED OFF
  digitalWrite(RELAY_PIN, LOW);   // Start with fan OFF

  // Debug: Check Wi-Fi connection
  Serial.println("Connecting to Wi-Fi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection failed!");
  } else {
    Serial.println("Connected to WiFi");
  }

  timer.setInterval(1000L, sendSensor); // Check the sensor value every second
}

void loop() {
  Blynk.run();  // Run Blynk functions
  timer.run();  // Run timer-based functions
}
