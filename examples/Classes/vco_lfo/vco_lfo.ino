//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
#include <Wire.h> 
////////////////////////////////////


#include <ADDAC.h>

#include <ADDAC_Random.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Lin2Log.h>
#include <ADDAC_Comparator.h>
#include <ADDAC_Euclidean.h>
#include <ADDAC_Ntof.h>
#include <ADDAC_VCO.h>
#include <ADDAC_LFO.h>
#include <ADDAC_Smooth.h>



// INCLUDES THE MAIN ADDAC LIBRARY

// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;
ADDAC_Lin2Log L2G;
ADDAC_Comparator Comp,Comp2,Comp3;
ADDAC_Euclidean Euclides(4);  
ADDAC_Ntof ntof;
ADDAC_LFO LFO1;
ADDAC_Smooth SM;
//ADDAC_VCO vco(0,0,0);


float tri;
float interval = 25;
float inc = 0.01f;

boolean UP=true;
unsigned long time =0;

void setup(){
  // initialize VCO 
  VCO.initialize();         // initialize timer1, and set a 1/2 second period
  VCO.startup(VCO_update);  // attaches callback() as a timer overflow interrupt
  
  VCC.setup();
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}

void VCO_update(){ // DO NOT OVERLOAD THIS FUNCTION!!!
  VCC.WriteChannel(0, UP* VCC.cvValuesA[5]+ ((1- VCC.cvValuesA[5])/2.0f));
  UP=!UP;
}


void loop(){
  VCC.update(); // NEED TO UPDATE THE VCC!
LFO1.SINupdate(false, SM.calc(VCC.ReadManual(A,0)*1000.0f,0.998), 1, 0, 0, 1);
      VCC.ReadCvs(A);
      //VCC.PrintCvs(A);
      
   
      
    
    
      VCO.update(LFO1.CVstream, VCC.ReadManual(A,4));
      //VCO.update(Rnd.CVstream,VCC.cvValuesA[5]);
      //VCO.update(VCC.cvValuesA[0],VCC.cvValuesA[5]);
  
  

    #ifdef DEBUG
      Serial.println();
      delay(60);
    #endif

}





