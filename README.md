# Laporan-IOT-058-084

## 📌 Informasi Umum
**Judul Proyek: Mengukur Jarak dengan ESP32**
**Anggota Tim:**  
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
Tambahkan diagram alur atau arsitektur sistem IoT. Bisa berupa flowchart atau diagram blok.  
```text
Sensor → Microcontroller → Cloud → Dashboard
```
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