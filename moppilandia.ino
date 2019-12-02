
int ledPins[5] = {12,11,10,9,8};
int yellowLED = 12;
int greenLED = 11;
int redLED = 10;
int blueLED = 9;
int whiteLED = 8;

int buttonPins[5] = {22,24,26,28,30};
int buttonTone[5] = {261, 293, 329, 349, 392};
int lastButtonState[5] = {LOW,LOW,LOW,LOW,LOW};
unsigned long lastDebounceTime[5] = {0,0,0,0,0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int yellowButton = 22; 
int greenButton = 24;
int redButton = 26;
int blueButton = 28;
int whiteButton = 30;

int level = 1;

int speaker = 5;


void setup() {
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);


  pinMode(yellowButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(whiteButton, INPUT);


}

int game() {
  int buttonCombination[100];
  for(int i=0; i<level; i++)
  {
    buttonCombination[i] = random(5);
    hitButton(buttonCombination[i]);
    delay(300);
  }
  int step = 0; 
  int pressedButton;
  while(step<level)
  {
      pressedButton = buttonHit();
      if(pressedButton == buttonCombination[step])
      {
        hitButton(buttonCombination[step]);
        resetButtons();
        step++;
      }
      else if(pressedButton != -1)
      {
        return 0;
      }
  }
  return 1;
}

int buttonHit()
{
  int state;
  for(int i=0; i<5; i++)
  {
    state = digitalRead(buttonPins[i]);
    if(state != lastButtonState[i])
    {
      lastButtonState[i] = state;
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (state == HIGH) {
        return i;
      }
    }
  }
  return -1;
}

void resetButtons()
{
  for(int i=0; i<5; i++)
  {
    lastButtonState[i] = LOW;
  }
}

void hitButton(int i) 
{
        digitalWrite(ledPins[i], HIGH);
        tone(speaker, buttonTone[i]);
        delay(500);
        noTone(speaker);
        digitalWrite(ledPins[i],LOW);
}

void loop() 
{
  if(game())
  {
    level++;
    delay(500);
    tone(speaker, 261);
    delay(200);
    tone(speaker, 293);
    delay(200);
    tone(speaker, 329);
    delay(200);
    tone(speaker, 392);
    delay(1000);
    noTone(speaker);

  }
  else
  {
    level=1;
    delay(500);
    tone(speaker, 392);
    delay(500);
    tone(speaker, 261);
    delay(1000);
    noTone(speaker);
  }
  delay(1000);
}

// void loop() {
//   // put your main code here, to run repeatedly:

//   // YELLOW
//   if (digitalRead(yellowButton) == HIGH)
//   {
//     digitalWrite(yellowLED, HIGH);
//     tone(speaker, 261, 100);
//   }

//   // GREEN
//   if(digitalRead(greenButton) == HIGH)
//   {
//     digitalWrite(greenLED, HIGH);
//     tone(speaker, 293, 100);
//   }

//   // RED
//   if(digitalRead(redButton) == HIGH)
//   {
//     digitalWrite(redLED, HIGH);
//     tone(speaker, 329, 100);
//   }

//   // BLUE
//   if(digitalRead(blueButton) == HIGH)
//   {
//     digitalWrite(blueLED, HIGH);
//     tone(speaker, 349, 100);
//   }

//   // WHITE
//   if(digitalRead(whiteButton) == HIGH)
//   {
//     digitalWrite(whiteLED, HIGH);
//     tone(speaker, 392, 100);
//   }

//   else
//   {
//     digitalWrite(yellowLED, LOW);
//     digitalWrite(blueLED, LOW);
//     digitalWrite(greenLED, LOW);
//     digitalWrite(whiteLED, LOW);
//     digitalWrite(redLED, LOW);
//   }
// }
