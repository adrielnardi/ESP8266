//Biblioteca para conexão do WiFi com o Esp8266
#include <ESP8266WiFi.h>
char ssid[] = "XXXXXXX";     //Nome da  rede
char password[] = "XXXXXXX"; //Senha da rede

void setup()
{
  //Inicialização da comunicação do Monitor Serial e da comunicação Wifi
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) //retorna se houve problema de conexão ou não. 
  {
    delay(500); //tempo de meio segundo e vai tentar repetir a conexão
    Serial.print("."); //se a conexão não ofuncionar e algo tiver errado, vai mostrar “Connecting to WiFi..”.
  }
  Serial.println();

  Serial.print("Connected, IP address: "); //Assim que conectar vai mostrar seu Endereço IP Local
  Serial.println(WiFi.localIP());
}
void loop() {}
