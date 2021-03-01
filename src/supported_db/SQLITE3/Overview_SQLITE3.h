#include <QWidget>
#include <QString>

#include "supported_db/master-widget/Overview_Master.h"

class Overview_SQLITE3 : public Overview_Master {

  Q_OBJECT

  public:
    Overview_SQLITE3(QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    //bool load_data();
  private:
    QString connection;
};
