#include <SPI.h>
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

char msgRecibido[10];
uint8_t cont;

String str = "What's up";

void sendMSG(String buff) {
  //PORTJ = PORTJ & B10011111;

  //Envio sin recivo
  //PORTJ = PORTJ & B10011111;
  //PORTJ = PORTJ | B01100000;
  //delay(5);

  //Envio y recibo
  //PORTJ = PORTJ & B10011111;
  //PORTJ = PORTJ | B01000000; // habilitación de envío y recepción de msgs

  //Sin envio ni recibo
  //PORTJ = PORTJ & B10011111;
  //PORTJ = PORTJ | B00100000;

  Serial3.println(buff);
  //Serial.print(buff);

  Serial.flush();
  Serial3.flush();
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
  Serial.flush();
  Serial3.flush();
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
  Serial.begin(115200);
  /* Here we initialize RS485 serial at 9600 baudrate for communication */
  Serial3.begin(115200);
  /* This will initialize Controllino RS485 pins */

  //Controllino_RS485Init();  //Same as
  //  pinMode(CONTROLLINO_RS485_TX, INPUT);
  //  pinMode(CONTROLLINO_RS485_RX, INPUT);
  //  PORTJ &= B10011111;

  DDRJ = DDRJ | B01100000;

  
  PORTJ = PORTJ & B10011111;
  PORTJ = PORTJ | B01000000;

}

void loop() {
  if (receive(msgRecibido))
    Serial.print(msgRecibido);


  if (Serial.available())
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

        case'9': 
          Serial.flush();
          Serial3.flush();
          break;

      default:
        Serial.println("Default");
        sendMSG("Sending default");
        break;



    }
  }
}
