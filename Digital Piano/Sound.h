
#define C16 9555 		// 80Mhz/(523.251*16)-1 = 9554.6435
#define D16 8512		// 80Mhz/(587.330*16)-1 = 8512.1017
#define E16 7583		// 80Mhz/(659.255*16)-1 = 7583.3187
#define G16 6377		// 80Mhz/(783.991*16)-1 = 6576.6242


#define C32 4777 		// 80Mhz/(523.251*32)-1 = 4776.8217
#define D32 4256		// 80Mhz/(587.330*32)-1 = 4255.5508
#define E32 3791		// 80Mhz/(659.255*32)-1 = 3791.1593
#define G32 3188		// 80Mhz/(783.991*32)-1 = 3187.8121


// definetions for frequencies of all tones
#define C2	65
#define C_2	69
#define D2	73
#define D_2	77
#define E2	82
#define F2	87
#define F_2	92
#define G2	98
#define G_2	103
#define A2	110
#define A_2	116
#define B2	123
#define C3	130
#define C_3	138
#define D3	146
#define D_3 155
#define E3	164	
#define F3	174
#define F_3	185
#define G3	196
#define G_3	207
#define A3	220
#define A_3	233
#define B3	246
#define C4	261
#define C_4	277
#define D4	293
#define D_4	311
#define E4	329
#define F4	349
#define F_4	369
#define G4	392
#define G_4	415
#define A4	440
#define A_4 466
#define B4	493
#define C5	523
#define C_5 554
#define D5	587
#define D_5 622
#define E5	659
#define F5	698
#define F_5	739
#define G5	783
#define G_5	830
#define A5	880
#define A_5	932
#define B5	987
#define C6	1046
#define C_6 1108
#define D6	1174
#define D_6	1244
#define E6	1318
#define F6  1396
#define G6  1568
#define A6  1760
#define A_6 1864
#define B6  1979

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also initializes DAC
// Input: none
// Output: none
void Sound_Init(void);

// **************Sound_Tone*********************
// Change SysTick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period);


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void);
