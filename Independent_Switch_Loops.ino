#include <Cth.h>

long wash_minutes = 60;
long spin_minutes = 15;
long washcycle_seconds = 5;
long washstop_seconds = 2;

long millis_multiplier = 1000;


long wash_millis = wash_minutes*millis_multiplier;
long spin_millis = spin_minutes*millis_multiplier;
long wash_cycle = washcycle_seconds*1000;
long wash_stop = washstop_seconds*1000;

const int wash_pin = 2;
const int spin_pin = 4;

const int forward = 6;
const int reverse = 8;
const int spindry = 10;

int wash_state = 0;
int spin_state = 0;

long wash_start = 0;

long spin_start = 0;

long washcycle_start = 0;

long washstop_start = 0;

bool state = 1;
bool washcycle_state = 0;
bool washstop_state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(wash_pin, INPUT);
  pinMode(spin_pin, INPUT);
  pinMode(forward, OUTPUT);
  pinMode(reverse, OUTPUT);
  pinMode(spindry, OUTPUT);

  Serial.println(wash_millis);
  delay(5000);

}



void loop(){
  if(wash_state == 0 && digitalRead(wash_pin) == HIGH){
    wash_state = 1;
    washcycle_state = 1;
    washstop_state = 0;
    
    wash_start = millis();
    washcycle_start = millis();
    
    
  }
  if(wash_state == 1  && washcycle_state ==1 && washstop_state == 0 && millis() - wash_start <= wash_millis && millis()- washcycle_start <= wash_cycle){
    Serial.println("Washing");
    Serial.println(millis()-wash_start <= wash_millis);
    digitalWrite(forward, state);
    digitalWrite(reverse, !state);
  }
  
  if(wash_state == 1  && washcycle_state ==1 && washstop_state == 0 && millis() - wash_start <= wash_millis && millis()- washcycle_start > wash_cycle){
    Serial.println("Start of Stop");
     Serial.println(millis()-wash_start <= wash_millis);
    washstop_state = 1;
    washcycle_state = 0;
    washstop_start = millis();
  }

  if(wash_state == 1  && washcycle_state == 0 && washstop_state == 1 && millis() - wash_start <= wash_millis && millis()- washstop_start <= wash_stop){
    Serial.println("OFF");
     Serial.println(millis()-wash_start <= wash_millis);
    digitalWrite(forward, LOW);
    digitalWrite(reverse, LOW);
  }

  if (wash_state == 1  && washcycle_state == 0 && washstop_state == 1 && millis() - wash_start <= wash_millis && millis()- washstop_start > wash_stop){
    Serial.println("Reverse");
     Serial.println(millis()-wash_start <= wash_millis);
    washstop_state = 0;
    washcycle_state = 1;
    state = !state;
    washcycle_start = millis();
  }
  
  if(wash_state == 1 && millis() - wash_start > wash_millis){
    Serial.println("Stop wash");
     Serial.println(millis()-wash_start <= wash_millis);
    wash_state = 0;
    washcycle_state = 0;
    digitalWrite(forward, LOW);
    digitalWrite(reverse, LOW);
  }

  if(spin_state == 0 && digitalRead(spin_pin) == HIGH){
    spin_state = 1;
    spin_start = millis();
  }

  if(spin_state == 1 && millis() - spin_start <= spin_millis){
    digitalWrite(spindry, HIGH);
  }

  if(spin_state == 1 && millis() - spin_start > spin_millis){
    spin_state = 0;
    digitalWrite(spindry, LOW);
  }
  
}
