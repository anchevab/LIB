// *** Hardwarespecific defines ***
#define cbi(reg, bitmask) *reg &= ~bitmask
#define sbi(reg, bitmask) *reg |= bitmask
#define pulseLatch sbi(P_EP, B_EP); asm ("nop"); cbi(P_EP, B_EP)

#define fontbyte(x) pgm_read_byte(&cfont.font[x])  
#define bitmapbyte(x) pgm_read_byte(&bitmap[x])  

#define regtype volatile uint8_t
#define regsize volatile uint8_t
#define bitmapdatatype uint8_t*
