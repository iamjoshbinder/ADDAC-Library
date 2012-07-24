//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include Physics class
#include <ADDAC_Physics.h>
//iclude Comparators class
#include <ADDAC_Comparator.h>


//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Physics physics1;
ADDAC_Comparator comp1;

// DEBUGGING CONSOLE
#define DEBUG 

void setup()
{
  VCC.setup();

#ifdef DEBUG
  Serial.begin(115200);
#endif

}

void loop(){
  VCC.update();



  if(VCC.MODE==0){



    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){

      //create a marble physic and stream the x_position to channel "0" and y_position to channel 1.
      physics1.update(VCC.ReadCv(A,0),VCC.ReadCv(A,1),VCC.ReadCv(A,5),VCC.ReadCv(A,3));//float _gx, float _gy, float _material, float _speed
      VCC.WriteChannel(0, physics1.x);
      VCC.WriteChannel(1, physics1.y);

      //create a comparator to trigger the bumper
      boolean bumpTrigger= comp1.Comparator(VCC.ReadManual(A,0),0.5);  

      if(bumpTrigger){

        // bump the marble ball
        physics1.bump(500);

      }

    }

  }


#ifdef DEBUG
  Serial.print("x: ");
  Serial.print(physics1.x);
  Serial.print(" | y: ");
  Serial.print(physics1.y);
  Serial.println();
  delay(10);
#endif

}



















