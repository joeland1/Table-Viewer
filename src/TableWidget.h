#include <QWidget>

class TableWidget : public QWidget {

  Q_OBJECT

  public:
    enum table_format {SQLITE3};
    TableWidget(QWidget *parent = nullptr, int table_style);
    bool load_data();
  private slots:

  private:

};
