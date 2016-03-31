#include <ESP8266WiFi.h>

const char* ssid = "freebox_GEMGOB";
const char* password = "38213B6FB0";
int photocellPin = 0;
int photocellReading;
int relay_1 = 2; // GPIO2
int relay_2 = 0; // GPIO0
int relay_3 = 4; // GPIO4
int relay_4 = 5; // GPIO5
WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);

pinMode(relay_1, OUTPUT);
digitalWrite(relay_1, LOW);

pinMode(relay_2, OUTPUT);
digitalWrite(relay_2, LOW);

pinMode(relay_3, OUTPUT);
digitalWrite(relay_3, LOW);

pinMode(relay_4, OUTPUT);
digitalWrite(relay_4, LOW);

// connection au SSID
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// mise ne place du serveur 
server.begin();
Serial.println("Server started");

// vous affiche au moniteur serie l'adress ip du module
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");

}

void loop() {
// Check if a client has connected
  
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println("new client");
while(!client.available()){
delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Match the request

int value1 = LOW;
int value2 = LOW;
int value3 = LOW;
int value4 = LOW;
if (request.indexOf("/relay1=ON") != -1) {
digitalWrite(relay_1, HIGH);
value1 = HIGH;
}
if (request.indexOf("/relay1=OFF") != -1) {
digitalWrite(relay_1, LOW);
value1 = LOW;
}

if (request.indexOf("/relay2=ON") != -1) {
digitalWrite(relay_2, HIGH);
value2 = HIGH;
}
if (request.indexOf("/relay2=OFF") != -1) {
digitalWrite(relay_2, LOW);
value2 = LOW;
}

if (request.indexOf("/relay3=ON") != -1) {
digitalWrite(relay_3, HIGH);
value3 = HIGH;
}
if (request.indexOf("/relay3=OFF") != -1) {
digitalWrite(relay_3, LOW);
value3 = LOW;
}

if (request.indexOf("/relay4=ON") != -1) {
digitalWrite(relay_4, HIGH);
value4 = HIGH;
}
if (request.indexOf("/relay4=OFF") != -1) {
digitalWrite(relay_4, LOW);
value4 = LOW;
}

// Set ledPin according to the request
//digitalWrite(ledPin, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.println("le relai 1 est: ");

if(value1 == HIGH) {
client.print("Allumé");
} else {
client.print("Eteint");
}
client.println("<br><br>");
client.println("Cliquez <a href=\"/relay1=ON\">ICI</a> pour allumer le relai 1 <br>");
client.println("Cliquez <a href=\"/relay1=OFF\">ICI</a> pour eteindre le relai 1 <br>");
client.println("<br><br>");

client.println("le relai 2 est: ");
if(value2 == HIGH) {
client.print("Allumé");
} else {
client.print("Eteint");
}client.println("<br><br>");
client.println("Cliquez <a href=\"/relay2=ON\">ICI</a> pour allumer le relai 2 <br>");
client.println("Cliquez <a href=\"/relay2=OFF\">ICI</a> pour eteindre le relai 2 <br>");
client.println("<br><br>");

client.println("le relaie 3 est: ");
if(value3 == HIGH) {
client.print("Allumé");
} else {
client.print("Eteint");
}
client.println("<br><br>");
client.println("Cliquez <a href=\"/relay3=ON\">ICI</a> pour allumer le relai 3 <br>");
client.println("Cliquez <a href=\"/relay3=OFF\">ICI</a> pour eteindre le relai 3 <br>");
client.println("<br><br>");

client.println("le relaie 4 est: ");
if(value4 == HIGH) {
client.println("Allumé");
} else {
client.println("Eteint");
}
client.println("<br><br>");
client.println("Cliquez <a href=\"/relay4=ON\">ICI</a> pour allumer le relaie 4 <br>");
client.println("Cliquez <a href=\"/relay4=OFF\">ICI</a> pour eteindre le relaie 4 <br>");
client.println("</html>");



delay(1);
Serial.println("Client disonnected");
Serial.println("");}


