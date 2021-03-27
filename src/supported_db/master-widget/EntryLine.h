#include <QLineEdit>
#include <QString>
class EntryLine : public QLineEdit {

  Q_OBJECT

  public:
    EntryLine(QWidget *parent = nullptr);
    bool has_been_changed();

  private slots:
    void set_bool_has_been_changed(bool new_status);
  private:

};
