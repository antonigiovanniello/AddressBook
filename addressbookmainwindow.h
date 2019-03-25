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

#ifndef ADDRESSBOOKMAINWINDOW_H
#define ADDRESSBOOKMAINWINDOW_H

#include <QMainWindow>
#include "AddressBookMultiMapModel.h"
#include "AddressBookVectorModel.h"

namespace Ui {
class AddressBookMainWindow;
}

class AddressBookMainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit AddressBookMainWindow(QWidget *parent = nullptr);
        ~AddressBookMainWindow();

    private slots:
        void on_inputLineEdit_textEdited(const QString &arg1);
        void on_multiMapButton_toggled(bool checked);
        void on_vectorButton_toggled(bool checked);
        void onLoadedSymbols(int total, int loaded, int nMilliseconds);

        void on_loadMultiplier_valueChanged(int value);

    private:
        std::unique_ptr<model::AbstractBookModel> multiMapModel_, vectorModel_;
        std::unique_ptr<model::AddressBookModel> ABModel_;

    private:
        Ui::AddressBookMainWindow *ui;
};

#endif // ADDRESSBOOKMAINWINDOW_H
