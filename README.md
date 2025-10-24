# 🌸 Women_Day (20.10 Project)

Welcome to **Women_Day**, the most unnecessarily charming ESP32 project you'll build this month.  
It’s basically an **ESP32 + Adafruit OLED display** setup that shows cool messages or animations to celebrate **20.10 – Vietnamese Women’s Day**.  
You know, because code can be romantic too, or at least what a nerd think.

---

## ✨ What It Does

- Lights up that cute little **OLED screen** with messages, icons, or anything you want.  
- Built with **ESP32** (because Wi-Fi and Bluetooth are never a bad idea).  
- Uses the **Adafruit SSD1306** library for the OLED (yes, the one everyone uses).  
- Fully customizable text, images, and timing.  
- Bonus points for making someone smile when they see it.

---

## 🧰 What You’ll Need

| Item | Purpose |
|------|----------|
| ESP32 board | The brain of this masterpiece |
| Adafruit OLED (SSD1306) | The tiny screen that does all the showing off |
| Jumper wires | You know what these do |
| Breadboard or soldered board | For “professional” vibes |
| Power supply | USB, battery, or sheer optimism |

---

## ⚡ Wiring

Connect the OLED to the ESP32 like this (I²C version):

| OLED Pin | ESP32 Pin |
|-----------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

> If nothing shows up on screen, congratulations, you’ve joined the universal club of “forgot the I²C address.”  
> (Default is usually `0x3C`, but check your module.)

---

## 🧑‍💻 Setup

1. Clone this thing:
   ```bash
   git clone https://github.com/ducklin404/women_day.git
   cd women_day

2. Open it with **PlatformIO** (in VS Code).
3. Make sure the board in `platformio.ini` matches your ESP32.
4. Connect your board and upload the code.
5. Watch magic happen. Or debugging messages. Sometimes both.

---

## 🎨 Customizing

Open the code in `src/main.cpp` (or wherever your genius lives) and tweak stuff like:

* Messages to display
* Font size or text position
* Animation delay
* Maybe even draw your own icons

Feeling fancy? Add:

* A **button** to switch messages.
* A **Wi-Fi connection** to fetch live quotes.
* Or an **RTC** to show real time (like a clock that compliments people).

---

## 🧩 Project Structure

```
women_day/
├── include/      # Header files, configs, and dreams
├── lib/          # Custom libraries (if any)
├── src/          # Main code goes here
├── test/         # Optional: where bugs go to die
└── platformio.ini # Config file for PlatformIO
```

---

## 🛠 Troubleshooting

| Problem            | What You Probably Did                              |
| ------------------ | -------------------------------------------------- |
| OLED is blank      | Wrong address, wiring, or power. Maybe all three.  |
| ESP32 won’t upload | You picked the wrong COM port, didn’t you?         |
| Text is garbled    | Wrong OLED type or resolution.                     |
| Nothing works      | Did you actually save before uploading? Be honest. |

---

## 💡 Ideas for the Future

* More fancy animation
* More fancy animation
* More fancy animation
* More fancy animation
* Over engineer the animation

---

## 📜 License

MIT License.
You can do whatever you want with this, just don’t sell it for a million dollars and pretend you invented OLEDs.

---

## 💬 Credits

Made by [ducklin404](https://github.com/ducklin404)
Built with caffeine, chaos, and mild affection for embedded systems.
