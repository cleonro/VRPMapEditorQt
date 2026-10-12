#ifndef _MAP_OP_GRAPHICS_H_
#define _MAP_OP_GRAPHICS_H_

#include "MapOperationsIAccess.h"

class OMapOperationsGraphics : public OMapOperationsIAccess
{
	Q_OBJECT
public:
	struct tTextureData 
	{
		QImage pixmap_;
		GLuint* texid_;
	};

public:
	void StopWorkers() { thread_google_.Stop(); StopImport(); }
	void ReleaseTextures();
	void ImagesReady() { translate_x_ = 0; translate_y_ = 0; }
	void Draw(float transparency = 0.7);
	void Init(void *data);
	inline void SetDrawArcs(bool b) { draw_arcs_ = b; graph_.BlockArcDraw() = !b;}
	inline bool GetDrawArcs() {return draw_arcs_;}
	inline int& LineWidth() {return line_width_;}
protected:
	OMapOperationsGraphics();
	~OMapOperationsGraphics();

	int line_width_;
	bool drawline_;
	float line_[4];//line drawn on map
	GLuint texid_[9];
	float translate_x_;
	float translate_y_;
	bool draw_arcs_;
	WorkerThread thread_google_;

	bool GetImageFromGoogle();
	bool access_blocked_;//shows if access to resources is blocked
	void DrawMap();

	//thread
	static void GetImageFromGoogleThread(void* data);
};

#endif