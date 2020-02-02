const int echo=7;
const int trigger=9;
const int red=4;
const int yellow=2;
const int green=5;
const int enable=12;
const int motorone=10;
const int motortwo=11;
const int tempsensor=A0;
const int dryrunindicator=A5;
String drydisplaydata;
float drydata;
int counter=0;
float sensorinput;
float displaysensor;
float overrange;
float tankoverrange;
long inputdata;
float dutycycle;
float motorpwm;
float data;
float tank;
long sleep_count;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(echo,OUTPUT);
  pinMode(trigger,INPUT);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(motorone,OUTPUT);
  pinMode(motortwo,OUTPUT);
  pinMode(tempsensor,INPUT);
  pinMode(dryrunindicator,OUTPUT);

}

void loop() {
  digitalWrite(echo,LOW);
  delayMicroseconds(2);
  digitalWrite(echo,HIGH);
  delayMicroseconds(10);
  digitalWrite(echo,LOW);
  inputdata=pulseIn(trigger,HIGH);
  data=inputdata*0.034/2;
  sensorinput=analogRead(tempsensor);
  
  displaysensor=((5*sensorinput)*100/1023);
  tank=400-data;
  tankoverrange=tank;
  dutycycle=tank*0.64;
  motorpwm=255.-dutycycle;
  overrange=motorpwm;
  if(overrange<0. || overrange>255.){
    motorpwm=0;
    }
  if(tankoverrange<0){
    tank=0;
    }else if(tankoverrange>400){
      tank=400;
      }
  if((tank>200) && (tank<395)){
    digitalWrite(yellow,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(red,LOW);
    digitalWrite(enable,HIGH);
    analogWrite(motorone,motorpwm);
    digitalWrite(motortwo,LOW);
    stopmotor();
    }else if(tank<200){
      digitalWrite(green,HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(red,LOW);
      digitalWrite(enable,HIGH);
      analogWrite(motorone,motorpwm);
      digitalWrite(motortwo,LOW);
      stopmotor();
      
      }else if(tank>395){
        digitalWrite(green,LOW);
        digitalWrite(yellow,LOW);
        digitalWrite(red,HIGH);
        digitalWrite(enable,HIGH);
        analogWrite(motorone,0);
        digitalWrite(motortwo,LOW);
        sleep();
        }
  Serial.print(motorpwm);
  Serial.print(',');
  Serial.print(tank);
  Serial.print(',');
  Serial.print(displaysensor);
  Serial.print(',');
  Serial.println(drydisplaydata);
  counter++;
  
  delay(1000);

}
void sleep(){
  sleep_count=0;
  while(sleep_count!=20){
    sleep_count++;
    }
  
  }
void stopmotor(){
  if(counter==0){
    drydata=data;
    }
  
  if(counter>=12){
    counter=0;
    if((drydata-2.00)<=data  && (drydata+2)>=data){
      drydisplaydata="0";
      digitalWrite(dryrunindicator,HIGH);
      delay(500);
      digitalWrite(dryrunindicator,LOW);
      delay(500);
      digitalWrite(dryrunindicator,HIGH);
      delay(500);
      digitalWrite(dryrunindicator,LOW);
      delay(500);
      digitalWrite(dryrunindicator,HIGH);
      delay(6000);
      digitalWrite(dryrunindicator,LOW);
      }else{
        drydisplaydata="1";
        }
        drydata=data;
    }
  
  
  
  }
