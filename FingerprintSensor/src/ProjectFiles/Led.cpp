/*
 * Led.cpp
 *
 * Created: 4/19/2022 11:00:10 AM
 *  Author: Simona
 */ 

#include "Led.h"


Led::Led()
{

}

Led::~Led()
{

}

void Led::set(bool r, bool g, bool b)
{
	if(r) sbi(PORTD,R_LED); else cbi(PORTD,R_LED);
	if(g) sbi(PORTD,G_LED); else cbi(PORTD,G_LED);
	if(b) sbi(PORTD,B_LED); else cbi(PORTD,B_LED);
}