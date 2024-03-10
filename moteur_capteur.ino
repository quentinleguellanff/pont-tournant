const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 6400;
const int sensor=8;
const int LED=13;
const int switchPins[] = {4, 5, 6, 7};
bool detected = false; // booleen permettant de determiner si le capteur a detecter quelquchose
int currentPositionStep = 0;
int lastPosition = 0;


void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT); // LED Pin Output
  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop()
{
  
  if(detected){
    if(Serial.available() > 0) {
      String data = Serial.readString();
      Serial.println(data);
      switch(data.toInt()) 
      {
          case 0: {
            rotateBridge(&lastPosition, &currentPositionStep, 0, 0);
            break;
          }
          case 1: {
            rotateBridge(&lastPosition, &currentPositionStep, 1, 320);
            break;
          }
          case 2: {
            rotateBridge(&lastPosition, &currentPositionStep, 2, 160);
            break;
          }
          case 3: {
            rotateBridge(&lastPosition, &currentPositionStep, 3, 0);
            break;
          }
          case 4: {
            rotateBridge(&lastPosition, &currentPositionStep, 4, -160);
            break;
          }
          case 5: {
            rotateBridge(&lastPosition, &currentPositionStep, 5, -320);
            break;
          }
          case 6: {
            rotateBridge(&lastPosition, &currentPositionStep, 6, -480);
            break;
          }
          case 7: {
            rotateBridge(&lastPosition, &currentPositionStep, 7, -640);
            break;
          }
          case 8: {
            rotateBridge(&lastPosition, &currentPositionStep, 8, -800);
            break;
          }
          case 9: {
            rotateBridge(&lastPosition, &currentPositionStep, 9, -960);
            break;
          }
          case 10: {
            rotateBridge(&lastPosition, &currentPositionStep, 10, -1120);
            break;
          }
          case 15:
            if(lastPosition != 15) {
              moveBackward(3200);
              currentPositionStep -= 3200;
              lastPosition = 15;
            }
            break;
          default:
            break; 
      }
    }
  }

  while(!detected) {
    currentPositionStep = 0;
    digitalWrite(dirPin, HIGH);
    int sensorStatus = digitalRead(sensor);
    if(isSensorDetected(sensorStatus)){
      detected = true;      
    }
    else {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2000);
    }
  }
}

bool isSensorDetected(int sensorStatus){
  if(sensorStatus == HIGH){
    digitalWrite(LED, LOW); // LED LOW
    return false;
  }
  else{
    digitalWrite(LED, HIGH); // LED HIGH
    return true;
  }
}

void moveForward(int stepNumber) {
    for(int x = 0; x < stepNumber; x++)
    {
        digitalWrite(dirPin, LOW);
        
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
    }
    delay(1000); // Wait a second
}

void moveBackward(int stepNumber) {
    for(int x = 0; x < stepNumber; x++)
    {
        digitalWrite(dirPin, HIGH);

        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
    }
    delay(1000); // Wait a second
}

int getPositionFromButtons(int switchPins[]) {
  
  int binaryValue = 0;
  // Lire l'état des switches et construire la valeur binaire
  for (int i = 0; i < 4; i++) {
    // Si le bouton est enfoncé (LOW), mettre le bit correspondant à 1
    if (digitalRead(switchPins[i]) == LOW) {
      binaryValue |= (1 << i);
    }
  }
  delayMicroseconds(10000);
  return binaryValue;
}

void rotateBridge(int *lastPosition, int *currentPositionStep, int positionValue, int positionStepValue) {
  if(*lastPosition != positionValue){
      if(*currentPositionStep > positionStepValue) {
        moveBackward(*currentPositionStep - positionStepValue);
      }
      else {
        moveForward(positionStepValue - *currentPositionStep);
      }
      *currentPositionStep = positionStepValue;
      *lastPosition = positionValue;
  }
}