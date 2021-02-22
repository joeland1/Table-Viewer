#include <QWidget>
#include <QString>

#include "supported_db/master-widget/Overview_Master.h"

class Overview_SQLITE3 : public Overview_Master {

  Q_OBJECT

  public:
    Overview_SQLITE3(QString table_name = nullptr, QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    //bool load_data();
  private:
};
