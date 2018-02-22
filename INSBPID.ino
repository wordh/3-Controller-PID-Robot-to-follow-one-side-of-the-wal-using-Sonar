#define left_front 5
#define left_back 6
#define right_front 10
#define right_back 11

#define trigPin1 4
#define echoPin1 7


long duration1, distance1;

int speedL = 0; 
int speedR = 0;

int speedmax = 200;

int preverror = 0;
int error = 0;
int derror = 0;
int ierror = 0;

int Kp = 0.5;
int Kd = 20;
int Ki = 0.75;

int pd;




void setup()
{
  pinMode(left_front, OUTPUT);
  pinMode(right_front, OUTPUT);
  pinMode(right_back, OUTPUT);
  pinMode(left_back, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  Serial.begin(9600);
}



void loop()
{
  Side();
    
  error = distance1 - 2;
  
  derror = error-preverror;
  ierror+=error;
   
  preverror=error;
  
  pd=Kp*error+Kd*derror+Ki*ierror;  


  if ( pd > 0 ) 
  {
    speedR -= pd;
    speedL = speedmax;
  }
    
    
  else if ( pd < 0 ) 
  {
    speedL += pd;
    speedR = speedmax;
  }
    
  
  if ( speedR < 1 )   speedR=0;
  if ( speedL < 1 )   speedL=0;
  
  //if ( speedR > speedmax )   speedR=speedmax;
  //if ( speedL > speedmax )   speedL=speedmax;
    
    
  analogWrite(left_front, speedL);
  analogWrite(left_back, 0);
  analogWrite(right_front, speedR);
  analogWrite(right_back, 0);
    

  Serial.print(error);
  Serial.print("           ");
  Serial.print(speedL);
  Serial.print(" ");
  Serial.println(speedR); 
}



void Side()
{
  digitalWrite(trigPin1, LOW);  // Added this line
  delay(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delay(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
}

