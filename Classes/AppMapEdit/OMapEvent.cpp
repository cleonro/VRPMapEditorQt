#include "OMapEvent.h"
#include "MapOperationsGraphics.h"


OMapEvent::OMapEvent() : QEvent(QEvent::User)
{
	type_ = E_MAP_START_TIMER;
	erase_data_ = nullptr;
	data_ = NULL;
}


OMapEvent::~OMapEvent()
{
    if (type_ == E_MAP_TEXTURE_READY) {
        delete static_cast<OMapOperationsGraphics::tTextureData*>(data_);
    }
}
