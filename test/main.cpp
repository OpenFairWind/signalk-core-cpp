
#include <stdio.h>
#include "DataBase.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

int main()
{

    SignalK::DataBase db1;
    std::ifstream t("jfull.txt");
    if (t.is_open()) {
        
        db1.load(t, false,false);
        SignalK::DataBase db2 = db1;
        //cout << db2;
        cout << db2.subtree("");
       /* cin.get();
        cout<<"SUBTREE"<<endl;
        cout << db2.subtree("vessels.urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c.navigation.position");
        cin.get();
        cin.get();
        cout<<"vesselPROP"<<endl;
        cout << db2.getVesselProperty("urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c", "navigation.position");
        cin.get();
        cout<<"GETSOURCE"<<endl;
        cout << db2.getSource("ttyUSB0");
        cin.get();
        SignalK::DataBase db3("urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c", "v1.0.0");
        cout<<"STM JSON"<<endl;
        cout << db3.toJson();
        cin.get();
        cout<<"SELF_free"<<endl;
        cout<<db3<<endl;
        cin.get();
        cout<<endl;
        cout<<"SELF"<<endl;
        cout << db3.getSelf()<< " " << db3.getVersion()<< endl;
        cout<<"close program"<<endl;
    */
        SignalK::DataBase db4("urn:mrn:signalk:uuid:705f5f1a-efaf-44aa-9cb8-a0fd6305567c", "v1.0.0");
      //  cout << db4.toJson();
        cin.get();
        //cout << db4.getSelf()<< " " << db4.getVersion()<< endl;
        cin.get();
        std::ifstream d("jdelta.txt");
        std::string delta((std::istreambuf_iterator<char>(d)),
                          std::istreambuf_iterator<char>());
        db2.update(delta);
        cout << db2.subtree("");
        cin.get();

        cout<< db2;

    }

    return 0;
}
