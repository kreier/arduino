// https://github.com/miguel5612/MQSensorsLib
//

#include <MQUnifiedsensor.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

//Definitions
#define pin A0 //Analog input 0 of your arduino
#define type 131 //MQ131
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ131(pin, type);

//Variables
float NOx, CL2, O3;

void setup()
{
  Serial.begin(57600);  // start serial to PC
  lcd.begin(16, 2); // initialize LCD with number of columns and rows
  //init the sensor
  /*****************************  MQInicializar****************************************
  Input:  pin, type 
  Output:  
  Remarks: This function create the sensor object.
  ************************************************************************************/ 
  MQ131.inicializar(); 
  //pinMode(calibration_button, INPUT);  
}

void loop()
{
  printTitle();
  delay(20000);
  
  MQ131.update(); // Update data, the arduino will be read the voltaje in the analog pin
  /*
    // Si el valor de RL es diferente a 10K por favor asigna tu valor de RL con el siguiente metodo:
    MQ131.setRL(10);
  */
   /*
  //Rutina de calibracion - Uncomment if you need (setup too and header)
  if(calibration_button)
  {
    float R0 = MQ131.calibrate();
    MQ131.setR0(R0);
  }
  */
  /*****************************  MQReadSensor  ****************************************
  Input:   Gas - Serial print flag
  Output:  Value in PPM
  Remarks: This function use readPPM to read the value in PPM the gas in the air.
  ************************************************************************************/ 
  //Read the sensor and print in serial port
  //Lecture will be saved in lecture variable
  //float lecture =  MQ131.readSensor("", true); // Return O3 concentration
  // Options, uncomment where you need
  NOx =  MQ131.readSensor("NOx"); // Return NOx concentration
  CL2 =  MQ131.readSensor("CL2"); // Return CL2 concentration
  O3 =  MQ131.readSensor("O3"); // Return O3 concentration

  Serial.println("***************************");
  Serial.println("Lectures for MQ-131");
  Serial.print("Volt: ");Serial.print(MQ131.getVoltage(false));Serial.println(" V"); 
  Serial.print("R0: ");Serial.print(MQ131.getR0());Serial.println(" Ohm"); 
  Serial.print("NOx: ");Serial.print(NOx,2);Serial.println(" ppm");
  Serial.print("CL2: ");Serial.print(CL2,2);Serial.println(" ppm");
  Serial.print("O3: ");Serial.print(O3,2);Serial.println(" ppm");
  Serial.println("***************************");  
}

void printTitle()
{
  lcd.setCursor(0,0);
  lcd.print("MQ131 OzonSensor");  
}
