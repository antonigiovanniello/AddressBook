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

#pragma once
#pragma warning(disable:4100)

#include <QtWidgets>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>

namespace model {

struct AddressBookModelEntry {
    const std::string &entry_str_;
};

class AbstractBookModel {
    public:
        AbstractBookModel(): loaded_(false) {}
        virtual ~AbstractBookModel() = default;
        virtual void offerKey(const QString &key, std::vector<AddressBookModelEntry *> &cur_symbols) = 0;
        virtual size_t symbolsCount() = 0;
        virtual void doLoadModel(const std::pair<std::string, AddressBookModelEntry> &entry) = 0;
        virtual void clearModel() = 0;
        virtual int totalSymbols() = 0;

        bool loaded() const;
        void setLoaded(bool loaded);

    protected:
        bool loaded_;
};

class AddressBookModel : public QAbstractTableModel {
        Q_OBJECT

    public:
        explicit AddressBookModel(QWidget *parent = nullptr) :
            QAbstractTableModel(parent),
            model_(nullptr),
            load_mul_(1) {
        }

    signals:
        void loadedSymbols(int total, int loaded, int nMilliseconds);

    public slots:
        void offerKey(const QString &key);

        // QAbstractItemModel interface
    public:
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;
        bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex()) override;

    public:
        void load_model();
        void clear_model();

        void set_model(AbstractBookModel *model);

        size_t symbolsCount() {
            return model_->symbolsCount();
        }

        void setLoadMultiplier(int load);


    private:
        std::set<std::string> entry_str_pool_;
        std::vector<AddressBookModelEntry *> cur_symbols_;
        QString cur_key_;
        AbstractBookModel *model_;
        int load_mul_;
};

}
