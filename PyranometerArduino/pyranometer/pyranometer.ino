/*
 Pyranometer sensor : SP-212 from Apogee Instruments
 */

int pyranometerPin = A0;    
int pyranometerValue = 0;  
const int CALIBRATION_FACTOR = 5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  pyranometerValue = analogRead( pyranometerPin );    
  map( pyranometerValue, 0, 1023, 0, 3300 );  // convert to get result in mV
  Serial.println( pyranometerValue * CALIBRATION_FACTOR ); // 5 W m⁻² per mV, see https://www.apogeeinstruments.com/content/SP-100-200-spec-sheet.pdf
  delay( 100 ); // 10Hz 
}
