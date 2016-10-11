//---------------------------------------------------------------------------


#pragma hdrstop

#include "SYXMLParser.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
////////////////////////////////////////////////////////////////////////////////
///   SYXMLNode																 ///
////////////////////////////////////////////////////////////////////////////////
/**************************
 * FUNCTION:SYXMLNode
 * DESCRIPTION:建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLNode::SYXMLNode(std::wstring xmlstr, std::wstring tag)
{
	this->xmlstr = xmlstr;
	this->tag = tag;
}

/**************************
 * FUNCTION:~SYXMLNode
 * DESCRIPTION:解建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLNode::~SYXMLNode()
{
}

/**************************
 * FUNCTION:Clone
 * DESCRIPTION:複製一份
 * PARAMETERS:none
 * RETURNED:new SYXMLNode
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLNode *SYXMLNode::Clone(void)
{
	return new SYXMLNode(this->xmlstr, this->tag);
}

/**************************
 * FUNCTION:Attribute
 * DESCRIPTION:取得XML裡面的屬性
 * PARAMETERS:XML str
 * RETURNED:str
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
std::wstring SYXMLNode::Attribute(std::wstring value)
{
	size_t pos1 = xmlstr.find(L"<")+1;
	size_t pos2 = xmlstr.find(L">");
	std::wstring single = xmlstr.substr(pos1, pos2-pos1);


	pos1 = single.find(L"<", pos1)+1;
	pos1 = single.find(L" ", pos1)+1;

	//for case when value = 'xmlns'
	//<DIDL-Lite xmlns:dc="http://purl.org/dc/elements/1.1/"
	//xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/"
	//xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/">
	while (true)
	{
		pos1 = single.find(value, pos1)+1;

		if (pos1==0) break; //for case no find this Attribute
		if (single.find(L" ", pos1) == pos1+value.length()-1 || single.find(L"=", pos1) == pos1+value.length()-1 )
		{
			break;
		}
	}


	if (pos1 == 0) return L"";
	pos1 = single.find(L"=", pos1)+1;
	pos1 = single.find(L"\"", pos1)+1;
	pos2 = single.find(L"\"", pos1+1);

	//OutputDebugStringA(single.substr(pos1, pos2-pos1).c_str());
	//OutputDebugStringA("\n");
	return single.substr(pos1, pos2-pos1);
}

/**************************
 * FUNCTION:GetText
 * DESCRIPTION:取得XML裡面的本文
 * PARAMETERS:XML str
 * RETURNED:str
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
std::wstring SYXMLNode::GetText(void)
{
	size_t t1 = xmlstr.find(L">");
	size_t t2 = xmlstr.find(L"/>")+1;
	if (t1 == t2 )
	{
		return NULL;
	}

	std::wstring tmp = xmlstr.substr(t1+1, xmlstr.length()-t1-1-tag.length()-3);
	return tmp;
}
////////////////////////////////////////////////////////////////////////////////
///   SYXMLList																 ///
////////////////////////////////////////////////////////////////////////////////
/**************************
 * FUNCTION:SYXMLList
 * DESCRIPTION:建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLList::SYXMLList()
{
	list.clear();
}

/**************************
 * FUNCTION:~SYXMLList
 * DESCRIPTION:解建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
 SYXMLList::~SYXMLList()
 {
	while(!list.empty())
	{
		delete list.back();
		list.pop_back();
	}
 }

 /**************************
 * FUNCTION:Push
 * DESCRIPTION:儲存SYXMLNode節點
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
 void SYXMLList::Push(SYXMLNode *node)
 {
	if (node){
		list.push_back(node);
	}
 }

 /**************************
 * FUNCTION:GetText
 * DESCRIPTION:取得Node裡面XML的本文
 * PARAMETERS:index
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
 std::wstring SYXMLList::GetText(unsigned int index)
 {
	if (index > list.size()) return NULL;

	SYXMLNode *node = list[index];
	if (node != NULL)
	{
		return node->GetText();
	}
	return NULL;
 }

 /**************************
 * FUNCTION:GetText
 * DESCRIPTION:取得Node裡面XML的屬性
 * PARAMETERS:attribute, index
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
 std::wstring SYXMLList::Attribute(std::wstring value, unsigned int index)
 {
	if (index > list.size()) return NULL;

	SYXMLNode *node = list[index];
	if (node != NULL)
	{
		return node->Attribute(value);
	}
	return NULL;
 }

/**************************
 * FUNCTION:Print
 * DESCRIPTION:Debug用
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
void SYXMLList::Print(void)
{
	for (std::vector<SYXMLNode*>::size_type i = 0; i != list.size(); i++ )
	{
		SYXMLNode *node = list[i];
		OutputDebugString(node->GetText().c_str());
		OutputDebugString(L"\n");
	}
}
////////////////////////////////////////////////////////////////////////////////
///   SYXMLParse															 ///
////////////////////////////////////////////////////////////////////////////////
/**************************
 * FUNCTION:SYXMLParse
 * DESCRIPTION:建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLParse::SYXMLParse()
{
}
/**************************
 * FUNCTION:~SYXMLParse
 * DESCRIPTION:解建構子
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLParse::~SYXMLParse()
{
}

/**************************
 * FUNCTION:Parse
 * DESCRIPTION:Parse
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLList *SYXMLParse::Parse(SYXMLNode *node, std::wstring tag)
{
	return this->Parse(node->GetText(), tag);
}

/**************************
 * FUNCTION:Parse
 * DESCRIPTION:Parse
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLList *SYXMLParse::Parse(SYXMLList *list, std::wstring tag)
{
	return this->Parse(list->GetText(), tag);
}

/**************************
 * FUNCTION:Parse
 * DESCRIPTION:Parse
 * PARAMETERS:none
 * RETURNED:none
 * CREATED:
 * BY:sawyer
 * COMMENTS:2013.01.18
 **************************/
SYXMLList *SYXMLParse::Parse(std::wstring xmlstr, std::wstring tag)
{
	std::wstring context = xmlstr;

	std::wstring begin = L"<";
	begin.append(tag);


	std::wstring end = L"</";
	end.append(tag);
	end.append(L">");

	size_t pos1 = context.find(begin);
	size_t pos2 = 0;
	size_t pos3 = 0;
	size_t pos4 = 0;



	// no this tag
	if (pos1 > xmlstr.length()){ return NULL;}



	//new
	SYXMLList *newList = new SYXMLList();


	//單一行 <ff id=\"123\" />
	size_t t1 = context.find(L">");
	size_t t2 = context.find(L"/>")+1;
	if (t1 == t2 )
	{

		SYXMLNode *newNode = new SYXMLNode(context.substr(pos1, t2-pos1+1), std::wstring(tag));
		newList->Push(newNode);
		return newList;
	}

	std::wstring tmp_str1;
	std::wstring tmp_str2;


	//<xxx> </xxx>
	while (true)
	{
		pos1 = context.find(begin, pos2);
		//find to end
		if (pos1>xmlstr.length()) break;
		//for case "manufacture"
		//<manufacturer>manufacturer name</manufacturer>
		//<manufacturerURL>URL to manufacturer site</manufacturerURL>
		tmp_str1 = begin;
		tmp_str2 = begin;
		tmp_str1.append(L">");
		tmp_str2.append(L" ");
		if ( context.find(tmp_str1, pos2) != pos1 &&  context.find(tmp_str2, pos2) != pos1)
		{
			break;
		}

		//for case
		//<device>
		//  <list>
		//    <device>
		//    </device>
		//  </list>
		//</device>
		pos4 = 0;
		while (true)
		{
			pos2 = context.find(end, pos1+pos4+1);

			//for case
			//<device>
			//<deviceType>
			while(true)
			{
				pos3 = context.find(begin, pos1+pos4+1);
				t1 = context.find(tmp_str1, pos1+pos4+1);
				t2 = context.find(tmp_str2, pos1+pos4+1);
				if ( t1 == pos3 || t2 == pos3)
				{
					break;
				}
				else
				{
					pos4 = pos3-pos1;
				}
			}

			if (pos2 < pos3)
			{
				break;
			}else{
				pos4 = pos2-pos1;
			}
		}



		SYXMLNode *newNode = new SYXMLNode(context.substr(pos1, pos2-pos1+end.length()), tag);
		newList->Push(newNode);
	}
	return newList;
}
