/*********************************
 *      CTCSS Routines
*********************************/

/*****************
 * Set CTCSS
******************/

void setCTCSS()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);          // print the function title
  printCTCSS();                              // print the current CTCSS setting
  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendCTCSS();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA) {              // increment CTCSS value
                   CTCSSctr++;
                   if (CTCSSctr > NUMBEROFTONES) { // table max
                       CTCSSctr = 1;
                      }
                   printCTCSS();   
                }
          else if (key == txtB) {              // decrement CTCSS value
                   CTCSSctr--;
                   if (CTCSSctr < 1) {
                       CTCSSctr = NUMBEROFTONES; // table min
                       }
                   printCTCSS();    
                }
      }
  }
  
}

/*******************************************
 * Print CTCSS entry pointed to by CTCSSctr
********************************************/

void printCTCSS()
{
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("CTCSS = "));
   lcd.print(CTCSStable[CTCSSctr - 1]);       // print the table entry
   lcd.setCursor(0, 3);
   lcd.print(txtAorB);
}
/*************************************
 *      get the current CTCSS 
 *      scroll through the taable of 
 *      values
*************************************/

void getCTCSS()
{
#ifdef DEBUG
 Serial.println(F("get CTCSS"));
#endif  
  char tempCTCSSchar[6];
  sendReadcmd("TF?\r");
  get_UV3buff();
  memcpy(radioCTCSS, UV3buff, 5);
  radioCTCSSf = atof(radioCTCSS)/ 100;                     // convert read CTCSS
  for (int i = 0; i < 50; i++) {                          // look for match to set value of CTCSSctr
      memcpy(tempCTCSSchar, CTCSStable[i], 6);
      float tempCTCSSf = atof(CTCSStable[i]) * 10;
      tempCTCSSf = tempCTCSSf/10;
      if (tempCTCSSf == radioCTCSSf) {                     // matched break out
         String tempIPbuf = "CTCSS: ";
         for (int j = 0; j < 5; j++) {
              tempIPbuf += tempCTCSSchar[j];
         }
#ifdef BLE
          tempIPbuf.toCharArray(iPhoneBuffer, 13);
         iPhoneBuffer[14] = '\0';
         sendDataToIphone() ;     
#endif
          CTCSSctr = i + 1;
          break;
          }
      }

}

/***********************************
 *   Save the CTCSS
***********************************/
void sendCTCSS()
{
#ifdef DEBUG
  Serial.println(F("send CTCSS"));
#endif  
   radioCTCSSf = atof(CTCSStable[CTCSSctr - 1]) * 100;
   radioCTCSSi = radioCTCSSf;
   sprintf(radioCTCSS, "%05i",radioCTCSSi);
   sendStorecmd("TF", radioCTCSS);

   lcd.setCursor(0, 3);
   lcd.print(F("CTCSS Freq Saved"));
   delay2k();
}


