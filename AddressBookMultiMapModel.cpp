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

#include "AddressBookMultiMapModel.h"

namespace model {

AddressBookMultiMapModel::AddressBookMultiMapModel()
{}

void AddressBookMultiMapModel::offerKey(const QString &key, std::vector<AddressBookModelEntry *> &cur_symbols)
{
    auto kstr = key.toStdString();
    std::transform(kstr.begin(), kstr.end(), kstr.begin(), ::tolower);
    for(auto it = symb_map_.lower_bound(kstr); it != symb_map_.end(); ++it) {
        if(it->first.find(kstr) == 0) {
            cur_symbols.push_back(&it->second);
        } else {
            break;
        }
    }
}

void AddressBookMultiMapModel::doLoadModel(const std::pair<std::string, AddressBookModelEntry> &entry)
{
    symb_map_.insert(entry);
}


}
