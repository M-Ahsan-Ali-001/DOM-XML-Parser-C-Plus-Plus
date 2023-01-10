#include<stdio.h>
#include<iostream>
#include"tinyxml2.h"

using namespace tinyxml2;
int main()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("first.xml");
	tinyxml2::XMLElement* p_root_element = doc.RootElement();
	std::cout << p_root_element->GetText() << '\n';
	return 0;

}
