#include "sshconfig.h"
#include "ui_sshconfig.h"

extern QSettings *prefs;

sshconfig::sshconfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sshconfig)
{
    ui->setupUi(this);

    updateTargetList();

    updateInformation();
}

void
sshconfig::updateInformation()
{
    QString server = ui->comboBox->currentText();
    ui->lineEdit->setText(prefs->value(server + "/targetUsername", "flumer").toString());
    ui->lineEdit_2->setText(prefs->value(server + "/targetPassword", "flumer").toString());
}

void
sshconfig::updateTargetList()
{
    QStringList servers = prefs->childGroups();

    ui->comboBox->clear();

    for (int i = 0; i < servers.size(); i++) {
        if (servers[i] != "General") {
            ui->comboBox->addItem(servers[i]);
        }
    }
}

sshconfig::~sshconfig()
{
    delete ui;
}

bool sshconfig::logincheck() {

    return true;
}

void sshconfig::sendkey() {
    if (logincheck()) {
        return;
    }
}
