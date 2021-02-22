#include <QWidget>

class Overview_Master : public QWidget {

  Q_OBJECT

  public:
    Overview_Master(QWidget *parent = nullptr);
    std::string get();

  private slots:

  private:
};
