#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <iolpc2378.h>
#include <can.h>
#include <bsp.h>

// #define CAN_MEM_BASE    0xE0038000

// #define MAX_PORTS 2   /* Number of CAN port on the chip */    

#define BITRATE100K28_8MHZ        0x00090017

#define ACCF_BYPASS          0x02   // filter off, receive all


bool can1SendMessage(canMessage_t *);
bool can2SendMessage(canMessage_t *);
void canRxInterrupt(pVoidFunc_t);



/* Please note, this PCLK is set in the bsp.h file. Since the example
  program is set to test USB device, there is only a limited number of
  options to set CCLK and PCLK when USB is used. The default setting is
  CCLK 57.6MHz, PCLK is 1/2 CCLK 28.8MHz. The bit timing is based on the
  setting of the PCLK, if different PCLK is used, please read can.h carefully
  and set your CAN bit timing accordingly.

  No CAN interrupts
*/
void canInit(void) {
  PCONP |= (1 << 13) | (1 << 14); // Enable clock to the peripheral

  PINSEL0 &= ~0x00000F0F;
  PINSEL0 |= 0x0000A05; // port0.0~1, function 0x01, port0.4~5, function 0x10

  AFMR = ACCF_BYPASS;        // Acceptance filtering off, receive all messages
  CAN1MOD = CAN2MOD = 1;  // Reset CAN
  CAN1IER = CAN2IER = 0;  // Disable Receive Interrupt
  CAN1GSR = CAN2GSR = 0;  // Reset error counter when CANxMOD is in reset

  CAN1BTR = CAN2BTR = BITRATE100K28_8MHZ;
  CAN1MOD = CAN2MOD = 0x0;  // CAN in normal operation mode
}

/* 
 * Enable CAN interrupts and install handler
 */
void canRxInterrupt(pVoidFunc_t canHandler) {
  vicInstallIRQhandler(canHandler, 1, VIC_CAN12);
  CAN1IER = CAN2IER = 0x01;   // Enable receive interrupts
} 


/* 
 * return true if a message is available in the receive
 * buffer of the specified CAN port
 * bit 8 in CANRXSR is set if message available for port 1
 * bit 9 in CANRXSR is set if message available for port 2
 */
bool canReady(uint8_t port) {
  assert((port == 1) || (port == 2));
  return (CANRXSR & (1 << (7 + port)));
}

          
bool canWrite(uint8_t port, canMessage_t *msg) {
  bool result;
  
  assert((port ==1) || (port == 2));
  if (port == 1) {
    result = can1SendMessage(msg);
  } else { 
    result = can2SendMessage(msg);
  }
  return result;
}
            

         
/*
 * Assume 11-bit identifier
 */          
void canRead(uint8_t port, canMessage_t *msg) {
  assert((port == 1) || (port == 2));
  if (port == 1) {
    msg->id = (CAN1RID & 0x000007FF);
    msg->len = ((CAN1RFS & 0x000F0000) >> 16);
    msg->dataA = CAN1RDA;
    msg->dataB = CAN1RDB;
    CAN1CMR |= 0x04;
  } else {
    msg->id = (CAN2RID & 0x000007FF);
    msg->len = ((CAN2RFS & 0x000F0000) >> 16);
    msg->dataA = CAN2RDA;
    msg->dataB = CAN2RDB;
    CAN2CMR |= 0x04;
  }
}

          
bool can1SendMessage(canMessage_t *msg) {
  uint32_t canStatus;
  bool result = false;

  canStatus = CAN1SR;
  if ( canStatus & 0x00000004 ) {
    CAN1TID1 = msg->id;
    CAN1TFI1 = msg->len << 16; 
    CAN1TDA1 = msg->dataA;
    CAN1TDB1 = msg->dataB;
    CAN1CMR = 0x21;
    result = true;
  }
  else if ( canStatus & 0x00000400 ) {
    CAN1TID2 = msg->id;
    CAN1TFI2 = msg->len << 16;
    CAN1TDA2 = msg->dataA;
    CAN1TDB2 = msg->dataB;
    CAN1CMR = 0x41;
    result = true;
  }
  else if ( canStatus & 0x00040000 ) { 
    CAN1TID3 = msg->id;
    CAN1TFI3 = msg->len << 16;
    CAN1TDA3 = msg->dataA;
    CAN1TDB3 = msg->dataB;
    CAN1CMR = 0x81;
    result = true;
  }
  return result;
}

bool can2SendMessage(canMessage_t *msg) {
  uint32_t canStatus;
  bool result = false;

  canStatus = CAN2SR;
  if ( canStatus & 0x00000004 ) {
    CAN2TID1 = msg->id;
    CAN2TFI1 = msg->len << 16; 
    CAN2TDA1 = msg->dataA;
    CAN2TDB1 = msg->dataB;
    CAN2CMR = 0x21;
    result = true;
  }
  else if ( canStatus & 0x00000400 ) {
    CAN2TID2 = msg->id;
    CAN2TFI2 = msg->len << 16;
    CAN2TDA2 = msg->dataA;
    CAN2TDB2 = msg->dataB;
    CAN2CMR = 0x41;
    result = true;
  }
  else if ( canStatus & 0x00040000 ) { 
    CAN2TID3 = msg->id;
    CAN2TFI3 = msg->len << 16;
    CAN2TDA3 = msg->dataA;
    CAN2TDB3 = msg->dataB;
    CAN2CMR = 0x81;
    result = true;
  }
  return result;
}
          
