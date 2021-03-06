/**********************************
 *       Main Menu
 *       scroll through the menu 
 *       titles or accept number 
 *       directly
***********************************/

void mainMenu()
{
  lcd.clear();
  lcd.setCursor(0, 0);      // line 1 col 8
  lcd.print(F("Function Selection"));      // print the function title
  lcd.setCursor(0, 2);
  lcd.print(F("Enter Fn "));
  menuSwitch = 0;                    // ensure while loop runs
  inputFld[1] = txtNull;  // clear enough input field
  menuSelect = 1;
  printMenuselect();  
  while(menuSwitch == 0) {          // loop until exit key is pressed or menu option is complete
 
        str=String(menuSelect); //converting integer into a string
        str.toCharArray(inputFld,2); //passing the value of the string to the character array   
        key = keypad.getKey();      // see if a key has been pressed
        if (key) {
            if (buzzerEnabled == true){        // check if buzzer should buzz
                beep();                    
                }
           printMenuselect();       
           if (key == txtHashTag) {      // exit key
               lcd.clear();            // clear the lcd
               menuSwitch = 1;        // ensure stop while loop compare and main menu returns to loop
               break;
               }
               else if (key == txtStar ) {     // user confirmed with a * key
                    processMenu();
                     break;
                    }
              else if (key == txtA) {              // increment function number
                       menuSelect++;                // bump the menu number
                       if (menuSelect > MAXFUNCTIONS) {
                           menuSelect = 1;
                           }             
                       printMenuselect();
                       }  else if (key == txtB) {           // decrement function number
                                   menuSelect--;    
                                   if (menuSelect < 1) {
                                       menuSelect = MAXFUNCTIONS;
                                       }
                                    printMenuselect()  ;
                       }  else if (key == txtC) {        
                                   menuSelect = menuSelect + 5;    
                                   if (menuSelect > MAXFUNCTIONS) {
                                       menuSelect = 1;   
                                   }                    
                       }  else if (key == txtD) {   
                                   menuSelect = menuSelect - 5;    
                                   if (menuSelect < 1) {
                                       menuSelect = MAXFUNCTIONS;
                                       }
                       }  else {
                                if (inputCtr < 10) {           // check if enter 1st digit
                                    lcd.print(txtSpaceTwo);
                                    lcd.setCursor(9, 2);
                                    } else {
                                            inputCtr = 0;
                                            lcd.setCursor(10, 2);
                                            }
                                    lcd.print(key);                 // display input key  
                                    inputFld[inputCtr] = key;
                                    menuSelect = atoi(inputFld);
                                    if (menuSelect < 1 || menuSelect > MAXFUNCTIONS) {
                                        lcd.setCursor(9, 2);
                                        lcd.print(menuSelect);
                                        menuSelect = 1;
                                        lcd.setCursor(0, 3);
                                        lcd.print(F("Invalid selection"));
                                        delay2k();
                                        lcd.setCursor(0, 3);
                                        lcd.print(txtSpace20);
                                    }
                       }
          printMenuselect();    
          inputCtr = 0;  
          }
  }
}
/*********************************
 *    print input field results
*********************************/

void printMenuselect()
{
  lcd.setCursor(0, 1);
  lcd.print(functionLabels[menuSelect - 1]);
  lcd.setCursor(9, 2);
  lcd.print(txtSpaceTwo);
  lcd.setCursor(9, 2);
  lcd.print(menuSelect);
  lcd.setCursor(9, 2);

}

/***************************************
 *    Process Menu
***************************************/
void processMenu()
{
       switch (menuSelect)    {    
          case 1:              // set the receive freq
           freqSwitch = 1;
           setFreq();
           break;
            
          case 2:              // set the xmit freq
           freqSwitch = 2;
           setFreq();
           break;

          case 3:             // Squelch level
           setSquelchlevel();
           break;

          case 4:            //  Tone Sqlch ON/OFF 
           setToneMode();
           break;
           
           case 5:             // Set CTCSS  
           CTCSSswitch = 1;      
           setCTCSS(); 
           break;
    
          case 6:             // Reptr ON/OFF
           toggleRepeater();
           getConfiginfo();
           printFreq();
           break;


          case 7:            // Set Beep 
           toggleBeep();
           break;
            
           
          case 8:            // fan on/off
           toggleFan();
           break;

          case 9:            // Set time
          settheTime();
          break;

          case 10:           // Set Volume
          settheVolume();
          break;
          
          case 11:           // Display System Info
          get_repeater_info();
          break;

          case 12:          // Reset RS-UV3
          reset_RS_UV3();
          break;
          
          case 13:           //   Set Call Sign 
          SetCallsign();
          break;

          case 14:          //   Transmit Call Sign
          xmitCallsign();
          break;
          
          case 15:           //   Set Hang Time 
          SetHangTime();
          break;

          case 16:          //   Set ID Time
          SetIDtime();
          break;
          
          case 17:          //   Set Time Out Timer
          setTimeouttimer();
          break;

          case 18:          //   toggle transmitter
          toggleTransmitter();
          break;

          case 19:         // Toggle DTFM Detect
          toggleDTFM();
          break;
          
          case 20:         // Set Code Speed
          setCodeSpeed();
          break;
          
         default:
           break;   
  
        }
     menuSwitch = 1;          // ensure stop while loop compare and main menu returns to loop

}

