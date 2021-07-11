void setup()				//initiating setup function (only one time execute)
 {
  pinMode(A5,INPUT);			//To read sensor MQ135
  pinMode(2,OUTPUT);			//To give signal
}

void loop() 
{
  int analogin=analogRead(A5);		//Reading analog values from sensor MQ135
  int i=1,maximum_range,minimum_range;
  maximum_range=minimum_range=analogin;

  while(i<=3000)                       			//5 min Setting Air Maximum And Minimum Ranges
  {
    if(maximum_range<analogin)
      maximum_range=analogin;
   if(minimum_range>analogin)
      minimum_range=analogin;
   delay(100);
   analogin=analogRead(A5);
   i++;
  }

  int values=maximum_range*0.07;            	//+or- 7% of varying values 
/* Assume minimum_range is 300 and maximum_range is 350. 
   If there is different in analogin value like 
  300-24.5(7%)=~275 below indicates signal POOR 
  350+24.5(7%)=~375 above indicates signal POOR */
 
  int m=0,h=0,j=0;
  
while(h<8)              				//8 hours delay
  {m=0;
  while(m<55)            			//55 minute delay
    {j=0;
      while(j<299)     				//59.7 sec delay
        {
        analogin=analogRead(A5);
        if((analogin)<(minimum_range-values) || analogin>(maximum_range+values))   
					//Poor Quality Air Detected
          {
          digitalWrite(2,HIGH);delay(100);
          digitalWrite(2,LOW);delay(100);
          }
          else 				//Do nothing
            {delay(200);}
          j++;           
        }
      m++;
      }
    h++;
    }					//Every 8 hous loop ends and to initiate new values of minimum and maximum Saturated range
}					//enter again loop function 
