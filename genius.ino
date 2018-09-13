/**
 * GENIUS
 * @author Random
 * Date 11/09/2018
 */


// tone(pino, frequencia, duração)
// onde a frequencia do tom é setada em hertz, e a duração, em milisegundos.
// noTone(pino)


/* INCLUDES */

// For random numbers
#include <time.h>
#include <stdlib.h>


/* FUNCTION DECLARATION */

// Play note+led
void play(int button);

// Play sequency
void playSequency(int rodada);

// Play and stop note+led
void genius(int button);

// Get playing button
int getButton();

// Get players answer
void answer();


/* VARIABLES */

// Notes + LEDs: 0+2 = verde = 262 ...
int noteled[] = { 262, 294, 330, 349 };

// 32 size vector for GENIUS
int sequency[32];

// Round
int rodada = 0;


/* SETUP */

void setup() {

  // LED verde
  pinMode(8, INPUT);
  pinMode(2, OUTPUT);

  // LED vermelho
  pinMode(9, INPUT);
  pinMode(3, OUTPUT);

  // LED azul
  pinMode(10, INPUT);
  pinMode(4, OUTPUT);

  // LED amarelo
  pinMode(11, INPUT);
  pinMode(5, OUTPUT);

  // Buzzer
  pinMode(7, OUTPUT);

  // Generate array
  for (int i = 0; i < 32; i++) sequency[i] = random(8, 12);

}


/* LOOP */

void loop() {

  if (rodada > 32) exit(0);

  playSequency(rodada);
  answer();

  rodada++;

  delay(1000);

}


/* FUNCTION DEFINITION */

void play(int button) {

  tone(7, noteled[button - 8]);
  digitalWrite(button - 6, HIGH);

  delay(1000);

  noTone(7);
  digitalWrite(button - 6, LOW);

  delay(1000);

}

void playSequency(int rodada) {

  for (int i = 0; i <= rodada; i++) play(sequency[i]);

}

// Play and stop note+led
void genius(int button) {

  // Play
  while (digitalRead(button) == HIGH) {

    tone(7, noteled[button - 8]);
    digitalWrite(button - 6, HIGH);

    delay(200);

  }

  // Stop
  noTone(7);
  digitalWrite(button - 6, LOW);

}

// Get playing button
int getButton() {

  do {

    for (int i = 8; i < 12; i++) {

      if (digitalRead(i) == HIGH) {

        genius(i);
        return i;

      }

    }

  } while (true);

}

// Get players answer
void answer() {

  for (int i = 0; i <= rodada; i++) {

    // If players fail a new array is generated and round is reseted after a beep+LEDs
    if (getButton() != sequency[i]) {

      // Beep+LEDs
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      tone(7, 110); // LA
      delay(500);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      noTone(7);


      // Re-generation+reset
      for (int i = 0; i < 32; i++) sequency[i] = random(8, 12);
      rodada = -1;

    }

  }

}


/* PIANINHO
  // LED verde
  if (digitalRead(8) == HIGH) {

    tone(7, 262);             // DO
    digitalWrite(2, HIGH);

    delay(200);

  } else {

    noTone(7);
    digitalWrite(2, LOW);

  }

  // LED vermelho
  if (digitalRead(9) == HIGH) {

    tone(7, 294);             // RE
    digitalWrite(3, HIGH);

    delay(200);

  } else {

    noTone(7);
    digitalWrite(3, LOW);

  }

  // LED azul
  if (digitalRead(10) == HIGH) {

    tone(7, 330);              //MI
    digitalWrite(4, HIGH);

    delay(200);

  } else {

    noTone(7);
    digitalWrite(4, LOW);

  }

  // LED amarelo
  if (digitalRead(11) == HIGH) {

    tone(7, 349);              //FA
    digitalWrite(5, HIGH);

    delay(200);

  } else {

    noTone(7);
    digitalWrite(5, LOW);

  }
*/
