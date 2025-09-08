# 1-DOF Robot Arm User Guide

Welcome! This guide explains how to control the 1-DOF (degree-of-freedom) robot arm using serial commands.

## Connecting to the Robot Arm

1.  Connect the robot arm to your computer via the provided USB cable.
2.  Open a serial monitor application (e.g., the Arduino IDE Serial Monitor, PuTTY, or PlatformIO's Serial Monitor).
3.  Configure the connection with the following settings:
    *   **Port**: The COM or TTY port assigned to the robot arm.
    *   **Baud Rate**: `115200`
    *   **Line Ending**: Newline (`\n`)

Once connected, the robot arm will greet you with a welcome message.

## Control Commands

To control the arm, send one of the following commands through the serial monitor, followed by pressing Enter.

### 1. Move to Position

Moves the arm to a specific angle instantly.

*   **Command**: `P<angle>`
*   **`<angle>`**: An integer representing the target angle (from 0 to 180).
*   **Example**: `P90` - This command will move the arm to the 90-degree position.

### 2. Move to Position in Time

Moves the arm to a target angle smoothly over a specified duration.

*   **Command**: `T<angle>,<duration>`
*   **`<angle>`**: The target angle (0-180).
*   **`<duration>`**: The time for the movement in milliseconds (e.g., 1000ms = 1 second).
*   **Example**: `T180,2000` - This command will move the arm to 180 degrees over a period of 2 seconds.

## Understanding Feedback Messages

The robot arm provides real-time feedback on its status. Each message is prefixed to indicate its type:

*   **`[INFO]`**: Provides general information, such as when a movement begins.
    *   *Example*: `[INFO] Starting move from 90 to 180 in 2000ms`

*   **`[SUCCESS]`**: Confirms that a command has been completed successfully.
    *   *Example*: `[SUCCESS] Movement complete.`
    *   *Example*: `[SUCCESS] Moved to position: 90`

*   **`[ERROR]`**: Appears if you send an invalid or unrecognized command.
    *   *Example*: `[ERROR] Unknown command: X123`
    *   *Example*: `[ERROR] Invalid format. Use T<angle>,<time>`
