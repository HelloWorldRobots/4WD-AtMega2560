#include <LiquidCrystal.h> 
#include <ShiftRegister74HC595.h>
#include <RBD_LightSensor.h>
ShiftRegister74HC595<1> sr(52, 53, 54);
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);
RBD::LightSensor light_sensor(A2);
bool Offroad = false;
int info;
const int ButtonPin = 29;
int ButtonState; 
int Contrast=0;
const int LED_A = 32;
const int LED_B = 33;
const int LOWER_LED = 34;
const int TrigPin = A0;
const int EchoPin = A1;
const int ForwardL = 2;
const int ForwardR = 3;
const int BackwardL = 4;
const int BackwardR = 5;
const int LEDPIN = 10;
const int a = 6;
const int b = 7;
const int c = 8;
const int d = 9;
int Light;
int range = 6;  
int near = 8;
int Follow = 20;
int Point = 35;


/* This is the setup for the robot, which also contains the "center-point" for the code */
void setup() {
  /* Setting up all the pins */
  analogWrite(22, Contrast);
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LOWER_LED, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(ForwardL, OUTPUT);
  pinMode(ForwardR, OUTPUT);
  pinMode(BackwardL, OUTPUT);
  pinMode(BackwardR, OUTPUT);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  analogWrite(29, Contrast);
  pinMode(ButtonPin, INPUT_PULLUP);
  lcd.begin(16,2);
  
  /* Booting Up LED (Used to determine errors) */
  for(int p = 0; p < 8; p++){
  digitalWrite(LOWER_LED, HIGH);
  delay(350);
  digitalWrite(LOWER_LED, LOW);
  delay(350);
  }
  NIGHT_MODE();
  /* Serial Begins at 9600 Baud Rate */
  Serial.begin(9600);
   String start[] = {"Following Mode", "Obstacle Avoider", "Maze Mode", "Manual Mode"};
  String Speed[] = {
    "100", "50", "25"
  };
  lcd.print("Select the mode: ");
  delay(2000);
  lcd.clear();
  for(int i = 0; i < 4; i++){

    lcd.begin(16,2);
    lcd.print(start[i]);
    delay(2500);
    int ButtonState = digitalRead(ButtonPin);
    if(ButtonState == LOW){
      lcd.clear();
      delay(500);
      lcd.print("Setting it up...");
      delay(500);
      lcd.clear();
      lcd.print("Set to " + start[i]);
      delay(670);
      lcd.clear();
 
      lcd.print("Starting...");
      delay(950);
      lcd.clear();
      lcd.print("Select the Speed of the Motors");
      delay(1000);
      lcd.clear();
      lcd.print("Offroading Mode ?");
      delay(2500);
      int ButtonState = digitalRead(ButtonPin);
      if(ButtonState == LOW){
        lcd.clear();
        lcd.print("Making Adjustments..");
        delay(1000);
        lcd.clear();
        Offroad = true;
      }

      lcd.clear();
      lcd.print(start[i]);
      break;
      
      if(start[i] == "Following Mode"){
        while(true){
        FollowObjectAuto();
        }
        
      }
      if(start[i] == "Obstacle Avoider"){
        while(true){
          AutoMode();
        }
      }
      if(start[i] == "Maze Mode"){
        while(true){
         Go_To_Point_A();
        }
        
      }
      if(start[i] == "Manual Mode"){
        /* The main "loop" that runs the program together */
            while(true){
            /* Functions called in this loop, can be later seen below in the code */
            BlinkLED();
            /* Checks, if there is signal from Bluetooth (connected to the Serial Pins) */
            if(Serial.available() > 0){
              /* Reads the Signal */
              info = Serial.read();
             }
              /* Checks, the signal and executes the action respectively */
              if(info == '2'){
                
                  if(Offroad == false){
                  /* Defining "long" inches and using it to detect any nearby object's, while in Manual Control of the Robot*/
                  long inches;
                  Object_Detection(inches);
                  /* Obstacle deteced, procceds to safety */
                  if(inches < near){
                     backward();
                     /* Goes backward for 300 microsecs */
                     delay(300);
                     stops();
                   }
                  /* Light's UP, when recieved the command */
                  }
                  Light_UP();
                  Serial.println("Forward");
                  forward();
                  /* Goes forward for 680 MicroSecs */
                  delay(680);
                  /* Checks Again for Obstacles */
                  if(Offroad == false){
                    long inches;
                  Object_Detection(inches);
                  if(inches < near){
                     backward();
                     delay(300);
                     stops();
                   }
                  }
                  stops();
                  /* And checks again for more accuracry */
                  if(Offroad == false){
                  long inches;
                  Object_Detection(inches);
                  if(inches < near){
                     backward();
                     delay(300);
                     stops();
                   }
                  }
                  /* Reset's the signal (info) */
                  info = 0;
                   }
                  else if(info == '3'){
                    Light_UP();
                    Serial.println("Backward");
                    Buzzer();
                    backward();
                    delay(680);
                    stops();
                    info = 0;
                       }
                  else if(info == '4'){
                    if(Offroad == false){
                    long inches;
                    Object_Detection(inches);
                    if(inches < near){
                       backward();
                       delay(300);
                       stops();
                     }
                    }
                       Light_UP();
                       left();
                       if(Offroad == false){
                        delay(680);
                       }
                       else if(Offroad == true){
                        delay(1200);
                       }
                       
                    if(Offroad == false){   
                      long inches;
                    Object_Detection(inches);
                    if(inches < near){
                       backward();
                       delay(300);
                       stops();
                     }
                    }
                       stops();
                     if(Offroad == false){  
                      long inches;
                     Object_Detection(inches);
                     if(inches < near){
                        backward();
                        delay(300);
                        stops();
                      }
                     }
                        info = 0;   
                  }
                  
                
                  else if(info == '5'){
                    if(Offroad == false){
                    Light_UP();
                    long inches;
                    Object_Detection(inches);
                    if(inches < near){
                       backward();
                       delay(300);
                       stops();
                     }
                    }
                       right();
                       if(Offroad == false){
                        delay(680);
                       }
                       else if(Offroad == true){
                        delay(1200);
                      }
                    if(Offroad == false){
                    long inches;
                    Object_Detection(inches);
                    if(inches < near){
                       backward();
                       delay(300);
                       stops();
                     }
                    }
                    
                     stops();
                     if(Offroad == false){
                     long inches;
                     Object_Detection(inches);
                     if(inches < near){
                        backward();
                        delay(300);
                        stops();
                       }
                     }
                        info = 0;
                      }
                 
          
                  else if(info == '1'){
                    /* Emergency Stop */
                    Light_UP();
                    stops();
                    info = 0;
                    
                  }
                  else if(info == '7'){
                    /* Autonomus Mode - Goes to a dedicated point */
                     Light_UP();
                     Go_To_Point_A();
                      
                  }
                   else if(info == '8'){
                    /* Autonomus Mode - Obstacle Avoider */
                    Light_UP();
                    AutoMode();
                    
                  }
                   else if(info == '9'){
                    /* Autonomus Mode - Follow's an Object */
                    Light_UP();
                    
                    FollowObjectAuto();
                    
                    
                    }
                    else if(info == 'B'){
                      LightsOn();
                    }
                
            }        
      }
    }
    lcd.clear();
    delay(500);
    
    
    }        
          }
  
void loop() {
/* Empty Loop */

}
/* Start of the funcs */

// Forward //
void forward(){
  /* Changed The Volt's to determine the movement of the Motors */ 
  // HIGH - 5V or 3.3V for 3.3V and LOW for 0V //
  // Front Motors //
  digitalWrite(ForwardR, HIGH);
  digitalWrite(ForwardL, LOW);
  digitalWrite(BackwardR, HIGH);
  digitalWrite(BackwardL, LOW);
  // Back Motors //
  digitalWrite(a, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(d, LOW);
}
// Backward //
void backward(){
  digitalWrite(ForwardR, LOW);
  digitalWrite(ForwardL, HIGH);
  digitalWrite(BackwardR, LOW);
  digitalWrite(BackwardL, HIGH); 
  digitalWrite(a, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(d, HIGH);
}
// Left //
void left(){
  digitalWrite(ForwardR, HIGH);
  digitalWrite(ForwardL, LOW);
  digitalWrite(BackwardR, LOW);
  digitalWrite(BackwardL, HIGH); 
  digitalWrite(a, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(d, LOW);
  
}
// Right //
void right(){
  digitalWrite(ForwardR, LOW);
  digitalWrite(ForwardL, HIGH);
  digitalWrite(BackwardR, HIGH);
  digitalWrite(BackwardL, LOW); 
  digitalWrite(a, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(b, LOW);
  digitalWrite(d, HIGH);
}

// Stop //
void stops(){
   digitalWrite(ForwardR, LOW);
  digitalWrite(ForwardL, LOW);
  digitalWrite(BackwardR, LOW);
  digitalWrite(BackwardL, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  
}
void LightsOn(){
  int light = light_sensor.getPercentValue();
  if(light < 45){
    for(int u; u < 3; u++){
    sr.setAllHigh(); // set all pins HIGH
     delay(500);
  
    sr.setAllLow(); // set all pins LOW
     delay(500); 
    }
   sr.setAllHigh();
  }
}

// Obstacle Avoidance Function //
void AutoMode(){
  /* Check's the inches */
  long inches;
  Object_Detection(inches);
  

 
   if(inches > range){
    /* Goes Forward till there is no obstacle */
    forward();
   
    Object_Detection(inches);
    
    }
    /* Found Obstacle, Avoids it */
    if(inches < range){  
      Serial.println(inches);
      backward();
      delay(1555);
      stops();
      /* Tone func, to make sound (piezo) when object averted */
      tone(10, 699, 650);
      delay(150);
      right();
      delay(1000);
      Object_Detection(inches);
    
    
   }
 
     
   }

/* Follow The Object */
void FollowObjectAuto(){
  /* Check's the range of the object */
   long inches;
   Object_Detection(inches);
  if(inches > Follow){
    /* If inches is less then Follow, turn right and left to begin searching for the object */
     for(int m; m < 3; m++){
       /* Turn's right slowly stopping in different angles, to find object */
        right();
        delay(250);
        stops();
        Object_Detection(inches);
       
          if(inches < Follow){
            /* Found Object ? Break the for loop !*/
                break;
          }
        delay(250);
    }
  
      for(int g; g < 6; g++){
       /* Turn's left slowly stopping in different angles, to find object */
        left();
        delay(250);
        stops();
       
        Object_Detection(inches);
     
        if(inches < Follow){
           /* Found Object ? Break the for loop !*/
           break;
        }
        delay(250);
        
   
      }
 }
  /* After, breaking the for, loop check again and go forward till the object is less then the range (Follow) */
  if(inches < Follow){
    
    forward();
    /* Checks again, for obstacle */
    Object_Detection(inches);
    
    
  }
  

}
/* Go's to designated point */
void Go_To_Point_A(){
  

  /* Check's if there is obstacle */
   long inches;
   Object_Detection(inches);
  /* Repeat this for 3 times to get to the designated point */
  for(int v; v < 3; v++){

  if(inches > Point){
    /* If there is no obstacle, keep going forward */
    forward();
    long inches;
    Object_Detection(inches);
    
    }
  if(inches < Point){
    /* If, there is obstacle turn right */
    right();
    delay(680);
    stops();
    long inches;
    Object_Detection(inches);
    
    
    }
  }
  
  
}



/* Simple Code to Blink LED, Uses Voltage to turn "on" and "off" */
void BlinkLED(){
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  delay(350);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  delay(350);
}

/* Used to Light the Front LEDS */
void Light_UP(){
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
}

/* Buzzer, when going backward */
void Buzzer(){
  for(int r = 0; r < 3; r++){
   tone(10, 250, 250);
    
  }
}

void Obstacle_Buzz(){
   tone(10, 699);
}
/* TURN's on the Lower LED */
void NightMode(){
  digitalWrite(LOWER_LED, HIGH);
}

/* From MicroSecs to Inches - To calculate distance from object (ultrasonic) */ 
long microsecondsToInches(long microseconds){
 return microseconds / 74 / 2;
}

/* Object Detection */

void Object_Detection(long &inches){
    /* Long Duration */
    long duration;
    /* This is used to generate a clear signal */
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(TrigPin, LOW);
    
    /* Check's the pulses (HIGH, LOW) */
    duration = pulseIn(EchoPin, HIGH);
    inches = microsecondsToInches(duration);
}
