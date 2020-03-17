#include "StdAfx.h" // Vladimir Novick
#include "CppUnitTest.h"
#include "CDialogProperty.h"
#include <iostream>
#include <string>
#include <regex>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

		TEST_METHOD(DialogProperties) {
			CDialogProperty property;
			string value = "A8B2C6";
			property.ColorBackgrownd->value = value;
			auto ret = property.ColorBackgrownd->value;
			Assert::AreEqual(ret, value);
			string r2 = property["ColorBackgrownd"];
			
			Assert::AreEqual(r2, value);


			auto propertyList = property.GetProperties();

			for (auto it = propertyList.begin(); it != propertyList.end(); ++it) {
				log("--> ", *it);
			}
			string xml = property.ToXml();
			log("XML string: ", xml);
			property.ColorBackgrownd->value = "";
			property.Parse(xml);
			string xml2 = property.ToXml();
			Assert::AreEqual(xml2, xml);
		};

		TEST_METHOD(XML_parsing) {
			stringstream stringBuilder;
			string s("<info>\n <tag1 key1>\n <tag2 key2>contents2</tag2>\n <tag3> contents 3</tag3>\n</tag1>\n</info>\n");
			smatch m;
			regex e("<([a-z,A-z,0-9,_]+)[ ]*([^>]*)>([^<]+)</[^>]*>"); // try to match <tag key>contents</tag> or <tag>contents</tag> , where
			
			//	Capture group 0

			//<tag2 key2>contents2</ tag2>

			//	Capture group 1
			//	tag2

			//	Capture group 2
			//	key2

			//	Capture group 3
			//	contents2
																	 

			// "<(/*)(\\S+?)\\b(.*?)(/*)>"
			log("source:\n", s);
			log("\n===============================\n", "");
			while (regex_search(s, m, e, regex_constants::match_any)) // provide override default settings with POSIX, where extended mode (e.g. lazy quantifiers are not supported)
			{
				int i = 0;
				for (auto x : m)
				{
					if (i == 0)
						log("\nWhole match: ","");
					else
						log("\nCapture group \n", to_string(i));
					stringBuilder.str("");
					stringBuilder << x;
					log("",stringBuilder.str());
					i++;
				}
				log("\n===============================\n","");
				s = m.suffix().str();

			}
		};


	};
}
