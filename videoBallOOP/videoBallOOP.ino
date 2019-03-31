class Ball
{
    // Class Member Variables
    // These are initialized at startup
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

    void setPunched() {
      if (value > thresh) {
        punched = true;
      } else {
        punched = false;
      }
    }
};

//const int PIEZO_PIN = A0; // Piezo output

//int curr = 5;

Ball ball0(0, 100);
Ball ball1(1, 400);
Ball ball2(2, 400);
Ball ball3(3, 400);
Ball ball4(4, 400);
Ball ball5(5, 400);

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
  ball0.setPunched();

  //Serial.println(String(ball0.getPunched()));

  if (ball0.getPunched()) {
    Serial.println("PUNCHED");
    delay(1000);
  } else {}
}
