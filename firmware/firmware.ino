#include <ESP8266WiFi.h>
#include <DHT.h>
#include <NusabotSimpleTimer.h>
#include <MQTT.h>

NusabotSimpleTimer timer;
DHT dht(5, DHT11);
WiFiClient net;
MQTTClient client;

const char ssid[] = "follow_at_nusabot";
const char pass[] = "yaterserah";

float temp, humid;

void connect()
{
    Serial.print("Menghubungkan ke WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("Terhubung ke WiFi");
    Serial.print("Menghubungkan ke broker");
    while (!client.connect("chipid-unik", "public", "public"))
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Terhubung ke Broker");
}

void readSensor()
{
    humid = dht.readHumidity();
    temp = dht.readTemperature();

    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.println(temp);
}

void setup()
{
    Serial.begin(9600);
    WiFi.begin(ssid, pass);
    dht.begin();
    timer.setInterval(5000, readSensor);
    client.begin("public.cloud.shiftr.io", net);

    connect();
}

void loop()
{
    timer.run();
}