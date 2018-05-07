#include <SPI.h>
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

char msgRecibido[10];
uint8_t cont;

String str = "What's up";

void sendMSG(String buff) {
  PORTJ = PORTJ & B10011111;
  PORTJ = PORTJ | B01000000; // habilitación de envío y recepción de msgs

  Serial3.println(buff);
  //Serial.print(buff);
}

bool receive(char buff[]) {
  PORTJ = PORTJ & B10011111; // Ponemos nuestro puerto RS485 en modo lectura.

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

void TestRS485 (int mode) {
  DDRJ = DDRJ | B01100000;
  PORTJ = PORTJ & B10011111;
  /*pinMode(CONTROLLINO_RS485_TX, OUTPUT);
    pinMode(CONTROLLINO_RS485_RX, INPUT);
    pinMode(CONTROLLINO_RS485_RE, OUTPUT);
    pinMode(CONTROLLINO_RS485_DE, OUTPUT);*/
  switch (mode)
  {
    case 0:
      PORTJ = PORTJ & B10011111;
      PORTJ = PORTJ | B01000000;
      /*digitalWrite (CONTROLLINO_RS485_RE, HIGH);
        digitalWrite (CONTROLLINO_RS485_DE, HIGH);*/
      delay (10);
      Serial.println ("Sending test message, expected to return;");
      Serial3.print("UUUUU Controllino RS485 test Message.UUUUU");
      break;

    case 1:
      PORTJ = PORTJ & B10011111;
      PORTJ = PORTJ | B01100000;
      /*digitalWrite (CONTROLLINO_RS485_RE, LOW);
        digitalWrite (CONTROLLINO_RS485_DE, HIGH);*/
      delay (10);
      Serial.println ("Sending test message, not expected to return;");
      Serial3.print("UUUUU Controllino RS485 test Message.UUUUU");
      break;

    case 2:
      PORTJ = PORTJ & B10011111;
      PORTJ = PORTJ | B00100000;
      /* digitalWrite (CONTROLLINO_RS485_RE, HIGH);
        digitalWrite (CONTROLLINO_RS485_DE, LOW);*/
      delay (10);
      Serial.println ("Sending test message, not expected to be sended;");
      Serial3.print("UUUUU Controllino RS485 test Message.UUUUU");
      break;

    default:
      Serial.println("Wrong mode!");
      return;
  }
}

/*This function enters loop and waits for any incoming data on serial 3.*/
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

void setup() {
  /* Here we initialize USB serial at 9600 baudrate for reporting */
  Serial.begin(9600);
  /* Here we initialize RS485 serial at 9600 baudrate for communication */
  Serial3.begin(9600);
  /* This will initialize Controllino RS485 pins */
  Controllino_RS485Init();
  //RecieveRS485();

}

void loop() {
  if (receive(msgRecibido))
    Serial.print(msgRecibido);


  if (Serial.available())
  {
    switch (Serial.read())
    {
      case '1':
        //TestRS485(0);
        sendMSG("HOLA QUE TAL");
        //Serial.println("Que esta pasando");
        break;

      case '2':
        //TestRS485(1);
        sendMSG("SEgunda opcion\n");
        break;

      case '3':
        //  TestRS485(2);
        sendMSG("100010101010101011111100000JWEJEJEJEJEJEJEJJE\n");
        break;

      default:
        sendMSG("a la 4ª va la vencida");
        break;



    }
  }
}
