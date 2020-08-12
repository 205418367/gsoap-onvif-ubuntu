#ifndef __ONVIFDEVICE_H
#define __ONVIFDEVICE_H
#pragma once
#include <iostream>
#include <algorithm>
#include <openssl/rsa.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "soapPrint.h"

//控制方位
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define LEFTUP 4
#define LEFTDOWN 5
#define RIGHTUP 6
#define RIGHTDOWN 7
#define ZOOMIN 8
#define ZOOMOUT 9

//控制速度
#define LOWER 1
#define LOW 2
#define MEDIUM 3
#define FAST 4
#define FASTER 5

//预置点位
#define GOTO 0
#define REMOVE 1

#define MAX_HOSTNAME_LEN 128
#define MAX_LOGMSG_LEN 256 

#define SOAP_TO         "urn:schemas-xmlsoap-org:ws:2005:04:discovery"
#define SOAP_ACTION     "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe"
#define SOAP_MCAST_ADDR "soap.udp://239.255.255.250:3702"                       // onvif规定的组播地址
#define SOAP_ITEM       ""                                                      // 寻找的设备范围
#define SOAP_TYPES      "dn:NetworkVideoTransmitter"                            // 寻找的设备类型
#define GET 3

typedef struct presetsinfo {
    std::string token;
    std::string name;
    float p;
    float t;
    float z;
} PreInfo;

typedef struct imagingsetting {
    int BacklightCompensationMode;
    float Brightness;
    float ColorSaturation;
    float Contrast;
    int ExposureMode;
    float ExposureTime;
    int AutoFocusMode;
    float Sharpness;
    int WhiteBalanceMode;
} ImagingSet;

using namespace std;
class OnvifDevice{
public:
  OnvifDevice(string url,string username,string passwd);
  ~OnvifDevice();
  int getMediaUrl(string& mediaAddr);
  int getProfile(string& profileToken);
  int getPTZUrl(string& PTZAddr);
  int GetVideoSources(string& videoSourceToken);
  int GetSnapshotUri(string& shotUri);

  //功能: 获取设备时间
  int getDateTime(int& year, int& month, int& day,
                  int& hour, int& minute, int& second);
  //功能: 设置设备时间
  int setDateTime();
  //功能: 获取设备信息
  int getDeviceInformation(string& Manufacturer,string& Model,
           string& FirmwareVersion,string& SerialNumber,string& HardwareId);
  //功能: 获取RTSP地址
  int getRTSPUrl(string& rtspUrl);
  //功能: 获取抓图地址
  int getIMAGEUrl(string& imageUrl);

  //功能：控制相机持续转动; 停止相机需要调用ptzContinuousStop接口
  // speed:LOWER LOW MEDIUM FAST FASTER
  // command:UP DOWN LEFT RIGHT LEFTUP LEFTDOWN RIGHTUP RIGHTDOWN ZOOMIN ZOOMOUT
  int ptzContinuousMove(int command,int speed);
  int ptzContinuousStop();
  //功能：控制相机转动一定角度,转动完毕会自动停止
  // command:UP DOWN LEFT RIGHT LEFTUP LEFTDOWN RIGHTUP RIGHTDOWN ZOOMIN ZOOMOUT
  int ptzRelativeMove(int command);
  
  //功能：控制预置位; command: GOTO REMOVE presettoken:1~300
  int ptzPreset(int command, string presettoken);
  //功能：根据预置点token查询name和position
  int GetOnePresets(const string& pretoken,float& x,float& y,float& z,string& prename);
  //功能：查询所有已设置的预置点token、name和ptz值
  int GetAllPresets(vector<PreInfo>& allpresets);
  //功能：设置预置点位。presetToken:1~300 ; presetName:name
  int SetPreset(string presetToken,string presetName);
  //功能：Continuous Focus Move; -1< speed <1
  int ContinuousFocusMove(float speed);
  //功能：Continuous Focus Stop
  int ContinuousFocusStop();
  //功能：复位
  int GotoHomePosition();
  //功能：设置ImagingSettings
  int SetImagingSettings();
  //功能：获取ImagingSettings
  int GetImagingSettings(ImagingSet& imageSet);
private:
  string m_deviceurl;
  string m_username;
  string m_passwd;
  string mediaAddr;
  string PTZAddr;
  string imageUrl;
  string strProfileToken;
  string videoSourceToken;

  float Brightness = 50.0;
  float ColorSaturation = 35.0;
  float Contrast = 25.0;
  bool ForcePersistence = true; 
  float ExposureTime = 10000.0;
};
//功能: 发现设备获取设备地址
void detectDevice(vector<string>& vecDevAddr);
#endif
