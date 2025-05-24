#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "YourDeviceName"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

#define RELAY_PIN D1
#define SOIL_PIN A0

int dryThreshold = 600; // Tune based on testing
SimpleTimer timer;

void checkSoilMoisture() {
  int moisture = analogRead(SOIL_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(moisture);

  // Send raw moisture value to Blynk (V2)
  Blynk.virtualWrite(V2, moisture);

  // Determine wet/dry status
  if (moisture > dryThreshold) {
    digitalWrite(RELAY_PIN,HIGH); // Pump ON
    Blynk.virtualWrite(V3, "Dry 🌵");  // Send status text to V3
  } else {
    digitalWrite(RELAY_PIN, LOW); // Pump OFF
    Blynk.virtualWrite(V3, "Wet 💧");  // Send status text to V3
  }
}


void setup()
{
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  timer.setInterval(60000L, checkSoilMoisture); // Every 60 sec
}

// This function is called every time you press the button in the Blynk app
BLYNK_WRITE(V1)                      // V1 = virtual pin assigned to the button
{
  int state = param.asInt();         // 1 = button ON, 0 = button OFF

  if (state == 1) {
    digitalWrite(RELAY_PIN, HIGH);    // Turn relay ON
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn relay OFF
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}