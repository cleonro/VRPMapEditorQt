#include "VehicleCostsWidget.h"
#include "Classes/AppMapEdit/RoutesGenerator/ORoutesGenerator.h"
#include <sstream>

CVehicleCostsWidget::CVehicleCostsWidget(std::vector<tVehicleType>& vehicles, QWidget* parent) : 
	QDialog(parent), vehicles_(vehicles) 
{
	ui_.setupUi(this);
	for(int i = 0; i < vehicles_.size(); i++) {
		tVehicleType t = vehicles_[i];
		ui_.combo->addItem(t.name_.c_str());

// 		ui_.lineTip->setText(t.name_.c_str());
// 		ui_.lineCap->setText(QString("%1").arg(t.capacity_));
// 		ui_.lineNrVeh->setText(QString("%1").arg(t.number_));
// 
// 		ui_.lineCostComb->setText(QString("%1").arg(t.cost_gas_));
// 		ui_.lineCostMent->setText(QString("%1").arg(t.cost_gas_idle_));
// 		ui_.lineCostEquip->setText(QString("%1").arg(t.cost_equip_));
// 		ui_.lineCostSal->setText(QString("%1").arg(t.cost_sal_));
// 		ui_.lineCostStat->setText(QString("%1").arg(t.cost_maint_));
	}
	//ui_.combo->setCurrentIndex(0);
}

CVehicleCostsWidget::~CVehicleCostsWidget()
{

}

void CVehicleCostsWidget::OnMem()
{
	QString name = ui_.lineTip->text();
	QString capac = ui_.lineCap->text();
	QString nr_veh = ui_.lineNrVeh->text();
	if(name.isEmpty() || capac.isEmpty() || nr_veh.isEmpty()) {
		return;//a veh type must have name, capacity, number of veh.
	}
	QString cost_comb = ui_.lineCostComb->text();
	QString cost_ment = ui_.lineCostMent->text();
	QString cost_equip = ui_.lineCostEquip->text();
	QString cost_sal = ui_.lineCostSal->text();
	QString cost_stat = ui_.lineCostStat->text();
	
	tVehicleType t;
	t.name_ = name.toAscii().constData();
	t.capacity_ = capac.toInt();
	t.number_ = nr_veh.toInt();
	
	t.cost_equip_ = cost_equip.toFloat();
	t.cost_gas_ = cost_comb.toFloat();
	t.cost_gas_idle_ = cost_stat.toFloat();
	t.cost_sal_ = cost_sal.toFloat();
	t.cost_maint_ = cost_ment.toFloat();

	if(t.number_ <= 0 || t.capacity_ <= 0 
		|| t.cost_equip_ < 0 || t.cost_gas_ < 0 
		|| t.cost_gas_idle_ < 0
		|| t.cost_sal_ < 0 || t.cost_maint_ < 0) {
			return;//vehicles number and capacity must be bigger than zero
					//every cost must be positive
	}

	//if vehicle name exists, replace its characteristics
	for(int i = 0; i < vehicles_.size(); i++) {
		if(t.name_ == vehicles_[i].name_) {
			vehicles_[i] = t;
			ui_.combo->setCurrentIndex(i);
			return;
		}
	}

	vehicles_.push_back(t);
	ui_.combo->addItem(name);
	ui_.combo->setCurrentIndex(vehicles_.size() - 1);
}

void CVehicleCostsWidget::OnDel()
{
	int i = ui_.combo->currentIndex();
	if(i < 0 || vehicles_.size() < 0) {
		return;
	}
// 	std::string name = ui_.combo->currentText().toAscii().constData();
// 	for(int i = 0; i < vehicles_.size(); i++) {
// 		if(name == vehicles_[i].name_) {
			vehicles_.erase(vehicles_.begin() + i);
			ui_.combo->removeItem(ui_.combo->currentIndex());
			return;
// 		}
// 	}
}

void CVehicleCostsWidget::OnIndexChanged(int index)
{
	int i = index;
// 	std::string name = ui_.combo->currentText().toAscii().constData();
// 	for(int i = 0; i < vehicles_.size(); i++) {
// 		if(name == vehicles_[i].name_) {
			
			tVehicleType t =  vehicles_[i];
			
			ui_.lineTip->setText(t.name_.c_str());
			ui_.lineCap->setText(QString("%1").arg(t.capacity_));
			ui_.lineNrVeh->setText(QString("%1").arg(t.number_));
			
			ui_.lineCostComb->setText(QString("%1").arg(t.cost_gas_));
			ui_.lineCostMent->setText(QString("%1").arg(t.cost_maint_));
			ui_.lineCostEquip->setText(QString("%1").arg(t.cost_equip_));
			ui_.lineCostSal->setText(QString("%1").arg(t.cost_sal_));
			ui_.lineCostStat->setText(QString("%1").arg(t.cost_gas_idle_));

			return;
// 		}
// 	}
}

void CVehicleCostsWidget::ToXml(xml_document<>& doc, const std::vector<tVehicleType>& vehicles)
{
	char *c;
	for(int i = 0; i < vehicles.size(); i++) {
		tVehicleType t = vehicles[i];
		xml_node<>* vehicle_node = doc.allocate_node(node_element, "Vehicle");	
		
		c = doc.allocate_string(t.name_.c_str(), t.name_.size() + 1);
		xml_node<>* name_node = doc.allocate_node(node_element, "Name", c);
		std::string tstr;
		std::ostringstream otstr;
		
		otstr<<t.capacity_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cap_node = doc.allocate_node(node_element, "Capacity", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.number_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* nb_node = doc.allocate_node(node_element, "Number", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.cost_equip_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cost_equip_node = doc.allocate_node(node_element, "Cost_Equip", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.cost_gas_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cost_gas_node = doc.allocate_node(node_element, "Cost_Gas", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.cost_gas_idle_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cost_gas_idle_node = doc.allocate_node(node_element, "Cost_Gas_Idle", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.cost_maint_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cost_maint_node = doc.allocate_node(node_element, "Cost_Maint", c);
		otstr.clear();
		otstr.str("");

		otstr<<t.cost_sal_;
		tstr = otstr.str();
		c = doc.allocate_string(tstr.c_str(), tstr.size() + 1);
		xml_node<>* cost_sal_node = doc.allocate_node(node_element, "Cost_Sal", c);
		otstr.clear();
		otstr.str("");

		vehicle_node->append_node(name_node);
		vehicle_node->append_node(cap_node);
		vehicle_node->append_node(nb_node);
		vehicle_node->append_node(cost_equip_node);
		vehicle_node->append_node(cost_gas_node);
		vehicle_node->append_node(cost_gas_idle_node);
		vehicle_node->append_node(cost_maint_node);
		vehicle_node->append_node(cost_sal_node);

		doc.append_node(vehicle_node);

	}
}

void CVehicleCostsWidget::FromXml(const xml_document<>& doc, std::vector<tVehicleType>& vehicles)
{
	xml_node<>* vehicle_node = doc.first_node("Vehicle");
	while(vehicle_node != NULL) {
		tVehicleType t;
		
		xml_node<>* name_node = vehicle_node->first_node("Name");
		xml_node<>* cap_node = vehicle_node->first_node("Capacity");
		xml_node<>* nb_node = vehicle_node->first_node("Number");
		xml_node<>* cost_equip_node = vehicle_node->first_node("Cost_Equip");
		xml_node<>* cost_gas_node = vehicle_node->first_node("Cost_Gas");
		xml_node<>* cost_gas_idle_node = vehicle_node->first_node("Cost_Gas_Idle");
		xml_node<>* cost_maint_node = vehicle_node->first_node("Cost_Maint");
		xml_node<>* cost_sal_node = vehicle_node->first_node("Cost_Sal");
		
		t.name_ = name_node->value();
		t.capacity_ = atoi(cap_node->value());
		t.number_ = atoi(nb_node->value());
		t.cost_equip_ = atof(cost_equip_node->value());
		t.cost_gas_ = atof(cost_gas_node->value());
		t.cost_gas_idle_ = atof(cost_gas_idle_node->value());
		t.cost_maint_ = atof(cost_maint_node->value());
		t.cost_sal_ = atof(cost_sal_node->value());

		vehicles.push_back(t);

		vehicle_node = vehicle_node->next_sibling("Vehicle");
	}
}