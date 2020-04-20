

int x=0;
void setup() {

  Serial.begin(9600);
}

void loop() {



  Serial.println("tx: "+(String)x+" rx");

  delay(1000);
  ;
}

class MyUART {     //creating a UART class

    private:

        int tx_pin;

        int rx_pin;
    public:

        MyUART(int t_pin, int r_pin);

        void send_char(char c);

        char receive_char(void);
};
MyUART mySerial(1,0);   // making a constructor function

MyUART::MyUART(int t_pin, int r_pin) {

                                        // Initialise tx and rx pin
for transmission
    tx_pin = t_pin;

    rx_pin = r_pin;

    pinMode(tx_pin, OUTPUT);

    pinMode(rx_pin, INPUT_PULLUP);

    digitalWrite(tx_pin, HIGH);
}
MyUART::send_char(char c) {

                                               // Send function over UART;
    delayMicroseconds(104);

    for (int i = 0; i < 8; i++) {

        digitalWrite(tx_pin, (c >> i) & 0x01);

        delayMicroseconds(104);
    }

    digitalWrite(tx_pin, HIGH);

    delayMicroseconds(104);
}

char MyUART::receive_char(void) {    // recieving a function over uart

    char rx_char = 0x00;

    while (digitalRead(rx_pin) == HIGH);

    delayMicroseconds(104);


    for (int i = 0; i < 8; i++) {

        rx_char |= (0x01 & digitalRead(rx_pin)) << i;

        delayMicroseconds(104);
    }

    delayMicroseconds(104);

    return rx_char;
}
