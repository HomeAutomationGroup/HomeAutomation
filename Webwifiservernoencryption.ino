/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.
 using a Duo WiFi shield.


 */

/*
 * SYSTEM_MODE:
 *     - AUTOMATIC: Automatically try to connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     - SEMI_AUTOMATIC: Manually connect to Wi-Fi and the Particle Cloud, but automatically handle the cloud messages.
 *     - MANUAL: Manually connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     
 * SYSTEM_MODE(AUTOMATIC) does not need to be called, because it is the default state. 
 * However the user can invoke this method to make the mode explicit.
 * Learn more about system modes: https://docs.particle.io/reference/firmware/photon/#system-modes .
 */
#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_AUTOMATIC); 
#endif

// your network name also called SSID
char ssid[] = "DDmini";
int keyIndex = 0;

TCPServer server(27014);

int GREEN_LED = D2;
int RED_LED = D0;
int BLUE_LED = D1;
int WHITE_LED = D5;
int YELLOW_LED = D7;

long randOn = 0;    //initialize a variable for the ON time
long randOff = 0;   //initialize a variable for the OFF time
     
void printWifiStatus();

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(RED_LED, OUTPUT);       // set the RED LED pin mode
  pinMode(BLUE_LED, OUTPUT);      // set the BLUE LED pin mode
  pinMode(GREEN_LED, OUTPUT);    // set the GREEN LED pin mode
  pinMode(WHITE_LED, OUTPUT);    // set the WHITE LED pin mode
  pinMode(YELLOW_LED, OUTPUT);    // set the YELLOW LED pin mode

  randomSeed(analogRead(0));    //randomize
  
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.on();
  WiFi.setCredentials(ssid);
  WiFi.connect();
  
  while (WiFi.connecting()) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  IPAddress localIP = WiFi.localIP();
  while (localIP[0] == 0) {
    localIP = WiFi.localIP();
    Serial.println("waiting for an IP address");
    delay(1000);
  }

  // you're connected now, so print out the status  
  printWifiStatus();
  
  Serial.println("Starting webserver on port 27014");
  server.begin();                           // start the web server on port 27014
  Serial.println("Webserver started!");
}

void randomToggle(){

    randOn = random(100, 1200);      //generate On time between 0.1 to 1.2 seconds
    randOff = random(200, 900);      //generate Off time between 0.2 to 0.9 seconds

    digitalWrite(RED_LED, HIGH);     //sets the led On
    delay(randOn);                   //waits for a random time while On
    digitalWrite(RED_LED, LOW);      //sets the led Off
    delay(randOff);                  //waits for a random time while Off
    
    digitalWrite(GREEN_LED, HIGH);     //sets the led On
    delay(randOn);                   //waits for a random time while On
    digitalWrite(GREEN_LED, LOW);      //sets the led Off
    delay(randOff);                  //waits for a random time while Off
    
    digitalWrite(BLUE_LED, HIGH);     //sets the led On
    delay(randOn);                   //waits for a random time while On
    digitalWrite(BLUE_LED, LOW);      //sets the led Off
    delay(randOff);                  //waits for a random time while Off
    
    digitalWrite(WHITE_LED, HIGH);     //sets the led On
    delay(randOn);                   //waits for a random time while On
    digitalWrite(WHITE_LED, LOW);      //sets the led Off
    delay(randOff);                  //waits for a random time while Off
    
    digitalWrite(YELLOW_LED, HIGH);     //sets the led On
    delay(randOn);                   //waits for a random time while On
    digitalWrite(YELLOW_LED, LOW);      //sets the led Off
    delay(randOff);                  //waits for a random time while Off
}

void loop() {
  
  // listen for incoming clients
  TCPClient client = server.available();
  
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        switch(c){
          case 'R': 
              digitalWrite(RED_LED,HIGH);
              Serial.println();
              break;

           case 'G':
              digitalWrite(GREEN_LED,HIGH);
              Serial.println();
              break;

          case 'B':
              digitalWrite(BLUE_LED,HIGH);
              Serial.println();
              break;

          case 'W':
              digitalWrite(WHITE_LED,HIGH);
              Serial.println();
              break;

          case 'Y':
              digitalWrite(YELLOW_LED,HIGH);
              Serial.println();    
              break;
    
         case 'r':
              digitalWrite(RED_LED,LOW);
              Serial.println();
              break;
         case 'g':
              digitalWrite(GREEN_LED,LOW);
              break;
         case 'b':
              digitalWrite(BLUE_LED,LOW);
              break;
         case 'w':
              digitalWrite(WHITE_LED,LOW);
              break;
         case 'y':
              digitalWrite(YELLOW_LED,LOW);
              break;

         case 'O':
              for(int i = 0; i < 2; i++){
                randomToggle();
              }
              break;

         default:
              break;
          
          Serial.println();    
        }

        Serial.write(c);
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 10; analogChannel < 18; analogChannel++) {
            int sensorReading =  analogRead(analogChannel);//analogChannel;
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

