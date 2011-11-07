#ifndef _MAP_OP_GRAPHICS_H_
#define _MAP_OP_GRAPHICS_H_

#include "MapOperationsIAccess.h"

#define _USE_INTEL_ 1

class OMapOperationsGraphics : public OMapOperationsIAccess
{
	Q_OBJECT
public:
	struct tTextureData 
	{
		QImage* pixmap_;
		GLuint* texid_;
	};

public:
	void Draw(float transparency = 0.7);
	void Init(void *data);
	inline void SetDrawArcs(bool b) { draw_arcs_ = b; graph_.BlockArcDraw() = !b;}
	inline bool GetDrawArcs() {return draw_arcs_;}
	inline int& LineWidth() {return line_width_;}
protected:
	OMapOperationsGraphics();
	~OMapOperationsGraphics();

	//for intel problems
	QImage pixmaps_[9];
	//

	int line_width_;
	bool drawline_;
	float line_[4];//line drawn on map
	GLuint texid_[9];
	float translate_x_;
	float translate_y_;
	bool draw_arcs_;
	uintptr_t thread_google_;

	bool GetImageFromGoogle();
	bool access_blocked_;//shows if access to resources is blocked
	void DrawMap();

	//thread
	static void GetImageFromGoogleThread(void* data);
	static void GetImageFromGoogleThread2(void* data);
};

#endif