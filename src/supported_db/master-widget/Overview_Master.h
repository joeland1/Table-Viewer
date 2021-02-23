#include <QWidget>

class Overview_Master : public QWidget {

  Q_OBJECT

  public:
    Overview_Master(QWidget *parent = nullptr);
    std::string get();

    void set_database_type(std::string type);
      std::string get_database_type();
    void set_database_name(std::string name);
      std::string get_database_name();

  private slots:

  private:
    std::string database_type;
    std::string database_name;
};
