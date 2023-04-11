// SM {starting percentage, minimum angle, maximum angle, default speed}
// Motion first movement:number of motors:{move to percent, speed}   Second movement:Number of motors: {move to percent, speed}

#include<Servo.h>

#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))
#define toP(current,minimum,range) ((current-minimum)*100/(range))
#define toA(percent,minimum,range) (minimum+percent*(range)/100)

Servo S0; //Servo10
Servo S1; //Servo9
Servo S2; //Servo8
Servo S3; //Elbow (Servo7)

const int NumOfMotors = 4;         // Number of motors
const int NumOfParam = 4;          // Number of Parameters in Motor Definition
const int MotionMovements = 4;     // Number of Movements in motion Move
const int NumbMotions = 2;         // number of Motions in project

// Defined movements
int Move [NumbMotions][MotionMovements][NumOfMotors][2]={{{{0,5},{25,1},{0,5},{0,1}},{{0,5},{25,1},{0,5},{0,1}},{{0,5},{25,1},{0,5},{0,1}},{{0,5},{25,1},{0,5},{0,1}}},
                                               {{{20,5},{10,1},{010,5},{10,1}},{{2,5},{50,1},{50,5},{10,1}},{{35,5},{0,1},{25,5},{10,1}},{{20,5},{20,1},{10,5},{10,1}}}};

// Servo Motor Definitions   {starting angle, minimum angle, maximum angle, minimum delay increment in STP}
int SM[NumOfMotors][NumOfParam]={{120,120,70,10},{80,80,120,10},{30,30,180,10},{120,30,122,10}}; //0,25,0,0 //Base Position (120,80,30,122);

int R[NumOfMotors]={0,0,0,0};     //   Current countdown time
int C[NumOfMotors]={0,0,0,0};     //   Current percentage
int T[NumOfMotors]={0,0,0,0};     //   Target percentage
int S[NumOfMotors]={0,0,0,0};     //   angle range for motor
bool N[NumOfMotors]={false,false,false,false};     //   need to move motor (1=move, 0 = not move}


unsigned long LST;                // LaST Loop Time  (in ms)
const unsigned long DELAY=100;     // Time STeP (in ms)

void SetupMotors(void){
  for (int i=0;i<4;i++){
    S[i]=SM[i][2]-SM[i][1];    
    R[i]=SM[i][3];
    C[i]=toP(SM[i][0],SM[i][1],S[i]);
    T[i]=C[i];
  }
  S0.write(toA(C[0],SM[0][1],S[0]));
  S1.write(toA(C[1],SM[1][1],S[1]));
  S2.write(toA(C[2],SM[2][1],S[2]));
  S3.write(toA(C[3],SM[3][1],S[3]));
}

void MoveMotor(int Motor){
  if (R[Motor] == 0){
    int currAngle = toA(C[Motor],SM[Motor][1],S[Motor]);
    int targetAngle = toA(T[Motor],SM[Motor][1],S[Motor]);
    currAngle = currAngle + 1*sgn(targetAngle - currAngle);
    C[Motor]=toP(currAngle,SM[Motor][1],S[Motor]);//C[Motor]+1*sgn(T[Motor]-C[Motor]);
    switch(Motor){
      case 0:
        S0.write(currAngle);
        break;
      case 1:
        S1.write(currAngle);
        break;
      case 2:
        S2.write(currAngle);
        break;
      case 3:
        S3.write(currAngle);
        break;
      }
  }  
    else R[Motor]--; 
    if (C[Motor] == T[Motor]) N[Motor]=false;
    else N[Motor]=true;
  }
     
void setup() {
  S0.attach(10);
  S1.attach(9);
  S2.attach(8);
  S3.attach(7);
  SetupMotors();
  LST=millis();
  Serial.begin(9600);
  Serial.println("Hello");
  S0.write(toA(C[0],SM[0][1],S[0]));
  S1.write(toA(C[1],SM[1][1],S[1]));
  S2.write(toA(C[2],SM[2][1],S[2]));
  S3.write(toA(C[3],SM[3][1],S[3]));
  
  //T[1]=toA(Move[0][0][1][0],SM[1][1],S[1]);
  //N[1]=true;
}

int kk = 0;



void loop() {
  if (millis()>=LST){
    LST += DELAY;     
  }
}
