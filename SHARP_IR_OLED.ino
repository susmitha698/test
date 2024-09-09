/* This code works with SHARP IR proximity sensor and 132x64 OLED display and a push button
 * It displays the measured distance in "mm" and with every button press it switch to "cm" or "inch" and goes back
 * Refer to www.surtrtech.com for more details
 */
#include <SharpIR.h>              //IR sensor library and OLED Adafruit library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define ir A0
#define model 20150  //or1080 depends on the model it actually means the range in cm 20-150 or 10-80
                     //  1080 for GP2Y0A21Y
                    //  20150 for GP2Y0A02Y
#define Button1 2   //Push button digital pin, please note that it should be wired with this pin and GND

bool Button1_state; //Here we store the button state if it's LOW or HIGH

short State=1;      //State is 1 at default and could change to 2 or 3

SharpIR IR_prox(ir,model);   //IR sensor name "IR_prox"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)

void setup() {
  
  pinMode(Button1, INPUT_PULLUP); //Here I activate the internal pull up for the button (Always on HIGH state, when pressed goes LOW)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.setTextSize(2);                
  display.setTextColor(WHITE);
  display.print("DigitSpace"); //Project sponsor www.DigitSpace.com
  display.display();
  delay(2000);
  

}

void loop() {

  int dis_cm=IR_prox.distance();   //Read the distance in cm



    Button1_state=digitalRead(Button1);     //We're constantly reading the button wired on D2 if it's pressed or not
     if(Button1_state==LOW){               //if the button is pressed
         if(State<3)                       //We check the State value it should be 1 or 2
         State+=1;
         
         else                              //if it's 3 we go back to one
         State=1;
         
     delay(200);                          //a delay is needed so the push won't be counted twice or more times
     }


      display.clearDisplay();
      display.setCursor(20,20);

      if(State==1){                           //Depending on the button state we will display mm, cm or in
      display.print(dis_cm*10);
      display.print(" mm");                  //in mm we just multiply by 10
      }
      if(State==2){
      display.print(dis_cm);
      display.print(" cm");                  //cm is default
      }
      if(State==3){
      display.setTextSize(1);
      display.setCursor(40,0);
      display.print("USA Baby");           //Was just messing up you can remove it of course :D :D 
      display.setTextSize(2);
      display.setCursor(20,20);
      float in_m=dis_cm/2.54;               //Conversion to inches also a float
      display.print(in_m);
      display.print(" in");
      }                                    //You can add as many state as you want to add other units just do the correct changes
      
      display.display();
      delay(50);
      display.clearDisplay();

}
