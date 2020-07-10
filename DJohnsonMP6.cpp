#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

enum marital {single = 0, married, divorced};
string prefixMaker(char gender, marital status)
{
	string prefix;
	if (gender == 'M')
	{
		prefix = "Mr.";
	}
	else
	{
		switch (status)
		{
		case married:
		case divorced: prefix = "Mrs."; break;
		default: prefix = "Ms.";
		}
	}
	return prefix;
}
string makeName(string name)
{
	string fname = "", lname = "", init = "";	
	int comma = name.find(',');
	string aftercomma = name.substr(comma + 1, string::npos);
	string before_period;
	int space = aftercomma.find(' ');
	for (int i = 0; i < comma; i++)
	{	
		if (name[i] != ' ')
		{
			lname += name[i];							
		}
		else
			"\0";
	}
	if (aftercomma.find('.') == string::npos)
	{
		for (int p = 0; p < aftercomma.size(); p++)
		{
			if (aftercomma[p] == ' ')
				"\0";
			else
			{			
				fname += aftercomma[p];
			}
		}
	}
	else
	{
		init = aftercomma.substr(aftercomma.find('.') - 1, 2);
		before_period = aftercomma.substr(0, aftercomma.size() - init.size());
		for (int p = 0; p < aftercomma.size() - 1; p++)
		{
			if (before_period[p] == ' ')
				"\0";
			else
			{				
				fname += before_period[p];
			}
		}
	}			
	name = lname + ',' + " " + fname + init;
	return name;
}
string fixName(string name)
{
	string fname = "", lname = "", init = "";
	int comma = name.find(',');
	string aftercomma = name.substr(comma + 1, string::npos);
	string before_period;
	int space = aftercomma.find(' ');
	for (int i = 0; i < comma; i++)
	{
		if (name[i] != ' ')
		{
			lname += name[i];
		}
		else
			"\0";
	}
	if (aftercomma.find('.') == string::npos)
	{
		for (int p = 0; p < aftercomma.size(); p++)
		{
			if (aftercomma[p] == ' ')
				"\0";
			else
			{
				fname += aftercomma[p];
			}
		}
		
	}
	else
	{
		init = aftercomma.substr(aftercomma.find('.') - 1, 2);
		before_period = aftercomma.substr(0, aftercomma.size() - init.size());

		for (int p = 0; p < aftercomma.size() - 2; p++)
		{ 
			if (before_period[p] == ' ')
				"\0";
			else
			{
				fname += before_period[p];
			}
		}
	}
	name = fname +  " " + init + " " + lname;
	return name;
}
marital getStatus(char& s, marital& status)
{		
	if (s == 'M')
		status = married;
	else if (s == 'S')
		status = single;
	else if (s == 'D')
		status = divorced;
	return status;
}
int main()
{	
	char gender = ' ', s = ' ';
	string mf = "", line = "", fullname = "", fixedname = "", title = "";
	string name = "";
	marital status;
	ifstream fin;
	fin.open("mp6Names.txt");
	cout << "  Original name" << setw(30) << "   Standardized Name" << endl;
	while (!fin.eof())
	{
		fin >> gender >> s;		
		status = getStatus(s,status);
		getline(fin, name);
		fullname = makeName(name);
		fixedname = prefixMaker(gender, status) + " " + fixName(name);
		cout << fullname << setw(30) << fixedname << endl;
	}	
	fin.close();
	/* 
	My Output:

  Original name             Standardized Name
Bach, Johann S.            Mr. Johann S. Bach
Curie, Marie A.           Mrs. Marie A. Curie
Parker, Alice M.           Ms. Alice M. Parker
Meir, Golda T.            Mrs. Golda T. Meir
Robeson, Paul             Mr. Paul  Robeson
Ashe, Arthur              Mr. Arthur  Ashe
Tubman, Harriet A.        Mrs. Harriet A. Tubman
Braille, Louis            Mr. Louis  Braille
	*/
}