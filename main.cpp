#define MONITOR_SERIAL Serial
#define RADAR_SERIAL Serial1

#define RADAR_RX_PIN 17
#define RADAR_TX_PIN 18

#define LED_PIN 16
#define LIGHT_SENSOR_PIN 4

#include <ld2410.h>

ld2410 radar;

unsigned long lastPrint = 0;

void setup()
{
  MONITOR_SERIAL.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);

  RADAR_SERIAL.begin(256000, SERIAL_8N1, RADAR_RX_PIN, RADAR_TX_PIN);

  if (radar.begin(RADAR_SERIAL))
  {
    MONITOR_SERIAL.println("Radar connected");
  }
  else
  {
    MONITOR_SERIAL.println("Radar not connected");
  }
}

void loop()
{
  radar.read();

  bool dark = digitalRead(LIGHT_SENSOR_PIN);   // 1 = tối , 0 = sáng
  bool presence = radar.presenceDetected();

  // Điều kiện bật đèn
  if (dark && presence)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  // In trạng thái mỗi 1 giây
  if (millis() - lastPrint > 1000)
  {
    lastPrint = millis();

    Serial.print("Light: ");
    if(dark) Serial.print("Dark ");
    else Serial.print("Bright ");

    Serial.print("| Presence: ");
    if(presence) Serial.println("Detected");
    else Serial.println("None");
  }
}