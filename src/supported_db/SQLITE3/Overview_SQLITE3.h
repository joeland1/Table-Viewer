#include <QWidget>
#include <QString>

#include "supported_db/master-widget/Overview_Master.h"

class Overview_SQLITE3 : public Overview_Master {

  Q_OBJECT

  public:
    Overview_SQLITE3(QString path = nullptr,QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    bool write_to_db();
  private:
    QString path;
};
