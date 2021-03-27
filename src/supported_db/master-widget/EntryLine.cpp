#include "supported_db\master-widget\EntryLine.h"

#include <QLineEdit>

EntryLine::EntryLine(QWidget *parent):QLineEdit(parent)
{
  has_been_changed = false;
  connect(this, &QLineEdit::textEdited, this, [this](QString new_text){
    this->has_been_changed=true;
  };
}

bool EntryLine::has_been_changed()
{
  return this->has_been_changed;
}

void EntryLine::set_bool_has_been_changed(bool new_status)
{
  this->has_been_changed= new_status;
}
