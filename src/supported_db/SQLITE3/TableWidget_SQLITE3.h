#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QSplitter>

#include "supported_db/master-widget/TableWidget_Master.h"

class TableWidget_SQLITE3 : public TableWidget_Master {

  Q_OBJECT

  public:
    TableWidget_SQLITE3(QString table_name = nullptr, QString db_path = nullptr, QWidget *parent = nullptr);
    //bool set_login();
  private slots:
    //bool load_data();
    void display_ctx_menu_qwidget(const QPoint &);
    void display_ctx_menu_qpushbutton(const QPoint &);
    bool write_to_db();

  private:
    QString file_location;
    QSplitter *master_splitter;
};
