
/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************
Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com

License: Attribution-NonCommercial-ShareAlike 3.0 Unsupported (CC BY-NC-SA 3.0)

Note:    This piece of source code is supposed to be used as a demonstration ONLY. More
         sophisticated calibration is required for industrial field application.

                                                    Sandbox Electronics    2012-05-31
************************************************************************************/

/************************Hardware Related Macros************************************/
#define MG_PIN A0 //define which analog input channel you are going to use
#define DC_GAIN 8.5 //define the DC gain of amplifier

/***********************Software Related Macros************************************/
#define READ_SAMPLE_INTERVAL 50 //define how many samples you are going to take in normal operation
#define READ_SAMPLE_TIMES 5 //define the time interval(in milisecond) between each samples in
                                                     //normal operation

#define DEBUG false //print more structured serial monitor output
   

/**********************Application Related Macros**********************************/
//These two values differ from sensor to sensor. user should determine this value.
#define ZERO_POINT_VOLTAGE 2.20/DC_GAIN //Numerator is the o utput of the sensor in volts when the concentration of CO2 is 400PPM (atmospheric concentration)
#define REACTION_VOLTGAE 0.030 //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

/*****************************Globals***********************************************/
float CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};
                                                     //two points are taken from the curve.
                                                     //with these two points, a line is formed which is
                                                     //"approximately equivalent" to the original curve.
                                                     //data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280)
                                                     //slope = ( reaction voltage ) / (log400 –log1000)

void setup()
{
    Serial.begin(9600); //Default baudrate 9600
}

void loop()
{
    float volts = MGRead(MG_PIN);
    if (DEBUG == true){
      Serial.print( "SEN0159:" );
      Serial.print(volts);
      Serial.print( "V           " );
      Serial.print("CO2:");
    }
    
    int percentage = MGGetPercentage(volts,CO2Curve);
    if(percentage == -1 && DEBUG == true){
      Serial.print( "<400" );
    }else{
      Serial.print(percentage);
    }
   
    if(DEBUG == true){
    Serial.print( "ppm" );
    }
    Serial.print("\n");

    delay(500);
}

/*****************************  MGRead *********************************************
Input:   mg_pin - analog channel
Output:  output of SEN-000007
Remarks: This function reads the output of SEN-000007
************************************************************************************/
float MGRead(int mg_pin)
{
    int i;
    float v=0;

    for (i=0;i<READ_SAMPLE_TIMES;i++) {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v = (v/READ_SAMPLE_TIMES) *5/1024 ;
    return v;
}

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.
************************************************************************************/
int  MGGetPercentage(float volts, float *pcurve)
{
   if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {
      return -1;
   } else {
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);
   }
}
