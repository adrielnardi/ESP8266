//Web Server é um programa que responde as solicitações HTTP|cliente solicita
#include <ESP8266WiFi.h>           //Biblioteca para acesso WiFi
char ssid[] = "Oficial_2.4G";     //Nome da  rede
char password[] = "33862654";    //Senha da rede
int LED = 4;                    // variável LED recebe inteiro 4
WiFiServer server(80);         //define porta 80 para o servidor
 
void setup() {
  Serial.begin(115200);      
  pinMode(LED, OUTPUT);      // define LED saída de dados
  Serial.println();
  Serial.print("Conectando-se a "); 
  Serial.println(ssid);    
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  server.begin();          // servidor é iniciado
}
 
void loop() {
  WiFiClient client = server.available(); // verifica se existe um cliente conectado com dados a serem transmitidos.
  if (client) {                       //toda vez que o cliente conectar, ele informa no monitor serial
    Serial.println("New Client.");  // avisa monitor serial novo cliente
    String currentLine = "";        // variável para armazenar a mensagem desse client
    while (client.connected()) {   //enquanto o cliente tiver conectado
      if (client.available()) {   //verificamos se existem bytes, dados, a serem lidos
        char c = client.read();   // caso existam os dados, armazenamos na variável c
        Serial.write(c);          // mostrado o valor no monitor serial
        if (c == '\n') {          //se o simbolo for \n significa nova linha
          if (currentLine.length() == 0) {     //se a mensagem acabou e nao tiver mais bits a serem lidos
            client.println("HTTP/1.1 200 OK");           //confirma para o cliente msg recebida
            client.println("Content-type:text/html");    //avisa cliente conteudo html
            client.println();
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 2 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 2 off.<br>");
            client.println();
            break;              //sai do while
          } else {
            currentLine = ""; //impede a string de ficar com espaços em branco
          }
        } else if (c != '\r') {  //início de uma nova linha
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {  //verifica se a requisição foi acionar LED
          digitalWrite(LED, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {   //verifica se a requisição desliga LED
          digitalWrite(LED, LOW);
        }
      }
    }
    client.stop();                            //finaliza conexão
    Serial.println("Client Disconnected.");  // monitor serial avisado que foi finalizado
  }
}
