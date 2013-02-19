#include <malloc.h>

#include <iostream>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>


#include <redfox/json.h>
#include <redfox/pq/connection.h>

using namespace Redfox::PQ;

using namespace Redfox::JSON;


// #include "BasicExcel.hpp"

// using namespace YExcel;

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::gregorian;

int main() {
    Connection conn("host=db dbname=mhjh user=postgres");
    // Result rt = conn.execute(
    //         "select * from account where charac_id = 1");
    time_t cur_t = time(0);
    std::string ds("2011/10/22");
    date cur_date(*localtime(&cur_t));
    std::string cur_s = to_iso_string(cur_date);
    std::string end_s = to_iso_string(cur_date + days(1));
    std::cout << cur_s << std::endl
              << end_s << std::endl;
    try {
        Result rt = conn.execute(
                "select sum(gold)::integer as gold_sum from payorder "
                " where ordertime > to_timestamp($1, 'YYYYMMDD') "
                " and  ordertime <= to_timestamp($2, 'YYYYMMDD')",
                cur_s, end_s);

        if (rt.rows() <= 0) {
            return 0;
        }
        std::cout << rt.getType(size_t(0)) << std::endl;
        if (!rt.getIsNull((size_t)0, (size_t)0)) {
            std::cout <<  rt.get<int>((size_t)0, (size_t)0) << std::endl;
        }
    } catch (...) {
        std::cout << "error" << std::endl;
    }
    return 0;
}

int main6() {
    date d2 = from_string("2013-3-1");
    time_t cur_t = time(0);
    date cur_date = date_from_tm(*localtime(&cur_t));
    date new_date = cur_date + days(1);
    std::cout << cur_date << std::endl << new_date;
    return 0;
}


int main5() {
    std::cout << std::ceil(5/(double)2) << std::endl;
    return 0;
}

// int main4() {
//     BasicExcel e;
//     BasicExcelWorksheet* sheet1;
//     if (!e.Load("example.xls")) {
//         return 1;
//     }
//     sheet1 = e.GetWorksheet("a");

//     if (!sheet1) {
//         return 1;
//     }
//     size_t maxRows = sheet1->GetTotalRows();
//     size_t maxCols = sheet1->GetTotalCols();
//     std::cout << "Dimension of " << sheet1->GetAnsiSheetName() <<
//         " (" << maxRows << ", " << maxCols << ")" << endl;
//     return 1;
// }

// #include <xl/libxl.h>

// using namespace libxl;

// int main3()
// {
//     Book* book = xlCreateBook();
//     if(!book) {
//         return 1;
//     }
//     if(!book->load("example.xls")) {
//         return 1;
//     }
//     Sheet* sheet = book->getSheet(0);
//     if(!sheet) {
//         return 1;
//     }
//     const char* s = sheet->readStr(1, 1);
//     if(s) {
//         std::cout << "str:" << s << std::endl;
//     }
//     double d = sheet->readNum(1, 1);
//     std::cout << "num:" << d << std::endl;
//     sheet->writeNum(3, 1, 1000);

//     int year, month, day;
//     book->dateUnpack(sheet->readNum(4, 1), &year, &month, &day);
//     std::cout << year << "-" << month << "-" << day << std::endl;
//     book->save("example.xls");
//     book->release();
//     return 0;
// }


class A {
public:
    A () : a(3) {}

    ~A() {
        a = 7;
    }

    void test() {
        assert(this != 0);
        std::cout << a << std::endl;
    }

    int a;
};

int main2() {
    A *a(new A);
    a->a = 10;
    boost::function<void (A*)> funca = boost::bind(&A::test, _1);
    a->a = 111;
    delete a;
    a = 0;
    funca(a);
    return 0;
}

int main1() {
    std::string str("{\"gold\": 100,\"money\": 100,\"prestige\": 100,\"stamina\": 100,\"exp\": 100,\"items\": [[400251,0,1],[400251,0,1]]}");
    // Redfox::JSON::Value item_value = Redfox::JSON::parse(str);
    // if(!item_value.isBlank()){
    //     Redfox::JSON::Array item_array = item_value.get<Redfox::JSON::Array>();
    //     for (Redfox::JSON::Array::iterator it = item_array.begin();
    //          it != item_array.end(); ++it) {
    //         Redfox::JSON::Array item_num_array = it->get<Redfox::JSON::Array>();
    //         for (Redfox::JSON::Array::iterator it_num = item_num_array.begin();
    //              it_num != item_num_array.end(); ++it_num) {
    //             std::cout << it_num->get<long long>() << std::endl;
    //         }
    //     }
    //     return 0;
    // }
    // Redfox::JSON::Object obj;
    // obj.insert(std::make_pair("test", (Redfox::JSON::Array)str));
    // std::stringstream ss;
    // ss << obj;
    // std::cout << ss.str() << std::endl;
    // Redfox::JSON::Value item_value = Redfox::JSON::parse(str);
    // if (!item_value.isBlank()) {
    //     std::cout << "ok" << std::endl;
    // } else {
    //     std::cout << "err" << std::endl;
    // }

    Object obj;
    Redfox::JSON::Value item_value = Redfox::JSON::parse(str);
    if(!item_value.isBlank()){
        obj = item_value.get<Object>();
    }
    // obj.insert(std::make_pair("gold", "100"));
    std::stringstream ss;
    ss << obj;
    std::cout << ss.str() << std::endl;
    int gold = 0;
    Value::iterator it = obj.find("gold");
    if ((it != obj.end()) && (!it->second.isBlank())) {
        Value gold_value  = it->second;
        gold = gold_value.get<long long>();
    }
    std::cout << gold << std::endl;
    return 0;
}
