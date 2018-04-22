#ifndef _SignalK_Database_
#define _SignalK_Database_
#include <string>
#include <iostream>

namespace SignalK {
	class DataBase
	{
		
	public:
		
		DataBase();
		DataBase(const std::string& self, const std::string& version);
		DataBase(const std::string& json, bool flatten, bool strict);
		DataBase(const DataBase& other);
		DataBase(SignalK::DataBase&& other);
		~DataBase();
		void load(const std::string& json, bool flatten=false, bool strict = false);
		void load(std::istream& input, bool flatten=false, bool strict = false);
		std::string toJson();
		std::string subtree(std::string path);
		std::string getVersion();
		std::string getSelf();
		std::string getSource(std::string id) {
			return subtree("sources." + id);
		}
		std::string getVesselProperty(std::string id, std::string path) {
			return subtree("vessels." + id+"."+path);
		}
		bool update(std::string update);
	protected:
		friend std::ostream& operator<< (std::ostream& os, const DataBase& dt);
		class Node;
		Node* root;
		
	};
	std::ostream& operator<< (std::ostream& os, const DataBase& dt);
}
#endif

