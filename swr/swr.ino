
/*
    ************************************************************** 
    *        POWER & SWR meter on 2x16 char LCD display          *
    *                  By ON7EQ  Aug 2011                        *
    ************************************************************** 

  The circuit:
  
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * GND to LCD VO pin (pin 3) (contrast)
 
 * pin 13 = LCD backlight control (1= backlight ON). Use an emittor follower (like BC639) to control LCD backlight (this draws about 120mA) 


 * pin 4 = connect a piezo buzzer (other end to ground) 


 * pin A0 : SWR probe FWD  voltage input (SWR bridge type 'MONIMATCH')
 * pin A1 : SWR probe REFL voltage input   

    ! Set the diode forward voltage in variable 'Diode'.  For 1SS99 or other Schottky diodes, it is around 130mV @ 0,1mA


 * pin A5 : Power Supply Voltage input  


MODE SELECT : there are 2 possibilities to select mode :
--------------------------------------------------------

1Â° with 3 position toggle switch:

* pin Digital 2 : 'bip' Sound Switch : when grounded -> SWR 'bip' tone mode
* pin Digital 3 : PEP mode Switch : when grounded -> PEP mode

  When switch in center position : normal power/swr mode, instant power & dBm readout
  When using a center toggle switch, Pin 5 must be connected to +5v 
  If a 3-way toggle switch is present, it will be automatically detected and the variable 'PushButton' set accordingly.

  
2Â° with push button for cycling modes:

* pin Digital 5 : Mode push button : when grounded (pulse), next mode is selected
 ! the mode is stored in EEPROM & memorized for next boot


BAND SELECT : 
-------------
It can be necessary to apply different parameters / calibration factors per band.

* pin Digital 6 : BAND push button : when grounded (pulse), next band is selected
 ! the band is stored in EEPROM & memorized for next boot

 */

// include the LCD library code:
#include <LiquidCrystal.h>

// include math functions
#include "math.h" 

// include EEPROM write
#include <EEPROM.h>

// variables

#define TonePin      (4)    // Pin for beeper
#define ToneSwitch   (2)    // one end of 3 way toggle switch
#define PEPswitch    (3)    // the other end of 3 way toggle switch
#define ModeSwitch   (5)    // push button switch (no 3 way toggle switch)
#define BANDSwitch   (6)    // push button switch band change
#define LCDbacklight (13)   // output to power the LCD backlight


#define VoltSupplyMini (66) // minimum battery voltage expressed in 100mV (if lower, alarm is generated)
//                          // for Âµ7805, minimum 7v required



// voltage divider at A5  - select proper values so that voltage never exceeds 5v on A5 !
// With R1 = 1k2 and R2 = 4k7, max input voltage = 25v

#define R1           (12)   // from GND to A5, express in 100R  (12 = 1200 Ohm)
#define R2           (47)   // from + power supply to A5, express in 100R  (47 = 4700 Ohm)


// calibration variables for forward power : 
//     PowCal=(VoltFWDÂ²/Power)/1000  (where Power = Power over 50 Ohm in Watt)
// Carry out calibration with sufficient power !

#define PowCalHF     (100)    // HF band
#define PowCal6m     (21)     // 6m band
#define PowCal4m     (30)     // 4m band  --> pmax @ 5000mV = 833 W (as example)
#define PowCal2m     (117)    // 2m band
#define PowCal70     (57)     // 70cm band
#define PowCal23     (3165)   // 23cm band
#define PowCal13     (64800)  // 13cm band

char* myStrings[]={"  HF ", "  6m ", "  4m ","  2m ", " 70cm"," 23cm"," 13cm"};


/////////////////////// 3 way-mode switch or pushbutton ? ///////////////////////////////////

int PushButton = (1);           // 1 = Pushbutton  /  0 = toggle switch
                                // there is an automatic detection in the display subroutine 

////////////////////////////////////////////////////////////////////////////////////////////

// modes
byte PEP = (1);                   // 0 if PEP measured
byte Tone = (1);                  // 0 if tone SWR tune (bip)

byte MODE = (0);                  // Mode 0 = instant power / Mode 1 = PEP / Mode 2 = Bip
byte BAND =(0);                   // BAND 0 = HF / 1 = 6m  / 2 = 4m / 3 = 2m  / 4 = 70cm  / 5 = 23cm  / 6 = 13cm

unsigned long DisplayTime = 0;    // timer display refresh
unsigned long PeakTime = 0;       // timer peak (PEP) detect
unsigned long BacklightTime = 0;  // backlight LCD hold time
unsigned long BandTime = 0;       // band display hold time

float VoltFWD = 0;
float VoltFWDmax = 0;
float VoltPEP = 0;
float VoltREF = 0;

unsigned int Diode = 130;         // diode forward voltage, expressed in mV

unsigned int PowCal = 103 ;       // calibration factor for power: PowCal=(VoltFWDÂ²/Power)*1000
unsigned long PWR = 0;            // power (expressed in 100 mW)
unsigned int PowDis = 0;          // power for display
float SWR = 0;                    // SWR 
float Vratio = 0;                 // Voltage ratio VoltREF/VoltFWD

int SWRDis = 0;                  // power calculation for showing in display

int VoltFWDmini = 0;

unsigned long PWRmax = 0;         // the maximum power range, band dependant

int beeponce = (0);              // emit only 1 beep for modechange
int beepband = (0);              // emit only 1 beep for bandchange

int SWRtonePitch = (800);        // low lone = low SWR
int SWRtoneLenght = (100);       // long tone = low SWR

int debugled = (0);              // LED at pin13 = debug
int decay = (0);                 // PEP decay rate

unsigned int SupplyVoltage = (0); // Power supply voltage

byte RunOnce =(1);                // detect wether in SETUP or LOOP mode
byte DisplayCycle = (0);          // counts the cycles in display mode (for low volt alert)

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// *************************************************************   
// ********************  S  E  T  U  P  ************************
// *************************************************************   

void setup() {

  //setup pins
  pinMode(LCDbacklight, OUTPUT);  //Backlight LCD display
  pinMode(PEPswitch, 2);      // if grounded --> 'PEP' mode
  pinMode(ToneSwitch, 2);     // if grounded  --> 'Bip' mode
  pinMode(ModeSwitch, 2);     // if grounded  --> cycle through modes
  pinMode(BANDSwitch, 2);     // if grounded  --> cycle through bands
  
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  
 // READ mode from EEPROM & set parameters
 MODE = EEPROM.read(1);
       if (MODE == 0) {         // normal instant power & SWR
              Tone = 1;
              PEP = 1; }
       if (MODE == 1) {        // Tone tune SWR
              Tone = 1;
              PEP = 0; }
       if (MODE == 2) {        // PEP power
              Tone = 0;
              PEP = 1; }
    
 // READ band from EEPROM
  BAND = EEPROM.read(2);
        if (BAND == 0) {         
              BAND = 3;            // No HF for time being, default = 2m
              PowCal = PowCalHF;}
        if (BAND == 1) {         
              PowCal = PowCal6m;}    
        if (BAND == 2) {         
              PowCal = PowCal4m;}
        if (BAND == 3) {         
              PowCal = PowCal2m;}    
        if (BAND == 4) {         
              PowCal = PowCal70;}
        if (BAND == 5) {         
              PowCal = PowCal23;}    
        if (BAND == 6) {         
              PowCal = PowCal13;}
           
     
// calculate max range for this band             
              
double PWRmax = pow((5000 + Diode),2) ;
PWRmax = PWRmax / PowCal / 1000;

// calculate minimum power for 'SWR < 1.5' indication threshold 

// SWR = 1.5 means PWRref / PWRFwd = 0.2
// this means that VoltFWD = diode voltage / SQRT (0.2)
       
// for threshold SWR = 3 : replace 0.45 by SQRT (0.5) = 0.71         
       
VoltFWDmini = (Diode / 0.45);
VoltFWDmini = 2* VoltFWDmini;  // safety factor, required in practice


 

// Print a message to the LCD.
  
  digitalWrite(LCDbacklight,1) ;  // turn backlight on
//  lcd.setCursor(0, 0);
//  lcd.print("Pwr & SWR Meter");
//  lcd.setCursor(0, 1);
//  lcd.print("   6m - 13cm   ");
//    pinMode(TonePin, OUTPUT);
//    tone(TonePin,1200);
//    delay(150);
//    tone(TonePin,1600);
//    delay (150);
//    tone(TonePin,2000);
//    delay (150);
//    noTone (TonePin);
//    delay (2000);
    
//  lcd.setCursor(0, 1);
//  lcd.print("by ON7EQ 08/2011");  
//  delay (2000);  
  

//Power SupplyVoltage measure & display  
//  measuresupplyvolt ();
//  delay (1500);
//
//
//  
//// print max power   
//  lcd.clear(); 
//  
//  lcd.setCursor(2, 0);
//  lcd.print("QRV on");
//  lcd.print( myStrings[BAND]);
//  
//  clearline1();
//  lcd.setCursor(2, 1);
//  lcd.print("Pmax = ");

// if > 1kw, 1kW is enough :o)
//
//if (PWRmax >= 1000) {
//   lcd.print(" 1 kW   "); } 
//
//else {
//    
//  if (PWRmax < 1) {
//   
//            PowDis = PWRmax * 1000;
//            if (PowDis > 100) {          //round PowDis up to ten
//               PowDis = PowDis / 10;
//               PowDis = PowDis * 10;
//               } 
//               
//    //       if (PowDis < 100) {
//    //            lcd.print(" ");
//    //            } 
//    //       if (PowDis< 10) {
//    //            lcd.print(" ");
//    //            } 
//           lcd.print((PowDis), DEC);
//           lcd.print("mW  "); 
//           
//  }
//  
//  else {
//  
//            PowDis = PWRmax ;
//            
//          //format PowDis
//          
//             if (PowDis > 100) {          //round PowDis up to ten
//                  PowDis = PowDis / 10;
//                  PowDis = PowDis * 10;
//                  } 
//                 
//    //         if (PowDis < 100) {
//    //              lcd.print(" ");
//    //              } 
//    //         if (PowDis< 10) {
//    //              lcd.print(" ");
//    //              } 
//             lcd.print((PowDis), DEC);
//             lcd.print("w  ");
//          }
//}
//  delay (4000);  
//  lcd.clear(); 

 // set timers
 DisplayTime = millis ();
 BacklightTime = millis ();      
             
  
} // end of setup
  
// *************************************************************       
// ***********************  L  O  O  P  ************************
// *************************************************************   

void loop() {
 
RunOnce = 0;     // Now we are in loop  
  
 // Check if mode to be cycled

if (digitalRead (ModeSwitch) == 0) {  // Mode cycle pushbutton depressed

              digitalWrite(LCDbacklight, 1) ;        // turn backlight on
              BacklightTime = millis ();  //reset timer to light LCD
                 if (beeponce == 0 ) {
                   tone(TonePin,1750);
                   delay (100);
                   tone(TonePin,1000);
                   beeponce = 1;
                   delay (20);
                 }
                 delay (50);             // give tone & debounce
                 noTone (TonePin);   
                           
                
              if (digitalRead (ModeSwitch) == 1) { // released
               
                  beeponce = 0;
                  
                          MODE = MODE + 1;  
                            if (MODE >= 3) MODE = 0;
                          
                            EEPROM.write(1,MODE);  // store new mode permanently 
                            
                            if (MODE == 0) {       // normal instant power & SWR
                              Tone = 1;
                              PEP = 1; }
                            if (MODE == 1) {       // Tone tune SWR
                              Tone = 1;
                              PEP = 0; }
                            if (MODE == 2) {       // PEP power
                              Tone = 0;
                              PEP = 1; 
                              VoltFWDmax = (0);
                              PeakTime = millis (); }
  
                              }
              }
  
  // Check if band to be cycled
  
 if (digitalRead (BANDSwitch) == 0) {                // BAND cycle pushbutton depressed

              digitalWrite(LCDbacklight, 1) ;        // turn backlight on
              BacklightTime = millis ();             //reset timer to light LCD
                 if (beepband == 0 ) {
                   tone(TonePin,1200);
                   delay(100);
                   tone(TonePin,1600);
                   delay (100);
                   tone(TonePin,2000);
                   beepband = 1;
                   delay (50);
                 }
                 delay (50);                        // give tone & debounce
                 noTone (TonePin);   
                           
                
              if (digitalRead (BANDSwitch) == 1) {   // released
               
                  beepband = 0;
                  
                          BAND = BAND + 1;  
                            
                            if (BAND >= 7) BAND = 1;    // set 0 if HF is enabled !
                          
                            EEPROM.write(2,BAND);       // store new mode permanently 
                            
                            if (BAND == 0) {            //set proper calibration constants
                                  PowCal = PowCalHF;}
                            if (BAND == 1) {         
                                  PowCal = PowCal6m;}    
                            if (BAND == 2) {         
                                  PowCal = PowCal4m;}
                            if (BAND == 3) {         
                                  PowCal = PowCal2m;}    
                            if (BAND == 4) {         
                                  PowCal = PowCal70;}
                            if (BAND == 5) {         
                                  PowCal = PowCal23;}    
                            if (BAND == 6) {         
                                  PowCal = PowCal13;}
                                  
                                  
               //show  band  
                    lcd.setCursor(11, 1);
                    lcd.print( myStrings[BAND]);
                    
                //show Pmax for this band                                
                    clearline0();
                    lcd.setCursor(0, 0);
                    lcd.print("Pmax = ");

              // calculate max range for this band             
                            
              double PWRmax = pow((5000 + Diode),2) ;
              PWRmax = PWRmax / PowCal / 1000;
              
                  // if > 1kw, 1kW is enough :o)
                  if (PWRmax >= 1000) {
                     lcd.print(" 1 kW   "); } 
                  
                  else {
                      
                    if (PWRmax < 1) {
                     
                              PowDis = PWRmax * 1000;
                              if (PowDis > 100) {          //round PowDis up to ten
                                 PowDis = PowDis / 10;
                                 PowDis = PowDis * 10;
                                 } 
                                 
                    //         if (PowDis < 100) {
                    //              lcd.print(" ");
                    //              } 
                    //         if (PowDis< 10) {
                    //              lcd.print(" ");
                    //              } 
                             lcd.print((PowDis), DEC);
                             lcd.print("mW  "); 
                             
                    }
                    
                    else {
                    
                              PowDis = PWRmax ;
                              
                            //format PowDis
                            
                               if (PowDis > 100) {          //round PowDis up to ten
                                    PowDis = PowDis / 10;
                                    PowDis = PowDis * 10;
                                    } 
                                   
                     //          if (PowDis < 100) {
                     //               lcd.print(" ");
                     //               } 
                     //          if (PowDis< 10) {
                     //               lcd.print(" ");
                     //               } 
                               lcd.print((PowDis), DEC);
                               lcd.print("w  ");
                                    }
                            }                            
                   
                   BandTime = millis();  // reset display timer for bandchange display        
                   // delay (1000);
                      }
              }
  
   
 // read sensors 

if (PushButton == 0) {             // Read 3 way switch
 Tone = digitalRead (ToneSwitch);  // read tone button
 PEP = digitalRead (PEPswitch);    // read PEP button
}


 VoltFWD = analogRead(A0);        // Read FWD sensor voltage
 VoltREF = analogRead(A1);        // Read REFL sensor voltage
 
 // PEP detect
 
 if (VoltFWD > VoltFWDmax) {  
      VoltFWDmax = VoltFWD;
      PeakTime = millis ();
      decay = 1;
       }
       
// decay

else if ((millis() - PeakTime) > 400) {  // 400 = PEP Peak hold time
              VoltFWDmax = VoltFWDmax / (decay + 0.3);
              PeakTime = millis ();
              decay = decay + 1;         //decay 
                }
      
// LCD refresh if no tone mode 
if (((millis() -  DisplayTime) > 200) and (Tone == 1)){   //200 = display refresh rate in PEP & dBm mode
    DisplayTime = millis ();
    refreshdisplay();
    }
if (Tone == 0) {                         // in tone mode, refresh triggered by tone
     decay = 0;
     refreshdisplay();
     } 
  
    
}

// =========================================================
// ************ Refresh LCD display Routine ****************
// =========================================================


void refreshdisplay () {  

 
  // check for low battery
  
   DisplayCycle = DisplayCycle ++ ;     
   
   if (DisplayCycle >= 50) {   // every 50 display cycles, check battery voltage
     DisplayCycle = (0);
     measuresupplyvolt ();
     }
   
  
  // check if band change and display to hold
  
  if (((millis() -  BandTime) < 3000)) return;  // show band change parameters
   
  
  // Check if toggle switch for mode is present, default is push button 
  
 if ((digitalRead (ToneSwitch) == 0)  or digitalRead (PEPswitch) == 0) {
   PushButton = (0);                    // toggle switch is present
 }
  
  
  // LCD Backlight
 
  if (VoltFWD>0) {  
 digitalWrite(LCDbacklight,1) ;        // turn backlight on
 BacklightTime = millis ();             //set timer 
  }
 else if (((millis() -  BacklightTime) > 8000)) {    // 8 seconds backlight
  digitalWrite(LCDbacklight, 0) ;                    // turn backlight off  
 }
  
  // Overrange detect
 VoltFWD = analogRead(A0);
 
 if ((VoltFWD>1022) and (digitalRead (ModeSwitch) == 1) ) { 
   lcd.clear();
   lcd.setCursor(1, 0);
   lcd.print("- Overrange -"); 
   lcd.setCursor(2, 1);
   lcd.print(VoltFWD); 
 
  // calculate max range for this band             
                            
    double PWRmax = pow((5000 + Diode),2) ;
    PWRmax = PWRmax / PowCal / 1000;
    
    // if P > 1kw, 1kW is enough :o)
    if (PWRmax >= 1000) {
       lcd.print(" 1 kW   "); } 
    
      else {
          
        if (PWRmax < 1) {                      // We are measuring milliwatts
         
                  PowDis = PWRmax * 1000;
                  if (PowDis > 100) {          //round PowDis up to ten
                     PowDis = PowDis / 10;
                     PowDis = PowDis * 10;
                     } 
                     
                 if (PowDis < 100) {
                      lcd.print(" ");
                      } 
                 if (PowDis< 10) {
                      lcd.print(" ");
                      } 
                 lcd.print((PowDis), DEC);
                 lcd.print(" mW "); 
                 
        }
        
        else {
        
                  PowDis = PWRmax ;                      // We are measuring watts
         
                    //format PowDis
                
                   if (PowDis > 100) {                   //round PowDis up to ten
                        PowDis = PowDis / 10;
                        PowDis = PowDis * 10;
                        } 
                       
                   if (PowDis < 100) {
                        lcd.print(" ");
                        } 
                   if (PowDis< 10) {
                        lcd.print(" ");
                        } 
                   lcd.print((PowDis), DEC);
                   lcd.print(" w ");
                        }
                }                            
  
   tone(TonePin,2500);
   delay (200) ;
   noTone(TonePin);
   
   if  (digitalRead (ModeSwitch) == 1) delay (2000) ;
   lcd.clear();
   return;
}
  // process FWD voltage
  
 VoltFWD = map(VoltFWD, 0,1023,0,5000);
 VoltFWD = (VoltFWD + Diode);       //correct for diode voltage drop
 
  //process REF 

 VoltREF = map(VoltREF, 0,1023,0,5000);
 VoltREF = (VoltREF + Diode);      //correct for diode voltage drop

 
 // POWER Display
 lcd.setCursor(0, 0);
 lcd.print("Pwr "); 
 
 
 /* CALIBRATION ROUTINE FORWARD VOLTAGE  ////////////////////
 
 // This routine prints on LCD the FWD voltage measured.
 // When no power applied, the FWD voltage displayed will be the diode voltage in mV
 // To calculate the calibration factor, take the reading (including diode voltage)
 // Uncomment this routine to enter calibration mode
 
 lcd.setCursor(0, 0);
 lcd.print("VoltFWD= "); 
 lcd.print(VoltFWD, DEC);   
 delay(500);                
 
 */   //////////////////////////////////////////////////////
 
 //calcultate Power Max, we will need it later
 double PWRmax = pow((5000 + Diode),2) ;
 PWRmax = PWRmax / PowCal / 1000; 
 
 
 if (PEP == 1) {    // Instant POWER MODE
           double PWR = pow(VoltFWD,2) ;
           PWR= PWR / PowCal / 1000;
            if (VoltFWD<(Diode+2)) {
              PWR = 0;
              }
        
        if (PWRmax < 1) {               // milliwatt readout
         
             PowDis = PWR * 1000;    
                 if (PowDis < 100) {
                      lcd.print(" ");
                      } 
                 if (PowDis < 10) {
                      lcd.print(" ");
                      } 
                 lcd.print((PowDis), DEC);
                 lcd.print(" mW ");        
                if ((PWR > 0) & (Tone == 1)) {
                
                    if ((10*log10(PWR*1000)) >= 0) {lcd.print("+");} //  +  dBm
                 lcd.print(10*log10(PWR*1000)); // dBm calculation
                 }
                 else if (Tone == 1) {
                 lcd.print("(dBm)");
                   }
               if (Tone == 0) lcd.print("(Bip)");
                   
        }
        
        else {
           PowDis = PWR * 10;
       
           if (PowDis/10 < 100) {
                lcd.print(" ");
                } 
           if (PowDis/10 < 10) {
                lcd.print(" ");
                } 
           lcd.print((PowDis/10), DEC);lcd.print(".");
           lcd.print((PowDis)%10, DEC);
           lcd.print("w ");
           if ((PWR > 0) & (Tone == 1)) {
           if ((10*log10(PWR*1000)) >= 0) {lcd.print("+");} //  +  dBm
           lcd.print(10*log10(PWR*1000)); // dBm calculation
           }
           else if (Tone == 1) {
           lcd.print("(dBm)");
             }
         if (Tone == 0) lcd.print("(Bip)");
            }
           }
   
   
   
     
               
 else if (PEP == 0) {    // PEP POWER MODE
 
           Tone == 1;   // Reset Tone mode
 
             VoltPEP = map(VoltFWDmax, 0,1023,0,5000);
             VoltPEP = (VoltPEP + Diode); //correct for diode voltage
    
           double PWR = pow(VoltPEP,2) ;
           PWR= PWR / PowCal / 1000;
            if (VoltPEP<(Diode+2)) {
              PWR = 0;
              }
           
            if (PWRmax < 1) {     //milliwatt readout
        
                 PowDis = PWR * 1000;    
                 if (PowDis < 100) {
                      lcd.print(" ");
                      } 
                 if (PowDis < 10) {
                      lcd.print(" ");
                      } 
                 lcd.print((PowDis), DEC);
                 lcd.print(" mW (PEP)");     
                     
            }
            
            else {              
           PowDis = PWR * 10;
           if (PowDis/10 < 100) {
                lcd.print(" ");
                } 
           if (PowDis/10 < 10) {
                lcd.print(" ");
                } 
           lcd.print((PowDis/10), DEC);lcd.print(".");
           lcd.print((PowDis)%10, DEC);
           lcd.print("w (PEP)");
            }
               }
  
              
 // SWR Display
 
 // print the band
 
  lcd.setCursor(11, 1);
  lcd.print( myStrings[BAND]);
 
 lcd.setCursor(0, 1);
 lcd.print("SWR  "); 
 
if ((VoltFWD <= (Diode+2)) or (PEP == 0))  {    // No power = no SWR to detect
     lcd.print(" -.-  ");  
     }  
 
    else if ( (VoltFWD > (Diode+1)) & (VoltFWD < (VoltFWDmini)) & (VoltREF <= (Diode+1))){   // at low power no SWR display or < 1.5
    lcd.print("<1.5 ");
     }
  
 
 else { 
 Vratio = VoltREF / VoltFWD;
 
 // Check ROUTINE
 
 //lcd.print(VoltREF, DEC);   // DEBUG
 //lcd.print(Vratio, DEC);    // DEBUG
 
 SWR = ((1 + Vratio)/ (1 - Vratio));
 
 if ((SWR > 3.1) & (PEP == 1)) {
   lcd.print(" > 3  "); 
    tone(TonePin,2500);
    delay (60);
    noTone(TonePin);
   }
 
 else {
 SWRDis = SWR * 10;
 
 if (SWRDis < 10){    // SWR cannot be lower than 1.0
    SWRDis = 10 ;
    }

  if (SWRDis/10 < 10) {
      lcd.print(" ");
      }
 
 lcd.print((SWRDis/10), DEC);lcd.print(".");
 lcd.print((SWRDis)%10, DEC); 
 lcd.print("  ");   
   

   
 /// SWR 'Bip' MODE
  
 if ((Tone == 0) and (digitalRead (ModeSwitch) == 1)) {
        SWRtonePitch = map((SWRDis*SWRDis),100,900,300,2200); 
        SWRtoneLenght = map((SWRDis*SWRDis),100,900,300,60); 
        tone(TonePin,SWRtonePitch);
        delay (SWRtoneLenght);
        noTone(TonePin);
       }

}
}    

if ((Tone == 0) and (digitalRead (ModeSwitch) == 1)){
  delay (SWRtoneLenght/3);       // leave silence between SWR beeps, only if no mode change required
 }
}


void clearline0 () {            // subroutine clear top line display
  lcd.setCursor(0, 0);
  lcd.print("                "); 
}

void clearline1 () {            // subroutine clear bottom line display
  lcd.setCursor(0, 1);
  lcd.print("                "); 
}

void measuresupplyvolt () {    // Power SupplyVoltage measure

 SupplyVoltage = analogRead(A5);        // Read power supply voltage
 SupplyVoltage = map(SupplyVoltage, 0,1023,0,(50*(R2+R1)/R1));
 if (SupplyVoltage <= 50) return;       // not running on batteries !
 if (SupplyVoltage >= 84) SupplyVoltage=SupplyVoltage+6 ;   // running on ext power, correct for diode voltage drop 0.6v 
 
// print power supply voltage if startup or low battery condition
 
 if ((RunOnce == 1)  or  (SupplyVoltage <= VoltSupplyMini))   {
 
        lcd.clear(); 
        
        lcd.setCursor(0, 0);
        lcd.print("Batt Volt=");  
               if (SupplyVoltage < 100) {
                 lcd.print(" ");
                      } 
                 if (SupplyVoltage < 10) {
                      lcd.print(" ");
                      } 
                 lcd.print((SupplyVoltage/10), DEC);
                     lcd.print(".");
                 lcd.print((SupplyVoltage)%10, DEC); 
                      lcd.print("v");
        if   (SupplyVoltage  <= VoltSupplyMini) {           
          lcd.setCursor(2, 1);                 
          lcd.print("LOW BATTERY !");
        }
        delay (1500);
       }    
  
}  
  
