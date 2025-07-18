# 🌱Quenchtessential: IoT Plant Watering and Monitoring

> Water _quenches_ the thirst of plants, thus it is _quintessential_.

<img src="demo/the_solution.png" width="100%">

## 🧐 What?
Quenchtessential is an ESP32-based IoT solution built to automatically water my houseplant while monitoring its health through a full-stack [dashboard app](https://leogmendoza.github.io/quenchtessential/)! 

## 😱 Why? 
Life is busy as an eng student, so I don't want my plant to feel neglected.. Also, I was inspired by my previous company [Xandar Kardian](https://xkcorp.com/) and their vital sign sensor hardware + remote _patient_ monitoring software solution and have been meaning to clone it mwuahahahaaah😈

## ⭐ Features
- **Automated Watering**:  
  Uses an FSM to pump water and feed the plant when the moisture sensor says it meets the "thirsty threshold"

- **Live Health Monitoring**:  
  Displays real-time and historical moisture data on a modern web dashboard for trend visualization
  
- **WiFi-enabled**:  
  Connects to a network (w/o hardcoding credentials) using a captive portal and talks to the backend via MQTT
  
- **Plug-and-Play**:  
  Deployed & cloud-hosted full-stack app and wall-powered, so no local setup needed--as if it was a real product!

## ⚙️ System Architecture

### Block Diagram
<img src="demo/architecture.jpg" width="80%">

### Tech Stack
- **Microcontroller**: ESP32 (C++ on PlatformIO w/ FreeRTOS)
- **Backend**: Node.js + Express (REST API)
- **Frontend**: React + Chart.js (data visualization)
- **Database**: PostgreSQL (hosted on Supabase)
- **Protocols**: MQTT (sensor data), HTTP (dashboard)
- **Hosting**: GitHub Pages (frontend), Render (backend)
- **CI/CD**: Docker (backend containerization), GitHub Actions (build/deploy)

### Circuit Components
- ESP32 Dev Board
- Capacitive Soil Moisture Sensor
- 5V Relay Module
- 5V Water Pump
- 9V Breadboard Power Supply

## 📸 Demos

### Pumping Test
<img src="demo/pumping_test.gif" width="60%">

### WiFi Setup
<img src="demo/wifi.gif" width="60%">

### Overview Video
[![Overview Video](https://img.youtube.com/vi/Terha1n3Sfg/0.jpg)](https://www.youtube.com/watch?v=Terha1n3Sfg)

### Pumping Demo Video
[![Pumping Demo Video](https://img.youtube.com/vi/Bf9aWEiihe4/0.jpg)](https://www.youtube.com/watch?v=Bf9aWEiihe4)

## GitHub Actions Workflows

[![Frontend Deployment](https://github.com/leogmendoza/quenchtessential/actions/workflows/frontend-cd.yml/badge.svg)](https://github.com/leogmendoza/quenchtessential/actions/workflows/frontend-cd.yml)

[![ESP32 Build](https://github.com/leogmendoza/quenchtessential/actions/workflows/esp32-ci.yml/badge.svg)](https://github.com/leogmendoza/quenchtessential/actions/workflows/esp32-ci.yml)

[![Backend Build](https://github.com/leogmendoza/quenchtessential/actions/workflows/backend-ci.yml/badge.svg)](https://github.com/leogmendoza/quenchtessential/actions/workflows/backend-ci.yml)

Call the **Backend API** yourself!:  
- [GET history?range=live](https://quenchtessential-backend.onrender.com/history?range=live)
- [GET history?range=24h](https://quenchtessential-backend.onrender.com/history?range=24h)
- [GET history?range=7d](https://quenchtessential-backend.onrender.com/history?range=7d)
- [GET history?range=all](https://quenchtessential-backend.onrender.com/history?range=all)
- [GET last-watered](https://quenchtessential-backend.onrender.com/last-watered)

## Resources/Inspo
- ["Preventing Plant Death with Technology" by Emilostuff](https://youtu.be/9Fx9zQJe3H4?si=yKk7J3-3mnWMjWvk)
- ["I gave a plant DEPRESSION" by Kevin Gong](https://youtu.be/e1WxDusYRaw?si=OXE9YvLOd8fOHdHj)
- Internship at [Xandar Kardian](https://xkcorp.com)
