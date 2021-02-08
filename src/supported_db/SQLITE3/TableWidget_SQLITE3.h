#include <QWidget>
#include <QGridLayout>
#include <QString>

#include "supported_db/master-widget/TableWidget_Master.h"

class TableWidget_SQLITE3 : public TableWidget_Master {

  Q_OBJECT

  public:
    TableWidget_SQLITE3(QWidget *parent = nullptr);
  private slots:

  private:
    QString *file_location;
};
