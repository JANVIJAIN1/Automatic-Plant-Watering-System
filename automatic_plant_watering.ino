const int sensorPin = A0;
const int relayPin = 7;

const int threshold = 1003;
const unsigned long pumpDuration = 5000;

unsigned long pumpStartTime = 0;

bool pumpRunning = false;
bool pumpLocked = false;

void setup() {
  Serial.begin(9600);

  digitalWrite(relayPin, HIGH);
  pinMode(relayPin, OUTPUT);

  Serial.println("Smart Plant Watering System Ready!");
}

void loop() {

  int moisture = analogRead(sensorPin);

  Serial.print("Moisture Reading: ");
  Serial.println(moisture);

  if (moisture <= threshold) {

    digitalWrite(relayPin, HIGH);

    pumpRunning = false;
    pumpLocked = false;

    Serial.println("Soil Wet - Pump OFF");
  }

  else {

    if (!pumpLocked) {

      if (!pumpRunning) {
        digitalWrite(relayPin, LOW);

        pumpRunning = true;
        pumpStartTime = millis();

        Serial.println("Soil Dry - Pump ON");
      }

      if (millis() - pumpStartTime >= pumpDuration) {

        digitalWrite(relayPin, HIGH);

        pumpRunning = false;
        pumpLocked = true;

        Serial.println("5 Seconds Completed - Pump OFF");
      }
    }

    else {
      Serial.println("Waiting for Wet Soil");
    }
  }

  delay(200);
}
