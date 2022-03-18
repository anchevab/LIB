// *** Hardwarespecific defines ***
#define cbi(reg, bitmask) (*(reg + 1)) = bitmask
#define sbi(reg, bitmask) (*(reg + 2)) = bitmask
#define pulseLatch sbi(P_EP, B_EP); asm ("nop"); cbi(P_EP, B_EP)

#define fontbyte(x) cfont.font[x]  
#define bitmapbyte(x) bitmap[x]

#define PROGMEM
#define regtype volatile uint32_t
#define regsize volatile uint16_t
#define bitmapdatatype unsigned char*

