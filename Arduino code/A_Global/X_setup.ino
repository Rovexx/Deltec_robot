void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting setup"));

  // TM1637 7 Segment setup
  display_left.setBrightness(0x0f);
  display_right.setBrightness(0x0f);
  display_left.clear();
  display_right.clear();

  // Servo setup                                                <-- tail code depricated in V2
  // if (!tailServo.attached()) {
	// 	tailServo.setPeriodHertz(50); // standard 50 hz servo
	// 	tailServo.attach(SERVO_PIN, 1000, 2000); // Attach the servo after it has been detatched
	// }
  // tailServo.write(0);
  if (!phoneServo.attached()) {
		phoneServo.setPeriodHertz(50); // standard 50 hz servo
		phoneServo.attach(SERVO_PIN, 1000, 2000); // Attach the servo after it has been detatched
	}
  phoneServo.write(0);

  // Relay motor setup
  pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_PIN, OUTPUT);
  digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, HIGH);

  // Test tail
  // wiggleTail(); <-- tail code depricated in V2

  // Test phone servo
  phoneServo.write(45);

  // Setup WiFi
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    WiFiLoadAnimation();
    loadingBar ++;
    if (loadingBar > 7) {
      loadingBar = 0;
      Serial.print(".");
    }
    delay(100);
  }
  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}