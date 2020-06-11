#include <MIDI.h>



#define CH1 2
#define CH2 3
#define CH3 4
#define CH4 5
#define CH5 6
#define CH6 7
#define CH7 8
#define CH8 9
#define CH9 10
#define CH10 19
#define CH11 16
#define LED1 13
#define LED2 11
#define RUNNING 1
#define STOPPED 0

unsigned char leds[]={CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11};
unsigned char Runstate=STOPPED;
boolean LED1state = 0;



unsigned int count = 0; //initialize time code count at 0

MIDI_CREATE_DEFAULT_INSTANCE();

void mClockCallback(void)
{
 if(Runstate==RUNNING)          //counter for clock outout
 {
    count++;
  if(count >= 3)
  {
    count=0;
  
    LED1state = !LED1state;
    digitalWrite(LED1, LED1state);
    
   }
 }
  
}

void mStartCallback(void)
{
  Runstate =RUNNING;
  digitalWrite(LED2, HIGH);           //running light indicator
  LED1state = 0;
  count=1; 
  
}
void mStopCallback(void){
  Runstate=STOPPED;
  count = 0;                          //stop running light
  LED1state = 0;
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
  
}


void setup() {

  MIDI.setHandleClock(mClockCallback);
  MIDI.setHandleStart(mStartCallback);
  MIDI.setHandleStop(mStopCallback);

  pinMode(LED1,OUTPUT);
  digitalWrite(LED1, LOW);
  
  pinMode(LED2,OUTPUT);
  digitalWrite(LED2, LOW);
  
 
  {
    pinMode(leds[1,2,3,4,5,6,7,8,9,10,11,12],OUTPUT);
    digitalWrite(leds[1,2,3,4,5,6,7,8,9,10,11,12], LOW);
  }

  MIDI.begin(10);
}


void Gate(byte note, char state)
{
  byte output;
  // 36-46 is our outputs 1-11
  //36 is middle C
  if(note<36)
    return;
  if(note>46)
    return;
    
    
  output = note-36;

  digitalWrite(leds[output],state);
}

void loop() {

  
    if (MIDI.read())
    {
      byte type = MIDI.getType();
      byte Data1 = MIDI.getData1();
      byte Data2 = MIDI.getData2();
      byte Channel = MIDI.getChannel();
 //   MIDI.send(type,Data1,Data2,Channel);  //turn on if midi thru is added


        if(type == 144)  //Note On
        {
          Gate(Data1,HIGH);
        }
        else if(type == 128)  //Note Off
        {
          Gate(Data1,LOW);
        }
      }   
    }

  
