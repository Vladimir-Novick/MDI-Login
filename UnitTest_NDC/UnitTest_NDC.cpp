#include "pch.h"
#include "CppUnitTest.h"
#include "tinyxml2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace tinyxml2;
using namespace std;

namespace UnitTestNDC
{
	TEST_CLASS(UnitTestNDC)
	{
	public:
		

		void log(char* message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str() + "\n").c_str());
		}

		void log(char* message, int idat) {
			Logger::WriteMessage((string(message) + to_string(idat) + "\n").c_str());
		}

		TEST_METHOD(TestXML)
		{
			static const char* xml =
				"<information>"
				"	<attributeApproach v='1' />"
				"	<textApproach>"
				"		<v>2</v>"
				"	</textApproach>"
				"</information>";

			XMLDocument doc;
			doc.Parse(xml);

			int v0 = 0;
			int v1 = 0;

			XMLElement* attributeApproachElement = doc.FirstChildElement()->FirstChildElement("attributeApproach");
			attributeApproachElement->QueryIntAttribute("v", &v0);

			XMLElement* textApproachElement = doc.FirstChildElement()->FirstChildElement("textApproach");
			textApproachElement->FirstChildElement("v")->QueryIntText(&v1);

			log("values 1 are the same: \n", v0);
			log("value 2 are the same:\n", v1);
		}
	};
}
