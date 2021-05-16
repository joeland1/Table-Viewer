#include <QApplication>
#include "Navigator.h"
#include "error_handling.h"

int main(int argc, char *argv[]) {
  qInstallMessageHandler(customMessageHandler);
  QApplication app(argc, argv);

  Navigator window;

  window.resize(250, 150);
  window.show();

  return app.exec();
}
