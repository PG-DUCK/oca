﻿#include "de10_silicon_base.h"
#include "utility.h"

de10_silicon_base::de10_silicon_base(const char *address, int port, int verb):tcpclient(address, port, verb){
  //Initialize and compute configurations
  testUnitCfg = 0;
  hkEn = 0;
  //  ConfigureTestUnit(0);
  dataEn = 1;
  //  SetIntTriggerPeriod(0x02faf080);
  //  SetCalibrationMode(0);
  //  SelectTrigger(0);
  pktLen = 0x0000028A;
  feClkDuty  = 0x00000004;
  feClkDiv   = 0x00000028;
  adcClkDuty = 0x00000004;
  adcClkDiv  = 0x00000002;
  //  SetDelay(0x00000145);
  //  SetMode(0);
  detId = 0x000000E3;

  changeText("hello");
  if (verbosity>0) {
    printf("%s) de10 silicon created\n", __METHOD_NAME__);
  }
}

//--------------------------------------------------------------

de10_silicon_base::~de10_silicon_base(){
}

//--------------------------------------------------------------
int de10_silicon_base::readReg(int regAddr, uint32_t &regCont){
  char readBack[LEN]="";
  int ret=0;
  if (SendCmd("readReg")==0) {
    SendInt((uint32_t)regAddr);
  }
  else {
    ret = 1;
  }

  if (client_receive(readBack)<=0) ret = 1;

  if (verbosity>0) {
    printf("%s) Read: %s\n", __METHOD_NAME__, readBack);
  }
  regCont = atoi(readBack);
  return ret;
}

//FIX ME: use the proper functions or the 2D array to retrieve configurations
int de10_silicon_base::Init() {
  //client_send("trigger -off\n");
  //client_send("write -x 040700\n");
  char c[sizeof (uint32_t) * 8 +1];
  char readBack[LEN]="";
  uint32_t regContent = 1;

  if (verbosity>0) {
    printf("%s) [>>> initializing (reset everything)]\n", __METHOD_NAME__);
  }
  SendCmd("init");
  client_receive(readBack);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, readBack);
  }

  //Register 1
  regContent = (testUnitCfg&0x00000003) << 8 | (hkEn&0x00000001) << 6 \
                | testUnitEn | (dataEn&0x00000001);
  SendInt(regContent);

  //Register 2
  regContent = intTrigPeriod|calEn|intTrigEn;
  SendInt(regContent);

  //Register 3
  regContent = detId&0x000000FF;
  SendInt(regContent);

  //Register 4
  regContent = pktLen;
  SendInt(regContent);

  //Register 5
  regContent = ((feClkDuty&0x0000FFFF)<<16) | (feClkDiv&0x0000FFFF);
  SendInt(regContent);

  //Register 6
  regContent = ((adcClkDuty&0x0000FFFF)<<16) | (adcClkDiv&0x0000FFFF);
  SendInt(regContent);

  //Register 7
  regContent  = delay;
  SendInt(regContent);

  printf("%s) Qui!\n", __METHOD_NAME__);
  
  return 0;
}

int de10_silicon_base::SetDelay(uint32_t delayIn){
  char readBack[LEN]="";
  delay = (delayIn & 0x0000FFFF);
  client_send("set delay");
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%x", delay);
  client_send(c);
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::SetMode(uint8_t modeIn) {
  char readBack[LEN]="";
  mode=(modeIn << 4)&0x00000010;
  client_send("set mode");
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%d", mode);
  client_send(c);
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::GetEventNumber() {
  char readBack[LEN]="";
  //	printf("[>>> getting events]\n");
  client_send("get event number");
  client_receive(readBack);
  return 0;
}

//FIX ME: Shall not read event numbers from HPS, but print the ones already got
char* de10_silicon_base::PrintAllEventNumber() {
  static char numbers[1023]="";
  //char readBack[LEN]="";
  // snprintf(numbers, 1023, "Dampe %02d: %6d", selfaddress, 0);
  // printf("[>>>>>] dampe: %s\n", numbers);
  //client_send("print all event number");
  //client_receive(readBack);
  return numbers;
}

int de10_silicon_base::EventReset() {
  // client_send("write -x 020400\n");
  // client_send("write -x 040700\n");
  char readBack[LEN]="";
  if (verbosity>0) {
    printf("%s) [>>>>>] resetting events (reinitialize)\n", __METHOD_NAME__);
  }
  client_send("event reset");
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::GetEvent(uint32_t* evt){
  char readBack[LEN]="";
  client_send("get event");

  //Get the event from HPS and loop here until all data are read
  //FIX ME: make it working with variable lengths
  uint32_t evtRead = 0;
  while(evtRead < kevtLen) {
    evtRead += client_receive(evt, kevtLen-evtRead);
  }

  return evtRead;
}

//TO DO: there will be another method, in future to really calibrate: put in cal mode, start the trigger, stop the calibration and let the system compute pedestals, sigmas, etc...
int de10_silicon_base::SetCalibrationMode(uint32_t calEnIn){
  char readBack[LEN]="";
  calEn = (calEnIn&0x00000001)<<1;
  client_send("Calibrate");
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%d", calEn);
  client_send(c);
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::WriteCalibPar(){
  //char readBack[LEN]="";
  //client_send("WriteCalibPar");
  //client_receive(readBack);
  printf("%s) FIX ME: do not yet implemented in HPS\n", __METHOD_NAME__);
  return 0;
}

int de10_silicon_base::SaveCalibrations(){
  //char readBack[LEN]="";
  //client_send("SaveCalibrations");
  //client_receive(readBack);
  printf("%s) FIX ME: do not yet implemented in HPS\n", __METHOD_NAME__);
  return 0;
}

int de10_silicon_base::SetIntTriggerPeriod(uint32_t intTrigPeriodIn){
  char readBack[LEN]="";
  intTrigPeriod = intTrigPeriodIn&0xFFFFFFF0;
  client_send("intTriggerPeriod");
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%x", intTrigPeriod);
  client_send(c);
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::SelectTrigger(uint32_t intTrigEnIn){
  char readBack[LEN]="";
  intTrigEn = intTrigEnIn&0x00000001;
  client_send("selectTrigger");
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%d", intTrigEn);
  client_send(c);
  client_receive(readBack);
  return 0;
}

int de10_silicon_base::ConfigureTestUnit(uint32_t testUnitEnIn){
  char readBack[LEN]="";
  testUnitEn = (testUnitEnIn&0x00000001)<<1;
  client_send("configureTestUnit");
  //FIX ME: controllare ritorno chiamata sopra
  char c[sizeof (uint32_t) * 8 + 1];
  sprintf(c, "%d", testUnitEnIn);
  client_send(c);
  client_receive(readBack);
  return 0;
}
