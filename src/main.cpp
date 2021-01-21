#include <QApplication>
#include "launch_menu.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Launch window;

  window.resize(250, 150);
  window.setWindowTitle("Joe Bot");
  window.show();

  return app.exec();
}
