#ifndef _MAP_OP_IACCESS_H_
#define _MAP_OP_IACCESS_H_

#include "MapOperations.h"
#include "../Network/curl/curl.h"

class OMapOperationsIAccess : public OMapOperations
{
	Q_OBJECT
public:

protected:
	OMapOperationsIAccess();
	~OMapOperationsIAccess();

	char* buffer_;
	static int size_b_;

	std::vector<double>* path_;
	OGraphRoute* route_;

	//curl
	CURL *curl;

	//write data received by curl calls in buffer_
	static unsigned int write_tc(char *in, unsigned int size, unsigned int nmemb, char *out);
	bool CallCurl(char addr[]);
	bool FindRoute(double latitude0, double longitude0, double latitude1, double longitude1);
	bool FindRoute(int i, int j);
	bool ParseDirectionsResponseXML();
	
	//polyline decoder 
	static bool PolylineDecoder(char* encoded, std::vector<double>* polyline);

	//polyline encoder
	static void EncodeSignedNumber(int num, std::string& str);
	static void EncodeNumber(int num, std::string& str);
	static void PolylineEncoder(std::string& str, std::vector<double>* polyline);
};

#endif
