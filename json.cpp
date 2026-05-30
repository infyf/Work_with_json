#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <set>
using namespace std;

int main()
{
    const string URL = "mails.json"; 
    ifstream f(URL, ifstream::binary); 
    string line; 
    if (!f.is_open()) {
        cout << "File was not opened!";
    }
    long idCount = 0; 

    string s; 
    set<string> arr, subjCopy, subjAm;
    multiset<string> subj; 
    multiset<string>::iterator subjit = subj.begin();
    string weekDays[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" }; 
    int daysCounts[7], daysCountMax[7]; 
    for (int i = 0; i < 7; i++) {
        daysCounts[i] = 0;
        daysCountMax[i] = 0;
    }
    int EtoS = 0; // äëÿ ÷åòâåðòîãî
    int StoE = 0;


    int posXFrom5;
    int posDate5;
    int XFromSize5;
    string xFromObj5;
    int posSubj5;
    int posXFolder5;
    int subjSize5;
    string subjObj5;
    int posDate5_1;
    int posXTo5;
    int DataSize5;
    string DataObj5;
    int idx5 = 0;
    int* arr5 = new int[subj.size()];

    int dayIdx;
    int maxDay;
    int sum = 0;
    while (getline(f, line)) { 
        if (line.find("_id") != -1) {
            idCount++;
        }

        for (size_t i = line.find("\"From\"") + 10; i < line.find("\", \"Subject\"")
            && i < line.find("\", \"X-Folder\"")
            && i < line.find("\", \"To\" : \"ned"); i++) {
            s += line[i];
        }
        arr.insert(s);
        s = ""; 


        for (int a = 0; a < 7; a++) { 
            if (line.find(weekDays[a]) != -1) {
                int posTo = line.find("\"To\"") + 8;
                string toObj = line.substr(posTo, line.length() - posTo); 
                toObj = toObj.substr(0, toObj.find("\""));
                if (toObj.find("ebass@enron.com") != -1) {
                    daysCounts[a]++;
                }
            }
        }

        int posXTo = line.find("\"X-To\"") + 10;
        int posMesId = line.find("\"Message-ID\"") - 3;
        int XToSize = posMesId - posXTo;
        string xToObj = line.substr(posXTo, XToSize); 
        int posXFrom = line.find("\"X-From\"") + 10;
        int posDate = line.find("\"Date\"") - 3;
        int XFromSize = posDate - posXFrom;
        string xFromObj = line.substr(posXFrom, XFromSize); 
        if (xToObj.find("Eric Bass") != -1 && xFromObj.find("Shanna Husser") != -1) {
            EtoS++;
        }
        else if (xToObj.find("Shanna Husser") != -1 && xFromObj.find("Eric Bass") != -1) {
            StoE++;
        }


        posXFrom5 = line.find("\"X-From\"") + 10;
        posDate5 = line.find("\"Date\"") - 3;
        XFromSize5 = posDate5 - posXFrom5;
        xFromObj5 = line.substr(posXFrom5, XFromSize5);

        posSubj5 = line.find("\"Subject\"") + 13;
        posXFolder5 = line.find("\"X-Folder\"") - 3;
        subjSize5 = posXFolder5 - posSubj5;
        subjObj5 = line.substr(posSubj5, subjSize5);
  
        posDate5_1 = line.find("\"Date\"") + 10;
        posXTo5 = line.find("\"X-To\"");
        DataSize5 = posXTo5 - posDate5_1;
        DataObj5 = line.substr(posDate5_1, DataSize5);
 
        if (xFromObj5.find("Laurie Ellis") != -1 && DataObj5.find("2000") != -1) {
            subj.insert(subjObj5);
        }
    }

    f.close();
    ifstream fin(URL, ifstream::binary); 
    while (getline(fin, line))
    {

        int datePos6 = line.find("\"Date\"");
        datePos6 += 10;
        int xToPos6 = line.find("\"X-To\"");
        xToPos6 -= 3;
        int dateSize6 = xToPos6 - datePos6;
        string DateObj6 = line.substr(datePos6, dateSize6); 
        for (size_t a = 0; a < 7; a++) {
            if (DateObj6.find(weekDays[a]) != -1) { 
                daysCountMax[a]++; 
            }
        }

        maxDay = daysCountMax[0]; 
        for (size_t i = 0; i < 7; i++) { ó
            if (maxDay < daysCountMax[i]) { 
                maxDay = daysCountMax[i];
                dayIdx = i; 
            }
        }
    }
    fin.close();

    ofstream fout("res.txt");
    for (auto a : arr) {
        fout << a << endl;
    }

    cout << "Id count: " << idCount << endl;
    cout << "From count: " << arr.size() << endl;
    cout << "Eric to Shanna: " << EtoS << endl;
    cout << "Shanna to Eric: " << StoE << endl;
    cout << "Mondays: " << daysCounts[0] << endl;
    cout << "Tuesdays: " << daysCounts[1] << endl;
    cout << "Wednesdays: " << daysCounts[2] << endl;
    cout << "Thursdays: " << daysCounts[3] << endl;
    cout << "Fridays: " << daysCounts[4] << endl;
    cout << "Saturdays: " << daysCounts[5] << endl;
    cout << "Sundays: " << daysCounts[6] << endl;
    cout << "Max day count: " << weekDays[dayIdx] << " " << maxDay << endl;
    for (subjit = subj.begin(); subjit != subj.end(); subjit++)
    {
        idx5 = subj.count(*subjit);
        subjAm.insert(*subjit + ": " + to_string(idx5));
    }
    for (auto b : subjAm) {
        cout << b << endl;
    }
}
