# esp32difbot
ESP32 differential controlled by a wii mote

This is an Arduino code for controlling two DC motors using an ESP32 board and a Wii Nunchuk. The code uses the ESP32Wiimote library to interface with the Nunchuk and receives the x and y values of the joystick. These values are used to calculate the speed and direction of the left and right motors, which are then set using the runMotor function. The CalculateDrive function maps the joystick values to motor speeds and calls the runMotor function with the appropriate parameters. The runMotor function sets the motor direction and speed using the specified input pins and PWM value.#
