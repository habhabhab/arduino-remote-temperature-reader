/*--------------------------------------------------------------
  author of this magical code: Hannes Breuer, https://github.com/habhabhab
  server script author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>

const int sensorPin = A0;
const int sensorVal;

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 2, 254);   // IP address needs to change depending on network
EthernetServer server(80);        // server at port 80

void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
}

void loop()
{
  EthernetClient client = server.available();  // try to get client

  if (client) {  // got client?
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      
      //read value from sensor
      int sensorVal = analogRead(sensorPin);
      //calculate voltage from sensor value
      float voltage = (sensorVal/1024.0) * 5.0;
      //calculate temperature from voltage
      float temperature = (voltage - .5) * 100;
      
      if (client.available()) {   // client data available to read
        char c = client.read(); // read 1 byte (character) from client
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
          if (c == '\n' && currentLineIsBlank) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // send web page
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Raumtemperatur bei Hannes</title>");
            client.println("</head>");
            client.println("<body>");
            client.println("<p>Sensor Value: ");
            client.println(sensorVal);
            client.println("</p>");
            client.println("<p>Volts: ");
            client.println(voltage);
            client.println("</p>");
            client.println("<p>Temp: ");
            client.println(temperature);
            client.println("</p>");
            client.println("</body>");
            client.println("</html>");
            break;
          }
          // every line of text received from the client ends with \r\n
          if (c == '\n') {
            // last character on line of received text                    
            // starting new line with next character read
            currentLineIsBlank = true;
          } 
          else if (c != '\r') {
            // a text character was received from client
            currentLineIsBlank = false;
          }
        } // end if (client.available())
      } // end while (client.connected())
    delay(1);      // give the web browser time to receive the data
    client.stop(); // close the connection
  } // end if (client)
}
