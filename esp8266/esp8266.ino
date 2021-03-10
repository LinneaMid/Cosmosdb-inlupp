#include <ESP8266WiFi.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

char* ssid = "Mi_Guest";
char* pass = "Mider@7719950";
char* conn = "HostName=iot20-lin-iothub.azure-devices.net;DeviceId=ESP8266;SharedAccessKey=9elwtEoJcmrNjLsifwSSCKJ1G3wk26f+aHFVaUeEFMU=";

bool messagePending = false;
float prevTemp = 0;
time_t epochTime;

DHT dht(DHT_PIN, DHT_TYPE);
IOTHUB_CLIENT_LL_HANDLE deviceClient;

void setup() {
  initSerial();
  initWifi();
  initEpochTime();
  initDHT();
  initDevice();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  float currentTemp = temperature;

  if (!messagePending) {
    if ((currentTemp > (prevTemp + 1)) || (currentTemp < (prevTemp - 1))) {
      prevTemp = currentTemp;

      epochTime = time(NULL);
      Serial.printf("Current Time: %lu. ", epochTime);

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(", Humidity: ");
      Serial.println(humidity);

      delay(500);

      if (!(std::isnan(temperature)) && !(std::isnan(humidity)))  {
        char payload[256];

        StaticJsonBuffer<sizeof(payload)> buf;
        JsonObject &root = buf.createObject();
        root["device"] = "esp8266";
        root["macAddress"] = WiFi.macAddress();
        root["ts"] = epochTime;
        root["temp"] = temperature;
        root["hum"] = humidity;
        root.printTo(payload, sizeof(payload));

        sendMessage(payload);
      }
    }
  }

  IoTHubClient_LL_DoWork(deviceClient);
  delay(10);

}
