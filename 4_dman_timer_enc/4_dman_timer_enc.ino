/*
 * Functional Differential Manchester Encoder
 * Robert Ruark 2022
 */
 
#include <Arduino.h>

HardwareTimer timer(TIM1);
bool txVal = false;
bool process_next_bit   = true;
bool process_next_byte  = true;
bool current_bit        = 1;
bool current_byte[8]    = {1,1,1,1,1,1,1,1};
int state               = 0;
byte tx_byte[5]         = {0xFF,0xEB,0x55,0x14,0xAA};
int bit_index           = 0;
int half_period_pos     = 0;
bool half_period_val[2] = {1,1};
bool process_next_half_period = true;
int max_reps            = 10;
int reps                = 0;
int byte_position       = 0;

void OnTimer1Interrupt() 
{
    digitalWrite(PB10, txVal);
    process_next_half_period = 1;
}

void setup() {
    pinMode(PB10, OUTPUT);
    pinMode(PA7, INPUT_PULLUP);
    Serial.begin(115200);
    // Configure timer
    timer.setPrescaleFactor(125); // Set prescaler to 2564 => timer frequency = 36MHz/125 = 288000 Hz
    timer.setOverflow(9); // Set overflow to 9 => timer frequency = 288000 Hz / 9 = 32.0 kHz
    timer.attachInterrupt(OnTimer1Interrupt);
    timer.refresh(); // Make register changes take effect
    timer.resume(); // Start
}
void loop() 
{
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    max_reps     = Serial.parseInt();
    int temp_int = Serial.parseInt();
    tx_byte[0]   = byte(temp_int);

    // say what you got:
    Serial.print("Transmitting ");
    Serial.print(max_reps);
    Serial.print(" bytes of ");
    Serial.println(tx_byte[0], DEC);
    state=0;
    reps = 0;
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
  
  if(process_next_bit)
  {
    if(process_next_byte)
    {
      reps++;
      byte temp = tx_byte[state];
      for (int i = 0; i < 8; i++)
      {
        bool b = temp & 0x80;
        current_byte[i]=b;
        //Serial.print(b);
        temp = temp << 1;
      }
      if(reps<max_reps)
      {
        state = 0;
      }
      else
      {
        state++;
        if(state==5) state = 1;
      }
      process_next_byte = false;
    }
    current_bit = current_byte[bit_index];

    //here's what turns bits into diff manchester:
    if(current_bit == 0)
    {
      half_period_val[0] = !half_period_val[1];// bit=0, so invert from previous state
      half_period_val[1] = !half_period_val[0];// always invert on second half period
    }
    else
    {
      half_period_val[0] = half_period_val[1]; // bit = 1, so no inversion from previous state
      half_period_val[1] = !half_period_val[0];// always invert on second half period
    }
    
    bit_index++;
    if(bit_index==8)
    {
      bit_index = 0;
      process_next_byte = true;
    }
    process_next_bit = false;
  }

  if(process_next_half_period)
  {
    txVal = half_period_val[half_period_pos];
    half_period_pos++;
    if(half_period_pos == 2)
    {
      process_next_bit = true;
      half_period_pos  = 0;
    }
    process_next_half_period = false;
  }
}
