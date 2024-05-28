# Turbo-Pup
8DOF Wheeled Robotic Dog Project

## Overview
Welcome to this robotic puppy project repository! This project combines the power of the Turbo Drive, an ESP32-based controlling board for motion control, and a Raspberry Pi 4B for advanced functionalities like gait planning, systematic modeling, and sensory extensions.

## Features

### Turbo Drive:
- **ESP32-S3**: Faster operation speed and capable of multithreading/core tasks.
- **Motor Control**:
  - Capable of controlling 8 leg servo motors.
  - Capable of controlling 4 wheel BLDC motors.
- **Current Sensing**: Inline current sensing for all four leg servos.
- **Signal Isolation**: All motor-driven signals are isolated by linear drivers.
- **IMU**: Integrated on-board IMU chip.
- **Display**: Utilization of an extended mini I2C OLED screen for extra status and information display.
- **Battery Monitoring**: Battery voltage monitor can be projected onto the mini I2C display.

### Raspberry Pi 4B:
- **Gait Planning**: Coordinated movement planning.
- **Visual System**: Camera integration for environment perception.
- **Module Integration**: Support for additional modules.
  - Laser radar SLAM for mapping and navigation.
- **Interactive Display**: Customizable faces displayed on a screen for communication.

### Additional Features:
- **Modular Design**: Easily expandable and customizable architecture.
- **PlatformIO and Arduino Structure**: Well-organized project structure for easy development and maintenance.

## Roadmap

### Main Objectives
- [x] Motion control for leg servo motors.
- [x] Motion control for wheel motors.
- [x] Math solvers.
- [ ] Gait planner.
- [ ] IMU integration.

### Extended Objectives
- [ ] Utilize extended I2C OLED screen for status display.
- [ ] Implement visual system with camera.
- [ ] Customizable faces display.
- [ ] Implement additional modules.

## Getting Started
I will need to start with some programming, so this part will be added first after finishing the main objectives.

## License
This project is licensed under the GPL 3.0 License, allowing for unrestricted use, modification, and distribution. See the LICENSE file for details.

## Disclaimer
Use the Turbo Pup robotic dog project at your own risk. The developers are not liable for any damage or injury caused by its use.

Happy building and coding with Turbo Pup! 🐾
