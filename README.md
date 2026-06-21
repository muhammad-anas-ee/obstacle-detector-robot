# 🤖 Obstacle Detection Robot

An autonomous obstacle-avoiding robot built with **Arduino Uno**, **HC-SR04 Ultrasonic Sensor**, and a **Servo Motor** for dynamic 180° scanning. Developed as a lab project for **EL1005 — Digital Logic Design Lab** at FAST-NUCES, CFD Campus.

---

## 📸 Project Demo

![Obstacle Detection Robot - Front View](images/car_photo_1.jpg)
![Obstacle Detection Robot - Side View](images/car_photo_2.jpg)

---

## ⚙️ How It Works

1. The **ultrasonic sensor** is mounted on a **servo motor** at the front of the robot.
2. The servo scans **left (160°)**, **center (90°)**, and **right (20°)** to detect obstacles.
3. **Distance = (Time × Speed of Sound) / 2**
4. If an obstacle is detected within **20 cm**, the robot:
   - Stops
   - Scans left and right
   - Turns toward the side with more clearance
5. If both sides are blocked, it reverses and turns right.

---

## 🧰 Components

| Component | Quantity | Unit Price (PKR) | Total (PKR) |
|---|---|---|---|
| Arduino Uno | 1 | 1800 | 1800 |
| Ultrasonic Sensor (HC-SR04) | 1 | 500 | 500 |
| Motor Driver Shield (L293D) | 1 | 1200 | 1200 |
| TT Gear Motor | 4 | 150 | 600 |
| Servo Motor | 1 | 900 | 900 |
| Wheels | 4 | 50 | 200 |
| 18650 Li-ion Battery | 2 | 120 | 240 |
| 18650 Battery Holder | 1 | 60 | 60 |
| Jumper Wires (pack) | 1 | 200 | 200 |
| DC Power Switch | 1 | 60 | 60 |
| Acrylic Sheet (chassis) | 1 | 300 | 300 |
| **Total** | | | **6060** |

---

## 📁 Repository Structure

```
obstacle-detector-robot/
│
├── obstacle_detector.ino   # Main Arduino sketch
├── images/
│   ├── car_photo_1.jpg
│   └── car_photo_2.jpg
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8+ or v2.x)
- `Servo.h` library (built-in with Arduino IDE)

### Upload Steps
1. Clone this repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/obstacle-detector-robot.git
   ```
2. Open `obstacle_detector.ino` in Arduino IDE.
3. Connect your Arduino Uno via USB.
4. Select **Board:** Arduino Uno and correct **Port**.
5. Click **Upload**.

### Pin Configuration

| Component | Arduino Pin |
|---|---|
| Ultrasonic TRIG | A0 |
| Ultrasonic ECHO | A1 |
| Motor A Enable (PWM) | D5 |
| Motor A IN1 | D2 |
| Motor A IN2 | D4 |
| Motor B Enable (PWM) | D6 |
| Motor B IN1 | D7 |
| Motor B IN2 | D8 |
| Servo Motor | D9 |

---

## 📊 Results

- ✅ Successfully detected and avoided obstacles on flat surfaces
- ✅ 180° scanning via servo provided wide angular detection
- ✅ Reliable real-time direction decision-making
- ⚠️ Minor delay observed due to sensor response time and motor friction

---

## 👥 Team

| Name | Roll No. |
|---|---|
| Muhammad Anas | 24F-6125 |
| Muhammad Usman | 24F-6118 |

**Submitted to:** Engr. Rana Mubeen Tariq — Lab Engineer, EE Department  
**Institution:** FAST-NUCES, Chiniot-Faisalabad (CFD) Campus

---

## 🔗 Connect

- 💼 LinkedIn: [Muhammad Anas](https://www.linkedin.com/in/YOUR_LINKEDIN_USERNAME)

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).
