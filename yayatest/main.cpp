#include <iostream>
#include "ctmgrdb.hpp"
#include  "cmdbuilder.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#include "cmdbuilder.h"
static int gettemp()
{
    return (rand() %  (37 - 9 + 1)) + 9;
}
static int gethumid()
{
    return (rand() %  (100 - 10 + 1)) + 10;
}
static void buildfakecmd()
{
    CommandBuilder c("temp");
    time_t tt = time(NULL);
    struct tm* tm = localtime(&tt);
    for (int i=0;i < 24;i++)
    {

           tm->tm_hour += i;
           time_t time = mktime(tm);
        c.addMeasurement(1,gettemp(),gethumid(),time);


    }

    std::string input =c.buildcmd();
    //std::cin >> input;
    std::ofstream out("/home/mat/output.txt");
    out << input;
    out.close();
}
static void testGetMeasures()
{
    CTManagerDataBase d("/media/mat/data/devel/raspdev/yayasensor/db/dbweather.db");
    CommandBuilder * c = d.getMeasure("2020-09-13 20:12:40","2020-09-13 20:14:40",1);
std::cout <<    c->buildcmd() << std::endl;
}
int main()
{
    srand(time(0));
    cout << "test 0.1 !" << endl;
    testGetMeasures();
    return 0;
}

