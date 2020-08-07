#include "onvifdevice.h"
#include <unistd.h>

int main(){ 
    //vector<string> addr;
    //detectDevice(addr);
    //for(vector<string>::iterator it = addr.begin(); it != addr.end(); ++it){
        //cout<<"####"<<*it<<"####"<<endl;
        //string::size_type idx = (*it).find("192.168.8.220");
        //if(idx == string::npos)
            //continue;

        //cout<<"####"<<*it<<"####"<<endl;
        string it = "http://192.168.8.220/onvif/device_service http://[fe80::6a6d:bcff:fe48:2025]/onvif/device_service";
        OnvifDevice onvifDevice(it, "admin", "leinao123");
        //string rtspUrl;
        //onvifDevice.getProfile(rtspUrl);
        //cout<<"rtspUrl :"<<rtspUrl<<endl;
        //onvifDevice.ptzContinuousMove(LEFT,LOWER);
        //onvifDevice.ptzContinuousStop();
	//onvifDevice.ptzRelativeMove(LEFT);

        //sleep(3);
	//onvifDevice.ptzPreset(SET,"1");
	//onvifDevice.ptzPreset(GOTO,"1");
        
        //onvifDevice.SetPreset("1","test");
        //float x,y,z;string prename;
        //onvifDevice.GetOnePresets("3",x,y,z,prename);
        //cout<<"x :"<<x<<endl;

        vector<PreInfo> allpresets;
        onvifDevice.GetAllPresets(allpresets);
        for (int i=0;i<allpresets.size();i++){
            PreInfo preset = allpresets[i];
	    cout<<"name :"<<preset.name<<endl;
            cout<<"token :"<<preset.token<<endl;
            cout<<"p :"<<preset.p<<endl;
            cout<<"t :"<<preset.t<<endl;
            cout<<"z :"<<preset.z<<endl;
        }
    return 0;
}
