#ifndef __DFROBOT_ALCOHOL_H__
#define __DFROBOT_ALCOHOL_H__

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define           ADDRESS_0                 0x72
#define           ADDRESS_1                 0x73
#define           ADDRESS_2                 0x74
#define           ADDRESS_3                 0x75           // iic slave Address

#define           MEASURE_MODE_AUTOMATIC    0x00           // active  mode
#define           MEASURE_MODE_PASSIVE      0x01           // passive mode

#define           AUTO_READ_DATA            0x00           // auto read ozone data
#define           PASSIVE_READ_DATA         0x01           // passive read ozone data


#define           MODE_REGISTER             0x03           // mode register
#define           SET_PASSIVE_REGISTER      0x04           // read ozone data register

#define           AUTO_DATA_HIGE_REGISTER   0x09           // AUTO data high eight bits
#define           AUTO_DATA_LOW_REGISTER    0x0A           // AUTO data Low  eight bits

#define           PASS_DATA_HIGE_REGISTER   0x0B           // AUTO data high eight bits
#define           PASS_DATA_LOW_REGISTER    0x0C           // AUTO data Low  eight bits

#define           OCOUNT                    100             // Ozone Count Value
#define           DATA_LEN                  9               // Uart data len
#define           IIC_FLAG                  1
#define           UART_FLAG                 2
#define           TIME_OUT                  500            // time out
#define           ERROR                     -1

class DFRobot_Alcohol{
public:
  DFRobot_Alcohol();
  ~DFRobot_Alcohol();
  void     SetModes(uint8_t Mode);
  int16_t  ReadAlcoholData(uint8_t CollectNum = 20);
  uint8_t  readBuf[14] = {0};
  uint8_t  sendBuf[14] = {0};
  uint8_t  CmdALOHA[9]   = {0xFF,0x01,0x78,0x40,0x00,0x00,0x00,0x00,0x47};
  uint8_t  CmdPolling[9] = {0xFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46};
  uint8_t  CmdRead[9]    = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  uint8_t  Uart_IIC_Flag = 0;
private:
  void     WriteAlcohol(uint8_t Reg , uint8_t pdata);
  void     WriteAlcohol_R(uint8_t Reg , uint8_t pdata);
  int16_t  ReadAlcohol(uint8_t Reg);
  int      OzoneData[OCOUNT] = {0x00};
  int      getAverageNum(int bArray[], int iFilterLen);
  uint8_t  _addr;                               // IIC Slave number
  uint8_t  _M_Flag = 0;                         // Mode flag

  virtual void writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len) = 0;
  virtual uint8_t readData(uint8_t Reg ,uint8_t *Data ,uint8_t len) = 0;
};


class DFRobot_Alcohol_IIC:public DFRobot_Alcohol{
public:
  DFRobot_Alcohol_IIC(TwoWire *pWire=&Wire ,uint8_t addr = 0x75);
  bool begin(void);
protected:
  virtual void writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
  virtual uint8_t readData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
private:
  TwoWire *_pWire;
  uint8_t _IIC_addr;
};


class DFRobot_Alcohol_UART:public DFRobot_Alcohol{
public:
  DFRobot_Alcohol_UART(SoftwareSerial *s ,uint16_t Baud);
  bool begin(void);
protected:
  virtual void writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
  virtual uint8_t readData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
private:
  SoftwareSerial *_s;
  uint32_t _Baud;
};


#endif