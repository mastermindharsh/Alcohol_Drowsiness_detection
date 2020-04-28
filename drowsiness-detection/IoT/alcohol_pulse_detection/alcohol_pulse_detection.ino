#include <LiquidCrystal_I2C.h>

int Val,set1,set2,hb,cnt,strt,hb1;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  Serial.begin(9600);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(2,LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("ALCOHOL");
  lcd.setCursor(4,1);
  lcd.print("DETECTION");
  delay(2000);
  lcd.clear();

}
void loop()
{
  
  Val = analogRead(A0);
 
  hb = analogRead(A1);
  if((hb < 200)&&(set2 == 0))
  {
  strt = strt+1;
  if(strt < 30)
  {
  if(hb <= 20)
  {
   cnt = cnt + 1; 
  }
  }
  if(strt == 30)
  {
   hb1 = cnt+40;
   cnt=0;
   strt=0;
   set2=1; 
  }
  }

  if(((hb > 200)&&(hb < 300))&&(set2 == 0))
  {
   hb1=0; 
  }

  if(((hb > 200)&&(hb < 300))&&(set2 == 1))
  {
   set2=0; 
  }
  

  
  lcd.setCursor(0,0);
  lcd.print("ALC:");
  lcd.print(Val);
  lcd.print(" ");
  lcd.setCursor(8,0);
  lcd.print("HB:");
  lcd.print(hb1);
  lcd.print(" ");
  
  
  if((Val > 500)||(hb1 > 60))
  {
   digitalWrite(2,LOW);
   digitalWrite(3,HIGH);
   delay(2000);
   digitalWrite(3,LOW); 
  }
  else if(((Val < 650)&&(hb1 < 75))&&(set1 == 0))
  {
   digitalWrite(2,HIGH); 
  }

  delay(100);
}
void serialEvent() 
{
  while (Serial.available() > 0) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.println(inChar);
    if(inChar == '1')
    {
     digitalWrite(2,LOW);
     digitalWrite(3,HIGH);
     delay(2000);
     digitalWrite(3,LOW); 
     set1=1;  
    }
    else if(inChar == '0')
    {
     set1=0; 
    }
  }
}
