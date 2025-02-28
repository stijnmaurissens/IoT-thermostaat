#define BLYNK_TEMPLATE_ID "user4"
#define BLYNK_TEMPLATE_NAME "user4@server.wyns.it"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char auth[] = "yQHG91Cj5sPK_GHya43KiVRyqxOtYj1O";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Proximus-Home-035278";
char pass[] = "sesmneh5r7bwum4z";


#define PIN_RED 23
#define PIN_GREEN 22
#define PIN_BLUE 21
int gewenst;

BlynkTimer timer;
WidgetLED led1(V3);

BLYNK_CONNECTED() {
  // Turn LED on, so colors are visible
  led1.on();
}

BLYNK_WRITE(V1) {
  gewenst = param.asInt();  // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(gewenst);
}
void setup() {
  // Debug console
  Serial.begin(115200);
  sensors.begin();
  delay(1000);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
  timer.setInterval(1000L, sendSensor);
  Blynk.setProperty(V3, "LED", "#ff0000");
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
}

void loop() {
  float t = sensors.getTempCByIndex(0);


  Blynk.run();
  timer.run();
  sensors.requestTemperatures();
  Blynk.virtualWrite(V5, sensors.getTempCByIndex(0));

   if ( t > gewenst) {
    setColor(255, 0, 0);
    led1.setColor("#ff0000");  //rood betekend dat de verwarming aan het verwarmen is
  } else if (gewenst >= t) {
    setColor(0, 255, 0);
    led1.setColor("#00ff00");  //groen laat weten dat het warm genoeg is
  }
}

void setColor(int R, int G, int B) {
  analogWrite(PIN_RED, R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE, B);
}

void sendSensor() {
  //float h = dht.readHumidity();
  float t = sensors.getTempCByIndex(0);
  Blynk.virtualWrite(V4, t);  // select your virtual pins accordingly
}
