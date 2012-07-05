#pragma once

#include <memory>

// std::tr1なのかboostなのか、気にしなくていいようにshared_ptrをusing。
// C++11ならテンプレートのtypedefが出来るらしいが･･･。
using std::tr1::shared_ptr;


namespace TestLib {

}// namespace TestLib

