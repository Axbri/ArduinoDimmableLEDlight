
const int R_LED = 11;
const int G_LED = 9;
const int B_LED = 10;

const int BUTTON = 8;
const int ENCODER_A = 12;
const int ENCODER_B = 13;

bool pervius_aState = true; 
bool aState = true; 
bool bState = true; 
int count = 0; 

void setup() {
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  digitalWrite(R_LED, HIGH); 
  digitalWrite(G_LED, HIGH); 
  digitalWrite(B_LED, HIGH); 
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  Serial.begin(119200); 
}

void loop() {

/*
  if(!digitalRead(BUTTON))
  {
    setLEDcolor(1, 0.1, 0); 
  }
  else
  {
    setLEDcolor(0, 0, 1); 
  }*/

  pervius_aState = aState; 
  aState = digitalRead(ENCODER_A); 
  bState = digitalRead(ENCODER_B); 

  if (!aState && pervius_aState) 
  {
    if(bState)
    {
      count++; 
    }
    else
    {
      count--; 
    }
  }

  float britness = count/20.0; 

  setLEDcolor(0, britness, 0); 

  Serial.print("Count: ");
  Serial.println(count);
  
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

