#include "twotermdialog.h"

#include <QLabel>
#include <KLocalizedString>

TwoTermDialog::TwoTermDialog(QWidget* parent)
  : KPageDialog(parent)
{
  setFaceType(Tree);
  
  QLabel *label = new QLabel( "Test Page" );
  addPage( label, i18n( "My Test Page" ));
  
  label = new QLabel( "Second Test Page" );
  KPageWidgetItem *page = new KPageWidgetItem( label, i18n( "My Second Test Page" ) );
  page->setHeader( i18n( "My header string" ) );
  page->setIcon( KIcon( "book" ) );
  
  addPage( page );
}


