#include <WiFi.h>
#include <ESP32Servo.h>

// WiFi hotspot credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678";

// Define servo objects
Servo leftFootServo;
Servo leftKneeServo;
Servo leftLegServo;
Servo leftUpperLegServo;
Servo rightFootServo;
Servo rightKneeServo;
Servo rightLegServo;
Servo rightUpperLegServo;

// Define servo pins
#define LEFT_FOOT_PIN    12
#define LEFT_KNEE_PIN    14
#define LEFT_LEG_PIN     26
#define LEFT_UPPER_PIN   27
#define RIGHT_FOOT_PIN   15
#define RIGHT_KNEE_PIN   16
#define RIGHT_LEG_PIN    17
#define RIGHT_UPPER_PIN  18

// Default positions
#define CENTER_POS       90
#define MAX_POS          180
#define MIN_POS          0

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Configure ESP32 as Access Point
  Serial.println("Configuring access point...");
  
  // Set up the access point (soft AP)
  WiFi.softAP(ssid, password);
  
  // Print the IP address
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  Serial.println("WiFi Access Point is now active");
  Serial.print("SSID: ");
  Serial.println(ssid);

  // Initialize servos
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Attach servos to pins and set default positions
  leftFootServo.setPeriodHertz(50);      // Standard 50 Hz servo
  leftFootServo.attach(LEFT_FOOT_PIN, 500, 2400);  // Min/max pulse width
  leftFootServo.write(CENTER_POS);

  leftKneeServo.setPeriodHertz(50);
  leftKneeServo.attach(LEFT_KNEE_PIN, 500, 2400);
  leftKneeServo.write(CENTER_POS);

  leftLegServo.setPeriodHertz(50);
  leftLegServo.attach(LEFT_LEG_PIN, 500, 2400);
  leftLegServo.write(CENTER_POS);

  leftUpperLegServo.setPeriodHertz(50);
  leftUpperLegServo.attach(LEFT_UPPER_PIN, 500, 2400);
  leftUpperLegServo.write(CENTER_POS);

  rightFootServo.setPeriodHertz(50);
  rightFootServo.attach(RIGHT_FOOT_PIN, 500, 2400);
  rightFootServo.write(CENTER_POS);

  rightKneeServo.setPeriodHertz(50);
  rightKneeServo.attach(RIGHT_KNEE_PIN, 500, 2400);
  rightKneeServo.write(CENTER_POS);

  rightLegServo.setPeriodHertz(50);
  rightLegServo.attach(RIGHT_LEG_PIN, 500, 2400);
  rightLegServo.write(CENTER_POS);

  rightUpperLegServo.setPeriodHertz(50);
  rightUpperLegServo.attach(RIGHT_UPPER_PIN, 500, 2400);
  rightUpperLegServo.write(CENTER_POS);

  Serial.println("Servo initialization complete");
}

void loop() {
  // Display number of connected devices every 10 seconds
  static unsigned long lastCheck = 0;
  unsigned long currentTime = millis();
  
  if (currentTime - lastCheck >= 10000) {  // 10 seconds
    lastCheck = currentTime;
    Serial.print("Connected clients: ");
    Serial.println(WiFi.softAPgetStationNum());
  }
  
  // Example servo movement pattern - uncomment to use
  // demoMovement();

  // Main loop can be expanded with other functionality
  delay(100);
}

// Function to make the robot stand in a neutral position
void standNeutral() {
  leftFootServo.write(90);
  leftKneeServo.write(90);
  leftLegServo.write(90);
  leftUpperLegServo.write(90);

  rightFootServo.write(90);
  rightKneeServo.write(90);
  rightLegServo.write(90);
  rightUpperLegServo.write(90);
  delay(1000);
}

// Function to perform a simple walking motion demo
void demoMovement() {
  // Sequence for demonstration purposes
  // First move to neutral position
  standNeutral();
  delay(1000);

  // Step 1: Shift weight to left foot
  leftFootServo.write(75);
  rightFootServo.write(75);
  delay(500);

  // Step 2: Lift right leg
  rightKneeServo.write(45);
  rightLegServo.write(120);
  delay(500);

  // Step 3: Move right leg forward
  rightUpperLegServo.write(120);
  delay(500);

  // Step 4: Lower right leg
  rightKneeServo.write(90);
  rightLegServo.write(90);
  delay(500);

  // Step 5: Shift weight to right foot
  leftFootServo.write(105);
  rightFootServo.write(105);
  delay(500);

  // Step 6: Lift left leg
  leftKneeServo.write(45);
  leftLegServo.write(120);
  delay(500);

  // Step 7: Move left leg forward
  leftUpperLegServo.write(120);
  delay(500);

  // Step 8: Lower left leg
  leftKneeServo.write(90);
  leftLegServo.write(90);
  delay(500);

  // Return to neutral stance
  standNeutral();
}
