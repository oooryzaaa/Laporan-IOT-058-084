# Laporan-IOT-058-084

## 📌 Informasi Umum
**Judul Proyek: Mengukur Jarak dengan ESP32**
**Anggota:**  
| Nama                      | NRP        |
| --------------------------| ---------- |
| Ica Zika Hamizah          | 5027241058 |
| Oryza Qiara Ramadhani     | 5027241084 |

**Platform/Board: ESP32**
**Bahasa Pemrograman: C++** 
**Topik: Mengukur Jarak**

---

## 🎯 Tujuan Proyek
- Memantau suhu dan kelembaban secara real-time.  
- Mengirim data sensor ke Thingspeak. 

---

## 🛠️ Alat dan Bahan
- **Hardware:**   
  - [ESP32]  
  - [HC-SR04] 
  - [LED]  
  - [Kabel Jumper]  

- **Software:**  
  - [Arduino IDE]  
  - [C++]  
  - [ThingSpeak]  

---

## 📐 Diagram Sistem
```text
    +-----------+
    |  Sensor   |
    | HC-SR04   |
    +-----+-----+
          |
          v
 +-----------------+
 | Microcontroller |
 |      ESP32      |
 +-----------------+
 |  - Baca sensor  |
 |  - Proses data  |
 |  - Kontrol LED  |
 +--------+--------+
          |
          v
   +--------------+
   |  Internet    |
   |   (WiFi)     |
   +------+-------+
          |
          v
    +------------+
    | ThingSpeak |
    |  Channel   |
    +------------+
          |
          v
    +-------------+
    | Dashboard   |
    | (Grafik /   |
    |  Monitoring)|
    +-------------+
```
### 💡 Penjelasan Alur Data
1. **HC-SR04** mengukur jarak dan mengirim data ke ESP32.  
2. **ESP32** membaca data, memprosesnya, dan bisa menyalakan LED jika jarak tertentu tercapai.  
3. ESP32 mengirim data ke **ThingSpeak** melalui WiFi (HTTP POST/MQTT).  
4. **ThingSpeak Channel** menyimpan data sensor.  
5. **Dashboard ThingSpeak** menampilkan data real-time dalam bentuk grafik.  

## [gambar] Penjelasan Code

Kode berikut digunakan untuk membaca jarak menggunakan sensor ultrasonik (HC-SR04) yang terhubung ke ESP32, menyalakan LED jika objek terdeteksi pada jarak tertentu, serta mengirimkan data jarak tersebut ke ThingSpeak untuk dicatat dan divisualisasikan.

### Library yang Digunakan
```cpp
#include <WiFi.h>
#include "ThingSpeak.h" 
```
- WiFi.h → digunakan untuk menghubungkan ESP32 ke jaringan WiFi.
- ThingSpeak.h → library resmi untuk mengirim/mengambil data dari platform ThingSpeak.

### Konfigurasi WiFi & ThingSpeak
```cpp
const char ssid[] = "nama_wifi(ssid)";
const char pass[] = "password_wifi";
unsigned long myChannelNumber = 3098791;
const char * myWriteAPIKey = "IQABIJ64BYEJDYKQ";
```
- ssid → nama jaringan WiFi.
- pass → password WiFi.
- myChannelNumber → nomor channel di ThingSpeak tempat data akan dikirim.
- myWriteAPIKey → kunci API untuk autentikasi agar bisa menulis data ke channel.

### Definisi Pin
``` cpp
const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 2;
```
- trigPin → pin TRIG sensor HC-SR04 (output).
- echoPin → pin ECHO sensor HC-SR04 (input).
- ledPin → pin untuk LED indikator.

### Objek WiFi Client
``` cpp
WiFiClient client;
```
Membuat objek client yang digunakan untuk koneksi HTTP dengan server ThingSpeak.

### Setup Awal
```cpp
void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); 
}
```

Serial.begin(9600) → memulai komunikasi serial untuk debugging.

pinMode(...) → atur pin sensor dan LED sebagai input/output.

WiFi.mode(WIFI_STA) → mengaktifkan mode station (ESP32 jadi client WiFi).

ThingSpeak.begin(client) → inisialisasi koneksi ke ThingSpeak.

