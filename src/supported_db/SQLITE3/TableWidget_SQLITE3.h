#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QSplitter>

#include "supported_db/master-widget/TableWidget_Master.h"

class TableWidget_SQLITE3 : public TableWidget_Master {

  Q_OBJECT

  public:
    TableWidget_SQLITE3(QString table_name = nullptr, QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    //bool load_data();

  private:
    QString *file_location;
    QSplitter *master_splitter;
    void sync_column_sizes();
};
