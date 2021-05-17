#include <Ethernet.h>
  
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 177 };
     
EthernetServer servidor(80);
  
String readString;

  
void setup(){
  
  pinMode(8, OUTPUT);
  Ethernet.begin(mac, ip);
  servidor.begin();
}
  
void loop(){
  EthernetClient cliente = servidor.available();
  if (cliente) {
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
  
        if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();
           
          cliente.println("<HTML>");
          cliente.println("<BODY>");
          cliente.println("<H1>Acende LED</H1>");
          cliente.println("<hr />");
          cliente.println("<br />");
          cliente.println("<p>LED <a href=\"/?led_ligar\"><button>LIGA</button></a><a href=\"/?led_desligar\"><button>DESLIGA</button></a>");
          cliente.println ("<p><a href=""http://afmulti.com.br/index.php/cursos-e-treinamentos/"">Visite nosso site!</a></p>"); 
          cliente.println ("<p><a href=""http://facebook.com/afmultiautomacao""> fanpage do Facebook</a> </p>");
          cliente.println("</BODY>");
          cliente.println("</HTML>");
           
          delay(1);
          cliente.stop();
           
          if(readString.indexOf("?led_ligar") > 0)
          {
            digitalWrite(8, HIGH);
          }
          else {
            if(readString.indexOf("?led_desligar") > 0)
            {
              digitalWrite(8, LOW);
            }
          }
          readString="";    
        }
      }
    }
  }
}
