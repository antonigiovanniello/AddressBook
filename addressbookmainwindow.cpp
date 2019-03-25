/* Original Work Copyright (c) 2019 Giuseppe Baccini - giuseppe.baccini@live.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "addressbookmainwindow.h"
#include "ui_addressbookmainwindow.h"

AddressBookMainWindow::AddressBookMainWindow(QWidget *parent) :
    QMainWindow(parent),
    multiMapModel_(new model::AddressBookMultiMapModel()),
    vectorModel_(new model::AddressBookVectorModel()),
    ABModel_(new model::AddressBookModel(this)),
    ui(new Ui::AddressBookMainWindow)
{
    ui->setupUi(this);
    ABModel_->set_model(multiMapModel_.get());
    ui->addressBookTableView->setModel(ABModel_.get());
    ui->addressBookTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ABModel_.get(), SIGNAL(loadedSymbols(int, int, int)), this, SLOT(onLoadedSymbols(int, int, int)));
}

AddressBookMainWindow::~AddressBookMainWindow()
{
    delete ui;
}

void AddressBookMainWindow::on_inputLineEdit_textEdited(const QString &arg1)
{
    if(!ABModel_->symbolsCount()) {
        ui->statusBar->setStyleSheet("color : red;");
        ui->statusBar->showMessage(tr("no symbols loaded!"), 5000);
    }
    if(arg1.size() >= 3) {
        ABModel_->offerKey(arg1);
    } else {
        ABModel_->offerKey(QString());
        ui->statusBar->clearMessage();
    }
}

void AddressBookMainWindow::on_multiMapButton_toggled(bool checked)
{
    if(checked) {
        ABModel_->set_model(multiMapModel_.get());
    }
}

void AddressBookMainWindow::on_vectorButton_toggled(bool checked)
{
    if(checked) {
        ABModel_->set_model(vectorModel_.get());
    }
}

void AddressBookMainWindow::onLoadedSymbols(int total, int loaded, int nMilliseconds)
{
    ui->statusBar->setStyleSheet("color : blue;");
    ui->statusBar->showMessage(tr("loaded:%1/%2, millisecs:%3").arg(loaded).arg(total).arg(nMilliseconds));
}

void AddressBookMainWindow::on_loadMultiplier_valueChanged(int value)
{
    ABModel_->setLoadMultiplier(value);
}
