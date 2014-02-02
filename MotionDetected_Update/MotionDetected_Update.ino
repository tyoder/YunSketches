// Uses a PIR sensor to detect movement, then updates a 'Motion' Property at Evrythng
// PIR code based upon: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/

#include <Bridge.h>

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

String result = "";

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Bridge.begin();
  
}

void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(150);

    
    if (pirState == LOW) {
      // we have just turned on
      Console.println("Motion detected!");
      // We only want to print on the output change, not state
      updateProperty();
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
      delay(300);    
      if (pirState == HIGH){
      // we have just turned off
      Console.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

void updateProperty(){
   // Launch "curl" command and UPDATE a Thng Property at Evrythng
  Process p;
  p.begin("curl");
  //p.addParameter("-i");   Adding -i includes the response headers
  p.addParameter("-H");
  p.addParameter("Accept: application/json");
  p.addParameter("-H");
  p.addParameter("Content-type: application/json");
  p.addParameter("-H");
  p.addParameter("Authorization: YOUR API KEY HERE");
  p.addParameter("--request");
  p.addParameter("PUT");
  p.addParameter("--url");
  p.addParameter("http://api.evrythng.com/thngs/52e24fafe4b0418f6a410073/properties/motion");
  p.addParameter("-d");
  p.addParameter("[{ \"value\": \"1\" }]");
  p.run();   // Run the process and wait for its termination
  
  
   while(p.running()){
     Console.println("Sending update...");
   }
   
   // A process output can be read with the stream methods
  while (p.available()>0) {
    char c = p.read();
    result = result + c;
  }
  Console.print("Update successful. Response: ");
  Console.println(result);
  
  int mylen = result.length();
  Console.print("Response length: ");
  Console.println(mylen);
  
}
