//-------------------------------------------------------------------------
// msp430-spi-3.c 
// (c) 2014 Christophe BLAESS - www.blaess.fr/christophe
// Licensed under GPLv2.
// 
// Exemples de mon article "Dialogue en SPI entre Raspberry Pi et MSP430"
// Gnu/Linux Magazine France hors serie special "Raspberry Pi avance".
// ------------------------------------------------------------------------

#include <stdlib.h>
#include <msp430g2553.h>


int main(void)
{
	int val = 0;

	// Stop the watchdog.
	WDTCTL = WDTPW + WDTHOLD;

	// Wait for the SPI clock to be idle (low).
	while ((P1IN & BIT4)) ;

	// Select secondary function for P1.1 (MISO) P1.2 (MOSI) P1.4 (CLK)
	P1SEL  = BIT1 + BIT2 + BIT4;
	P1SEL2 = BIT1 + BIT2 + BIT4;

	// Reset USART and put in configuration mode.
	UCA0CTL1 |= UCSWRST;

	// UCA0 Configuration (see. slau144 p.445)
	// UCCKPH = 0 -> Data changed on leading clock edges and sampled on trailing edges.
 	// UCCKPL = 0 -> Clock inactive state is low.
	//   SPI Mode 0 :  UCCKPH * 1 | UCCKPL * 0
	//   SPI Mode 1 :  UCCKPH * 0 | UCCKPL * 0  <--
	//   SPI Mode 2 :  UCCKPH * 1 | UCCKPL * 1
	//   SPI Mode 3 :  UCCKPH * 0 | UCCKPL * 1
	// UCMSB  = 1 -> Most Significant Bit first.
	// UC7BIT = 0 -> 8 bits, 1 -> 7 bits.
	// UCMST  = 0 -> slave, 1 -> master.
	// UCMODE_x  x=0 -> 3-pin SPI,
	//           x=1 -> 4-pin SPI UC0STE active high,
	//           x=2 -> 4-pin SPI UC0STE active low,
	//           x=3 -> i²c.
	// UCSYNC = 1 -> Synchronous mode (SPI).
	//
	UCA0CTL0 = UCCKPH*0 | UCCKPL*0 | UCMSB*1 | UC7BIT*0 | UCMST*0 | UCMODE_0 | UCSYNC*1;

	// Enable USART.
	UCA0CTL1 &= ~UCSWRST;

	while (1) {
		while ((IFG2 & UCA0RXIFG) == 0) ;
			
		val = UCA0RXBUF;
		while (UCA0STAT & UCBUSY) ;
		UCA0TXBUF = val;
        }
	return 0;
}

