#pragma once


#include "VariousObjects.h"
#include "GLCamera.h"

class OAppBaseState
{

	friend class OAppManager;

public:
	

	virtual void Init(void* data);
	virtual void Update(void* data = NULL);
	virtual void Update2(void* data = NULL);
	virtual void Draw();

	virtual void* GetDataForInput();

	inline OGL3DCamera& GetCamera() {return camera_;}

protected:

	static OAppBaseState& GetInstance();

	OAppBaseState();
	~OAppBaseState();

	OGL3DCamera camera_;
};


#define APPMNGR OAppManager::GetInstance()

class OAppManager
{
public:

	enum eAppStates {
		APP_BASE_STATE = 0,
		APP_MAP_EDIT
	};

	//virtual void Update(void* data = NULL);
	void ChangeState(eAppStates);
	OAppBaseState* GetState();
	static OAppManager& GetInstance();
	inline int GetStateId() {return app_state_id_;}
	inline void* GetDataForInput() { if(app_state_) return app_state_->GetDataForInput();
									else return NULL;}
protected:
	OAppManager();
	~OAppManager();
	OAppBaseState* app_state_;
	int app_state_id_;
};
