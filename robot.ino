#include <WiFi.h>
#include <ESP32Servo.h>

// WiFi hotspot credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678";

// Define servo objects
Servo leftFootServo;
Servo leftLowerLegServo;    // Changed from leftKneeServo
Servo leftUpperLegServo;    // Changed from leftLegServo
Servo leftHipServo;         // Changed from leftUpperLegServo
Servo rightFootServo;
Servo rightLowerLegServo;   // Changed from rightKneeServo
Servo rightUpperLegServo;   // Changed from rightLegServo
Servo rightHipServo;        // Changed from rightUpperLegServo

// Define servo pins
#define LEFT_FOOT_PIN    12
#define LEFT_LOWER_PIN   14  // Changed from LEFT_KNEE_PIN
#define LEFT_UPPER_PIN   26  // Changed from LEFT_LEG_PIN
#define LEFT_HIP_PIN     27  // Changed from LEFT_UPPER_PIN
#define RIGHT_FOOT_PIN   15
#define RIGHT_LOWER_PIN  16  // Changed from RIGHT_KNEE_PIN
#define RIGHT_UPPER_PIN  17  // Changed from RIGHT_LEG_PIN
#define RIGHT_HIP_PIN    18  // Changed from RIGHT_UPPER_PIN

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

  leftLowerLegServo.setPeriodHertz(50);
  leftLowerLegServo.attach(LEFT_LOWER_PIN, 500, 2400);
  leftLowerLegServo.write(CENTER_POS);

  leftUpperLegServo.setPeriodHertz(50);
  leftUpperLegServo.attach(LEFT_UPPER_PIN, 500, 2400);
  leftUpperLegServo.write(CENTER_POS);

  leftHipServo.setPeriodHertz(50);
  leftHipServo.attach(LEFT_HIP_PIN, 500, 2400);
  leftHipServo.write(CENTER_POS);

  rightFootServo.setPeriodHertz(50);
  rightFootServo.attach(RIGHT_FOOT_PIN, 500, 2400);
  rightFootServo.write(CENTER_POS);

  rightLowerLegServo.setPeriodHertz(50);
  rightLowerLegServo.attach(RIGHT_LOWER_PIN, 500, 2400);
  rightLowerLegServo.write(CENTER_POS);

  rightUpperLegServo.setPeriodHertz(50);
  rightUpperLegServo.attach(RIGHT_UPPER_PIN, 500, 2400);
  rightUpperLegServo.write(CENTER_POS);

  rightHipServo.setPeriodHertz(50);
  rightHipServo.attach(RIGHT_HIP_PIN, 500, 2400);
  rightHipServo.write(CENTER_POS);

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
  leftLowerLegServo.write(90);
  leftUpperLegServo.write(90);
  leftHipServo.write(90);

  rightFootServo.write(90);
  rightLowerLegServo.write(90);
  rightUpperLegServo.write(90);
  rightHipServo.write(90);
  delay(1000);
}

// Function to perform a simple walking motion demo
void demoMovement() {
  // Walking cycle based on reference implementation

  // Stand right foot
  rightFootServo.write(90-40-10);        // right foot
  rightLowerLegServo.write(90-40+20);    // right lower leg
  rightUpperLegServo.write(90+40-20);    // right upper leg
  rightHipServo.write(90-40-10);         // right hip
  leftHipServo.write(90+40-10);          // left hip
  leftUpperLegServo.write(90-40+70);     // left upper leg
  leftLowerLegServo.write(90+40-70);     // left lower leg
  leftFootServo.write(90+40-10);         // left foot
  delay(100);

  // Stand right foot left foot forward
  rightFootServo.write(90-40-10);        // right foot
  rightLowerLegServo.write(90-40+20);    // right lower leg
  rightUpperLegServo.write(90+40-20);    // right upper leg
  rightHipServo.write(90-40-10);         // right hip
  leftHipServo.write(90+40-10);          // left hip
  leftUpperLegServo.write(90-40+70);     // left upper leg
  leftLowerLegServo.write(90+40-0);      // left lower leg
  leftFootServo.write(90+40-10);         // left foot
  delay(100);

  // Stand left foot front
  rightFootServo.write(90-40-0);         // right foot
  rightLowerLegServo.write(90-40+30);    // right lower leg
  rightUpperLegServo.write(90+40-0);     // right upper leg
  rightHipServo.write(90-40-0);          // right hip
  leftHipServo.write(90+40-0);           // left hip
  leftUpperLegServo.write(90-40+30);     // left upper leg
  leftLowerLegServo.write(90+40-0);      // left lower leg
  leftFootServo.write(90+40-0);          // left foot
  delay(100);

  // Stand left foot front left side
  rightFootServo.write(90-40+10);        // right foot
  rightLowerLegServo.write(90-40+30);    // right lower leg
  rightUpperLegServo.write(90+40-0);     // right upper leg
  rightHipServo.write(90-40+10);         // right hip
  leftHipServo.write(90+40+10);          // left hip
  leftUpperLegServo.write(90-40+30);     // left upper leg
  leftLowerLegServo.write(90+40-0);      // left lower leg
  leftFootServo.write(90+40+10);         // left foot
  delay(100);

  // Stand left foot
  rightFootServo.write(90-40+10);        // right foot
  rightLowerLegServo.write(90-40+70);    // right lower leg
  rightUpperLegServo.write(90+40-70);    // right upper leg
  rightHipServo.write(90-40+10);         // right hip
  leftHipServo.write(90+40+10);          // left hip
  leftUpperLegServo.write(90-40+20);     // left upper leg
  leftLowerLegServo.write(90+40-20);     // left lower leg
  leftFootServo.write(90+40+10);         // left foot
  delay(100);

  // Stand left foot right foot forward
  rightFootServo.write(90-40+10);        // right foot
  rightLowerLegServo.write(90-40+0);     // right lower leg
  rightUpperLegServo.write(90+40-70);    // right upper leg
  rightHipServo.write(90-40+10);         // right hip
  leftHipServo.write(90+40+10);          // left hip
  leftUpperLegServo.write(90-40+20);     // left upper leg
  leftLowerLegServo.write(90+40-20);     // left lower leg
  leftFootServo.write(90+40+10);         // left foot
  delay(100);

  // Stand right foot front
  rightFootServo.write(90-40+0);         // right foot
  rightLowerLegServo.write(90-40+0);     // right lower leg
  rightUpperLegServo.write(90+40-30);    // right upper leg
  rightHipServo.write(90-40+0);          // right hip
  leftHipServo.write(90+40+0);           // left hip
  leftUpperLegServo.write(90-40+0);      // left upper leg
  leftLowerLegServo.write(90+40-30);     // left lower leg
  leftFootServo.write(90+40+0);          // left foot
  delay(100);

  // Stand right foot front right side
  rightFootServo.write(90-40-10);        // right foot
  rightLowerLegServo.write(90-40+0);     // right lower leg
  rightUpperLegServo.write(90+40-30);    // right upper leg
  rightHipServo.write(90-40-10);         // right hip
  leftHipServo.write(90+40-10);          // left hip
  leftUpperLegServo.write(90-40+0);      // left upper leg
  leftLowerLegServo.write(90+40-30);     // left lower leg
  leftFootServo.write(90+40-10);         // left foot
  delay(100);

  // Return to right foot position to complete the cycle
  rightFootServo.write(90-40-10);        // right foot
  rightLowerLegServo.write(90-40+20);    // right lower leg
  rightUpperLegServo.write(90+40-20);    // right upper leg
  rightHipServo.write(90-40-10);         // right hip
  leftHipServo.write(90+40-10);          // left hip
  leftUpperLegServo.write(90-40+70);     // left upper leg
  leftLowerLegServo.write(90+40-70);     // left lower leg
  leftFootServo.write(90+40-10);         // left foot
  delay(100);

  // Return to neutral position
  standNeutral();
}
