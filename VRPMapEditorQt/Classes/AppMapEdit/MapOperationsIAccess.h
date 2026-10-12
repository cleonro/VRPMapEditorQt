#ifndef _MAP_OP_IACCESS_H_
#define _MAP_OP_IACCESS_H_

#include "MapOperations.h"

class OMapOperationsIAccess : public OMapOperations
{
	Q_OBJECT
public:

protected:
	OMapOperationsIAccess();
	~OMapOperationsIAccess();


	std::vector<double>* path_;
	OGraphRoute* route_;

	QByteArray FetchUrl(const char* address);
	bool FindRoute(double latitude0, double longitude0, double latitude1, double longitude1);
	bool FindRoute(int i, int j);
	bool ParseDirectionsResponseXML(QByteArray response);
	
	//polyline decoder 
	static bool PolylineDecoder(char* encoded, std::vector<double>* polyline);

	//polyline encoder
	static void EncodeSignedNumber(int num, std::string& str);
	static void EncodeNumber(int num, std::string& str);
	static void PolylineEncoder(std::string& str, std::vector<double>* polyline);
};

#endif
