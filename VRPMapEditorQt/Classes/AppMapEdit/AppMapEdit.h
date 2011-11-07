#pragma once

#include "..\AppBaseState.h"
#include "MapOperationsInput.h"

//class CVRPMapEditorView;

class OAppMapEdit : public OAppBaseState
{
	friend class OAppManager;

public:
	virtual void Init(void* data);
	virtual void Update(void* data = NULL);
	virtual void Update2(void* data = NULL);
	virtual void Draw(float transparency = 0.7);

	virtual void ReDraw();

	virtual void* GetDataForInput();
protected:
	static OAppMapEdit& GetInstance();
	OAppMapEdit(void);
	~OAppMapEdit(void);

	void* view_;
};
