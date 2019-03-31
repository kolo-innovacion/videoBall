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

const int PIEZO_PIN = A0; // Piezo output

int curr = 5;

Ball ballX(curr, 400);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //  int piezoADC = analogRead(PIEZO_PIN);
  ballX.readValue();

  Serial.println(ballX.getValue());
}
