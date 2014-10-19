/*
 * Service.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#include "Service.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

Service::Service()
	: curl_handle(NULL)
{
	curl_handle = curl_easy_init();
}

Service::~Service() {
	  /* cleanup curl stuff */
	  curl_easy_cleanup(curl_handle);
}

void Service::informPlantWatered(int duration) const
{
	  curl_global_init(CURL_GLOBAL_ALL);

	  char* url = new char[256];

	  snprintf(url, 256, "http://146.0.40.96/balconygardener/service.php?action=infoPlantWatered&duration=%d", duration);

	  /* set URL to get */
	  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	  /* no progress meter please */
	  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	  /* get it! */
	  curl_easy_perform(curl_handle);
}

void Service::sendSensorData(const std::string& sensorName, double value) const
{
	  curl_global_init(CURL_GLOBAL_ALL);

	  char* url = new char[256];

	  snprintf(url, 256, "http://146.0.40.96/balconygardener/service.php?action=insertSensorData&sensorName=%s&value=%.3f", sensorName.c_str(), value);

	  /* set URL to get */
	  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	  /* no progress meter please */
	  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	  /* get it! */
	  curl_easy_perform(curl_handle);
}

/*
void Service::writebuf(void *ptr){
	Service::duration = atoi((char*)ptr);

}
size_t Service::write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	int dumb = writebuf(*(*ptr));
	return 0;
}

*/
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}


//http://146.0.40.96/balconygardener/service.php?action=shouldWater

int Service::readServerData()
{

	CURL *curl;
	    FILE *fp;
	    CURLcode res;
	    char buf[5];
	    char url[] = "http://146.0.40.96/balconygardener/service.php?action=shouldWater";
	    char outfilename[FILENAME_MAX] = "out.txt";
	    curl = curl_easy_init();
	    if (curl) {
	        fp = fopen(outfilename,"wb");
	        curl_easy_setopt(curl, CURLOPT_URL, url);
	        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	        res = curl_easy_perform(curl);
	        curl_easy_cleanup(curl);
	        fclose(fp);

	    }
	    fp=fopen(outfilename, "r");
	    fread(buf,1,sizeof(buf),fp);
	    fclose(fp);

	    return atoi(buf);

}


void Service::acknowledgeWater() const
{
	  curl_global_init(CURL_GLOBAL_ALL);

	  char* url = new char[256];

	  snprintf(url, 256, "http://146.0.40.96/balconygardener/service.php?action=ackWater");

	  /* set URL to get */
	  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	  /* no progress meter please */
	  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	  /* get it! */
	  curl_easy_perform(curl_handle);
}
