#include <Console.h>
#include <Process.h>

String result = "";

void setup() {
  // Initialize Bridge
  Bridge.begin();
  Console.begin();
  
  while (!Console){
    ;  // wait
  }
  Console.println("Console connected.");

  runCurl();
}

void loop() {
}

void runCurl() {
   
  // Launch "curl" command and get a Thng from Evrythng
  Process p;
  p.begin("curl");
  //p.addParameter("-i");   Adding -i includes the response headers
  p.addParameter("-H");
  p.addParameter("Accept: application/json");
  p.addParameter("-H");
  p.addParameter("Authorization: EvrythngAPIKey");
  p.addParameter("--request");
  p.addParameter("GET");
  p.addParameter("--url");
  p.addParameter("http://api.evrythng.com/thngs/523ed9f9e4b065f4854d06fe");
  p.run();   // Run the process and wait for its termination
  
  
  while(p.running());  //wait
  
  // A process output can be read with the stream methods
  while (p.available()>0) {
    char c = p.read();
    result = result + c;
  }
  
  Console.println(result);
  
  // Ensure the last bit of data is sent.
  Console.flush();

}
