#include <QApplication>
#include "Navigator.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Navigator window;

  window.resize(250, 150);
  window.show();

  return app.exec();
}
