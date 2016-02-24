#include"TextQuery.h"
#include"QueryResult.h"

TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
	string text;
	while (getline(is, text))  //ÿ�ζ�ȡһ��
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &lines = wm[word];  //linesΪ��ָ̬������ã��ı�linesͬ����ı�wm�е�����
			if (!lines)
				lines.reset(new set<int>);    //reset��shared_ptr�ĳ�Ա������.�����
			lines->insert(n);
		}
	}
}

const QueryResult
TextQuery::query(const string &word) const
{
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc = wm.find(word);
	if (loc != wm.end())
		return QueryResult(word, loc->second, file);
	else
		return QueryResult(word, nodata, file);
}