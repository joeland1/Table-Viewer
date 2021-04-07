#include "supported_db/master-widget/DataEntry_QLineEdit.h"

#include <QLineEdit>
#include <QString>
//might be removed idk yet
DataEntry_QLineEdit::DataEntry_QLineEdit(QString start_text, QWidget *parent):QLineEdit(parent)
{
  this->base_text = start_text;
  QLineEdit::setText(this->base_text);
}

void DataEntry_QLineEdit::setText(QString newText)
{
  this->base_text = newText;
  QLineEdit::setText(this->base_text);
}

void DataEntry_QLineEdit::save()
{
  this->base_text = QLineEdit::text();
}

QString DataEntry_QLineEdit::get_base_text()
{
  return this->base_text;
}
