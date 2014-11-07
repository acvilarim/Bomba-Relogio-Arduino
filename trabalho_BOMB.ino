

const int btn1 = 10;
const int btn2 = 11;
const int btn3 = 12;

const int display_a = 8;
const int display_b = 7;
const int display_c = 6;
const int display_d = 5;
const int display_e = 4;
const int display_f = 3;
const int display_g = 2;
int displayToBlink;
const int buzzer = 9;

int counter;
const int timerTick = 9;
int tick;

int state;
const int PAUSED = 0;
const int ARMED = 1;
const int DEFUSED = 2;
const int DETONED = 3;

boolean high;

int val1;
int val2;
int val3;

int result;

void setup() {
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  
  pinMode(display_a, OUTPUT);
  pinMode(display_b, OUTPUT);
  pinMode(display_c, OUTPUT);
  pinMode(display_d, OUTPUT);
  pinMode(display_e, OUTPUT);
  pinMode(display_f, OUTPUT);
  pinMode(display_g, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); 
  counter = -1;
  state = PAUSED;
  tick = 0;
  displayToBlink = display_a;
  high = false;
  
  result = random(3);
  Serial.print("Defused = " );                       
  Serial.println(result);  
}

void loop() {

  switch(state) {
    case PAUSED:
      val1 = digitalRead(btn1);
      val2 = digitalRead(btn2);
      val3 = digitalRead(btn3);
      if ((val1 == 0) || 
          (val2 == 0) ||
          (val3 == 0)){
        counter = 9;
        state = ARMED;
        digitalWrite(buzzer,HIGH);
        high = true;
      }

      break;
    case ARMED:
      //count down
      tick++;
      if (high) {
        digitalWrite(buzzer,LOW);
        high = false;
      } else {
        if (counter <= 3) {
          digitalWrite(buzzer,HIGH);
          high = true;
        }
      }        
      if (tick > timerTick) {
        tick = 0;
        counter--;
        if (counter > 3) {
          digitalWrite(buzzer,HIGH);
          high = true;
        }
      }
      if (counter <= 0 ) {
        state = DETONED;
        counter = -1;
      }
      tryDefuse();
      break;
    case DEFUSED:
      // apertou o botao certo, ok!
      break;
    case DETONED:
      // BUM!
      digitalWrite(buzzer, HIGH);
      break;
  }
  //Serial.print("Counter = " );                       
  //Serial.print(counter);      
  writeOnDisplay(counter);
  delay(100);
}

void tryDefuse() {
  val1 = digitalRead(btn1);
  val2 = digitalRead(btn2);
  val3 = digitalRead(btn3);
  
  switch(result) {
    case 0:
      if (val1 == 0) {
        state = DEFUSED;
        counter = -1;
      }
      if ((val2 == 0) || (val3 == 0)) {
        state =  DETONED;
        counter = -1;
      }
      break;
    case 1:
      if (val2 == 0) {
        state = DEFUSED;
        counter = -1;
      }
      if ((val1 == 0) || (val3 == 0)) {
        state =  DETONED;
        counter = -1;
      }
      break;
    case 2:
      if (val3 == 0) {
        state = DEFUSED;
        counter = -1;
      }
      if ((val1 == 0) || (val2 == 0)) {
        state =  DETONED;
        counter = -1;
      }
      break;
  }
  
}

void writeOnDisplay(int value) {
  digitalWrite(display_a,LOW);
  digitalWrite(display_b,LOW);
  digitalWrite(display_c,LOW);
  digitalWrite(display_d,LOW);
  digitalWrite(display_e,LOW);
  digitalWrite(display_f,LOW);
  digitalWrite(display_g,LOW);
  switch(value) {
    case 0: //0000
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_e,HIGH);
      digitalWrite(display_f,HIGH);
      break;
    case 1: //0001
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      break;
    case 2: //0010
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_g,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_e,HIGH);
      break;
    case 3: //0011
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    case 4: //0100
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_f,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    case 5: //0101
      digitalWrite(display_a,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_f,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    case 6: //0110
      digitalWrite(display_a,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_e,HIGH);
      digitalWrite(display_f,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    case 7: //0111
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      break;
    case 8: //1000
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_e,HIGH);
      digitalWrite(display_f,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    case 9: //1001
      digitalWrite(display_a,HIGH);
      digitalWrite(display_b,HIGH);
      digitalWrite(display_c,HIGH);
      digitalWrite(display_d,HIGH);
      digitalWrite(display_f,HIGH);
      digitalWrite(display_g,HIGH);
      break;
    default: //ERRO
      digitalWrite(displayToBlink,HIGH);
      displayToBlink--;
      if (displayToBlink < display_f) {
        displayToBlink = display_a;
      }
      break;
  }
}
