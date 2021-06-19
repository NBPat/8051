//-----------------------------------------------------------------------------
// F85x_Blinky.c  mod pf simplicity c8051-c-gu toolstick
//-----------------------------------------------------------------------------
#include <SI_C8051F850_Defs.h>
#include <SI_C8051F850_Register_Enums.h>
#define SYSCLK       24500000/8        // SYSCLK frequency in Hz
SI_SBIT(LED1, SFR_P1, 0);                  // P1.0 LED1
SI_SBIT(LED2, SFR_P1, 1);                  // P1.1 LED2
void Port_Init (void);
void Timer2_Init (int counts);
void SiLabs_Startup (void)
{
   WDTCN = 0xDE;
   WDTCN = 0xAD;
}

void main (void)
{
   Port_Init ();
   Timer2_Init (SYSCLK / 12 / 10);  // SYSCLK / 12 / 10 generateS interrupts  at a 10 Hz rate.
   IE_EA = 1;                       // Enable global interrupts
   while (1) {}                     // Spin forever
}
void Port_Init (void)
{
   P1MDOUT |= 0x01;                    // Enable LED1 as a push-pull output
   XBR2 = 0x40;                        // Enable crossbar and weak pull-ups
}
void Timer2_Init (int counts)
{
   TMR2CN = 0x00;                      // Stop Timer2; Clear TF2;use SYSCLK/12 as timebase
   CKCON &= ~0x60;                     // Timer2 clocked based on T2XCLK;
   TMR2RL = -counts;                   // Init reload values
   TMR2 = 0xffff;                      // Set to reload immediately
   IE_ET2 = 1;                         // Enable Timer2 interrupts
   TMR2CN_TR2 = 1;                     // Start Timer2
}
SI_INTERRUPT(Timer2_ISR, TIMER2_IRQn)
{
   TMR2CN_TF2H = 0;                       // Clear Timer2 interrupt flag
   LED1 = !LED1;                            // Change state of LED
   LED2 = !LED1;
}
