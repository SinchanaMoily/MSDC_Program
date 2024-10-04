#define relay 5
   void setup(){
   pinMode(relay,OUTPUT);
   Serial.begin(9600);
   }
   void loop(){
   digitalWrite(relay,HIGH);
   Serial.println("BULB IS ON");
   delay(1000);
   digitalWrite(relay,LOW);
   Serial.println("BULB IS OFF");
   delay(1000);
   }
