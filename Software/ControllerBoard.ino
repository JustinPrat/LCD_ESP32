float p = 3.1415926;
const int buttonPin = 3; 
int buttonState = 0;

#include <esp_now.h>
#include <WiFi.h>

const int xValuePin = 8;
const int yValuePin = 7;
const int led1 = 43;
const int led2 = 44;

uint8_t xValue = 0;
uint8_t yValue = 0;

int breathValue = 0;
bool isCountingUp = true;

uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(xValuePin, INPUT);
  pinMode(yValuePin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
    
  esp_now_init();
    
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
  Serial.println(WiFi.macAddress());
}

void loop() {
  delay(50);
  
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("Released");
  } else {
    Serial.println("Pressed");
  }

  xValue = analogRead(xValuePin) * (5.0 / 1023.0);
  yValue = analogRead(yValuePin) * (5.0 / 1023.0);

  String XA = "X value : ";
  String XB = XA + xValue;

  String YA = "/ Y value : ";
  String YB = YA + yValue;
  String stringOne = XB + YB;
  Serial.println(stringOne);

  String BreathA = "BreathValue : ";
  String BreathB = BreathA + breathValue;
  Serial.println(BreathB);

  analogWrite(led1, breathValue);
  analogWrite(led2, breathValue);

  if (breathValue >= 245) {
    isCountingUp = false;
  }
  else if (breathValue <= 0) {
    breathValue = 0;
    isCountingUp = true;
  }

  if (isCountingUp) {
    breathValue += 10;
  }
  else {
    breathValue -= 10;
  }

  uint8_t msg[3];
  msg[0] = xValue;
  msg[1] = yValue;
  msg[2] = buttonState;

  // char message[] = "Hi, this is a message from the transmitting ESP";
  // esp_now_send(receiverAddress, (uint8_t *) message, sizeof(message)-1); // -1 to not send the NULL terminator

  esp_now_send(receiverAddress, (uint8_t *) msg, sizeof(msg)); // -1 to not send the NULL terminator

}