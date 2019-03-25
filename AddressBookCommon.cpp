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

#include "AddressBookCommon.h"

namespace model {

void AddressBookModel::offerKey(const QString &key)
{
    cur_key_ = key;
    if(!cur_symbols_.empty()) {
        removeRows(0, static_cast<int>(cur_symbols_.size()), QModelIndex());
    }
    cur_symbols_.clear();
    if(!key.size()) {
        return;
    }

    QTime myTimer;
    myTimer.start();

    for(int i = 0; i<load_mul_; i++) {
        cur_symbols_.clear();
        model_->offerKey(key, cur_symbols_);
    }

    emit loadedSymbols(model_->totalSymbols(), static_cast<int>(cur_symbols_.size()), myTimer.elapsed());

    if(!cur_symbols_.empty()) {
        insertRows(0, static_cast<int>(cur_symbols_.size()), QModelIndex());
    }
}

int AddressBookModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(cur_symbols_.size());
}

int AddressBookModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant AddressBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::TextAlignmentRole) {
        return Qt::AlignLeft;
    }
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal && section == 0) {
        return tr("Symbol");
    }
    return QVariant();
}

QVariant AddressBookModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    if(index.row() >= static_cast<int>(cur_symbols_.size()) || index.row() < 0) {
        return QVariant();
    }
    if(index.column() != 0) {
        return QVariant();
    }
    if(role == Qt::DisplayRole) {
        return QString(cur_symbols_.at(static_cast<size_t>(index.row()))->entry_str_.c_str());
    }
    return QVariant();
}

bool AddressBookModel::insertRows(int position, int rows, const QModelIndex &)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
    endInsertRows();
    return true;
}

bool AddressBookModel::removeRows(int position, int rows, const QModelIndex &)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    cur_symbols_.clear();
    endRemoveRows();
    return true;
}

void AddressBookModel::load_model()
{
    std::ifstream ifs("list.txt");
    std::string line;
    while(std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string token;
        std::set<std::string> current_token_set;
        while(std::getline(iss, token, ' ')) {
            std::transform(token.begin(), token.end(), token.begin(), ::tolower);
            if(current_token_set.insert(token).second) {
                auto i_e_str = entry_str_pool_.insert(line);
                model_->doLoadModel(std::pair<std::string, AddressBookModelEntry>(token, {*i_e_str.first}));
            }
        }
    }
}

void AddressBookModel::clear_model()
{
    cur_key_.clear();
    if(cur_symbols_.size()) {
        removeRows(0, static_cast<int>(cur_symbols_.size()));
    }
    model_->clearModel();
    model_->setLoaded(false);
    entry_str_pool_.clear();
}

void AddressBookModel::set_model(AbstractBookModel *model)
{
    model_ = model;
    if(model_->loaded()) {
        return;
    }
    load_model();
    model_->setLoaded(true);
}

void AddressBookModel::setLoadMultiplier(int load)
{
    load_mul_ = load;
}

bool AbstractBookModel::loaded() const
{
    return loaded_;
}

void AbstractBookModel::setLoaded(bool loaded)
{
    loaded_ = loaded;
}

}
