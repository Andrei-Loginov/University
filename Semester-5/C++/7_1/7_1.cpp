#include "header.h"


int main(){
    DAY days[NDAYS];

    size_t size = read_days("input.txt", days);

    DATE dat {24, 2, 2009};
    //DATE dat{ 12, 12, 2005 };
    //DATE dat{ 17, 1, 1996 };
    //DATE dat{7, 7, 2015};
    //DATE dat{7, 7, 2009};
    //DATE dat{3, 9, 2025};
    DAY* ptr = search({dat}, days, size, comp_days_date);

    std::cout << "\nSearch by date ";
    print_date(dat);

    if (!ptr) std::cout << "\nNot found\n";
    else print_day(*ptr);
    

    return 0;
}
