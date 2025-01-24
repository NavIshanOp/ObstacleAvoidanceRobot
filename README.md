# Obstacle Avoidance Robot

This project is an Arduino-based obstacle avoidance robot. It uses an HC-SR04 ultrasonic sensor to detect obstacles, an L298N motor driver to control the motors, and a servo motor to scan the surroundings. The robot moves forward when the path is clear and turns left or right when it encounters an obstacle, based on the distances measured on each side.

## Components Required

- Arduino (Uno, Mega, or compatible)
- L298N Motor Driver Module
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- DC Motors with Wheels
- Robot Chassis
- Power Source (Battery Pack)
- Jumper Wires
- Breadboard (optional)
- Referred link :- https://cdn.ishandev.top/u/IKmV4k
## Circuit Connections

### HC-SR04 Ultrasonic Sensor
- **Trig**: Connect to Arduino pin 9
- **Echo**: Connect to Arduino pin 10

### L298N Motor Driver
- **ENA**: Connect to Arduino pin 2
- **IN1**: Connect to Arduino pin 3
- **IN2**: Connect to Arduino pin 4
- **ENB**: Connect to Arduino pin 7
- **IN3**: Connect to Arduino pin 5
- **IN4**: Connect to Arduino pin 6

### Servo Motor
- **Signal**: Connect to Arduino pin 8

### Power
- Connect the L298N and Arduino to an appropriate power source (e.g., a 7.4V Li-ion battery pack or USB power for testing).

## How It Works

1. **Initialization**:
   - The servo motor is set to the center position (90 degrees) at startup.
   - The HC-SR04 measures the distance directly in front of the robot.

2. **Obstacle Detection**:
   - If the distance in front is greater than 20 cm, the robot moves forward.
   - If an obstacle is detected within 20 cm, the robot stops and scans the left and right directions using the servo and ultrasonic sensor.

3. **Decision Making**:
   - The robot compares the distances to the left and right and chooses the direction with more space to turn.

4. **Movement**:
   - The robot turns in the chosen direction and then resumes moving forward.

## Code Overview

The code is written in Arduino C++ and utilizes the Servo library. The main functions are:

- `getDistance()`: Measures the distance using the HC-SR04 ultrasonic sensor.
- `checkSideDistance(int angle)`: Rotates the servo to the specified angle and measures the distance.
- `moveForward()`: Moves the robot forward.
- `turnLeft()`: Turns the robot to the left.
- `turnRight()`: Turns the robot to the right.
- `stopMotors()`: Stops the motors.

## Usage

1. Connect all components as per the circuit diagram.
2. Upload the provided `Obstacle_Avoidance_Robot.ino` file to your Arduino.
3. Power on the robot.
4. Observe the robot's behavior as it avoids obstacles and navigates around them.

## Example Output

- Serial Monitor Output:
  ```
  Obstacle Avoidance Robot Initialized
  Front Distance: 35
  Path is clear. Moving forward.
  Front Distance: 15
  Obstacle detected! Stopping motors.
  Distance at angle 150: 40
  Distance at angle 30: 25
  Turning left...
  ```

## Notes

- Adjust the motor speeds in `moveForward()`, `turnLeft()`, and `turnRight()` functions if necessary.
- Ensure the servo motor is properly calibrated to avoid mechanical strain.
- Use a stable power supply for the motors to ensure consistent performance.

## License
This project is open-source and free to use for educational and personal projects under MIT License.
