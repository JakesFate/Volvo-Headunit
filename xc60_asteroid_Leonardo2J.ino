    

//Lin Initailisation
#define linspeed                9600
unsigned long Tbit = 1000000/linspeed;

#define uartlenght                 10

//Tbits Header
#define breakf                 14
#define longpress              10



int frameerrordelay = ((breakf) - uartlenght)*Tbit;


#define numbers  8
byte message[numbers];
byte sync,PID,checksum;
byte texit, texit_1,  enter, enter_1, navil, navir, naviu, navid, navib1_1, navib1, navib2, volu, vold, next, prev, brightness;
byte navib2_1, prev_1, next_1, navil_1, navir_1, naviu_1, navid_1;
int aeg = 0;
char ctrlKey = KEY_LEFT_GUI;
int klahv = 1;

void setup() {

  UDCON |= (1<<DETACH);
delay(10000);
  UDCON &= ~(1<<DETACH);
  Keyboard.begin();
  Lininit();
}

void loop() {
LinReading();


 
}

void LinReading() {
  LinRead();
  PrintlnLin();
  ClearFrame();
}

void Lininit() {
  Serial1.begin(linspeed);
 
}

void LinRead() {
  if (1<<FE1) {

    delayMicroseconds(frameerrordelay);               //after Frame Error Tbit to Sync Field

 while(!Serial1.available()) { delayMicroseconds(1);}
    if (Serial1.available()) sync= Serial1.read(); 
if (sync == 85) {   
      
 while(!Serial1.available()) { delayMicroseconds(1);}
  if (Serial1.available()) {PID = Serial1.read();}
if (PID == 32) {
  
for (uint8_t i=0;i<4;i++)
    {
      while(!Serial1.available()) { delayMicroseconds(1); } 
      message[i] = Serial1.read();
    }
}

while(!Serial1.available()) { delayMicroseconds(1); }
  if (Serial1.available())
    {
    checksum = Serial1.read();
  
    }
    }
  }
}
//keyboard action definitions - here you define any key
void Apps() { 
 if (klahv == 1) 

{  Keyboard.press(ctrlKey);
  Keyboard.press('f');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
 if (klahv == 2) 

{  Keyboard.press(ctrlKey);
  Keyboard.press('g');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
 
  if (klahv == 3) 

{  Keyboard.press(ctrlKey);
  Keyboard.press('h');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
  if (klahv == 4) 

{  Keyboard.press(ctrlKey);
  Keyboard.press('i');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
enter=0;
klahv = klahv+1;
if (klahv== 5) { klahv = 1; }
}

void Next_1() { Keyboard.write(KEY_F1);  aeg = 0;delay (10);  }//source key
void Menu() { Keyboard.write(KEY_F2); aeg = 0;  delay (10); } // menu button
void Navib2_1(){ Keyboard.write(KEY_F3); aeg = 0; delay (10); }
void Endcall(){Keyboard.write(KEY_F4); aeg = 0; delay (10); } // End call or return to home
void Call() { Keyboard.write(KEY_F5); aeg = 0;  delay (10); } // Call voice command
void Navib1_1(){ Keyboard.write(KEY_F6); aeg = 0; delay (10); }
void Next() { Keyboard.write(KEY_F7); next = 0;  delay (10); }   // next track
void Prev() { Keyboard.write(KEY_F8); prev = 0;  delay (10); }  // prev track
void Prev_1() { Keyboard.write(KEY_F9);  aeg = 0;delay (10);  }//source key
void Exit() { Keyboard.write(KEY_F10);  texit = 0;delay (10);  }//source key
void Navib2() { Keyboard.write(KEY_RETURN); navib2 = 0; delay (10); }  //enter button
void Navib1() { Keyboard.write(KEY_ESC); navib1 = 0; delay (10); }  //enter button
void Navir() { Keyboard.write(KEY_RIGHT_ARROW); navir = 0; delay (10); }
void Navil() { Keyboard.write(KEY_LEFT_ARROW); navil = 0;delay (10);  }
void Naviu() { Keyboard.write(KEY_UP_ARROW); naviu = 0; delay (10); }
void Navid() { Keyboard.write(KEY_DOWN_ARROW); navid = 0; delay (10); }

 
void Navir_1(){  Keyboard.press(ctrlKey);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();; aeg = 0; delay (10); }
void Navil_1(){  Keyboard.press(ctrlKey);
  Keyboard.press('c');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
void Naviu_1(){  Keyboard.press(ctrlKey);
  Keyboard.press('d');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }
void Navid_1(){  Keyboard.press(ctrlKey);
  Keyboard.press('e');
  delay(100);
  Keyboard.releaseAll();; aeg = 0;delay (10);  }


void PrintlnLin() {
  if(sync == 85) {
  if (PID == 32) {
    
if (checksum == 255) //all buttons were released

{ // check if button was released after press then go to action
if (texit == 1){ Exit();}
if (enter == 1){Apps();} 
if (next == 1){Next();}
if (prev == 1){Prev();}
if (navir == 1){Navir();}
if (navil == 1){Navil();}
if (naviu == 1){Naviu();}
if (navid == 1){Navid();}
if (navib1 == 1){Navib1();}
if (navib2 == 1){Navib2();}
aeg=0;
texit_1 = 0;
enter_1 = 0;
navib1_1 = 0;
navib2_1 = 0;
next_1 = 0;
prev_1 = 0;
navir_1 = 0;
navil_1 = 0;
naviu_1 = 0;
navid_1 = 0;
} 


// here we check which message was received  (the bits received) through lin steering wheel bus

//check the front exit button  press
if(checksum == 0xBF) { //exit button
if (texit_1 == 0){texit = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
texit = 0;
texit_1 = 1;// goto long press function
Endcall();
}
}

if(checksum == 223) { //front enter
if (enter_1 == 0){enter = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
enter = 0;
enter_1 = 1;
Call();
}
}
if(message[1]==1) {  //navi left button checking for click or long press
if (navib1_1==0) {navib1 = 1;} //first click and if button will be released exit this loop
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
navib1_1 = 1;
navib1 = 0;
Menu();
// goto long press function
}
}

if(message[1]==8) {
if (navib2_1==0) {navib2 = 1;} //first click and if button will be released exit this loop
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
navib2_1 = 1;
navib2 = 0;
Navib2_1();
// goto long press function
}
}

if(checksum == 239) {   //next track
if (next_1 == 0){next = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
next_1 = 1;
next = 0;
Next_1();
  }
  }
  
if(message[1]==2) { //prev track
if (prev_1 == 0){prev = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
prev_1 = 1;
prev = 0;
Prev_1();
  }
  }

if(message[0]==4) { // navi joystick left
if (navil_1 == 0){navil = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
navil_1 = 1;
navil = 0;
Navil_1();
  }
}
if(message[0]==8) { // navi joystick right
if (navir_1 == 0){navir = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
navir_1 = 1;
navir = 0;
Navir_1();
  }
}

if(message[0]==1) { // navi joystick up
if (naviu_1 == 0){naviu = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
naviu_1 = 1;
naviu = 0;
Naviu_1();
  }
}

if(message[0]==2) { // navi joystick up
if (navid_1 == 0){navid = 1;}
aeg=aeg+1; //count how many times i was here without releasing
if (aeg >= longpress){ //long press because the button was not released  
navid_1 = 1;
navid = 0;
Navid_1();
  }
}

}
}
}

void ClearFrame() {
  sync = 0;
  PID = 0;
  for (int i=0;i<4;i++) {
    message[i] = 0;
  }
  checksum = 0;
}





