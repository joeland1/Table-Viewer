#include "supported_db/master-widget/Overview_Master.h"
#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"

#include <QWidget>
#include <QString>
#include <QList>

class Overview_SQLITE3 : public Overview_Master {

  Q_OBJECT

  public:
    Overview_SQLITE3(QString path = nullptr,QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    bool write_to_db(QList<TableWidget_SQLITE3 *> table_widgets);
  private:
    QString path;
};
