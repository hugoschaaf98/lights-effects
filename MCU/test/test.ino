void setup() {

  Serial.begin(9600);

}// end setup()

String s = "";

void loop() {

  //wait for data to be available
  if(Serial.available()){

    //read the data
    s = Serial.readString();
    
    //wait for the serial port to be ready to write on
    while(!Serial.availableForWrite());

    //write the string
    Serial.print("Arduino response : ");
    
    switch(s):
      case "how are you ?":
        Serial.println("fine");
      case "who is josselin ?":
        Serial.println("josselin is a has been");

      default :
        Serial.println(s);
        
    Serial.flush();

  }

  

}// end loop()
