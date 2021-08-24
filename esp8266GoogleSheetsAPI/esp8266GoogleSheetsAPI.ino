#include <ESP8266WiFi.h>
WiFiClientSecure cl;//Cria um cliente seguro (para ter acesso ao HTTPS)
String textFix = "GET /v4/spreadsheets/18cFkOvs58lPirBXlGS5foV1BR51OnZ1KjU0qqiEMZEc/values/";
String key = "?key=AIzaSyAQdP5yB-FpiocwdLBFOtToeSiNotVrLBM";//Chave de API
void setup()
{
    Serial.begin(115200);//Inicia a comunicacao serial
    WiFi.mode(WIFI_STA);//Habilita o modo estaçao
    WiFi.begin("XXXXX", "XXXXX");//Conecta na sua rede
    delay(3000);//Espera um tempo para se conectar no WiFi
}
void loop()
{
    cl.setInsecure();
    if (cl.connect("sheets.googleapis.com", 443) == true)//Tenta se conectar ao servidor do Google APIs na porta 443 (HTTPS)
    {
        String toSend = textFix;//Atribuimos a String auxiliar na nova String que sera enviada
        
        toSend += "C2:C4";//Os valores que queremos ler da planilha.
        toSend += key;//Adicionamos a chave na String
        toSend += " HTTP/1.1";//Completamos o metodo GET para nosso formulario.
        cl.println(toSend);//Enviamos o GET ao servidor-
        cl.println("Host: sheets.googleapis.com");//-
        cl.println();//-
      
        Serial.println("Dado recebido:\n");//Mostra no Serial Monitor todo o pacote recebido.-
        Serial.print(cl.readString());//-
        cl.stop();//Encerramos a conexao com o servidor.
    }
    else
    {
        Serial.println("Erro ao se conectar");
    }
  
    delay(5000);
}
