#include <QWidget>

class TableWidget_Master : public QWidget {

  Q_OBJECT

  public:
    TableWidget_Master(QWidget *parent = nullptr);
    std::string get();

  private slots:
    virtual bool write_to_db();

  private:
};
