/*
 * Zamok.cpp
 *
 * Created: 4/19/2022 11:01:05 AM
 *  Author: Simona
 */ 

#include "Zamok.h"


Zamok::Zamok()
{

}

Zamok::~Zamok()
{

}

void Zamok::odomkni()
{
	sbi(PORTD,ZAMOK); //odomknut
	_delay_ms(3000); //ostane odomknuty 3 sekundy a znovu sa zamkne
	cbi(PORTD,ZAMOK); //zamknut
}
