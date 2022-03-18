// *** Hardwarespecific defines ***
#define cbi(reg, bitmask) *reg &= ~bitmask
#define sbi(reg, bitmask) *reg |= bitmask
#define pulseLatch sbi(P_EP, B_EP); asm ("nop"); cbi(P_EP, B_EP)

#define fontbyte(x) cfont.font[x]  
#define bitmapbyte(x) bitmap[x]

#define regtype volatile uint32_t
#define regsize volatile uint32_t
#define bitmapdatatype unsigned char*
