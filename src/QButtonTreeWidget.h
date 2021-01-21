#include <QWidget>
#include <QString>
#include <QGridLayout>

class QButtonTreeWidget : public QWidget {

  Q_OBJECT

  public:
    QButtonTreeWidget(QWidget *parent = nullptr);
    void addEntry(QString text, bool is_collapsable);
  private slots:

  private:
    QGridLayout *layout;
};
