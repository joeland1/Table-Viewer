#include <QWidget>

class TableWidget_Master : public QWidget {

  Q_OBJECT

  public:
    TableWidget_Master(QWidget *parent = nullptr);
    virtual bool refresh_tables();
    std::string get();

  public slots:
    virtual bool write_to_db_table();

  private slots:
    virtual bool write_to_db_all();

  private:
};
