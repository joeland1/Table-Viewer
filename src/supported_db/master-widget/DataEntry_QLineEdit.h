#include <QLineEdit>

class DataEntry_QLineEdit : public QLineEdit {

  Q_OBJECT

  public:
    DataEntry_QLineEdit(QString start_text="", QWidget *parent = nullptr);
    void setText(QString newText);
    void save();
    QString get_base_text();
  private slots:
  private:
    QString base_text;
};
