# Emb-Alex-41-Obstacle-Avoiding-Robot
This repository contains the code, schematic and design files for an Obstacle-Avoiding Robot, developed as the graduation project for the AMIT Embedded Systems / Alex 41 Diploma. The robot autonomously navigates its environment, using an ultrasonic sensor mounted on a servo motor to detect obstacles and make movement decisions. The codes work with ATmega32, ATmega32A and their counterparts.

# Team Members 
- Abdullah Etman
- Anas Dorgham

# Features
- Ultrasonic Sensor on Servo Motor: The sensor is centered by default and rotates to scan the surroundings for obstacles.
- Dynamic Path Adjustment: The robot turns left, right, or performs a 180-degree turn based on the distance readings from the sensor.
- LCD Display: The robot displays its current direction and distance readings in real-time.
- Smooth Motor Control: The robot uses DC motors for forward and turning movements, ensuring smooth navigation and obstacle avoidance.

# Components
- 2x BO DC Motor
- 2x Wheels
- 4x 3.7V Li-ion Battery
- 1x Buck Converter (Step-down Converter)
- 1x Ultrasonic Sensor
- 1x Servo Motor
- 1x LCD (16x2)
- 1x L293D (H-Bridge)
- 2x 100nF capacitors
- 1x 330Ω resistors
- 1x LED
- 1x AMIT Kit (Includes ATmega32A, Crystal Oscillators, Resistors, Capacitors, a Reset Push Button, a Power On/Off Switch, and Power Supply Ports)
- Jumper Wires

# How It Works
- The ultrasonic sensor, mounted on a servo motor, initially checks the distance ahead.
- If no obstacle is detected, the robot moves forward.
- If an obstacle is detected, the robot stops and the servo motor rotates the sensor to check the right and left sides.
- Based on the readings, the robot either turns right, left, or performs a 180-degree turn.
- The servo motor is then re-centered, and the robot repeats the process.

# Technologies
- C Programming: For firmware development.
- Embedded C Libraries: For managing peripherals such as timers, motors, and sensors.

# Usage
This project can be used as a foundation for learning about embedded systems, real-time control, sensor integration, and autonomous navigation.
