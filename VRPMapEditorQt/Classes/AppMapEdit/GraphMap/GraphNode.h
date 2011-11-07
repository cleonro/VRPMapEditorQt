#pragma once

//#include <windows.h>
//#include <afxwin.h>

#include <vector>
#include <QDataStream>
#include "../../xml/rapidxml.hpp"

//start node -> vehicle type information 
// struct tVehicleType
// {
// 	char type_[5];
// 	float capacity_;
// };

struct tNodeInf
{
	//char name_[20];
	float waiting_time_;
	float quantity_;
};

class OGraphNode
{
public:

	friend QDataStream& operator<<(QDataStream& ar, const OGraphNode& node);
	friend QDataStream& operator>>(QDataStream& ar, OGraphNode& node);

	enum eNodeType {
		N_START = 0,
		N_CLIENT,
		N_DEPOT,
		N_TRANSIT
	};

	OGraphNode();
	~OGraphNode();

	virtual void GetCoordinates(double& lat, double& longit);
	virtual void SetCoordinates(double lat, double longit);
	inline eNodeType GetType() {return type_;}
	inline void SetType(eNodeType type) {type_ = type;}
	inline bool IsSelected() {return selected_;}
	inline void Select(bool slct) {selected_ = slct;}
	
	//inline std::vector<tVehicleType>* Vehicles() {return &vehicles_;}
	void SetNodeInf(tNodeInf node_info);
	tNodeInf GetNodeInf();
	inline char* GetName() {return name_;}
	inline char* Vehicles() {return vehicles_;}

	virtual void Draw(float transparency = 0.7);

	//special informations
	inline float& Accesibility() {return accesib_index_;}
	inline int& Locals() {return locals_;}
	inline int& Contracts() {return contracts_;}
	inline float& Price() {return price_;}
	inline const float& Accesibility() const {return accesib_index_;}
	inline const int& Locals() const {return locals_;}
	inline const int& Contracts() const {return contracts_;}
	inline const float& Price() const {return price_;}

	//export to xml
	void ToXml(rapidxml::xml_document<>& doc, rapidxml::xml_node<>*& node);
	//import from xml
	void FromXml(rapidxml::xml_node<>* node);

protected:
	double latitude_;
	double longitude_;
	eNodeType type_;
	bool selected_;

	//node information
	char name_[20];
	//client(depot/transit) type node information
	float waiting_time_;// waiting time in minutes, can be also used in other node types
	float quantity_;//colected quantity in kilograms (for a week) for a client node, 
					//or capacity for a depot/transit node
	//start node information
	//std::vector<tVehicleType> vehicles_;
	char vehicles_[200];
	
	//node "special" informations
	float accesib_index_;//accesibility index
	int locals_;//number of locals
	int contracts_;//number of contracts
	float price_;//price of a contract (lei/person/month)
};

