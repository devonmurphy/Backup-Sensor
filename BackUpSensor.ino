// Back Up Sensor by Devon Murphy
int readPin1 = 2; //These ping sensors need a read and trigger pin
int trigPin1 = 3;
int readPin2 = 4;
int trigPin2 = 5;
int pwmPin   = 6;
int ledpin   = 7;


int maxDist=60,minDist=2;
long scale = 1500/60; //Set so at 60 cm away the sound will pulse every 1.5 secs
long duration = 60;

int hold=0,hold1=0,hold2=0;
int trip=0,lasttrip;

void setup(){
}
void loop(){

  
  hold1=ping(trigPin1,readPin1); //Read the two sensors
  hold2=ping(trigPin2,readPin2);
  
  if(hold1<=hold2){ 
    //There are two sensors, but the one with the shortest distance is the most important
    hold=hold1;
  }
  else{
    hold=hold2; 
  }
 
  
  if(hold<=maxDist && hold>minDist){ //It starts to beep when the car is minDist away
    trip=1;
    
    digitalWrite(ledpin, HIGH);
    delay(50);
    digitalWrite(ledpin, LOW); 
    
    //The delay time increases as the distance increases
    delay(hold*scale); 
   
    

    tone(pwmPin,440,duration);//Make 60 ms long 440 Hz tone on a speaker
    
    if(lasttrip!=trip){
   //This executes once right after its tripped
   //Nothing utilizing this code works area yet
  }
  }
  
  else{
    trip=0;
    //The speaker shouldn't make noise when it isn't close to an object
    noTone(pwmPin); 
    digitalWrite(ledpin, LOW);
  }

  lasttrip=trip;
}
int ping(int tpin, int rpin){
  long duration, inches, cm;
  
  pinMode(tpin, OUTPUT); //Set the trigger pin to output
  digitalWrite(tpin, LOW); //Set the pin low and wait to clear noise
  delayMicroseconds(2);
  digitalWrite(tpin, HIGH); //Set the pin high for 10 ms
  delayMicroseconds(10);
  digitalWrite(tpin, LOW); //After the trigger pin has been high for 10 ms the pulse will be sent
  
  pinMode(rpin,INPUT); //Set the read pin to input
  duration = pulseIn(rpin,HIGH);  //The length of the wave is proportional to the distance
  cm = duration/58;//Micropik supplies us with this formula to calculate the range
  return cm;
}


