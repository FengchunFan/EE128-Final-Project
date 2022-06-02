/******************************************************************************
PIR_Motion_Detector_Example.ino
Example sketch for SparkFun's PIR Motion Detector
  (https://www.sparkfun.com/products/13285)
Jim Lindblom @ SparkFun Electronics
May 2, 2016

The PIR motion sensor has a three-pin JST connector terminating it. Connect
the wire colors like this:
- Black: D2 - signal output (pulled up internally)
- White: GND
- Red: 5V

Connect an LED to pin 13 (if your Arduino doesn't already have an LED there).

Whenever the PIR sensor detects movement, it'll write the alarm pin LOW.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/

/******************************************************************************
 * sound_detector_demo.ino
 * Sound detector sample sketch
 * Byron Jacquot @ SparkFun Electronics
 * February 19, 2014
 * https://github.com/sparkfun/Sound_Detector
 * 
 * This sketch demonstrates the use of the Sparkfun Sound Detector board.
 *
 * The Sound Detector is a small board that combines a microphone and some 
 * processing circuitry.  It provides not only an audio output, but also a 
 * binary indication of the presence of sound and an analog representation 
 * of it's amplitude.  
 *
 * This sketch demonstrates two different modes of usage for the Sound
 * Detector.  The gate output (a binary indication that is high when sound
 * is present, and low when conditions are quiet) is used to fire a pin-change 
 * ISR, which lights an LED when the sound is present.  The envelope output 
 * (an analog voltage to rises to indicate the amplitude of the sound) is 
 * sampled in the loop(), and it prints an indication of the level to the 
 * serial terminal. 
 *
 * For more details about the Sound Detector, please check the hookup guide.
 *
 * Connections:
 * The Sound Detector is connected to the Adrduino as follows:
 * (Sound Detector -> Arduino pin)
 * GND → GND
 * VCC → 5V
 * Gate → Pin 2
 * Envelope → A0
 * 
 * Resources:
 * Additional library requirements: none
 * 
 * Development environment specifics:
 * Using Arduino IDe 1.0.5
 * Tested on Redboard, 3.3v/8MHz and 5v/16MHz ProMini hardware.
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/
 /******************************************************************************
Photocell_Example.ino
Example sketch for SparkFun's photocell - light-variable resistor
  (https://www.sparkfun.com/products/9088)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a photocell with a 4.7k resistor.
- The resistor should connect from A0 to GND.
- The photocell should connect from A0 to 3.3V
- Connect an LED to pin 13 (if there's not one built into your Arduino)
As the resistance of the photocell increases (surroundings get darker), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/

const int MOTION_PIN = 7; // Pin connected to motion detector
const int LED_PIN = 13; // LED pin - active-high
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
//#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0
const int LIGHT_PIN = A1;

void soundISR()
{
  int pin_val;
  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(LED_PIN, pin_val);   
}

void setup() 
{
  Serial.begin(9600);
  pinMode(MOTION_PIN, INPUT_PULLUP);
  pinMode(PIN_GATE_IN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int value;
  value = analogRead(PIN_ANALOG_IN);
  int proximity = digitalRead(MOTION_PIN);
  int lightADC = analogRead(LIGHT_PIN);
  if (proximity == LOW) // If the sensor's output goes low, motion is detected
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motion detected!");
    //delay(1000);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    if(value > 30){
      Serial.println("Sound detected!");
    if(lightADC > 800){
      Serial.println("Light detected!");
      analogWrite(LED_PIN,20);
      delay(20);
      digitalWrite(LED_PIN, LOW);
      delay(1000);
    }else{
      digitalWrite(LED_PIN,HIGH);
      delay(1000);
      digitalWrite(LED_PIN, LOW);
      delay(1000);  
    }
    }
    //delay(1000);
  }
}
