/******************************************
 * setCodeSpeed
******************************************/

void setCodeSpeed()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);           // print the function title
  getCodeSpeed();                          // get the code speed
  printCodeSpeed();                        // print the current code speed
  lcd.setCursor(0, 3);
  lcd.print(txtAorB);

  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){             // loop until the * or # are pressed

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;                      // kill the loop
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendCodeSpeed();               // send the new code speed
                  lcd.clear();
                  menuSwitch = 1;                // kill the loop
                  break;
                  }
          else if (key == txtA ) {              // increment code speed value
                   codeSpeed++;
                   if (codeSpeed > 25) {
                       codeSpeed = 5;
                      }
                   printCodeSpeed();              // print the code speed value   
                }
          else if (key == txtB) {              // decrement code speed value
                   codeSpeed--;
                   if (codeSpeed < 5) {
                       codeSpeed = 25;
                       }
                   printCodeSpeed();              // print the code speed value       
                }
      }
  }
  
}

/*******************************************
 * Print Code Speed
********************************************/

void printCodeSpeed()
{
#ifdef DEBUG
Serial.println(F("Enter Print Code Speed"));
#endif
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("Code Speed = "));
   if (codeSpeed < 10) {           // handle code speed less than 10
    lcd.print(txtZero);
   }
 
   lcd.print(codeSpeed);
   lcd.print(F(" WPM"));
}
/*************************************
 *      get the current Code Speed 
*************************************/

void getCodeSpeed()
{
#ifdef DEBUG
 Serial.println(F("get code speed"));
#endif  
  sendReadcmd("CS?\r");
  get_UV3buff();
 Serial.print(F("UV3buff = ")); Serial.println(UV3buff);
  for (int i = 0; i < 2; i++) {             // move code speed from common buffer
        tempCodeSpeed[i] = UV3buff[i + 6];
        tempCodeSpeed[i + 1] = txtNull;
  }
  codeSpeed = atoi(tempCodeSpeed);
 
 }

/***********************************
 *   Save the Code Speed
***********************************/
void sendCodeSpeed()
{
#ifdef DEBUG
  Serial.println(F("send Code Speed"));
#endif  
   sprintf(tempCodeSpeed, "%02.2i", codeSpeed);      // format codeSpeed before sending to uv3
   tempCodeSpeed[3] = txtNull;
//#ifdef DEBUG   
 Serial.print("tempCodeSpeed = "); Serial.println(tempCodeSpeed);
//#endif
   sendStorecmd("CS", tempCodeSpeed);
   lcd.setCursor(0, 3);
   lcd.print(F("Code Speed Saved   "));
#ifdef BLE
      sendReadcmd("CS?\r");
      get_UV3buff();
      copyUV3buffToIphoneBuffer();
      sendDataToIphone();
#endif  
   delay2k();
}


