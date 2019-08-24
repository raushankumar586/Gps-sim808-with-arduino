#ifndef __HANDLE_GPS__
#define __HANDLE_GPS__
#include <Arduino.h>

#define MAX_GPS_BUFFER_SIZE 100
class HandleGps
{
public:
    
    HandleGps()
    {
    }
    bool Init();
	bool Attach();
	bool Detach();
	bool GetData();
	bool LoadData();
	bool IsValidData(char *data);
	bool parseGprmcData(char *data);
	bool parseGpgllData(char *data);
	void Setup();
	void Print();
	byte bufferIndex=0;
	byte bufferGps[MAX_GPS_BUFFER_SIZE];
    // const char *GpggaToken = "$GPGGA";
    const char *GpggaToken = "$GPGLL";
    
    struct gspdata{
		float lat;
		float lon;
	} GpsData;

};

#endif
