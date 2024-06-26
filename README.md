# AIoT Project

# Automatic Tomato Plant Care System

## Introduction

Welcome to the Automatic Tomato Plant Care System developed by Cốc Cốc. This system is designed to automate the process of monitoring and caring for tomato plants using Arduino and Python. This README file will guide you through setting up and using the system effectively.

## Team Members
   1. Phạm Đức Mạnh
   2. Nguyễn Thiên Nguyên
   3. Nguyễn Thanh Sơn
   4. Nguyễn Thanh Tú
   5. Nguyễn Hoàng Yến Ngọc
   6. Võ Tấn Sang
   7. Đỗ Nam Hải
## Features

- Automated watering based on soil moisture levels.
- Monitoring and maintaining optimal temperature and light conditions.
- Real-time data monitoring and analysis.
- Automatic notifications and alerts.
- User-friendly interface for configuration and monitoring.

## Requirements

- Arduino microcontroller board
- Sensors (soil moisture sensor, temperature/humidity sensor, light sensor)
- Water pump
- Camera
- Relay module (if required)
- Python environment for data analysis and visualization
- Internet connectivity for notifications (optional)

## Installation

1. Clone the project repository:
    ```
    git clone https://github.com/MannoKat/AIoT-Project.git
    ```

2. **Hardware Setup:**
   - Connect the sensors (soil moisture sensor, temperature/humidity sensor, light sensor) to the Arduino board.
   - Connect the water pump to the Arduino board (via a relay module if required).

3. **Software Setup:**
   - Upload the Arduino sketch (provided in `arduino_code/`) to your Arduino board.
   - Install the required Python packages by running:
     ```
     pip install -r requirements.txt
     ```

4. **Configuration:**
   - Modify the Arduino sketch and Python scripts to adjust sensor pins, thresholds, and any other parameters according to your setup and requirements.

5. **Usage:**
   - Run the Python script (`main.py`) to start the monitoring and control system.
   - Follow the prompts or GUI instructions to interact with the system.

## Troubleshooting

- If you encounter any issues during setup or operation, please refer to the troubleshooting section in the project report ([Multidisciplinary_Report_CocCoc.pdf](https://github.com/MannoKat/AIoT-Project/blob/main/Report/Multidisciplinary_Report_CocCoc.pdf)).

## Contributing

We welcome contributions from the community. If you have any suggestions, improvements, or bug fixes, please feel free to submit a pull request.

## Credits

This project was developed by Cốc Cốc at the Vietnamese-German University.

