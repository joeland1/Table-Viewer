#include <QWidget>
#include <QGridLayout>

class TableWidget_Master : public QWidget {

  Q_OBJECT

  public:
    virtual bool set_connnection();
    
  private slots:
    virtual bool load_data();

  private:
    QGridLayout *table_data;
};
