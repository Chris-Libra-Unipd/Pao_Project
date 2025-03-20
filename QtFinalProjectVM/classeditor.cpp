#include "classeditor.h"

classEditor::classEditor(QWidget* parent):QWidget(parent){}

//necessary since called in bookEditor destructor, classEditor remains abstract
classEditor::~classEditor(){}
