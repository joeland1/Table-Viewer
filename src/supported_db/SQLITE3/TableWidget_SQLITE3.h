#include <QWidget>
#include <QGridLayout>

class TableWidget : public QWidget {

  Q_OBJECT

  public:
    TableWidget_SQLITE3(QWidget *parent = nullptr);
  private slots:

  private:
    QGridLayout *table_data;
    QString file_location;
};
