#pragma once

#include <QEvent>

class OMapEvent : public QEvent
{
public:
	enum eMapEvents {
		E_MAP_START_TIMER = 0,
		E_MAP_STOP_TIMER,
		E_MAP_TEXTURE_READY
	};
public:
	OMapEvent();
	~OMapEvent();
	inline eMapEvents&	Type() {return type_;}
	inline void*&		Data() {return data_;}
	inline bool			EraseData() {return erase_data_;}
protected:
	eMapEvents	type_;
	void*		data_;
	bool*		erase_data_;//shows if received data must be deleted
};

