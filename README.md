# Turbo-Pup
8DOF mini wheeled Robotic dog Project 

Overview
# Turbo-Pup
8DOF mini wheeled Robotic dog Project 

Overview

Welcome to the Turbo Pup Robotic Dog project repository! This project combines the power of the Turbo Drive, an ESP32 based controlling board for motion control and  and a Raspberry Pi 4B for advanced functionalities such as gait planning, systematic modelling and sensory extensions.

Features:
Turbo Drive:
Using ESP32 S3 for a faster operation speed and being capable for multithreading/core tasks.
Include one USB-Micro for faster and easier debugging.
capable of control 8 leg servo motors.
capable of control 4 wheel BLDC motors.
Inline current sensing for all four ham servos.
All motor driven signals are isolated with a linear driver, which protects the MCU from unexpected situation and rises the 3.3v Output to 5v from signal pins.
Intergrate with a MPU6050 for Position detection.
Utilization of an extended mini IIC OLED screen for status and information display.
Battery voltage monitor.
Raspberry Pi 4B Functions:
Gait planning for coordinated movement.
Visual system with a camera for environment perception.
Integration of additional modules.
Customized face design for display.

Road map:
 Implement motion control for 8 leg servo motors.
 Integrate leg FK und IK.
 Implement motion control for 4-wheel block motors.
 Integrate MPU6050 IMU for stability.
 Utilize extended IIC OLED screen for status display.
 Implement gait planning on Raspberry Pi 4B.
 Integrate laser radar SLAM module.
 Implement visual system with camera.
 Design customizable faces for the robotic dog's screen.
 Implement additional functionalities (add as needed).
Getting Started:
Hardware Setup: Assemble the robotic dog according to the provided schematics and instructions.
Software Installation: Install the necessary software on both ESP32 S3 and Raspberry Pi 4B.
Configuration: Customize configuration files to match your hardware setup and preferences.
Compilation and Deployment: Compile and deploy code to respective devices following instructions in the repository.
Testing: Test functionality by wirelessly commanding the robotic dog and observing its behavior.
Contribution: Fork the repository, make modifications, and submit pull requests to contribute to the project.
Support:
For assistance or inquiries, open an issue on GitHub, and our community and development team will assist you promptly.

License:
This project is licensed under the MIT License, allowing for unrestricted use, modification, and distribution. See the LICENSE file for details.

Acknowledgments:
We thank the open-source community for their contributions and support, and the developers of ESP32 and Raspberry Pi platforms for enabling innovative robotics development.

Disclaimer:
Use the Turbo Pup robotic dog project at your own risk. The developers are not liable for any damage or injury caused by its use.

Happy building and coding with Turbo Pup! 🐾
Welcome to the Turbo Pup Robotic Dog project repository! This project combines the power of the Turbo Drive, an ESP32 based controlling board for motion control and  and a Raspberry Pi 4B for advanced functionalities such as gait planning, systematic modelling and sensory extensions.

Features:
Turbo Drive:
Using ESP32 S3 for a faster operation speed and being capable for multithreading/core tasks.
capable of control 8 leg servo motors.
capable of control 4 wheel BLDC motors.
Inline current sensing for all four ham servos.
All motor driven signals are isolated with a linear driver, which protects the MCU from unexpected situation/ rising the 3.3v Output to 5v from signal pins.
Intergrate with a MPU6050 for Position detection.
Utilization of an extended mini IIC OLED screen for status and information display.
Battery voltage monitor.

RaspberryPi4B:
Gait planning for coordinated movement.
Integration of additional modules:
Laser radar SLAM for mapping and navigation.
Visual system with a camera for environment perception.
Customizable faces displayed on a screen for interactive communication.
Modular Design: Easily expandable and customizable architecture to add new features and functionalities.
PlatformIO and Arduino Structure: Well-organized project structure for easy development and maintenance.
Todo List:
 Implement motion control for 8 leg servo motors.
 Integrate 2DOF forward and inverse kinematics.
 Implement motion control for 4-wheel block motors.
 Integrate MPU6050 IMU for stability.
 Utilize extended IIC OLED screen for status display.
 Implement gait planning on Raspberry Pi 4B.
 Integrate laser radar SLAM module.
 Implement visual system with camera.
 Design customizable faces for the robotic dog's screen.
 Implement additional functionalities (add as needed).
Getting Started:
Hardware Setup: Assemble the robotic dog according to the provided schematics and instructions.
Software Installation: Install the necessary software on both ESP32 S3 and Raspberry Pi 4B.
Configuration: Customize configuration files to match your hardware setup and preferences.
Compilation and Deployment: Compile and deploy code to respective devices following instructions in the repository.
Testing: Test functionality by wirelessly commanding the robotic dog and observing its behavior.
Contribution: Fork the repository, make modifications, and submit pull requests to contribute to the project.
Support:
For assistance or inquiries, open an issue on GitHub, and our community and development team will assist you promptly.

License:
This project is licensed under the MIT License, allowing for unrestricted use, modification, and distribution. See the LICENSE file for details.

Acknowledgments:
We thank the open-source community for their contributions and support, and the developers of ESP32 and Raspberry Pi platforms for enabling innovative robotics development.

Disclaimer:
Use the Turbo Pup robotic dog project at your own risk. The developers are not liable for any damage or injury caused by its use.

Happy building and coding with Turbo Pup! 🐾
