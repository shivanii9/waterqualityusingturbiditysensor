#define SENSOR  A0  //Arduino analog pin

float voltage,turbidity;

void setup()
{
  Serial.begin(9600);
  pinMode(SENSOR,INPUT); //Read sensor value
}

void loop()
{
  voltage=0.004888*analogRead(SENSOR);  //Voltage in V
  turbidity=(-1120.4*voltage*voltage+5742.3*voltage-4352.9)/1000;  //Turbidity in NTU
  if((voltage>=2.5)&(turbidity>=0))
  {
    Serial.println("Voltage="+String(voltage)+" V Turbidity="+String(turbidity)+" NTU");  
    delay(500);

    if(turbidity<6.0 && turbidity>0)
    {
      Serial.println("Water portable");
    }
    else{
      Serial.println("Water Not portable");
    }
  }
}