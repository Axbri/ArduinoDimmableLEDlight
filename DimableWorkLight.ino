
const int R_LED = 11;
const int G_LED = 9;
const int B_LED = 10;
const int BUTTON = 8;
const int ENCODER_A = 12;
const int ENCODER_B = 13;
const int POWER = 6;
const int FIR = 7;

const int MAX_BRIGHTNESS = 200;
const int MIN_BRIGHTNESS = 20; 
const int BRIGHTNESS_STEP = 10; 

bool pervius_aState = true; 
bool aState = true; 
bool bState = true; 
int brightness = (MIN_BRIGHTNESS + MAX_BRIGHTNESS) / 2; 
bool on_off = true; 
bool buttonState = true; 
bool previusButtonState = true; 

void setup() {
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  pinMode(POWER, OUTPUT);
  digitalWrite(R_LED, HIGH); 
  digitalWrite(G_LED, HIGH); 
  digitalWrite(B_LED, HIGH); 
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(FIR, INPUT);
  Serial.begin(119200); 
}

void loop() {
  pervius_aState = aState; 
  aState = digitalRead(ENCODER_A); 
  bState = digitalRead(ENCODER_B); 

  previusButtonState = buttonState; 
  buttonState = !digitalRead(BUTTON); 

  if (buttonState && !previusButtonState)
  {
    if (!on_off) {    // switch on if it was off
      on_off = true; 
      brightness = (MIN_BRIGHTNESS + MAX_BRIGHTNESS) / 2;
    }
    else
    {
      on_off = false; 
    }
  }

  if (!aState && pervius_aState) 
  {
    if(bState)
    {
      //if (brightness < MAX_BRIGHTNESS - BRIGHTNESS_STEP)
      //{
        brightness += BRIGHTNESS_STEP; 
      //}        
    }
    else
    {
      //if (brightness > MIN_BRIGHTNESS + BRIGHTNESS_STEP)
      //{
        brightness -= BRIGHTNESS_STEP; 
      //}      
    }
    brightness = constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS); 
  }

  if (on_off)
  {
    analogWrite(POWER, constrain(brightness, 0, 255));
  }
  else
  {
    analogWrite(POWER, 0);
  }

  if (brightness > MAX_BRIGHTNESS - BRIGHTNESS_STEP)
  {
    setLEDcolor(1, 0, 0); 
  }
  else if (brightness < MIN_BRIGHTNESS + BRIGHTNESS_STEP)
  {
    setLEDcolor(0.2, 0.5, 0.2); 
  }
  else 
  {    
    if (digitalRead(FIR))
      setLEDcolor(0, 1, 0); 
    else  
      setLEDcolor(0, 0, 1); 
  }
}

void setLEDcolor(float red, float green, float blue)
{
  int redInt = constrain(red * 255.0, 0, 255);   
  int greenInt = constrain(green * 255.0, 0, 255);  
  int blueInt = constrain(blue * 255.0, 0, 255);  
  
  analogWrite(R_LED, 255 - redInt); 
  analogWrite(G_LED, 255 - greenInt); 
  analogWrite(B_LED, 255 - blueInt); 
}

