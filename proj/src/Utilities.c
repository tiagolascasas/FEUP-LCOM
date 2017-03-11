#include "Utilities.h"
#include "RTC.h"
#include "i8042.h"

int unsubscribe_all()
{
	kbd_writeCMD(RESET_AND_ENABLE);

	if (timer_unsubscribe_int() || kbd_unsubscribe_int() || mouse_unsubscribe_int())
	{
		printf("Error: failure to unsubscribe peripherals\n");
		return 1;
	}
	else return 0;
}

char* makePath(char* path, char* file)
{
	char* formattedPath = (char*) calloc(strlen(path) - strlen("/asterinix"), sizeof(char));
	memcpy(formattedPath, path, strlen(path) - strlen("/asterinix"));

	char* fullPath;
	fullPath = (char*) calloc(strlen(formattedPath) + strlen(file) + 1, sizeof(char));

	if (fullPath != NULL)
	{
		strcat(fullPath, formattedPath);
		strcat(fullPath, file);
		return fullPath;
	}
	else return NULL;
}

time_t getCurrentTime()
{
	char date[6];
	rtc_get_date_and_time(date);

	time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = gmtime(&rawtime);
    timeinfo->tm_year = date[0] + CENTURY;
    timeinfo->tm_mon = date[1] - MONTH_CORRECTION;
    timeinfo->tm_mday = date[2];
    timeinfo->tm_hour = date[3];
    timeinfo->tm_min = date[4];
    timeinfo->tm_sec = date[5];
    timeinfo->tm_isdst = 0;

    time_t timestamp = mktime(timeinfo);

    return timestamp;
}

char* getCurrentTimeStr()
{
	char date[6];
	rtc_get_date_and_time(date);

	time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = gmtime(&rawtime);
    timeinfo->tm_year = date[0] + CENTURY;
    timeinfo->tm_mon = date[1] - MONTH_CORRECTION;
    timeinfo->tm_mday = date[2];
    timeinfo->tm_hour = date[3];
    timeinfo->tm_min = date[4];
    timeinfo->tm_sec = date[5];
    timeinfo->tm_isdst = 0;

	return asctime(timeinfo);
}
