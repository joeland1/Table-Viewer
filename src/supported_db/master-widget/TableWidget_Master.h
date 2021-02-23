#include <QWidget>

class TableWidget_Master : public QWidget {

  Q_OBJECT

  public:
    TableWidget_Master(QWidget *parent = nullptr);
    std::string get();
    virtual void sync_column_sizes() = default;

  private slots:

  private:
};
