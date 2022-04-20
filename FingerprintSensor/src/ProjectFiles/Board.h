/*
 * Board.h
 *
 * Created: 4/19/2022 10:58:31 AM
 *  Author: Simona
 */ 

#ifndef BOARD_H_
#define BOARD_H_

//skopirovane co sa defaultne vytvorilo v main.cpp
#ifndef F_CPU
#define F_CPU 12000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

//definujem si operacie
//x- register y- prislusny bit
#define sbi(x,y) x |= (1<<y) //bitovy posun do lava
#define cbi(x,y) x &= ~(1<<y) //and a ~ negacia, vynulovanie bitu na registri
#define tbi(x,y) x ^= (1<<y) // zmena bitu

//definujem si MAKRA - ledky podla toho na akom su porte
#define G_LED PORTD6
#define R_LED PORTD5
#define B_LED PORTD4 // na akom porte v atmege sa nachadza ledka

#define SNIMAC PORTC0
#define ZAMOK PORTD3

#define RX PORTD0
#define TX PORTD1

#endif /* BOARD_H_ */