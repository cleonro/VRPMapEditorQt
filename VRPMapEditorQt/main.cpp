#include "vrpmapeditorqt.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	FILE *str;
	AllocConsole();
	freopen_s(&str,"CONOUT$", "w", stdout );

	VRPMapEditorQt w;
	
	
	w.resize(QSize(1024, 768));

	w.show();
	
	return a.exec();
}
