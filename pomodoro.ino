int buzzer = 8;
int pauseButton = 2;
int startButton = 12;
int blueLed = 4;
int redLed = 7;

unsigned long tickStartTime;
unsigned long startTime;
unsigned long workTime = 25UL * 60UL * 1000UL; // 25min
unsigned long breakTime = 5UL * 30UL * 1000UL; // 5min
unsigned long tickTime = 1000; // 1s

int buttonState;
int startButtonState;
int ledState;
int studyState; // 0 -> work; 1 -> break;
int powerState; // 0 -> OFF; 1 -> ON;
int lastButtonState;
int lastStartButtonState;

int paused = 0;
unsigned long pauseStartTime;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(pauseButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  startTime = millis();
  tickStartTime = millis();
  studyState = 0;
  Serial.begin(9600);
}

void loop() { 
  buttonState = digitalRead(pauseButton);
  startButtonState = digitalRead(startButton);
  unsigned long currentTime = millis();
  
  if (startButtonState == LOW && lastStartButtonState == HIGH) {
    if (powerState == 0) {
      reset();
      allOn();
      startChime();
      powerState = !powerState;
      allOff();
    } else {
      allOn();
      endChime();
      powerState = !powerState;
      allOff();
    }
  }

  if (powerState == 1) {
    if (buttonState == LOW && lastButtonState == HIGH) {
      paused = !paused;

      if (paused == 1) {
        pauseStartTime = currentTime;
        pauseChime();
        allOn();
      } else {
        startTime += (currentTime - pauseStartTime); // add pause duration to startTime to offset the pause
        tickStartTime = currentTime;
        resumeChime();
        allOff();
      }
    }

    if (paused == 0) {
      if (currentTime - tickStartTime >= tickTime) {
        ledState = !ledState;
        if (studyState == 0) {
          digitalWrite(redLed, ledState);
        } else {
          digitalWrite(blueLed, ledState);
        }
      tickStartTime = currentTime;
      }
    
      if (studyState == 0) {
        if (currentTime - startTime >= workTime) {
          allOn();
          breakChime();
          studyState = !studyState;
          allOff();
        
          startTime = millis();
        } 
      } else {
        if (currentTime - startTime >= breakTime) {
          allOn();
          workChime();
          studyState = !studyState;
          allOff();

          startTime = millis();
        }
      }
    }
  }
  lastButtonState = buttonState;
  lastStartButtonState = startButtonState;
}

int reset() {
  studyState = 0;
  paused = 0;
  tickStartTime = millis();
  startTime = millis();
}

int startChime() {
  tone(buzzer, 784, 150); delay(200);
  tone(buzzer, 880, 150); delay(200);
  tone(buzzer, 988, 150); delay(200);  
  tone(buzzer, 1047, 300); delay(350);
}

int workChime() {
  tone(buzzer, 784, 100); delay(150);
  tone(buzzer, 880, 100); delay(150);
  tone(buzzer, 988, 100); delay(150);
  tone(buzzer, 784, 100); delay(150);
  tone(buzzer, 880, 100); delay(150);
  tone(buzzer, 988, 100); delay(150);
  tone(buzzer, 784, 100); delay(150);
  tone(buzzer, 880, 100); delay(150);
  tone(buzzer, 988, 100); delay(150);
}

int breakChime() {
  tone(buzzer, 1047, 100); delay(150);
  tone(buzzer, 784, 100);  delay(150);
  tone(buzzer, 659, 100);  delay(150);
  tone(buzzer, 1047, 100); delay(150);
  tone(buzzer, 784, 100);  delay(150);
  tone(buzzer, 659, 100);  delay(150);
  tone(buzzer, 1047, 100); delay(150);
  tone(buzzer, 784, 100);  delay(150);
  tone(buzzer, 659, 100);  delay(150);
}

int endChime() {
  tone(buzzer, 1047, 150); delay(200);
  tone(buzzer, 784, 200);  delay(250);
  tone(buzzer, 523, 400);  delay(400);
}

int pauseChime() {
  tone(buzzer, 880, 100); delay(150);
  tone(buzzer, 698, 120); delay(200);
}

int resumeChime() {
  tone(buzzer, 698, 100); delay(150);
  tone(buzzer, 880, 120); delay(200);
}

int allOn() {
  digitalWrite(redLed, HIGH);
  digitalWrite(blueLed, HIGH);
}

int allOff() {
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
}