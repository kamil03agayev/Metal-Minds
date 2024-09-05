WRO Robot - Color Detection and Obstacle Navigation

Overview

This project involves a robot designed for a competition where the primary objective is to navigate through obstacles by detecting specific colors (green and red) using computer vision. The robot utilizes OpenCV for color detection, an Arduino Nano for controlling hardware components, and an L298N motor driver for managing movement.

Components

1. Raspberry Pi 3 B+ 
   - For color detection and image processing.

2. Arduino Nano
   - Manages signals and controls the robot’s movements based on input from sensors and commands from the Python script.

3. L298N Motor Driver
   - Drives the motors for movement control.

4. Proximity Sensors (3)
   - Detect obstacles and provide proximity data to the Arduino Nano.

5. Servos and Motors
   - Controlled via Arduino Nano to navigate and interact with the environment.

Installation

Hardware Setup

1. Connect Proximity Sensors:
   - Attach each proximity sensor to the designated input pins on the Arduino Nano.

2. Connect Motor Driver (L298N):
   - Wire the motor driver to the Arduino Nano and motors according to the L298N specifications.

3. Connect Servos:
   - Connect servos to the appropriate pins on the Arduino Nano.

4. Power Supply:
   - Ensure that both the Arduino Nano and motor driver are supplied with appropriate power.

Software Setup

1. Install Python and Required Libraries:
   - Make sure Python is installed on your system.
   - Install OpenCV using pip:
     pip install opencv-python

2. Arduino Code:
   - Upload the provided Arduino sketch to the Arduino Nano. The sketch is responsible for receiving commands from the Python script and controlling the motors and servos.

3. Python Script:
   - The script captures video from the camera, detects colors, and sends commands to the Arduino Nano based on the detected colors.

Usage

1. Run the Python Script:
   - Execute the Python script to start color detection and send commands to the Arduino Nano.

2. Monitor Arduino:
   - Ensure the Arduino Nano is running the uploaded code and is connected to the hardware setup.

3. Navigate the Course:
   - The robot should automatically detect green and red obstacles and navigate accordingly.

Code Structure

- Python Script:
  - color_detection.py: Contains code for capturing video, detecting colors, and sending signals to the Arduino Nano.

- Arduino Code:
  - robot_control.ino: Arduino sketch for reading sensor data, receiving commands from the Python script, and controlling motors and servos.

Troubleshooting

- No Movement:
  - Check connections to the motor driver and ensure the motors are functioning.
  - Verify that the Arduino code is uploaded correctly.

- Color Detection Issues:
  - Adjust the color detection thresholds in the Python script for better accuracy.

- Sensor Issues:
  - Ensure proximity sensors are properly connected and calibrated.

Contributing

Feel free to fork this repository and submit pull requests with improvements or fixes. Contributions are welcome!



Acknowledgments

- OpenCV for powerful image processing capabilities.
- Arduino community for the extensive support and resources.
