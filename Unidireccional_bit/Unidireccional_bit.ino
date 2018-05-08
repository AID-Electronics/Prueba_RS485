#include <SPI.h>
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

#define pinEstado A0
#define pinMotor 2

bool estado;

char msgRecibido[10];
uint8_t cont;

String str = "What's up";

void sendMSG(String buff) {
  //Envio sin recivo
  PORTJ = PORTJ & B10011111;
  PORTJ = PORTJ | B01100000;

  Serial3.println(buff);
}

bool receive(char buff[]) {
  // PORTJ = PORTJ & B10011111; // Ponemos nuestro puerto RS485 en modo lectura.

  bool flag = false;
  int i = 0;

  while (Serial3.available())
  {
    char token = Serial3.read();
    buff[i] = token;
    i++;

    if (!flag)
      flag = true;


  }
  buff[i] = '\0';
  return flag;

}

void RecieveRS485() {
  Serial.println("Recieving RS485.");
  while (true)
  {
    if (Serial3.available())
    {
      // print the new byte:
      Serial.print((char)Serial3.read());

    }
  }
}

<<<<<<< HEAD


void mandarEstado_desdeSerial()
{
   if (Serial.available())
  {
    switch (Serial.read())
    {
      case '1':
        Serial.println("HIGH");
        digitalWrite(pinEstado,HIGH);
        break;

      case '2':
        Serial.println("LOW");
        digitalWrite(pinEstado,LOW);
        break;


      default:
        Serial.println("Default");
        
        break;



    }
  }
}
=======
void setupPinesMega(){
  pinMode(pinEstado, INPUT);
  pinMode(pinMotor, OUTPUT);
}

void loopMega(){
  estado = digitalRead(pinEstado);
  Serial.print(estado);
  Serial.print(" - ");
  if (estado == false) {
    digitalWrite(pinMotor,LOW);
    Serial.println("Esperando");
    delay(500);
  }

  else {
    digitalWrite(pinMotor,HIGH);
    String out;
    out += millis()/1000;
    sendMSG(out);
  }
}

>>>>>>> f7a8eff5a6ce3433312b216114d4432b5d0da7f1
void setup() {
  Serial.begin(1000000);
  Serial3.begin(115200);

  /* This will initialize Controllino RS485 pins */
  Controllino_RS485Init();  //Same as
  pinMode(pinEstado,OUTPUT);
  
  //  pinMode(CONTROLLINO_RS485_TX, INPUT);
  //  pinMode(CONTROLLINO_RS485_RX, INPUT);
  //  PORTJ &= B10011111;
  //
  //  DDRJ = DDRJ | B01100010;
  //
  //  PORTJ = PORTJ & B10011111;
  //  PORTJ = PORTJ | B01000000;
  setupPinesMega();
}

void loop() {
<<<<<<< HEAD
  if (receive(msgRecibido))
    Serial.print(msgRecibido);

  mandarEstado_desdeSerial();
 /* if (Serial.available())
  {
    switch (Serial.read())
    {
      case '1':
        Serial.println("Case 1");
        sendMSG("HOLA QUE TAL");
        break;

      case '2':
        Serial.println("Case 2");
        sendMSG(str);
        break;

      case '3':
        Serial.println("Case 3");
        sendMSG("state = 1;");
        break;

      default:
        Serial.println("Default");
        sendMSG("Sending default");
        break;



    }
  }*/
}
=======
  loopMega();
}


>>>>>>> f7a8eff5a6ce3433312b216114d4432b5d0da7f1
