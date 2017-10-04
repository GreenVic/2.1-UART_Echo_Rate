#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_uart.h>

#include "Uart.h"


// ������������� ������ UART
void UART_Initialize (uint32_t uartBaudRate)
{
  // ��������� ��� ������������� ����� �����-������
  PORT_InitTypeDef GPIOInitStruct;

  // ��������� ��� ������������� ������ UART
  UART_InitTypeDef UARTInitStruct;

  // ���������� ������������ ����� F � ������ UART
  RST_CLK_PCLKcmd (UART_CLOCK | UART_CLOCK_TX | UART_CLOCK_RX , ENABLE);

  // ����� ������������ ����� �����-������
  PORT_StructInit (&GPIOInitStruct);
  GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
  GPIOInitStruct.PORT_MODE  = PORT_MODE_DIGITAL;

  // ������������ � ������������� ����� ��� ������ ������ 
	GPIOInitStruct.PORT_FUNC  = UART_PORT_FuncRX;
  GPIOInitStruct.PORT_OE    = PORT_OE_IN;
  GPIOInitStruct.PORT_Pin   = UART_PORT_PinRX;
  PORT_Init (UART_PORT_RX, &GPIOInitStruct);

  // ������������ � ������������� ����� ��� �������� ������ 
  GPIOInitStruct.PORT_FUNC  = UART_PORT_FuncTX;	
  GPIOInitStruct.PORT_OE    = PORT_OE_OUT;
  GPIOInitStruct.PORT_Pin   = UART_PORT_PinTX;
  PORT_Init (UART_PORT_TX, &GPIOInitStruct);

  // ������������ ������ UART
  UARTInitStruct.UART_BaudRate            = uartBaudRate;                  // �������� �������� ������
  UARTInitStruct.UART_WordLength          = UART_WordLength8b;             // ���������� ����� ������ � ���������
  UARTInitStruct.UART_StopBits            = UART_StopBits1;                // ���������� STOP-�����
  UARTInitStruct.UART_Parity              = UART_Parity_No;                // �������� ��������
  UARTInitStruct.UART_FIFOMode            = UART_FIFO_OFF;                 // ���������/���������� ������
  UARTInitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE   // ���������� �������� �� ��������� � ������� ������
                                          | UART_HardwareFlowControl_TXE;

  // ������������� ������ UART
  UART_Init (UART_X, &UARTInitStruct);

  // ����� ������������ �������� ������� ������ UART
  UART_BRGInit (UART_X, UART_HCLKdiv1);

  // ����� ���������� ���������� (����� � �������� ������)
  UART_ITConfig (UART_X, UART_IT_RX | UART_IT_TX, ENABLE);

  // ���������� ������ ������ UART
  UART_Cmd (UART_X, ENABLE);
}

void UART_InitIRQ(uint32_t priority) // priority = 1
{
  // ���������� ���������� ����������� ���������� �� UART
  NVIC_SetPriority (UART_IRQ, priority);

  // ���������� ���������� ���������� �� UART
  NVIC_EnableIRQ (UART_IRQ);
}	


void UartSetBaud(uint32_t baudRate, uint32_t freqCPU)
{
	uint32_t divider = freqCPU / (baudRate >> 2);
	uint32_t CR_tmp = UART_X->CR;
	uint32_t LCR_tmp = UART_X->LCR_H;
	
//  while ( !(UART_X->FR & UART_FLAG_TXFE) ); // wait FIFO empty
	while ( (UART_X->FR & UART_FLAG_BUSY) ); // wait 

  UART_X->CR = 0;
  UART_X->IBRD = divider >> 6;
  UART_X->FBRD = divider & 0x003F;
  UART_X->LCR_H = LCR_tmp;
  UART_X->CR = CR_tmp;
}


// ��������� ���������� ���������� ������ UART
/*void UARTx_IRQHandler (void)
{
  // ���� ��������� ���������� �� ���������� ������ ������...
  if (UART_GetITStatusMasked (UART_X, UART_IT_RX) == SET)
  {
    // ����� ����������
    UART_ClearITPendingBit (UART_X, UART_IT_RX);

    // ������ ���-�� �����

  }

  // ���� ��������� ���������� �� ���������� �������� ������...
  if (UART_GetITStatusMasked(UART_X, UART_IT_TX) == SET)
  {
    // ����� ����������
    UART_ClearITPendingBit (UART_X, UART_IT_TX);

    // �������� �����

  }
}
*/
