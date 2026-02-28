const int potPin = 35;
const int ledPins[] = {25, 26, 27, 14};
const int numLeds = 4;

float currentPhase = 0.0;

const int freq = 5000;       // PWM frequency
const int resolution = 8;    // 8-bit resolution (0-255)

void setup() {
  pinMode(potPin, INPUT);

  for(int i = 0; i < numLeds; i++) {
    ledcAttach(ledPins[i], freq, resolution);
  }
}

void loop() {
  int potValue = analogRead(potPin);
  float speed = map(potValue, 0, 4095, 1, 100) / 100.0;

  currentPhase += speed;
  if(currentPhase > 2*PI) currentPhase -= 2*PI;

  for(int i = 0; i < numLeds; i++) {
    float ledPhase = currentPhase - (i * PI/2);
    float wave = sin(ledPhase);

    if(wave < 0) wave = 0;

    int brightness = wave * 255;
    ledcWrite(ledPins[i], brightness);
  }

  delay(10);
}