// == CONSTANTS ==
// pin connected to ST_CP of 74HC595
const byte PIN_LATCH = 11;
// pin connected to SH_CP of 74HC595
const byte PIN_CLOCK = 10;
// pin connected to DS of 74HC595
const byte PIN_DATA = 9;
 

// == GLOBAL DATA ==
byte val = 0;

int buttonZero = A0;
int buttonOne = A1;
int buttonEnter = A2;

int loopDelay = 100;
int debounceDelay = 100;


void setup() 
{
  //set pins to output so you can control the shift register
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  
  pinMode(buttonZero, INPUT);
  pinMode(buttonOne, INPUT);
  pinMode(buttonEnter, INPUT);
   
   
   
  writeShiftValue(0);


  Serial.begin(9600);
  
  Keyboard.begin();
}

void loop() 
{
    // -- set next LED on --
    if(digitalRead(buttonZero))
    {  
        delay(debounceDelay);
        if(digitalRead(buttonZero))
        {
          // 
          val <<= 1;
          writeShiftValue(val);
        }
    }
    // -- set next LED on --
    if(digitalRead(buttonOne))
    {  
        delay(debounceDelay);
        if(digitalRead(buttonOne))
        {
          // 
          val <<= 1;
          val+=1;
          writeShiftValue(val);
        }
    }
    // -- set next LED on --
    if(digitalRead(buttonEnter))
    {  
        delay(debounceDelay);
        if(digitalRead(buttonEnter))
        {
            Serial.print("keyboard: ");
            Serial.println(val);
            Keyboard.write(val);
            val = 0;
            writeShiftValue(val);
        }
    }
 
    // pause before next cycles
    delay(loopDelay);
}


void writeShiftValue(byte val){
   
    // take the PIN_LATCH low so LEDs don't change while you're sending in bits
    digitalWrite(PIN_LATCH, LOW);
 
    // send the bits
    shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, val);
 

    // take the latch pin high so the LEDs will light up
    digitalWrite(PIN_LATCH, HIGH);
    
    Serial.print("shift: ");
    Serial.println(val);
  
}

