# 🌱Quenchtessential: Remote Plant Monitoring

> Water _quenches_ the thirst of plants, thus it is _quintessential_.

<img src="demo/the_solution.png" width="100%">

## 🧐 What?
Quenchtessential is an ESP32-based IoT solution built to automatically water my houseplant while monitoring its health in real-time through a full-stack dashboard app! 

### Features
- 

## 😱 Why? 
Life is busy as an eng student, so I don't want my plant to feel neglected.. Also, I was inspired by my previous company [Xandar Kardian](https://xkcorp.com/) and their vital sign sensor hardware + remote patient monitoring software solution and have been meaning to clone it mwuahahahaaah😈

## ⚙️ Architecture

### Tech Stack
- **Microcontroller**: ESP32 (C++ on PlatformIO)
- **Backend**: Node.js + Express (REST API)
- **Frontend**: React + Chart.js (data visualization)
- **Database**: PostgreSQL (hosted on Supabase)
- **Protocols**: MQTT (sensor data), HTTP (dashboard)
- **Hosting**: GitHub Pages (frontend), Render (backend)
- **CI/CD**: Docker (backend containerization), GitHub Actions (build/deploy)

### Circuit
- 

## 📸 Demos
⚠️⚠️⚠️UNDER CONSTRUCTION⚠️⚠️⚠️

### Full Video
Coming soon🤫

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
