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
int gDelay = 1000;

class Gport
{
    int pin;
    int ledPin;

  public:
    Gport(int gp, int lp) {
      pin = gp;
      ledPin = lp;

      pinMode(pin, OUTPUT);
      pinMode(ledPin, OUTPUT);
    }

    void setActive() {
      digitalWrite(pin, active);
      digitalWrite(ledPin, HIGH);
      delay(gDelay);
    }
    void setNormal() {
      digitalWrite(pin, normal);
      digitalWrite(ledPin, LOW);
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

Ball ball0(0, 400);
Ball ball1(1, 400);
Ball ball2(2, 400);
Ball ball3(3, 400);
Ball ball4(4, 400);
Ball ball5(5, 400);

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
}

void loop()
{
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

void loop1()
{
  //output ball state to BS:
  gport0.setOutput(true);
  gport1.setOutput(true);
  gport2.setOutput(true);
  gport3.setOutput(true);
  gport4.setOutput(true);
  gport5.setOutput(true);


  gport0.setOutput(false);
  gport1.setOutput(false);
  gport2.setOutput(false);
  gport3.setOutput(false);
  gport4.setOutput(false);
  gport5.setOutput(false);
}
