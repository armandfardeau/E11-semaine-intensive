// include la librairie du servo
#include <Servo.h>
//include la librairie du rtc 
#include <Wire.h>
#include <RTClib.h>

//include la librairie du neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 10
#define STRIPSIZE 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

//rename des modules
RTC_DS1307 RTC;
Servo myServo;

// servo var part
  unsigned int servo = 3;
  //Position ouverte = 90 degré
  int open = 90;
  //Position fermé = 10 degré
  int close = 10;
  //boolean boxclosed
  bool boxClosed;

//var used in serial communication part
  char junk;
  String inputString="";
  String dateUser;
  String boxTime = "";

//var used to split the user time 
int dayUser;
int monthUser;
int yearUser;
int hourUser;
int minuteUser;  


//function declaration
void FunctionStringToInt(String _string){
  int i;
  for( i = 0; i< _string.length(); i++){
    switch (i) {
        case 0:
         dayUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
        case 1:
         dayUser += FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 2:
         monthUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 3:
        monthUser += FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 4:
          yearUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 5:
          yearUser += FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 6:
          yearUser += FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 7:
          yearUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 8:
          hourUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 9:
          hourUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 10:
          minuteUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
          case 11:
          minuteUser = FunctionCompare(_string[i])*pow(10,(_string.length()-i-1));
          break;
      } 
    } 
}

int FunctionCompare(char _char){
    if(_char == "0"){
        return 0;
    }
    if(_char == "1"){
      return 1;
    }
    if(_char == "2"){
      return 2;  
    }
    if(_char == "3"){
      return 3;  
    }
    if(_char == "4"){
      return 4;  
    }
    if(_char == "5"){
      return 5;  
    }
    if(_char == "6"){
      return 6;  
    }
    if(_char == "7"){
      return 7;  
    }
    if(_char == "8"){
      return 8;  
    }
    if(_char == "9"){
      return 9;  
    }
}

unsigned long FunctionTimeLeft(actualDay,actualMonth,actualYear,actualHour,actualMinute,futureDay,futureMonth,futureYear,futureHour,futureMinute){}
void setup() {
//RTC module begin
  Wire.begin();
  RTC.begin();
  // regler la date et l'heure à la compilation, décommenter pour ajuster l'heure, commenter une fois reglé
  //RTC.adjust(DateTime(__DATE__, __TIME__));
//RTC module end


// strip module begin
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
// strip module end  

// servo module begin  
  myServo.attach(servo);
//servo module end

//bluetooth module begin
  //BT is connected to TX and RX, it use Serial communication. Baud rate muste be send to 115200
  Serial.begin(115200);            // set the baud rate to 9600, same should be of your Serial Monitor
//Bluetooth module end 

//led13 begin
  //used for debug
pinMode(13, OUTPUT);
// led13 module end
 
}

void loop()
{
  DateTime now = RTC.now();
  //Serial.print(now.minute());
  //Serial.println(now.second());
  boxTime = String(now.day());
  boxTime += String(now.month());
  boxTime += String(now.year());
  boxTime += String(now.hour());
  boxTime += String(now.minute());


  if(Serial.available()){
    while(Serial.available())
      {
        inputString = Serial.readString(); //read the input
        //char inChar = (char)Serial.read(); //read the input
        //inputString += inChar;        //make a string of the characters coming on serial
      }
    
      
      if(inputString == "close"){   //incase of 'close' close the box
        digitalWrite(13, HIGH);
        boxClosed = true;
         myServo.write(close);
      }
      else if(inputString == "open"){   //incase of 'open' open the box
        digitalWrite(13, HIGH);
        boxClosed = false;
         myServo.write(open);
      }
      //if input is not empty then it must be full of something, like the numbers we need
      else{
        dateUser = inputString;
        FunctionStringToInt(dateUser);
      }
      while (Serial.available() > 0)  
      { junk = Serial.read() ; }      // clear the serial buffer
      inputString = "";
    }
  else if (boxClosed == true){
    if(dateUser == boxTime){
      digitalWrite(13, HIGH);
      boxClosed = false;
      myServo.write(open);
      }
    }
  else{}
}



  
