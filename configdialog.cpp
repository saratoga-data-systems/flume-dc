#include "configdialog.h"
#include "ui_configdialog.h"

extern QSettings *prefs;

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    ui->proxyHostnameEdit->setText(prefs->value("proxyHostname", "localhost").toString());
    ui->proxyUsernameEdit->setText(prefs->value("proxyUsername", "flumer").toString());
    ui->proxyPasswordEdit->setText(prefs->value("proxyPassword", "flumer").toString());
    ui->proxyPortEdit->setText(prefs->value("proxyPort", "22").toString());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConfigDialog::saveConfig);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void
ConfigDialog::saveConfig()
{
    prefs->setValue("proxyHostname", ui->proxyHostnameEdit->text());
    prefs->setValue("proxyUsername", ui->proxyUsernameEdit->text());
    prefs->setValue("proxyPassword", ui->proxyPasswordEdit->text());
    prefs->setValue("proxyPort", ui->proxyPortEdit->text());

    prefs->sync();
}
