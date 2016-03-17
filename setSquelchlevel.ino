/**************************** 
 *  Squelch  Level Option
****************************/

void setSquelchlevel()
{
#ifdef DEBUG
Serial.println(functionLabels[menuSelect-1]);
#endif
  for(int i = 0; i < 2; i++){     // clear the input field
      inputFld[i] = '/0';
  }
  inputCtr = 0;
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);    // print the function title
  getSquelchlevel();
  lcd.setCursor(0, 2);
  lcd.print(F("Squelch = "));
  lcd.setCursor(10, 2);
  lcd.print(squelchLevel);
  lcd.setCursor(0, 3);
  lcd.print(F("A or B")); 
  menuSwitch = 0;
    while(menuSwitch == 0) {
      key = keypad.getKey();               // see if a key has been pressed
      
      if (key) {
        lcd.setCursor(10, 2);    
 
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendSquelchlevel();              
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA) {              // increment squelch value
                   squelchValue++;
                   if (squelchValue > 9) { // max value
                       squelchValue = 0;
                      }
                   lcd.setCursor(10, 2);   
                   lcd.print(squelchValue);
                }
          else  if (key == txtB) {              // decrement squelch value
                   squelchValue--;
                   if (squelchValue < 0) {          // min value
                       squelchValue = 9;
                       }
                   lcd.setCursor(10, 2);    
                   lcd.print(squelchValue);
                }
      }
    }
}

/*************************************
 *      get the current squelch level
*************************************/

void getSquelchlevel()
{
#ifdef DEBUG  
  Serial.println(F("Get sql lvl"));
#endif

  sendReadcmd("SQ?\r");
  get_UV3buff();
  squelchLevel[0] = UV3buff[4];
  memcpy(iPhoneBuffer, txtSquelch, 4);
  iPhoneBuffer[4] = UV3buff[4];
  iPhoneBuffer[5] = '\0';
  sendDataToIphone();
  squelchValue = atoi(squelchLevel);
}

/***********************************
 *   Save the squelch level
***********************************/
void sendSquelchlevel()
{
#ifdef DEBUG  
  Serial.println(F("Send sql lvl"));
#endif

   squelchStr = String(squelchValue);
   squelchStr.toCharArray(squelchLevel, 2);
   sendStorecmd("SQ", squelchLevel);

#ifdef DEBUG
  Serial.print(F("Sqlch lvl = ")); Serial.println(squelchLevel); 
#endif

   lcd.setCursor(0, 3);   
   lcd.print(F("Squelch Level Saved"));
   delay2k();
   getSquelchlevel();
}

