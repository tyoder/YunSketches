#include <aJSON.h>
#include <Console.h>
#include <Process.h>

char* parseJson(char *jsonString) ;
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
  //runCurl();
  //delay(10000);
}

void runCurl() {
   
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
  
  
  //while(p.running());  //wait
  
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
  
  // Turn into character array to use ajson
  char* cstring = new char[result.length() + 1];
  strcpy(cstring, result.c_str());
  //Console.println(cstring[0]);
  //Console.println(cstring);
  
  // call local function to parse the json response
  char* response = parseJson(cstring);

    if (response) {
        Console.print(F("Successfully parsed Json response. Motion value is: "));
        Console.println(response);
    } else {
        Console.print(F("There was some problem in parsing the JSON"));
    }
  
    
  // Ensure the last bit of data is sent.
  Console.flush();

}

/**
 * Parse the JSON String. Uses aJson library
 * 
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
char* parseJson(char *jsonString) 
{
    char* value;
    // Get the root object, which here is an array of json objects
    aJsonObject* root = aJson.parse(jsonString);

    if (root != NULL) {
      // Got array
      //Console.println("Got array");
      aJsonObject* firstItem = aJson.getArrayItem(root, 0);
      if (firstItem != NULL){
        //Console.println("Got first item"); 
        aJsonObject* pinValue = aJson.getObjectItem(firstItem, "value");
        if (pinValue != NULL){
          //Console.println("Got pin value");
          value = pinValue->valuestring; 
        }
      }
    }

    if (value) {
        return value;
    } else {
        return NULL;
    }
}
