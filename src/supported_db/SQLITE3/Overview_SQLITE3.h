#include "supported_db/master-widget/Overview_Master.h"
//#include "supported_db/SQLITE3/TableWidget_SQLITE3.h"

//#include <QWidget>
#include <QString>
#include <QList>

class Overview_SQLITE3 : public Overview_Master {

  Q_OBJECT

  public:
    Overview_SQLITE3(QString path = nullptr,QWidget *parent = nullptr);
    ~Overview_SQLITE3();
    QString get_connection_info();
    
  public slots:
    bool write_to_db(QList<QWidget *> table_widgets);
  private slots:

  private:
    QString path;
    //QList<QList<unsigned char *>> og_record;
};
