
#include <stdio.h>
#include "DataBase.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

int main()
{

    SignalK::DataBase db1;
    std::ifstream t("jsontest.txt");
    if (t.is_open()) {
        
        db1.load(t, false, false);
        SignalK::DataBase db2 = db1;
        cout << db2;
        cin.get();
        cout << endl;
        cout << db2.subtree("vessels.urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c.navigation.position");
        cin.get();
        cout << db2.getVesselProperty("urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c", "navigation.position");
        cin.get();
        cout << db2.getSource("ttyUSB0");
        cin.get();
        SignalK::DataBase db3("urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c", "v1.0.0");
        cout << db3.toJson();
        cin.get();
        cout << db3.getSelf()<< " " << db3.getVersion()<< endl;
        cin.get();
        std::ifstream d("jsondelta.txt");
        std::string delta((std::istreambuf_iterator<char>(d)),
                          std::istreambuf_iterator<char>());
        db2.update(delta);
        cout << db2.subtree("");
        cin.get();
    }

    return 0;
}
