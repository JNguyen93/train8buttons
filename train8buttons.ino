#include <Bounce2.h>

int redPin0 = 22;
int greenPin0 = 23;
int bluePin0 = 24;
int counter0 = 0;
int button0 = 2;
int led0[3] = {redPin0, greenPin0, bluePin0};
int ans0 = 0;
bool sol0 = false;

int redPin1 = 25;
int greenPin1 = 26;
int bluePin1 = 27;
int counter1 = 0;
int button1 = 3;
int led1[3] = {redPin1, greenPin1, bluePin1};
int ans1 = 5;
bool sol1 = false;

int redPin2 = 28;
int greenPin2 = 29;
int bluePin2 = 30;
int counter2 = 0;
int button2 = 4;
int led2[3] = {redPin2, greenPin2, bluePin2};
int ans2 = 3;
bool sol2 = false;

int redPin3 = 31;
int greenPin3 = 32;
int bluePin3 = 33;
int counter3 = 0;
int button3 = 5;
int led3[3] = {redPin3, greenPin3, bluePin3};
int ans3 = 1;
bool sol3 = false;

int redPin4 = 34;
int greenPin4 = 35;
int bluePin4 = 36;
int counter4 = 0;
int button4 = 6;
int led4[3] = {redPin4, greenPin4, bluePin4};
int ans4 = 2;
bool sol4 = false;

int redPin5 = 37;
int greenPin5 = 38;
int bluePin5 = 39;
int counter5 = 0;
int button5 = 7;
int led5[3] = {redPin5, greenPin5, bluePin5};
int ans5 = 0;
bool sol5 = false;

int redPin6 = 40;
int greenPin6 = 41;
int bluePin6 = 42;
int counter6 = 0;
int button6 = 8;
int led6[3] = {redPin6, greenPin6, bluePin6};
int ans6 = 4;
bool sol6 = false;

int redPin7 = 43;
int greenPin7 = 44;
int bluePin7 = 45;
int counter7 = 0;
int button7 = 9;
int led7[3] = {redPin7, greenPin7, bluePin7};
int ans7 = 5;
bool sol7 = false;

int counters[8] = {counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7};
int solFlags[8] = {sol0, sol1, sol2, sol3, sol4, sol5, sol6, sol7};
int answers[8] = {ans0, ans1, ans2, ans3, ans4, ans5, ans6, ans7};
int buttons[8] = {button0, button1, button2, button3, button4, button5, button6, button7};
int* leds[8] = {led0, led1, led2, led3, led4, led5, led6, led7};

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

int off[3] = {0, 0, 0};
int red[3] = {255, 0 , 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int yellow[3] = {255, 255, 0};
int purple[3] = {255, 0, 255};
int aqua[3] = {0, 255, 255};
int test[3] = {255, 255, 255};
int* colors[6] = {red, green, blue, yellow, purple, aqua};
int colLen = arr_len(colors) - 1;

Bounce butt0 = Bounce();
Bounce butt1 = Bounce();
Bounce butt2 = Bounce();
Bounce butt3 = Bounce();
Bounce butt4 = Bounce();
Bounce butt5 = Bounce();
Bounce butt6 = Bounce();
Bounce butt7 = Bounce();

Bounce butts[8] = {butt0, butt1, butt2, butt3, butt4, butt5, butt6, butt7};

int maglock = 12;
bool locked = false;
void setup(){
  Serial.begin(9600);
  Serial.println("Colors");
  pinMode(maglock, OUTPUT);
  for(int i = 0; i < 8; i++){
    pinMode(leds[i][0], OUTPUT);
    pinMode(leds[i][1], OUTPUT);
    pinMode(leds[i][2], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
    butts[i].attach(buttons[i]);
    butts[i].interval(50);
    setColor(leds[i], red);
    if(counters[i] == answers[i]){
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" is true");
      solFlags[i] = true;
    }
    else{
      solFlags[i] = false;
    }
  }
}

void loop(){
  for(int i = 0; i < 8; i++){
    butts[i].update();
    if(butts[i].fell()){
      counters[i]++;
      Serial.println(counters[i]);
      setColor(leds[i], colors[counters[i]]);
      if(counters[i] == answers[i]){
        Serial.print("Button ");
        Serial.print(i);
        Serial.println(" is true");
        solFlags[i] = true;
      }
      else{
        solFlags[i] = false;
      }
      if(counters[i] == colLen){
        counters[i] = -1;
      }
    }
  }
  locked = false;
  for(int k = 0; k < 8; k++){
    //Serial.print("
    if(!solFlags[k]){
      //Serial.println("Locked!");
      locked = true;
    }
  }
  if(!locked){
    digitalWrite(maglock, LOW);
  }
  else{
    digitalWrite(maglock, HIGH);
  }
}

void setColor(int* led, int* color){
  #ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  #endif
  Serial.print("Red: ");
  Serial.print(color[0]);
  Serial.print(" Green: ");
  Serial.print(color[1]);
  Serial.print(" Blue: ");
  Serial.println(color[2]);
  analogWrite(led[0], color[0]);
  analogWrite(led[1], color[1]);
  analogWrite(led[2], color[2]);
}

