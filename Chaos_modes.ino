/*
  CHAOS PAPAGALI
  Lôro quer biscoito!
  by Rodrigo Feliciano
  https://www.youtube.com/pakequis
  https://www.pakequis.com.br
*/

/* Check dip switch config */
void check_mode(chaos_mode *cm)
{
  cm->chmode = 0;
  bitWrite(cm->chmode, 0, digitalRead(SW1));
  bitWrite(cm->chmode, 1, digitalRead(SW2));

  cm->day_or_night = digitalRead(SW3);
  cm->time_short_or_long = digitalRead(SW4);
}


/* phone call (1250ms ON, 1000ms off */
void mode_phone_call(void)
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(MOTOR_PIN, 1);
    delay(1250);
    digitalWrite(MOTOR_PIN, 0);
    delay(1000); 
  }
}

/* Phone alarm (500ms on, 500ms off */  
void mode_alarm(void)
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(MOTOR_PIN, 1);
    delay(500);
    digitalWrite(MOTOR_PIN, 0);
    delay(500); 
  }
}

/* Phone notification */
void mode_notification(void)
{
  digitalWrite(MOTOR_PIN, 1);
  delay(250);
  digitalWrite(MOTOR_PIN, 0);
  delay(100);   
  digitalWrite(MOTOR_PIN, 1);
  delay(250);
  digitalWrite(MOTOR_PIN, 0);
  delay(100);   
}

/* All modes */
void mode_chaos(void)
{
  int rnd_mode = random(0,4);
  switch (rnd_mode)
  {  
    case MODE0:   /* 20% */
      mode_phone_call();
    break;
      
    case MODE1:
      mode_alarm(); /* 20% */
    break;
      
    default:    /* Notification with 60% chance */ 
      mode_notification();
    break;
  }
}
