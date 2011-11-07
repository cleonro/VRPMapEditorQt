#include "OMapEvent.h"


OMapEvent::OMapEvent() : QEvent(QEvent::User)
{
	erase_data_ = false;
	data_ = NULL;
}


OMapEvent::~OMapEvent()
{

}
