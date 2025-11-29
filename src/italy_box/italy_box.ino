#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const int buttonPin = 7;

static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX); // Connects to module's TX
DFRobotDFPlayerMini player;

int lastState = HIGH;
int fileCount;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);
  Serial.println("Starting up");
  pinMode(buttonPin, INPUT_PULLUP);
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    fileCount = player.readFileCounts();
    Serial.println("Filecount is " + String(fileCount));
    player.volume(10);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  int currentState = digitalRead(buttonPin);
  if (currentState == LOW && lastState == HIGH) {
    Serial.println("Someone pressed the god damn button");
    playThatShit();
    delay(1000);
  }

  lastState = currentState;
}

void playThatShit() {  
  int trackNumber = random(1, fileCount);
  Serial.println("Selected track number " + String(trackNumber));
  player.play(trackNumber);
}