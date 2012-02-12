#pragma once

#include <QDialog>
#include "ui_VehicleCostsWidget.h"
#include "Classes/xml/rapidxml.hpp"

struct tVehicleType;
using namespace rapidxml;

class CVehicleCostsWidget : public QDialog
{
	Q_OBJECT

public:
	CVehicleCostsWidget(std::vector<tVehicleType>& vehicles, QWidget* parent = 0);
	~CVehicleCostsWidget();

	inline std::vector<tVehicleType>& Vehicles() {return vehicles_;}
	static void ToXml(xml_document<>& doc, const std::vector<tVehicleType>& vehicles);
	static void FromXml(const xml_document<>& doc, std::vector<tVehicleType>& vehicles);

protected slots:
	void OnMem();
	void OnDel();
	void OnIndexChanged(int index);

protected:
	Ui::VehicleCostsWidget ui_;
	std::vector<tVehicleType>& vehicles_;
};

