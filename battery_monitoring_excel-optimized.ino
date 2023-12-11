// https://github.com/gregsell/arduino-multicell-battery-monitoring/upload/main

// IMPORTANT:
// definition: C1 cell with lowest voltage, c6 highest voltage
// battery pack is grounded with microcontroller at the negative pole of the 'lowest' cell -> no negative voltages
// used for 6S1P lithium battery

const int numCells = 6; // nr of cells in series
const int inputs[numCells] = {A0, A1, A2, A3, A4, A5}; // analog input pins for respective cell
const float vCorr[numCells] = { 1.0, 1.995, 6.053, 6.005, 5.98, 5.98}; // factors correcting for the voltage dividers. These should be fine-tuned carefully.
float c[numCells] = {0}; // cell voltages
float minC[numCells] = {}; // smallest measured cell voltages
float maxC[numCells] = {0}; // largest measured cell voltages
float v[numCells] = {0}; // absolute voltages from GND to the respective cell

float avg = 0.0; // variable for measurement filtering

void setup() {

  Serial.begin(500000);
  // one-time initialization of minC values, soley for being overwritten later
  for (int i = 0; i < numCells; i++) {
    minC[i] = 5;
    String s = String(i+1);
    Serial.print("c"+s+ "  minC"+s+"  maxC"+s+" "); // column labels for the excel chart
  }
  Serial.println();
}

void loop() {
  
  for (int i = 0; i < numCells; i++) { // procedurally computes values for every cell -> number of cells can be changes very easily

    // averaging multiple measurements
    avg = 0;
    for (int k = 0; k < 5; k++) {
      avg += map (analogRead(inputs[i]), 0, 1023, 0, 500);
      delayMicroseconds(200); // small delay between measurements
    }
    avg = avg / 5.0;

    // compute absolute voltages from GND to respective cell
    v[i] = avg / 100.0 * vCorr[i];
    if (v[i] < 0) { v[i] = 0; }

    // derive relative cell voltages from absolute values
    if  (i == 0) { c[0] = v[0]; }
    else { c[i] = v[i] - v[i-1]; }

    // check for minima or maxima
    if ((c[i] < minC[i]) && (c[i] > 0.1)) { // the second condition is to avoid zero values showing up as minima. Anything like that probably was a loose wire and can thus be skipped.
      minC[i] = c[i]; 
    }
    if (c[i] > maxC[i]) {
      maxC[i] = c[i];
    }

    // serial printing/plotting

    Serial.print(c[i]);
    Serial.print(" ");
   
    Serial.print(minC[i]);
    Serial.print(" ");

    Serial.print(maxC[i]);
    Serial.print(" ");
  
  }
  Serial.println();
  //delay(100);
}
