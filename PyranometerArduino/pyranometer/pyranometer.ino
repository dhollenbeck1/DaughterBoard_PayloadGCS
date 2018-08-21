/*
 Pyranometer sensor : SP-212 from Apogee Instruments
 */

int pyranometerPin = A0;    
int pyranometerValue = 0;  
const float CALIBRATION_FACTOR = 0.5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  pyranometerValue = analogRead( pyranometerPin );    
  pyranometerValue = map( pyranometerValue, 0, 1023, 0, 5000 );  // convert to get result in ms
  Serial.println( (float)pyranometerValue * CALIBRATION_FACTOR ); // 0.5 W m⁻² per mV, see https://www.apogeeinstruments.com/content/SP-100-200-spec-sheet.pdf
  delay( 100 ); // 10Hz 
}
