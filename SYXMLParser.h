//---------------------------------------------------------------------------

#ifndef SYXMLParserH
#define SYXMLParserH
#include <vcl.h>   //for OutputDebugString
#include <string>
#include <vector>
//---------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
///   SYXMLNode																 ///
////////////////////////////////////////////////////////////////////////////////
class SYXMLNode
{
private:
	std::wstring xmlstr;
	std::wstring tag;
public:

	SYXMLNode(std::wstring xmlstr, std::wstring tag);
	~SYXMLNode();
	//Function
	SYXMLNode *Clone(void);
	std::wstring Attribute(std::wstring value);
	std::wstring GetText(void);
	std::wstring GetXMLStr() { return xmlstr; }
};
////////////////////////////////////////////////////////////////////////////////
///   SYXMLList																 ///
////////////////////////////////////////////////////////////////////////////////
class SYXMLList
{
private:

public:
	std::vector<SYXMLNode*> list;

public:
	SYXMLList();
	~SYXMLList();
	//function
	void Push(SYXMLNode *node);
	std::wstring GetText(unsigned int index = 0);
	std::wstring Attribute(std::wstring value, unsigned int index = 0);
	void Print(void);
};
////////////////////////////////////////////////////////////////////////////////
///   SYXMLParse															 ///
////////////////////////////////////////////////////////////////////////////////
class SYXMLParse
{
private:

public:
	SYXMLParse();
	~SYXMLParse();
	//Function
	SYXMLList *Parse(SYXMLNode *node, std::wstring tag);
	SYXMLList *Parse(SYXMLList *list, std::wstring tag);
	SYXMLList *Parse(std::wstring xmlstr, std::wstring tag);
};

#endif
