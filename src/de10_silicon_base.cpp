﻿#include "de10_silicon_base.h"
#include "utility.h"
#include <unistd.h>

uint32_t okVal = 0xb01af1ca;
uint32_t badVal = 0x000cacca;

de10_silicon_base::de10_silicon_base(const char *address, int port, paperoConfig::configParams* params, int _calMode, int _intTrig, int verb):tcpclient(address, port, verb){
  uint32_t cmdLenReply = 1;

  
  //Copy the parameters from the config file
  detId         = params->id  & 0x0000FFFF;
  cmdlenght     = params->cmdLen;
  testUnitCfg   = (uint32_t)params->testUnitCfg & 0x00000003;
  testUnitEn    = (uint32_t)params->testUnitEn & 0x00000001;
  hkEn          = (uint32_t)params->hkEn & 0x00000001;
  dataEn        = (uint32_t)params->dataEn & 0x00000001;
  pktLen        = params->pktLen;
  intTrigPeriod = params->intTrigPeriod & 0xFFFFFFF0;
  feClkDuty     = (uint32_t)params->feClkDuty & 0x0000FFFF;
  feClkDiv      = (uint32_t)params->feClkDiv & 0x0000FFFF;
  adcClkDuty    = (uint32_t)params->adcClkDuty & 0x0000FFFF;
  adcClkDiv     = (uint32_t)params->adcClkDiv & 0x0000FFFF;
  trig2Hold     = (uint32_t)params->trig2Hold & 0x0000FFFF;
  ideTest       = (uint32_t)params->ideTest & 0x00000001;
  adcFast       = (uint32_t)params->adcFast & 0x00000001;
  calEn         = (uint32_t)_calMode & 0x00000001;
  intTrigEn     = (uint32_t)_intTrig & 0x00000001;
  busyLen       = (uint32_t)params->busyLen & 0x0000FFFF;
  adcDelay      = (uint32_t)params->adcDelay & 0x0000FFFF;

  //Send command length and set it with the loopback value
  //Cannot use specific function since it is the first time setting the length
  SendInt(cmdlenght);
  ReceiveInt(cmdLenReply);
  //let's set as cmd lenght not the one passed but the one received back
  //FIXME: add a check that they are the same
  cmdlenght=cmdLenReply;//in number of char
  printf("%s) Set Cmd Lenght to reply: %d\n", __METHOD_NAME__, cmdLenReply);  

  //
  ConfigureTestUnit(testUnitCfg);
  SetIntTriggerPeriod(intTrigPeriod);
  SetCalibrationMode(calEn);
  SelectTrigger(intTrigEn);
  SetTrig2Hold(trig2Hold);

  //Make sure system is NOT running
  SetMode(0);

  if (verbosity>0) {
    printf("%s) de10 silicon created\n", __METHOD_NAME__);
  }
}

//--------------------------------------------------------------

de10_silicon_base::~de10_silicon_base(){
}

//--------------------------------------------------------------

void de10_silicon_base::SetCmdLenght(int lenght) {
  
  if (SendCmd("setCmdLenght")>0) {
    SendInt((uint32_t)lenght);
  }

  uint32_t reply = 0;
  ReceiveInt(reply);
  //let's set as cmd lenght not the one passed but the one received back (hoping they are equal)
  cmdlenght=reply;//in number of char
  printf("%s) Set Cmd Lenght to reply: %d\n", __METHOD_NAME__, reply);

  return;
}

//--------------------------------------------------------------
int de10_silicon_base::readReg(int regAddr, uint32_t &regCont){

  int ret=0;
  if (SendCmd("readReg")>0) {
    SendInt((uint32_t)regAddr);
  }
  else {
    ret = 1;
  }
  
  if (ReceiveInt(regCont)<=0) ret = 1;

  if (verbosity>0) {
    printf("%s) Read: %d\n", __METHOD_NAME__, regCont);
  }
  
  return ret;
}

//FIX ME: use the proper functions or the 2D array to retrieve configurations
int de10_silicon_base::Init() {

  int ret=0;
  uint32_t regContent = 1;
  uint32_t reply = 1;

  if (verbosity>0) {
    printf("%s) initializing (reset everything)\n", __METHOD_NAME__);
  }
  
  if (SendCmd("init")>0) {
    //Register 1
    regContent = (testUnitCfg << 8) | (hkEn << 6) \
      | (testUnitEn << 1) | dataEn;
    SendInt(regContent);
    
    //Register 2
    regContent = intTrigPeriod | (calEn<<1) | intTrigEn;
    SendInt(regContent);
    
    //Register 3
    regContent = detId;
    SendInt(regContent);
    
    //Register 4
    regContent = pktLen;
    SendInt(regContent);
    
    //Register 5
    regContent = (feClkDuty << 16) | feClkDiv;
    SendInt(regContent);
    
    //Register 6
    regContent = (adcClkDuty << 16) | adcClkDiv;
    SendInt(regContent);
    
    //Register 7
    regContent  = adcFast << 24 | ideTest << 19 | trig2Hold;
    SendInt(regContent);

    //Register 8
    regContent  = busyLen << 16 | adcDelay;
    SendInt(regContent);
  }
  else {
    ret = 1;
  }
  
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }
  
  return ret;
}

int de10_silicon_base::SetTrig2Hold(uint32_t delayIn){
  int ret=0;
  uint32_t reply = 1;
  trig2Hold = (delayIn & 0x0000FFFF);
  if (SendCmd("setDelay")>0) {
    SendInt(trig2Hold);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }
  return ret;
}

int de10_silicon_base::SetMode(uint8_t modeIn) {
  int ret=0;
  uint32_t reply = 1;
  mode=(modeIn << 4)&0x00000010;
  if (SendCmd("setMode")>0) {
    SendInt(mode);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>-1) {//FIX ME
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }  
  return ret;
}

int de10_silicon_base::GetEventNumber() {
  int ret=0;
  if (SendCmd("getEventNumber")<=0) ret = 1;
  uint32_t exttrigcount = 0;
  ReceiveInt(exttrigcount);
  uint32_t inttrigcount = 0;
  ReceiveInt(inttrigcount);
  if (verbosity>0) {
    printf("%s) event number: %d %d\n", __METHOD_NAME__, exttrigcount, inttrigcount);
  }
  return ret;
}

int de10_silicon_base::EventReset() {
  int ret = 0;
  uint32_t reply = 1;
  if (SendCmd("eventReset")<=0) ret = 1;
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) Resetting events (reinitialize): %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }  
  return ret;
}

void de10_silicon_base::AskEvent(){
  SendCmd("getEvent");
}

//FIX ME: this doesn't reply as the others (i.e. 0=OK), but with the size it did read 
int de10_silicon_base::GetEvent(std::vector<uint32_t>& evt, uint32_t& evtLen){
  //Get the event from HPS and loop here until all data are read
  uint32_t evtRead = 0;
  ReceiveInt(evtLen);//in int units
  //  printf("%s) Event Lenght = %u\n", __METHOD_NAME__, evtLen);
  if (evt.size()<evtLen) evt.resize(evtLen);
  evtLen*=sizeof(uint32_t);//in byte units
  while (evtRead < evtLen) {
    //    printf("%s) %d %d %d\n", __METHOD_NAME__, evtRead/sizeof(uint32_t), evtLen, evtRead);
    evtRead += Receive(&evt[evtRead/sizeof(uint32_t)], evtLen-evtRead);
  }

  // if (evtLen) {
  //   printf("%s) %d %d %d\n", __METHOD_NAME__, evtRead/sizeof(uint32_t), evtLen, evtRead);
  //   printf("%s) Length: %d\n",__METHOD_NAME__, evtLen);
  //   for (uint32_t jj=0; jj<(evtLen/4); jj++) {
  //     printf("%s)******%d %08x\n",__METHOD_NAME__, jj, evt[jj]);
  //   }
  //  }
  return evtRead;
}

//TO DO: there will be another method, in future to really calibrate: put in cal mode, start the trigger, stop the calibration and let the system compute pedestals, sigmas, etc...
int de10_silicon_base::SetCalibrationMode(uint32_t calEnIn){
  int ret = 0;
  uint32_t reply = 1;
  calEn = calEnIn & 0x00000001;
  if (SendCmd("calibrate")>0){
    SendInt(calEn<<1);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) Resetting events (reinitialize): %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }  
  return ret;
}

int de10_silicon_base::WriteCalibPar(){
  //char readBack[LEN]="";
  //client_send("WriteCalibPar");
  //client_receive(readBack);
  printf("%s) FIX ME: do not yet implemented in HPS\n", __METHOD_NAME__);
  return 1;
}

int de10_silicon_base::SaveCalibrations(){
  //char readBack[LEN]="";
  //client_send("SaveCalibrations");
  //client_receive(readBack);
  printf("%s) FIX ME: do not yet implemented in HPS\n", __METHOD_NAME__);
  return 1;
}

int de10_silicon_base::SetIntTriggerPeriod(uint32_t intTrigPeriodIn){
  int ret=0;
  uint32_t reply = 1;
  intTrigPeriod = intTrigPeriodIn & 0xFFFFFFF0;
  if (SendCmd("intTrigPeriod")>0) {
    SendInt(intTrigPeriod);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }
  return ret;
}

int de10_silicon_base::SelectTrigger(uint32_t intTrigEnIn){
  int ret=0;
  uint32_t reply = 1;
  intTrigEn = intTrigEnIn & 0x00000001;
  if (SendCmd("selectTrigger")>0) {
    SendInt(intTrigEn);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }
  return ret;
}

int de10_silicon_base::ConfigureTestUnit(uint32_t testUnitEnIn){
  int ret=0;
  uint32_t reply = 1;
  testUnitEn = testUnitEnIn & 0x00000001;
  if (SendCmd("configTestUnit")>0) {
    SendInt(testUnitEn<<1);
  }
  else {
    ret = 1;
  }
  ReceiveInt(reply);
  if (verbosity>0) {
    printf("%s) reply: %s\n", __METHOD_NAME__, reply==okVal?"ok":"ko");
  }
  return ret;
}
