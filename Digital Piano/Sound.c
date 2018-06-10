// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"


unsigned int cnt=0,Index=0,flag=0;

	
const unsigned int SineWave[32] = {8,9,10,10,12,13,14,15,15,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,1,1,2,3,3,5,6,7};

	
int sound_enable;

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();          					// Port B is DAC
	sound_enable=0;
	Index = 0;
	NVIC_ST_CTRL_R = 0;           // disable SysTick during setup
  NVIC_ST_RELOAD_R = C32;       // reload value
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){ // Systick Handler is triggerd after each period
// this routine sets the RELOAD and starts SysTick
	NVIC_ST_RELOAD_R = period;    // reload value
	sound_enable = 1;
	cnt=0;
	flag=0;
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	// NVIC_ST_CTRL_R &= ~0x00000002;		// disable the interrupt
	sound_enable=0;
	DAC_Out(0x00);
}


// Interrupt service routine
// Executed every 12.5ns*(period)

void SysTick_Handler(void){
	cnt++;
	if(cnt>=20000 && !flag){ //to stop after a certain amount of time for the same interrupt
		cnt=0;
		Sound_Off();
		flag=1;
	}
	if(sound_enable) {
		DAC_Out(SineWave[Index&0x1F]); 
	}
	Index++; 
}



