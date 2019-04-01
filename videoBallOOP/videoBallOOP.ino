//INICIO DE INSTRUCCIONES

//paso 0) teniendo todo conectado, conecta el Arduino a la PC, verifica en herramientas que la placa, procesador y puerto COM sean los correctos [Arduino NANO, AtMega328P (Old Bootloader), COM XX]

//paso 1)  elije la pelota [0-5] de la que quieres mostrar su valor y asigna el valor en la variable showBall:
int showBall = 3;

//paso 2)  una vez visualizado su valor promedio en herramientas-serial plotter, golpea la pelota y observa el valor que obtiene
//asigna en las siguientes variables el valor mínimo para considerar la pelota como golpeada; cada pelota tiene su propio threshold

int thresh0 = 400;
int thresh1 = 400;
int thresh2 = 400;
int thresh3 = 400;
int thresh4 = 400;
int thresh5 = 400;

//paso 3) guarda este código [CTRL+S] y súbelo a la placa [CTRL+U]

//paso 4) verifica que el LED correspondiente se encienda al golpear la pelota; la salida GPIO cambiará su estado al ser golpeada

//FIN DE INSTRUCCIONES

//Ball class definition:
class Ball
{
    int pin;
    int thresh;
    int value;
    bool punched;

  public:
    Ball(int p, int th) {
      pin = p;
      thresh = th;
      value = 0;
      punched = false;
    }

    int getValue() {
      return value;
    }
    void readValue() {
      value = analogRead(pin);
    }
    bool getPunched() {
      return punched;
    }

    void updatePunch() {
      if (value > thresh) {
        punched = true;
      } else {
        punched = false;
      }
    }
};


//Brightsign gpio class definition:

bool active = true;
bool normal = false;

int gDelay = 500;

class Gport
{
    int pin;
    int ledPin;

  public:

    void setNormal() {
      digitalWrite(pin, normal);
      digitalWrite(ledPin, LOW);
    }

    Gport(int gp, int lp) {
      pin = gp;
      ledPin = lp;

      pinMode(pin, OUTPUT);
      pinMode(ledPin, OUTPUT);
      setNormal();
    }
    void blinkOnce() {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
    }
    void setActive() {
      digitalWrite(pin, active);
      digitalWrite(ledPin, HIGH);
      delay(gDelay);
    }
    void setOutput(bool input) {
      if (input) {
        //in case Ball has been punched, Brightsign active value is set
        setActive();
        setNormal();
      } else {
        setNormal();
      }
    }

};

//instancing ball objects:

Ball ball0(0, thresh0);
Ball ball1(1, thresh1);
Ball ball2(2, thresh2);
Ball ball3(3, thresh3);
Ball ball4(4, thresh4);
Ball ball5(5, thresh5);

//instancing gpio outputs:
Gport gport0(12, 13);
Gport gport1(10, 3);
Gport gport2(8, 5);
Gport gport3(6, 7);
Gport gport4(4, 9);
Gport gport5(2, 11);

void setup()
{
  Serial.begin(9600);
  gport0.blinkOnce();
  gport1.blinkOnce();
  gport2.blinkOnce();
  gport3.blinkOnce();
  gport4.blinkOnce();
  gport5.blinkOnce();
}

void loop()
{
  //display for calibration:
  Serial.println(analogRead(showBall));
  //read all values:
  ball0.readValue();
  ball1.readValue();
  ball2.readValue();
  ball3.readValue();
  ball4.readValue();
  ball5.readValue();

  //refresh punched value according to curr value and thresh
  ball0.updatePunch();
  ball1.updatePunch();
  ball2.updatePunch();
  ball3.updatePunch();
  ball4.updatePunch();
  ball5.updatePunch();

  //output ball state to BS:
  gport0.setOutput(ball0.getPunched());
  gport1.setOutput(ball1.getPunched());
  gport2.setOutput(ball2.getPunched());
  gport3.setOutput(ball3.getPunched());
  gport4.setOutput(ball4.getPunched());
  gport5.setOutput(ball5.getPunched());
}
