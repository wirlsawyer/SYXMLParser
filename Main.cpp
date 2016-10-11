//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "SYXMLParser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	std::wstring xmlstr = L"<root><item id=\"1\">item1</item><item id=\"2\">item2</item></root>";
	SYXMLParse *XmlParse = new SYXMLParse();

	//<root>
	SYXMLList *_root = XmlParse->Parse(xmlstr, L"root");
	//<root/item>
	SYXMLList *_item = XmlParse->Parse(_root, L"item");
    for (std::vector<SYXMLNode*>::size_type i = 0; i != _item->list.size(); i++ )
	{
		SYXMLNode *element = _item->list[i];
		//<root/item id>
		std::wstring _strID = element->Attribute(L"id");
		std::wstring _strValue = element->GetText();

		OutputDebugString((_strValue +L" id="+_strID).c_str());


    }
	delete XmlParse;
}
//---------------------------------------------------------------------------
