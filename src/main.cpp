#include <Arduino.h>
#include <Servo.h>

// Define the servo pin
const int servoPin = 9;

// Create a servo object
Servo myServo;

// --- Non-Blocking Movement Variables ---
bool isMoving = false;
int moveTargetAngle;
int moveStartAngle;
unsigned long moveStartTime;
unsigned long moveDuration;

void parseCommand(char *command);
void moveToPosition(int angle);
void startMoveToPositionInTime(int targetAngle, int duration);
void updateMovement();

void setup()
{
  // Attach the servo to the pin
  myServo.attach(servoPin);
  // Start serial communication at a much faster baud rate
  Serial.begin(115200);

  // --- Welcome Message ---
  Serial.println(F("      ___"));
  Serial.println(F("     |   |"));
  Serial.println(F("     | R |"));
  Serial.println(F("     | O |"));
  Serial.println(F("     | B |"));
  Serial.println(F("     | O |"));
  Serial.println(F("     | T |"));
  Serial.println(F("     |___|"));
  Serial.println(F("        \\"));
  Serial.println(F("         \\"));
  Serial.println(F("          \\"));
  Serial.println(F("           \\______"));
  Serial.println(F("          |        |"));
  Serial.println(F("          |  ARM   |"));
  Serial.println(F("          |________|"));
  Serial.println(F("              ||"));
  Serial.println(F("              ||"));
  Serial.println(F("              ||"));
  Serial.println(F("             /  \\"));
  Serial.println(F("            /    \\"));
  Serial.println(F("           O      O"));
  Serial.println(F("")); // Add a blank line for spacing
  Serial.println(F("[INFO] Welcome, user! The 1DOF Robot Arm is ready."));
  Serial.println(F("[INFO] Send 'P<angle>' or 'T<angle>,<time>' to begin."));
  Serial.println(F("---------------------------------------------"));
}

void loop()
{
  // Check for new serial commands
  if (Serial.available() > 0)
  {
    static char command[32]; // Buffer to hold incoming command
    int len = Serial.readBytesUntil('\n', command, sizeof(command) - 1);
    command[len] = '\0'; // Null-terminate the string
    parseCommand(command);
  }

  // Update servo position if a timed move is in progress
  if (isMoving)
  {
    updateMovement();
  }
}

void parseCommand(char *command)
{
  if (command[0] == '\0')
    return; // Ignore empty commands

  switch (command[0])
  {
  case 'P':
  {
    // Move to position, e.g., P90
    int angle = atoi(command + 1);
    moveToPosition(angle);
    break;
  }
  case 'T':
  {
    // Move to position in time, e.g., T90,1000
    char *comma = strchr(command, ',');
    if (comma != NULL)
    {
      *comma = '\0'; // Split the string
      int angle = atoi(command + 1);
      int time = atoi(comma + 1);
      startMoveToPositionInTime(angle, time);
    }
    else
    {
      Serial.println(F("[ERROR] Invalid format. Use T<angle>,<time>"));
    }
    break;
  }
  default:
    Serial.print(F("[ERROR] Unknown command: "));
    Serial.println(command);
    break;
  }
}

void moveToPosition(int angle)
{
  isMoving = false;                 // Stop any ongoing timed movement
  angle = constrain(angle, 0, 180); // Ensure angle is within valid servo range
  myServo.write(angle);
  Serial.print(F("[SUCCESS] Moved to position: "));
  Serial.println(angle);
}

void startMoveToPositionInTime(int targetAngle, int duration)
{
  targetAngle = constrain(targetAngle, 0, 180);
  if (duration <= 0)
  {
    moveToPosition(targetAngle);
    return;
  }

  isMoving = true;
  moveStartAngle = myServo.read();
  moveTargetAngle = targetAngle;
  moveStartTime = millis();
  moveDuration = duration;

  Serial.print(F("[INFO] Starting move from "));
  Serial.print(moveStartAngle);
  Serial.print(F(" to "));
  Serial.print(moveTargetAngle);
  Serial.print(F(" in "));
  Serial.print(duration);
  Serial.println(F("ms"));
}

void updateMovement()
{
  unsigned long elapsedTime = millis() - moveStartTime;

  if (elapsedTime >= moveDuration)
  {
    // Movement finished
    isMoving = false;
    myServo.write(moveTargetAngle);
    Serial.println(F("[SUCCESS] Movement complete."));
  }
  else
  {
    // Calculate intermediate position (linear interpolation)
    float progress = (float)elapsedTime / (float)moveDuration;
    int currentAngle = moveStartAngle + (progress * (moveTargetAngle - moveStartAngle));
    myServo.write(currentAngle);
  }
}