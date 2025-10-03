#include <WiFi.h>
#include "ThingSpeak.h"

// --- KONFIGURASI JARINGAN & THINGSPEAK ---
const char ssid[] = "nama_wifi(ssid)";
const char pass[] = "password_wifi";
unsigned long myChannelNumber = 3098791;
const char * myWriteAPIKey = "IQABIJ64BYEJDYKQ";

const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 2;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); 
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Mencoba terhubung ke SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nTerhubung ke WiFi.");
  }

  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.03421 / 2;

  if (distance < 10 && distance > 0) {
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(ledPin, HIGH);
    Serial.println("Objek terdeteksi! Mengirim data ke ThingSpeak...");

    int httpCode = ThingSpeak.writeField(myChannelNumber, 1, distance, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Channel berhasil diupdate.");
    } else {
      Serial.println("Gagal update channel. Kode eror HTTP: " + String(httpCode));
    }

    delay(10000); 

  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Tidak ada objek dekat. Tidak mengirim data.");
  }
  
  Serial.println("------------------------------------");

  delay(1000); 
}