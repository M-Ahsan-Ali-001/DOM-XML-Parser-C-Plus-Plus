#include<stdio.h>
#include<iostream>
#include<vector>
#include<fstream>
#include"tinyxml2.h"



using namespace tinyxml2;
using namespace std;

class sax2Parser {
public:
	XMLDocument xmlFile;
	vector<const char*> xmlTags = { "author", "title", "genre", "price", "publish_date","description" };
	XMLElement* rootElement;
	XMLElement* bookDiv;
	fstream csvFile;
	string holder[7];

	void read_xml_file(){  xmlFile.LoadFile("compiler.xml"); }
	
    void assign_root_div() {
		rootElement = xmlFile.RootElement();
		bookDiv = rootElement->FirstChildElement("book");

	}

	void print_parsed_data() {
		while (bookDiv) {
			cout << "id :" << bookDiv->Attribute("id")<<"\n";
			for (size_t i{}; i < xmlTags.size(); ++i) {
				XMLElement* fetch = bookDiv->FirstChildElement(xmlTags[i]);
				cout << xmlTags[i]<<" : "<<fetch->GetText()<<"\n";
				cout << (i == xmlTags.size() - 1 ? "\n" : "");
			}
			bookDiv = bookDiv->NextSiblingElement("book");
		
		
		}
	}

	void write_csv()
	{
		assign_root_div();
		csvFile.open("Parsed_Content.csv", ios::out);
		csvFile<<"id"<< "," << "author"  << "," << "title" << "," << "genre" << "," << "price" << "," << "publish_date"
			<< "," << "description"<<"\n";
		int j = 1;
		while (bookDiv) {
			//cout << "id :" << bookDiv->Attribute("id") << "\n";
			holder[0] = bookDiv->Attribute("id");
			csvFile << bookDiv->Attribute("id")<<" , ";
			for (size_t i{}; i < xmlTags.size(); ++i) {
				if (j  >6)
				{
					j = 1;
				}
				XMLElement* fetch = bookDiv->FirstChildElement(xmlTags[i]);
				//cout << xmlTags[i] << " : " << fetch->GetText() << "\n";
			//	cout << (i == xmlTags.size() - 1 ? "\n" : "");
				holder[j] = fetch->GetText();
				csvFile << fetch->GetText() << " , ";
				j++;
			}
			csvFile << " \n";
			

			//csvFile << holder[0] << "," << holder[1] << "," << holder[2] << "," << holder[3]
				//<< "," << holder[4] << "," << holder[5] 
				//<< "," << holder[6] << "\n";
			
			bookDiv = bookDiv->NextSiblingElement("book");


		}

	
	}



};

int main()
{
	sax2Parser parser;
	parser.read_xml_file();
	parser.assign_root_div();
	parser.print_parsed_data();
	parser.write_csv();

   

}
