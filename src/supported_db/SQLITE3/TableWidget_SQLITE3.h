#include <QWidget>
#include <QGridLayout>

#include "supported_db/master-widget/TableWidget.h"

class TableWidget : public TableWidget {

  Q_OBJECT

  public:
    TableWidget_SQLITE3(QWidget *parent = nullptr);
  private slots:

  private:
    QString *file_location;
};
