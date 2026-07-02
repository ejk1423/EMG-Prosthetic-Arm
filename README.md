# Myoelectric-prosthetic-hand
ESP32-based EMG-controlled 3D-printed prosthetic hand prototype using MyoWare muscle sensing and servo-driven tendon actuation.
# Overview

This project explores a low-cost myoelectric prosthetic hand design using an ESP32 microcontroller, a MyoWare 2.0 muscle sensor, a PCA9685 servo driver, and servo-actuated tendon mechanisms. The system reads surface EMG signals from muscle flexion, processes the input on the ESP32, and controls servo motors to open and close the 3D-printed hand.

The goal of this project is to build a functional prototype that demonstrates embedded sensing, signal thresholding, servo control, mechanical actuation, and assistive robotics design.

# Demo

Add demo GIF or video link here.

Example:




# Features
Reads EMG muscle activity using a MyoWare 2.0 muscle sensor
Uses an ESP32 for signal acquisition and control logic
Controls multiple servo motors through a PCA9685 PWM servo driver
Uses external 5V power delivery for reliable servo actuation
Implements tendon-driven finger movement using braided fishing line
Uses elastic return tension to reopen fingers
Includes 3D-printed hand and forearm components
