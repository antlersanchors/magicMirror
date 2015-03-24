// magic mirror
// borrowing liberally at present from Row-Column Scanning
//  created 27 May 2009 modified 30 Aug 2011 by Tom Igoe

// 2-dimensional array of row pin numbers:
const int row[4] = {
	8,4,3,6 };

// 2-dimensional array of column pin numbers:
const int col[4] = {
	2,7,5,12};

// 2-dimensional array of pixels:
int pixels[4][4];

// variables for the incoming serial data
int indexIn = 0;
int redIn;
int blueIn;
int greenIn;

// define sensors
#define wheelRate A1


void setup() {

  Serial.begin(9600);

  // initialize the I/O pins as outputs
  // iterate over the pins:

  for (int thisPin = 0; thisPin < 4; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);  

    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(col[thisPin], HIGH);    

  }

  // initialize the pixel matrix:
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {

	if (Serial.available() > 0) {
		// read input from Processing:
		fetchStream();

		// draw the screen:
		refreshScreen();

	}
}

void fetchStream() {

    // get incoming byte:
    inByte = Serial.read();


  // turn off the last position:
  pixels[x][y] = HIGH;
  // read the sensors for X and Y values:
  // shave a bit of the top to help with mapping to the full 4 pixel range
  x = 3 - map(analogRead(sensor1), sensorLow1, sensorHigh1 * 0.9, 0, 3);
  y = map(analogRead(sensor2), sensorLow2, sensorHigh2 * 0.9, 0, 3);


  // Serial.print("Sensor A2: ");
  // Serial.println(analogRead(A2));
  // Serial.print("Sensor A1: ");
  // Serial.println(analogRead(A1));

  // set the new pixel position low so that the LED will turn on
  // in the next screen refresh:
  pixels[x][y] = LOW;

}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 4; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 4; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];

      // Serial.print("pixels :");
      // Serial.println(pixels[thisRow][thisCol]);

      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}