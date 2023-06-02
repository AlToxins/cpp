#include "Product.h"
#include"newwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Product w;
	w.show();
	return a.exec();
}
