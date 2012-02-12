#include "NodeViewDialog.h"
#include "VehicleCostsWidget.h"
#include "Classes/AppMapEdit/RoutesGenerator/ORoutesGenerator.h"
#include "Classes/xml/rapidxml_print.hpp"

CNodeViewDialog::CNodeViewDialog(QWidget* parent) : QDialog(parent)
{
	mTime = 0;
	mQuantity = 0;

	ui.setupUi(this);
	ui.toolButton->setEnabled(true);
}


CNodeViewDialog::~CNodeViewDialog()
{

}

void CNodeViewDialog::DataExchange(bool set)
{
	if(set) {
		ui.lineType->setText(mType);
		ui.lineName->setText(mName);
		ui.lineTime->setText(QString("%1").arg(mTime));
		ui.lineQuantity->setText(QString("%1").arg(mQuantity));
//		ui.lineVehicles->setText(mVehicles);
		
		ui.lineAccessibility->setText(QString("%1").arg(mAccessibility));
		ui.lineEditContracts->setText(QString("%1").arg(mContracts));
		ui.lineEditHabitants->setText(QString("%1").arg(mHabitants));
		ui.lineEditPrice->setText(QString("%1").arg(mPrice));

		if(mType != "Punct Pornire") {
			ui.toolButton->setEnabled(false);
		} else {
			ui.lineTime->setEnabled(false);
			ui.lineQuantity->setEnabled(false);
		}

		if(mType != "Client") {
			ui.lineEditHabitants->setEnabled(false);
			ui.lineEditContracts->setEnabled(false);
			ui.lineEditPrice->setEnabled(false);
		}

	} else {
		mType = ui.lineType->text();
		mName = ui.lineName->text();
		mTime = ui.lineTime->text().toFloat();
		mQuantity = ui.lineQuantity->text().toFloat();
	//	mVehicles = ui.lineVehicles->text();

		mAccessibility = ui.lineAccessibility->text().toFloat();
		mContracts = ui.lineEditContracts->text().toInt();
		mHabitants = ui.lineEditHabitants->text().toInt();
		mPrice = ui.lineEditPrice->text().toFloat();
	}
}

void CNodeViewDialog::ShowVehiclesWidget()
{
	std::vector<tVehicleType> vh;
	//transform a xml string (mVehicles) in a vector of vehicle informations
	vh.reserve(10);
	xml_document<> doc;
	std::string buffer =  mVehicles.toAscii().data();
	try {
		doc.parse<0>((char*)buffer.c_str());
		CVehicleCostsWidget::FromXml(doc, vh);
	} catch(parse_error er) {
		printf("\nVehicles information error\n");
	}
	
	CVehicleCostsWidget dlg(vh);
	if(dlg.exec() == QDialog::Accepted) {
		//transform a vector of vehicle informations in a xml string (mVehicles)
		doc.clear();
		CVehicleCostsWidget::ToXml(doc, vh);
		std::string str;
		rapidxml::print(std::back_inserter(str), doc, 0);
		mVehicles = str.c_str();
	}
}