/********************************************************************************
** Form generated from reading ui file 'kcmgeneralsettings.ui'
**
** Created: Mon Jun 15 15:56:37 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KCMGENERALSETTINGS_H
#define UI_KCMGENERALSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KCMSettingsWidget
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *kcfg_refreshInterval;

    void setupUi(QWidget *KCMSettingsWidget)
    {
        if (KCMSettingsWidget->objectName().isEmpty())
            KCMSettingsWidget->setObjectName(QString::fromUtf8("KCMSettingsWidget"));
        KCMSettingsWidget->resize(468, 150);
        vboxLayout = new QVBoxLayout(KCMSettingsWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(KCMSettingsWidget);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        kcfg_refreshInterval = new QSpinBox(KCMSettingsWidget);
        kcfg_refreshInterval->setObjectName(QString::fromUtf8("kcfg_refreshInterval"));
        kcfg_refreshInterval->setMaximum(50000);
        kcfg_refreshInterval->setSingleStep(100);

        hboxLayout->addWidget(kcfg_refreshInterval);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(KCMSettingsWidget);

        QMetaObject::connectSlotsByName(KCMSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *KCMSettingsWidget)
    {
        KCMSettingsWidget->setWindowTitle(QApplication::translate("KCMSettingsWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("KCMSettingsWidget", "Refresh interval [ms]", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(KCMSettingsWidget);
    } // retranslateUi

};

namespace Ui {
    class KCMSettingsWidget: public Ui_KCMSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCMGENERALSETTINGS_H
