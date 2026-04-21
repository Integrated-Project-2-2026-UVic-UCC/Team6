# Drone Cable Routing Accessory: Project Documentation

**Institution:** Universitat de Vic – Universitat Central de Catalunya  
**Course:** Integrated Project II  
**Academic Year:** 2025–2026  
**Project Group:** Team 6  

---

## 1. Project Overview
This project focuses on the design, development, and integration of a remote-controlled attachable hook and pulley system for drones. The primary application is to facilitate automated and safe **cable routing** in environments where manual deployment is hazardous, inefficient, or physically restricted.

## 2. Objectives
The project is driven by a clear set of technical and operational goals:

### 2.1 Main Objective
* To design and assemble a fully functional, remote-controlled hook attachment for drone-assisted cable deployment.

### 2.2 Specific Objectives
* **Pulley System:** Develop a reliable mechanism for cable management and tension control.
* **Safety Features:** Integrate hardware and software failsafes (such as limit switches) to ensure secure operations.
* **RF Communication:** Establish a robust Radio Frequency link via ESP-NOW for low-latency control.
* **Validation:** Conduct rigorous testing to optimize performance and payload stability.

---

## 3. Team Organization and Methodology
The project follows a structured multidisciplinary model managed under the **Scrum Framework**.

### 3.1 Roles and Responsibilities
* **Project Leader:** Jan Font
* **Mechanical Manager:** Martí Alsina
* **Electrical Manager:** Oriol Bonet
* **Software Manager:** Xavier Vilalta

---

## 4. Technical Architecture and Progress
The system is divided into three fundamental engineering pillars. Below is the progress achieved as of the current development phase:

### 4.1 Mechanical Tasks
* **Claw and Pulley Design:** Developed functional 3D designs for the mechanical gripping system.
* **Component Housing:** Finalized the protective enclosure to integrate all onboard electronics (XIAO ESP32-S3, relays, and batteries).
* **Final Assembly:** Currently proceeding with the integration of mechanical parts and electronics into the final flight-ready chassis.

### 4.2 Electrical and Software Tasks
* **Control Logic:** Implementation of an ESP-NOW communication protocol between the Transmitter and Receiver.
* **Actuation System:** Dual relay H-bridge setup for the high-power external motor and a dedicated servo for the claw mechanism.
* **Safety Integration:** Implementation of a **59170-1-S-00-D magnetic proximity sensor** acting as a "Limit Switch" (Final de carrera). 
    * **Hardware:** Connected to Pin D1 (GPIO 2) of the receiver.
    * **Logic:** The software prioritizes the sensor input; if a magnet is detected, the motor is automatically halted regardless of transmitter commands.
* **Power Management:** 5V regulation for logic and dedicated power for motor actuation via relays.

---

## 5. Project Roadmap and Current Status
The project is transitioning from component-level validation to full system integration and field testing.

### 5.1 Achievements to Date
* Successful RF communication link with safety overrides.
* Validation of the electrical control circuit and relay-based motor inversion.
* Completed 3D-printed components for the final prototype.
* Advanced software state: Final logic implemented, including safety limit failsafes.

### 5.2 Current Status
* **Assembly:** Final prototype construction is underway.
* **Testing:** Initial functional tests of the integrated system are being performed.
* **Iterative Improvements:** Refining the pulley tension and claw grip based on physical feedback.

### 5.3 Next Steps
* Full field testing with drone flight to validate payload stability.
* Optimization of the magnetic sensor placement for precise limit detection.
* Final documentation and performance reporting.

---

## 6. References
* Madsen, M. (2018). *DJI Phantom 3 – Payload Dropper v2*.
* Drone Sky Hook. *Dual Release and Drop PLUS for DJI Phantom 3*.
* 3Deddy. (2019). *DJI Phantom 3 – Payload Dropper*.
