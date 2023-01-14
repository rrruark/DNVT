/*
Non-functional Differential Manchester Encoder
Robert Ruark
2022
*/
#define period 31
int rep = 5000;
byte tx_byte[2] = {0xFF,0x4B};
bool state=0;
int initial = 0;
int ind = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PA0, OUTPUT);

}

// the loop function runs over and over again forever
void loop() 
{
  if(ind == 0)
  {
    initial =0;
  }
  else
  {
    initial = 1;
  }
  
  byte temp = tx_byte[initial];
  for (int i = 0; i < 8; i++)
  {
      bool b = temp & 0x80;
      //Serial.print(b);
      temp = temp << 1;
      if(!b)
      {
        state = !state;
        digitalWrite(PA0, state);
      }
      delayMicroseconds(period);
      state = !state;
      digitalWrite(PA0, state);
      delayMicroseconds(period);
  }
    
  ind++; 
  if(ind == rep)
  {
    ind = 0;
    delay(500);
  }
}
