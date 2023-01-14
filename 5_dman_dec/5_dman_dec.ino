/*
 * Crappy Differential Manchester Decoding.
 * This code chokes at 32kHz, but works for 16 kHz.
 * 
 * Robert Ruark
 * 2022
 */
#include <Arduino.h>

HardwareTimer timer(TIM1);
bool txVal = false;
bool process_next_bit   = true;
bool process_next_byte  = true;
bool current_bit        = 1;
byte current_byte       = 0x00;
int state               = 0;
byte tx_byte[5]         = {0xFF,0xEB,0x55,0x14,0xAA};
int bit_index           = 0;
int half_period_pos     = 0;
bool half_period_val[2] = {1,1};

int max_reps            = 10;
int reps                = 0;
int byte_position       = 0;
int short_count         = 0;

volatile bool reading   = 0;
volatile bool last_reading = 0;
volatile int reading_duration = 0;
volatile int last_reading_duration = 0;
volatile bool process_reading = false;

void OnTimer1Interrupt() 
{
    reading = digitalRead(PB11);
    //digitalWrite(PB10,reading);
    if(reading == last_reading)
    {
      reading_duration++;
    }
    else
    {
      last_reading_duration = reading_duration;
      reading_duration = 0;
      process_reading  = true;
    }
    last_reading = reading;
}

void setup() 
{
    //pinMode(PB10, OUTPUT);
    pinMode(PB0, OUTPUT);
    pinMode(PB11, INPUT);
    pinMode(PA7, INPUT_PULLUP);
    Serial.begin(1000000);
    // Configure timer
    timer.setPrescaleFactor(125); // Set prescaler to 2564 => timer frequency = 36MHz/125 = 288000 Hz
    timer.setOverflow(4); // Set overflow to 1 => timer frequency = 288000 Hz
    timer.attachInterrupt(OnTimer1Interrupt);
    timer.refresh(); // Make register changes take effect
    timer.resume(); // Start
}
void loop() 
{
  //Serial.println(last_reading_duration);
  if(process_reading)
  {
    process_reading = false;
    if(last_reading_duration>6)
    {
      current_byte = current_byte << 1;
      current_byte = current_byte | 1;
      short_count  = 0;
      bit_index++;
    }
    else
    {
      short_count++;
      if(short_count == 2)
      {
        current_byte = current_byte << 1;
        //current_byte = 0x00;
        bit_index++;
        short_count = 0;
      }
    }
    if(!short_count)
    {
      if(bit_index ==8)
      {
        Serial.print(current_byte,HEX);
        current_byte = 0x00;
        bit_index = 0;
      }
    }
  }
}
