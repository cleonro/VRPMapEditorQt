#pragma once

#include <windows.h>
//#include <afxwin.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>
#include "GraphMap/GraphMap.h"

#include "../../GLWidget.h"


#include <QDataStream>

#define SIZEMAP 512
#define SIZEBUFF 512000

class OMapOperations : public QObject
{
	Q_OBJECT
public:
	
	friend QDataStream& operator<<(QDataStream& ar, const OMapOperations& map_op);
	friend QDataStream& operator>>(QDataStream& ar, OMapOperations& map_op);
	void ExportGraphToXml(char* filename);
	void ImportGraphFromXml(char* filename);
	static void ImportGraphFromXmlThread(void* data);

	void SetView(CGLWidget* glview);

signals:
	void mapChanged();

protected:

	OMapOperations();
	~OMapOperations();

	//coordinate transformations
	void FromScreenCoordToWorldCoord(double xscreen, double yscreen, double& xworld, double& yworld);
	void FromWorldCoordToScreenCoord(double xworld, double yworld, double& xscreen, double& yscreen);
	void FromWorldCoordToLatLong(double xworld, double yworld, double& latitude, double& longitude);
	void FromLatLongToWorldCoord(double latitude, double longitude, double &xworld, double &yworld);

	//map informations
	int zoom_;
	char maptype_[11];
	double center_latitude_;
	double center_longitude_;
	//world coordinates of the center
	double center_xworld_;
	double center_yworld_;

	//graphical view
	CGLWidget* view_;

public:
	//graph map;
	OGraphMap graph_;

protected:
	OGraphNode* node_[2];	
	int index_[2];
	int selected_;//shows how many nodes are selected on the map (two at most)
	uintptr_t thread_importxml_;
	
	//return the index of a graph node, close to the point (xworld, yworld) 
	int SearchScreenCoordinatesInGraphNodes(double xscreen, double yscreen);
	//return the index of a graph route, close to the point(xworld, yworld)
	int SearchScreenCoordinatesInGraphRoutes(double xscreen, double yscreen);

	
};
