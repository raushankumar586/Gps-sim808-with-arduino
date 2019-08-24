#ifndef __HANDLE_GPS__
#define __HANDLE_GPS__
#include <Arduino.h>

#define TIMEOUT 4000 // 4 sec
#define ZERO 0
#define MAX_GPS_BUFFER_SIZE 100
class HandleGps
{
public:
    
    HandleGps()
    {
    }
    bool checkCmd(const char *cmd, const char *res, unsigned int timeout = TIMEOUT);
    bool SendCmd(const char *cmd, unsigned int timeout);
    bool CheckRes(const char *res, unsigned int timeout);
	bool Init();
	bool Attach();
	bool Detach();
	bool GetData();
	bool LoadData();
	bool IsValidData(char *data);
	bool parseGprmcData(char *data);
	bool parseGpgllData(char *data);
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
