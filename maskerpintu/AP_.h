void kedip(){
  for(int a=0;a<10;a++){
    digitalWrite(2, 1);
    delay(500);
    digitalWrite(2, 0);
    delay(500);
  }
}


void fwd() {
  while (1) {
    analogWrite(D5, kecepatan);
    digitalWrite(D6, 0);
    //digitalWrite(D7, 1);
    digitalWrite(2, 0);
    delay(100);
    digitalWrite(2, 1);
    delay(100);
    if (digitalRead(D1) == 0) {
    analogWrite(D5, 0);
    digitalWrite(D6, 0);
     // digitalWrite(D7, 0);
      break;
    }
  }
  
  kedip();
  
  while (1) {
    analogWrite(D5,255 - kecepatan);
    digitalWrite(D6, 1);
    digitalWrite(2, 0);
    delay(100);
    digitalWrite(2, 1);
    delay(100);
    //delay(200);
    if (digitalRead(D2) == 0) {
    analogWrite(D5, 0);
      digitalWrite(D6, 0);
      break;
    }
  }
 
}



void ap_mode() {

  digitalWrite(2, 0);

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    // Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //Serial.println(header);
            if (header.indexOf("/a1") >= 0) {
              
              Serial.println("satu");
              if (counter == 0) {
                fwd();
                counter = 1;
              }

              client.println("1");
            }
            if (header.indexOf("/a2") >= 0) {
              //digitalWrite(2, 1);
              counter = 0;
              Serial.println("Dua");
              client.println("2");
            }





            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }

    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    //Serial.println("");
  }

}
