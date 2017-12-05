#ifndef _UART_H
#define _UART_H

#include <stdint.h>

#define USE_UART2

#ifdef USE_UART2

	#define UART_X						MDR_UART2
	#define UART_IRQ					UART2_IRQn
	#define UART_CLOCK 				RST_CLK_PCLK_UART2	
	
	#ifdef USE_MDR1986VE9x
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTF
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTF
	
		#define UART_PORT_TX			MDR_PORTF
		#define UART_PORT_PinTX		PORT_Pin_1
		#define UART_PORT_FuncTX  PORT_FUNC_OVERRID
	
		#define UART_PORT_RX			MDR_PORTF	
		#define UART_PORT_PinRX		PORT_Pin_0
		#define UART_PORT_FuncRX  PORT_FUNC_OVERRID
		
	#elif defined ( USE_MDR1986VE1T )
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTD
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTD
	
		#define UART_PORT_TX			MDR_PORTD
		#define UART_PORT_PinTX		PORT_Pin_13
		#define UART_PORT_FuncTX  PORT_FUNC_MAIN
	
		#define UART_PORT_RX			MDR_PORTD	
		#define UART_PORT_PinRX		PORT_Pin_14
		#define UART_PORT_FuncRX  PORT_FUNC_MAIN	
    
	#elif defined ( USE_MDR1986VE3 )
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTD
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTD
	
		#define UART_PORT_TX			MDR_PORTD
		#define UART_PORT_PinTX		PORT_Pin_13
		#define UART_PORT_FuncTX  PORT_FUNC_MAIN
	
		#define UART_PORT_RX			MDR_PORTD	
		#define UART_PORT_PinRX		PORT_Pin_14
		#define UART_PORT_FuncRX  PORT_FUNC_MAIN    
		
	#endif	
	
#elif defined ( USE_UART1 )

	#define UART_X						MDR_UART1
	#define UART_IRQ					UART1_IRQn
	#define UART_CLOCK 				RST_CLK_PCLK_UART1

	#ifdef USE_MDR1986VE9x
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTA
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTA
		
		#define UART_PORT_TX			MDR_PORTA
		#define UART_PORT_PinTX		PORT_Pin_7
		#define UART_PORT_FuncTX  PORT_FUNC_OVERRID
		
		#define UART_PORT_RX			MDR_PORTA	
		#define UART_PORT_PinRX		PORT_Pin_6
		#define UART_PORT_FuncRX  PORT_FUNC_OVERRID
		
	#elif defined ( USE_MDR1986VE1T )
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTC
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTC
	
		#define UART_PORT_TX			MDR_PORTC
		#define UART_PORT_PinTX		PORT_Pin_3
		#define UART_PORT_FuncTX  PORT_FUNC_MAIN
	
		#define UART_PORT_RX			MDR_PORTC	
		#define UART_PORT_PinRX		PORT_Pin_4
		#define UART_PORT_FuncRX  PORT_FUNC_MAIN


	#elif defined ( USE_MDR1986VE3 )   
	
		#define UART_CLOCK_TX 		RST_CLK_PCLK_PORTC
		#define UART_CLOCK_RX 		RST_CLK_PCLK_PORTC
	
		#define UART_PORT_TX			MDR_PORTC
		#define UART_PORT_PinTX		PORT_Pin_3
		#define UART_PORT_FuncTX  PORT_FUNC_MAIN
	
		#define UART_PORT_RX			MDR_PORTC	
		#define UART_PORT_PinRX		PORT_Pin_4
		#define UART_PORT_FuncRX  PORT_FUNC_MAIN
		
	#endif	
	
#endif


void UART_Initialize (uint32_t uartBaudRate);
void UART_InitIRQ(uint32_t priority);
void UartSetBaud(uint32_t baudRate, uint32_t freqCPU);

#endif // _UART_H
