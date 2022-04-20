/*
 * ProjectMain.cpp
 *
 * Created: 4/18/2022 1:56:45 PM
 *  Author: Simona
 */ 


#include "Led.h"
#include "Zamok.h"
#include <Adafruit_Fingerprint.h>
#include "HardwareSerial.h"

int getFingerprintIDez();

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial);

void setup()
{
	sbi(PORTD,B_LED);
	Serial.begin(57600);
	_delay_ms(3000);
	sbi(PORTD,B_LED);
	sbi(PORTD,R_LED);
	Serial.println("\n\nAdafruit finger detect test");

	// set the data rate for the sensor serial port
	finger.begin(57600);
	delay(5);
	if (finger.verifyPassword()) {
		Serial.println("Found fingerprint sensor!");
		} else {
		Serial.println("Did not find fingerprint sensor :(");
		while (1);
}
Serial.println("Waiting for valid finger...");
}



void loop()                     // run over and over again
{
	
	getFingerprintIDez(); 
	//getFingerprintID();
	delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
	Zamok zamok;
	Led rgb_led;
	
	
	
	//nastavime na 1 bit v porte D - svieti na bielo
	//sbi(PORTD,R_LED);
	
	//sbi(PORTD,G_LED);
	//zamok.odomkni();
	//_delay_ms(2000);
	//cbi(PORTD,G_LED);
	
	//ja mam led napojeny na zem - vypinam log.0
	rgb_led.set(true,false,true);
	
	
	
	
	uint8_t p = finger.getImage();
	switch (p) {
		case FINGERPRINT_OK:
		Serial.println("Image taken");
		break;
		case FINGERPRINT_NOFINGER:
		Serial.println("No finger detected");
		return p;
		case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
		case FINGERPRINT_IMAGEFAIL:
		Serial.println("Imaging error");
		return p;
		default:
		Serial.println("Unknown error");
		return p;
	}

	// ak sa program dostal tu znamena to ze naslo odtlacok
	
	p = finger.image2Tz();
	switch (p) {
		case FINGERPRINT_OK:
		Serial.println("Image converted");
		break;
		case FINGERPRINT_IMAGEMESS:
		Serial.println("Image too messy");
		rgb_led.set(true,true,false);
		return p;
		case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		rgb_led.set(true,true,false);
		return p;
		case FINGERPRINT_FEATUREFAIL:
		Serial.println("Could not find fingerprint features");
		rgb_led.set(true,true,false);
		return p;
		case FINGERPRINT_INVALIDIMAGE:
		Serial.println("Could not find fingerprint features");
		rgb_led.set(true,true,false);
		return p;
		default:
		Serial.println("Unknown error");
		rgb_led.set(true,true,false);
		return p;
	}

	// OK converted!
	p = finger.fingerSearch();
	if (p == FINGERPRINT_OK) {
		Serial.println("Found a print match!");
		} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
		Serial.println("Communication error");
		rgb_led.set(true,true,false);
		return p;
		} else if (p == FINGERPRINT_NOTFOUND) {
		Serial.println("Did not find a match");
		rgb_led.set(true,true,false);
		return p;
		} else {
		Serial.println("Unknown error");
		rgb_led.set(true,true,false);
		return p;
	}

	// found a match!
	Serial.print("Found ID #"); Serial.print(finger.fingerID);
	Serial.print(" with confidence of "); Serial.println(finger.confidence);
	//odomknem zamok a nastavim ledku
	rgb_led.set(false,true,true);
	zamok.odomkni();
	_delay_ms(2000);
	//sbi(PORTD,G_LED);
	//zamok.odomkni();
	//_delay_ms(2000);
	//cbi(PORTD,G_LED);
	rgb_led.set(true,false,true);
	
	return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
	  uint8_t p = finger.getImage();
	  if (p != FINGERPRINT_OK)  return -1;

	  p = finger.image2Tz();
	  if (p != FINGERPRINT_OK)  return -1;

	  p = finger.fingerFastSearch();
	  if (p != FINGERPRINT_OK)  return -1;
	  
	  // found a match!
	  Serial.print("Found ID #"); Serial.print(finger.fingerID);
	  Serial.print(" with confidence of "); Serial.println(finger.confidence);
	  return finger.fingerID;
}




int main(void)
{	
	//nastavim smer portu
	sbi(DDRD,R_LED);
	sbi(DDRD,B_LED);
	sbi(DDRD,G_LED);
	sbi(DDRC, SNIMAC);
	sbi(DDRD, ZAMOK);
	
	//sbi(PORTD,B_LED);
	UCSR0B |= (1<<RX)|(1<<TX);	// enable rx and tx
	/* SW UART */
	cbi(DDRD,RX);			// Set as input
	sbi(DDRD,TX);			// set as output
	sbi(PORTD,TX);			// log.1 on STX
	sbi(PORTD,RX);			// pull-up
	
	//zopnutie tranzistoru na snimaci
	sbi(PORTC, SNIMAC);
	cbi(PORTC, SNIMAC); //zopne sa tranzistor
	setup();
    while (1) 
    {
		loop();
    }
}