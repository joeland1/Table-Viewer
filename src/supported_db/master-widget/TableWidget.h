#include <QWidget>
#include <QGridLayout>

class TableWidget : public QWidget {

  Q_OBJECT

  public:
    TableWidget(QWidget *parent = nullptr);
  private slots:
    bool load_data();
  private:
    QGridLayout *table_data;
};
