#ifndef __HANDLE_GPS__
#define __HANDLE_GPS__
#include <Arduino.h>
#define TIMEOUT 4000 // 4 sec
#define ZERO 0

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
	void GetData();


    
    struct gspdata{
		uint16_t year;
		uint8_t month;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
		uint8_t centisecond;
		float lat;
		float lon;
		float speed_kph;
		float heading;
		float altitude;
	}GPSdata;

};

#endif