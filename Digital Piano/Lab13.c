// Digital Piano
// Based on Lab13 from Embedded Systems - Shape The World course on edX.org
// An ultrasonic on PortF reads a distance which plays a certain tone
// Buttons on PortE each one plays a saved song
// only files .c and .h are relevant

#include "..//tm4c123gh6pm.h"
#include "Sound.h"
#include "TExaS.h"

unsigned long trig,echo,prev=0;  
unsigned long long st,en;
void PortF_Init(void);
void PortE_Init(void); 

unsigned long long s,ind,key;

//all frequencies converted, each index corresponds to an ultrasonic reading
const int arr[39] = {1265,1420,1594,1790,2009,2128,2255,2389,2531,2681,2841,3010,
3189,3378,3579,3792,4018,4257,4510,4778,5062,5363,5682,6020,6378,6757,7159,7584,8035,8513,9019,9556,
10124,10726,11364,12039,12755,13514,14317};
unsigned int i;
		
//saved songs
const int fur_elise[121]={E5, D_5, E5, D_5, E5, B4, D5, C5, A4, E3, A3, C4, E4, A4, B4, E3, G_3, E4, G_4, B4, C5, E3, A3, E4,
	E5, D_5, E5, D_5, E5, B4, D5, C5, A4, E3, A3, C4, E4, A4, B4, E3, G_3, E4, C5, B4, A4, E3, A3,
	B4, C5, D5, E5, G3, C4, G4, F5, E5, D5, G3, B3, F4, E5, D5, C5, E3, A3, E4, D5, C5, B4, E3, E4, E5, E5, E5, 
	E5, D_5, E5, D_5, E5, B4, D5, C5, A4, E3, A3, C4, E4, A4, B4, E3, G_3, E4, G_4, B4, C5, E3, A3, E4,
	E5, D_5, E5, D_5, E5, B4, D5, C5, A4, E3, A3, C4, E4, A4, B4, E3, G_3, E4, C5, B4, A4, E3, A3};

const int pirates[133]={D5,D5,D5,E5,F5,F5,G5,E5,E5,D5,C5,C5,D5,A4,C5,D5,D5,D5,E5,F5,F5,G5,E5,E5,D5,C5,C5,D5,A4,C5,
	D5,D5,D5,E5,F5,F5,G5,A5,A_5,A_5,A5,G5,A5,A4,D5,E5,F5,F5,G5,A5,D5,A4,D5,F5,E5,E5,F5,D5,E5,A5,C6,D6,D6,D6,E6,F6,
	F6,F6,G6,E6,E6,D6,C6,C6,D6,D5,A5,C5,D6,D6,D6,E6,F6,F6,F6,G6,E6,E6,D6,C6,D6,A5,C6,D6,D6,D6,F6,G6,G6,G6,A6,A_6,
	A_6,A6,G6,A6,D6,A5,D6,E6,F6,F6,G6,A6,D6,A5,D6,F6,E6,E6,D6,C6,D6,D6,D6,E6,E6,E6,G6,A6,F6,D6,A5};	
	
const int titanium[111]={A_4,A_4,C5,D_5,D5,D5,D5,D5,D5,A_4,F5,D_5,D_5,D_5,D5,D5,C5,C5,D_5,D_5,A_4,A_4,C5,D_5,D5,D5,D5,A_4,
	A_4,C5,G4,G4,G4,C5,G_5,G_5,G5,G5,G5,D5,D5,G5,G5,G5,D5,D5,F5,G5,G5,D5,D5,D_5,C5,C5,G_5,G_5,G5,G5,G5,D5,D5,G5,G5,G5,D5,D5,F5,G5
	,G5,D5,D_5,C5,D_5,C6,C6,A_5,A_5,G5,G5,A_5,A_5,A_5,G5,G5,G5,G5,D_6,D_6,D6,D6,C6,C6,D_5,C6,C6,A_5,A_5,G5,G5,A_5,A_5,A_5,G5,G5,G5,
	G5,D_6,D_6,D6,D6,C6
};

const int assassin[126]={D4,D4,D4,F4,F4,F4,G4,G4,G4,A4,A4,A4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,F4,F4,F4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,A4,A4,A4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,F4,F4,F4,
D4,D4,D4,A4,A4,A4,G4,G4,G4,A4,A4,A4,
D4,D4,D4,A4,A4,A4,G4,G4,G4,F4,F4,F4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,A4,A4,A4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,F4,F4,F4,
D4,D4,D4,F4,F4,F4,G4,G4,G4,A4,A4,A4,
D5,D5,D5,E5,E5,E5,F5,F5,F5,G5,G5,G5,A5,A5,A5,A5,A5,A5};

const int safe[106]={A3,E4,C5,B4,B4,B3,G4,D4,E4,E4,E4,D4,A3,B3,B3,D4,A3,E4,C5,B4,B4,B3,G4,E4,D4,G4,
	G4,G4,G4,G4,A4,B4,B4,B4,A4,A4,A4,G4,G4,F_4,D4,D4,D4,E4,E4,E4,E4,D4,B3,D4,D4,B4,B4,A4,A4,G4,G4,F_4,
	D4,E4,G4,G4,G4,G4,B4,B4,A4,A4,C5,B4,D4,E4,E4,E4,D4,B3,B3,B3,B3,B4,B4,A4,A4,G4,G4,F_4,D4,E4,G4,A4,
	B4,E4,E4,E4,E4,G4,A4,B4,D5,D5,B4,A4,B4,A4,G4,E4
};
	

void delay2(unsigned long usec){ 
  while(usec > 0 ) {  
    usec--;
  }
}

// store rising and falling edge times of ultrasonic echo in st and en variables
void pulseWait(unsigned long msec){ 
	unsigned int flag1=0,flag2=1;
  while(msec > 0 ) {  // repeat while there are still delay
		if(flag1==0 && GPIO_PORTF_DATA_R&0x08){
			st = msec;
			flag1=1;
		}
		if(flag1 && flag2 && !(GPIO_PORTF_DATA_R&0x08)){
			en = msec;
			flag2=0;
		}
    msec--;
  }
}

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);		

int main(void){ 
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // set system clock to 80 MHz   
  Sound_Init(); // initialize SysTick timer and DAC
  PortF_Init(); // ultrasonic port
	PortE_Init(); // buttons port
  EnableInterrupts();  // enable after all initialization are done
  while(1){   
		GPIO_PORTF_DATA_R |= 0x06; //trig = 1 for ultrasonic
    trig = GPIO_PORTF_DATA_R&0x04;
		delay2(40); // 10 microsecond delay
		GPIO_PORTF_DATA_R &= ~0x06; //trig = 0;
		trig =GPIO_PORTF_DATA_R&0x04;
		pulseWait(200000); // about 70 ms
		echo = GPIO_PORTF_DATA_R&0x08;
		s = st - en; // s now indicates the distance the ultrasonic is reading
		ind =  s*0.003145 - 1.887; // linear relationship between the reading and indeces of converted frequencies array
		if(ind > 0 && ind<39){
	 	 	Sound_Tone(arr[39-ind]);
		}
		key = GPIO_PORTE_DATA_R; // buttons to play saved tones
		if(key&0x02){
			int i;
			for(i=0; i<121; i++){
				int x = 80000000/(fur_elise[i]*32); //converting the frequency to system clock, 32 is for the 32 sine wave array
				Sound_Tone(x);
				delay(200);
				Sound_Tone(0);
				delay(10);
			}
			Sound_Off();
		}
		else if(key&0x04){
			int i;
			for(i=0; i<133; i++){
				int x = 80000000/(pirates[i]*32);
				Sound_Tone(x);
				delay(250);
				Sound_Tone(0);
				delay(10);
			}
			Sound_Off();
		}
		else if(key&0x10){
			int i;
			for(i=0; i<106; i++){
				int x = 80000000/(safe[i]*32);
				Sound_Tone(x);
				delay(250);
				Sound_Tone(0);
				delay(10);
			}
			Sound_Off();
		}else if(key&0x08){		
			int i;
			for(i=0; i<111; i++){
				int x = 80000000/(titanium[i]*32);
				Sound_Tone(x);
				delay(300);
				Sound_Tone(0);
				delay(5);
			}
			Sound_Off();
		}else if(key&0x20){
			int i;
			for(i=0; i<126; i++){
				int x = 80000000/(assassin[i]*32);
				Sound_Tone(x);
				delay(350);
				Sound_Tone(0);
				delay(10);
			}
			Sound_Off();
		}
  }          
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } 
    msec--;
  }
}

// Initializations for ports
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x0F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x06;          // 5) PF2 O/P, the rest I/P
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  //GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x0F;          // 7) enable digital pins PF4-PF0        
}

void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x10;          // activate Port E
  delay = SYSCTL_RCGC2_R;          // allow time for clock to stabilize
                                   // no need to unlock
  GPIO_PORTE_AMSEL_R &= ~0x3F;     // disable analog functionality on PE3-0
  GPIO_PORTE_PCTL_R &= ~0x0000FFFF;// configure PE5-0 as GPIO
  GPIO_PORTE_DIR_R = 0;            // make PE5-0 in
  GPIO_PORTE_AFSEL_R &= ~0x3F;     // disable alt funct on PE5-0
	GPIO_PORTE_PDR_R |= 0x3F;        // enable pull-down on PE3-0
  GPIO_PORTE_DEN_R |= 0x3F;        // enable digital I/O on PE5-0
}
