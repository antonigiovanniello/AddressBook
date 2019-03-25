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
#include "AddressBookCommon.h"

namespace model {

class AddressBookVectorModel : public AbstractBookModel {
    public:
        explicit AddressBookVectorModel();
        virtual void offerKey(const QString &key, std::vector<AddressBookModelEntry *> &cur_symbols) override;

        size_t symbolsCount() override {
            return symb_array_.size();
        }

        void doLoadModel(const std::pair<std::string, AddressBookModelEntry> &entry) override;

        virtual void clearModel() override {
            symb_array_.clear();
        }

        virtual int totalSymbols() override {
            return static_cast<int>(symb_array_.size());
        }

    private:
        std::vector<std::pair<std::string, AddressBookModelEntry>> symb_array_;
};

}
