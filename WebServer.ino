/*********************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**********************************/
//********************************
// Librerías
//********************************
#include <WiFi.h>
#include <WebServer.h>
//********************************
// Variables globales
//********************************
// SSID & Password
const char* ssid = "iPhone de Victor";  // Enter your SSID here
const char* password = "internet";  //Enter your Password here

const int A = 27;
const int B = 14;
const int C = 12;
const int D = 13;
const int E = 26;
const int F = 5;
const int G = 25;

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


uint8_t LED1pin = 2;

bool LED1status = LOW;
bool p1status = LOW;

char receivedChar; 
int lot1 = 1;
int lot2 = 1;
int lot3 = 1;
int lot4 = 1;
int lot5 = 1;
int lot6 = 1;
int lot7 = 1;
int lot8 = 1;
int ocupado = 0;
int vacio = 0;
int maxVacios = 4; // Máximo número de parqueos disponibles
int minVacios = 0; // Mínimo número de parqueos disponibles
int maxOcupado = 4; // Máximo número de parqueos disponibles
int minOcupado = 0; // Mínimo número de parqueos disponibles
//********************************
// Configuración
//********************************
void setup() {
  Serial.begin(115200);
  
  // Serial.println(ssid);


  // Serial.println("Inicio, Hola");
  // Configura el puerto UART2 a 115200 bps
  Serial2.begin(115200);

  pinMode(LED1pin, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.print(".");
  }
  // Serial.println("");
  // Serial.println("WiFi connected successfully");
  // Serial.print("Got IP: ");
  // Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  
  server.onNotFound(handle_NotFound);

  server.begin();
  // Serial.println("HTTP server started");
  delay(100);
}
//********************************
// loop principal
//********************************
void loop() {
  delay(2500);
  // Verifica si hay datos disponibles para leer en el puerto UART2
  if (Serial2.available() > 0 ) {
    // Lee el byte recibido
    char receivedChar = Serial2.read();
    // Muestra el byte en el monitor serial
    // Serial.print("Received char: ");
    // Serial.println(receivedChar);
      // Llama a la función si el caracter es una "a" minúscula
    if (receivedChar == 'a') {
      // Serial.print("Parqueo 1 ocupado \n");    
      lot1 = 0;
      ocupado++; 
    } else if (receivedChar == 'A'){
      // Serial.print("Parqueo 1 disponible \n");  
      lot1 = 1;
      vacio++;

    }

    if (receivedChar == 'b') {
      // Serial.print("Parqueo 2 ocupado \n");    
      lot2 = 0;
      ocupado++; 
    } else if (receivedChar == 'B'){
      // Serial.print("Parqueo 2 disponible \n");  
      lot2 = 1;
      vacio++;
    }

    if (receivedChar == 'c') {
      // Serial.print("Parqueo 3 ocupado \n");    
      lot3 = 0;
      ocupado++; 
    } else if (receivedChar == 'C'){
      // Serial.print("Parqueo 3 disponible \n");  
      lot3 = 1;
      vacio++;
    }

    if (receivedChar == 'd') {
      // Serial.print("Parqueo 4 ocupado \n");    
      lot4 = 0;
      ocupado++; 
    } else if (receivedChar == 'D'){
      // Serial.print("Parqueo 4 disponible \n");  
      lot4 = 1;
      vacio++;
    }
    // vacio = limitarValor(vacio, maxVacios, minVacios);
    // ocupado = limitarValor(ocupado, maxOcupado, minOcupado);
    
    // int valor = lot1 + lot2 + lot3 + lot4;
    // Display(valor);

  }

   if (Serial.available() > 0 ) {
    // Lee el byte recibido
    char receivedChar = Serial.read();
    // Muestra el byte en el monitor serial
    // Serial.print("Received char: ");
    // Serial.println(receivedChar);
      // Llama a la función si el caracter es una "a" minúscula
    if (receivedChar == 'e') {
      // Serial.print("Parqueo 1 ocupado \n");    
      lot5 = 0;
      ocupado++; 
    } else if (receivedChar == 'E'){
      // Serial.print("Parqueo 1 disponible \n");  
      lot5 = 1;
      vacio++;

    }

    if (receivedChar == 'f') {
      // Serial.print("Parqueo 2 ocupado \n");    
      lot6 = 0;
      ocupado++; 
    } else if (receivedChar == 'F'){
      // Serial.print("Parqueo 2 disponible \n");  
      lot6 = 1;
      vacio++;
    }

    if (receivedChar == 'g') {
      // Serial.print("Parqueo 3 ocupado \n");    
      lot7 = 0;
      ocupado++; 
    } else if (receivedChar == 'G'){
      // Serial.print("Parqueo 3 disponible \n");  
      lot7 = 1;
      vacio++;
    }

    if (receivedChar == 'h') {
      // Serial.print("Parqueo 4 ocupado \n");    
      lot8 = 0;
      ocupado++; 
    } else if (receivedChar == 'H'){
      // Serial.print("Parqueo 4 disponible \n");  
      lot8 = 1;
      vacio++;
    }
    // vacio = limitarValor(vacio, maxVacios, minVacios);
    // ocupado = limitarValor(ocupado, maxOcupado, minOcupado);
  }

  int valor = lot1 + lot2 + lot3 + lot4 + lot5 +lot6 + lot7 + lot8;
  Display(valor);
   
  // Serial.print("Afuera de la condición: \n");
//********************************
  server.handleClient();
  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
}
//********************************
// Handler de Inicio página
//********************************
void handle_OnConnect() {
  LED1status = LOW;
  // Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));

}
//********************************
// Handler de led1on
//********************************
void handle_led1on() {
  LED1status = HIGH;
  // Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status));
}

//********************************
// Handler de led1off
//********************************
void handle_led1off() {
  LED1status = LOW;
  // Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}
//********************************
// Procesador de HTML
//********************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html lang=\"en\">\n";
  ptr += "<head>\n";
  ptr += "  <meta charset=\"UTF-8\">\n";
  ptr += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "  <title>UVG - CIT</title>\n";
  ptr += "  <style>\n";
  ptr += "    html { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; display: inline-block; margin: 0px auto; text-align: center; background-color: #2ECC71;}\n";
  ptr += "    body { margin: 0; padding: 0;}\n";
  ptr += "    h1 { color: #FFFFFF; background-color: #2ECC71; padding: 30px; margin: 0;}\n"; // Fondo verde
  ptr += "    table { width: 80%; margin: 20px auto; border-collapse: collapse; border-radius: 10px; overflow: hidden; box-shadow: 0 0 45px rgba(0, 0, 0, 0.1);}\n";
  ptr += "    th, td { border: 1px solid #dddddd; text-align: center; padding: 15px;}\n"; // Centra el texto
  ptr += "    th { background-color: #5D6D7E; color: white; font-size: 18px;}\n";
  ptr += "    td { font-size: 16px;}\n";
  ptr += "    .button { display: block; width: 150px; background-color: #3498db; border: none; color: white; padding: 15px 30px; text-decoration: none; font-size: 18px; margin: 20px auto; cursor: pointer; border-radius: 4px; transition: background-color 0.3s; box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.2);}\n";
  ptr += "    .button:hover { background-color: #2980b9;}\n";
  ptr += "    .disponible { background-color: #ABEBC6; color: #000; font-weight: bold; box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.2);} \n"; // Fondo verde naturaleza, texto negro y negrita
  ptr += "    .ocupado { background-color: #FA8072; color: #000; font-weight: bold; box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.2);}\n"; // Fondo rosado, texto negro y negrita
  ptr += "  </style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "  <h1>UVG - CIT</h1>\n";
  ptr += "  <table>\n";
  ptr += "    <tr><th>Parqueo</th><th>Estado</th></tr>\n";

 // Simula el estado de parqueo basado en la letra recibida
for (int i = 0; i < 8; ++i) {
  ptr += "    <tr><td style=\"background-color: #f0f3f4;\">Parqueo " + String(i + 1) + "</td>"; // Fondo gris claro

  if (i == 0) {
    if (lot1 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot1 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 1) {
    if (lot2 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot2 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 2) {
    if (lot3 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot3 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 3) {
    if (lot4 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot4 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 4) {
    if (lot5 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot5 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 5) {
    if (lot6 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot6 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 6) {
    if (lot7 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot7 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  } else if (i == 7) {
    if (lot8 == 0) {
      ptr += "<td class=\"ocupado\">Ocupado</td></tr>\n";
    } else if (lot8 == 1) {
      ptr += "<td class=\"disponible\">Disponible</td></tr>\n";
    }
  }
}

  ptr += "  </table>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}



//********************************
// Handler de not found
//********************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void Display(int numero){
  if(numero == 1){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    digitalWrite(E,LOW);
    digitalWrite(F,LOW);
    digitalWrite(G,LOW);
  }else if(numero == 2){
     digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(F,LOW);
    digitalWrite(G,HIGH);
  }else if(numero == 3){
     digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,HIGH);
    digitalWrite(E,LOW);
    digitalWrite(F,LOW);
    digitalWrite(G,HIGH);
  }else if(numero == 4){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    digitalWrite(E,LOW);
    digitalWrite(F,HIGH);
    digitalWrite(G,HIGH);
  }else if(numero == 5){
     digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(D,HIGH);
    digitalWrite(E,LOW);
    digitalWrite(F,HIGH);
    digitalWrite(G,HIGH);
  }else if(numero == 6){
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(D,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(F,HIGH);
    digitalWrite(G,HIGH);
  }else if(vacio == 7){
     digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);
    digitalWrite(E,LOW);
    digitalWrite(F,LOW);
    digitalWrite(G,HIGH);
  }else if(numero == 8){
     digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(F,HIGH);
    digitalWrite(G,HIGH);
  }else if(numero == 0){
     digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(F,HIGH);
    digitalWrite(G,LOW);
  }
}
