//SensorValue == 1 -> undetected
//SensorValue == 0 -> detected

int infrared = 2;
int SensorState = 0;
int RevPoint = 0;
int CalPoint = 1;
int PointPerRev = 1;

unsigned long now;
unsigned long last;

void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  last = millis();
  while(1)
  {
    int SensorValue = digitalRead(infrared);
    
    if(SensorValue == 1 && SensorState == 0)      //waiting
    {
      SensorState = 0;
      delay(5);
    }

    if(SensorValue == 0 && SensorState == 0)      //point enter
    {
      SensorState = 1;
      delay(5);
    }
    
    if(SensorValue == 1 && SensorState == 1)      //point escape
    {
      SensorState = 2;
      delay(5);
    }

    if(SensorState == 2)
    {
      RevPoint = RevPoint + 1;
      SensorState = 0;
      delay(5);
    }

    if(RevPoint == CalPoint*PointPerRev)
    {
      RevPoint = 0;
      break;
    }
  }

  now = millis();

  //=================RPM Calulation Start================
  unsigned long dt = now - last; 
  unsigned long RPM = (CalPoint*60000)/dt;
  if (RPM >= 1000)
  {
    ;
  }
  else
  {
    Serial.print("RPM: ");
    Serial.println(RPM);
  }
  //=================RPM Calulation End==================
}
