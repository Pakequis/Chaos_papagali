/*
  CHAOS PAPAGALI
  Lôro quer biscoito!
  by Rodrigo Feliciano
  https://www.youtube.com/pakequis
  https://www.pakequis.com.br
*/

#include <LowPower.h>

#define MODE0   0
#define MODE1   1
#define MODE2   2
#define MODE3   3

/*************************/
/* Arduino Uno R3 */
//#define MOTOR_PIN   3
//#define SW1   4
//#define SW2   5
//#define SW3   6
//#define SW4   7
//#define LIGHT_SENSOR_PIN 1
/*************************/

/*************************/
/* Arduino Pro mini */
#define MOTOR_PIN   9
#define SW1   5
#define SW2   4
#define SW3   3
#define SW4   2
#define LIGHT_SENSOR_PIN 1
/*************************/

/******************************/
/* Chaos Papagali basic board */
//#define MOTOR_PIN   12
//#define SW1   4
//#define SW2   5
//#define SW3   6
//#define SW4   7
//#define LIGHT_SENSOR_PIN 3
/*************************/

#define LIGHT_THRESHOLD  450

/* time = random number x8 seconds */
#define TIME_MIN  8   /* 64 seconds */
#define TIME_MID  75  /* 600 seconds = 10 minutes */
#define TIME_MAX  450 /* 3600 seconds = 1 hour */

struct chaos_mode{
  uint8_t chmode;           /* 0 to 3 modes */
  bool day_or_night;        /* 0 = Day, 1 = night */
  bool time_short_or_long;  /* 0 = 1 to 10 minutes, 1 = 10 to 60 minutes */
};

struct chaos_mode modes;

int chaos_time = 0;
int light_value = 0;

void setup() 
{
  //Serial.begin(9600); //for debug only
  pinMode(MOTOR_PIN, OUTPUT);

  randomSeed(analogRead(0));
  
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);

  check_mode(&modes);

  //Serial.println(modes.chmode);

  if(modes.time_short_or_long == 1)
  {
    chaos_time = random(TIME_MID, TIME_MAX);  /* 600 to 3600 seconds */
  }else
  {
    chaos_time = random(TIME_MIN, TIME_MID); /* 64 to 600 seconds */
  }

  digitalWrite(MOTOR_PIN, LOW);
}

void loop() 
{
  light_value = analogRead(LIGHT_SENSOR_PIN);
  /* Execute one chaos mode */
  check_mode(&modes);  
    
  if(((light_value > LIGHT_THRESHOLD) && (modes.day_or_night)) || ((light_value < LIGHT_THRESHOLD) && (!(modes.day_or_night))))
  {
    switch (modes.chmode)
    {
      case MODE0:
        mode_phone_call();
        //Serial.println("Phone Call");
      break;
    
      case MODE1:
        mode_alarm();
        //Serial.println("Alarm");
      break;  
      
      case MODE2:
        mode_notification();
        //Serial.println("Notification");
      break;

      case MODE3:
        mode_chaos();
        //Serial.println("Chaos");
      break;
   
      default:    
    
      break;
    }
  }

  /* Check the random time (short or long) */
  if(modes.time_short_or_long == 1)
  {
    chaos_time = random(TIME_MID, TIME_MAX);  /* 600 to 3600 seconds */
  }else
  {
    chaos_time = random(TIME_MIN, TIME_MID); /* 64 to 600 seconds */
  }

//for debug only
/*  Serial.println(light_value);
  Serial.println(modes.chmode);
  Serial.println(modes.day_or_night);
  Serial.println(modes.time_short_or_long);
  Serial.print("random = ");
  Serial.println(chaos_time);
  delay(100);        */     

  /* Wait in low power mode */
  for(int p = 0; p < chaos_time; p++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
    //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
     //           SPI_OFF, USART0_OFF, TWI_OFF);
  }
}
