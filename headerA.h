/*Header file for node A*/


typedef unsigned char u8;

typedef char s8;

typedef unsigned int u32;

typedef int s32;

typedef unsigned short int u16;

typedef unsigned short int s16;


extern void delay_ms(u32 ms);

extern void delay_us(u32 us);

void delay_sec(u32 sec);


extern void lcd_data(u8 data);

extern void lcd_cmd(u8 cmd);

extern void lcd_init(void);

extern void lcd_string(s8 *ptr);

extern void lcd_integer(s32 num);


extern void uart0_init(u32 baudrate);

extern void uart0_tx(u8 data);

extern u8 uart0_rx(void);

extern void uart0_tx_string(s8 *ptr);

extern void uart0_rx_string(s8 *ptr, s32 max_bytes);

extern void uart0_integer(s32 num);

extern void uart0_float(float num);

extern void uart0_positive_num(u32 num);


extern void adc_init(void);

extern u16 adc_read(u8);


#define CS0 (1<<7)

extern void spi0_init(void);

extern u8 spi0_data(u8 data);


extern u16 mcp3204_adc_read(u8 ch_num);


extern void eint_handler(void)__irq;

extern void en_eint(void);


typedef struct can2_msg{

	u32 id, byteA, byteB;

	u8 rtr, dlc;

}can2;

extern void can2_init(void);

extern void can2_tx(can2 v);

extern void can2_rx(can2 *ptr);

extern void can2_rx_handlerA(void)__irq;

extern void en_can2_interruptA(void);

