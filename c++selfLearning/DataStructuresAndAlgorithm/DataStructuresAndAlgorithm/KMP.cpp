#include <iostream>
#include <vector>


std::vector<int> get_next(std::string s)
{
	std::vector<int> next = {0};
	int i = 1;
	int j = 0;
	int len = s.length();
	while (i < len)
	{
		if (j == 0 || s[i] == s[j])
		{	
			++j;
			++i;
			next.push_back(j);
		}
		else
		{
			j = next[j-1];
		}
	}
	for (int i : next)
	{
		std::cout << "next:"<< i << std::endl;
	}
	return next;
}

int get_index(std::string t, std::string sub)
{
	std::vector<int> next = get_next(sub);
	for (int i = 0, j = 0;; i < t.length())
	{
		if (j == 0 || t[i] == sub[j])
		{
			++i;
			++j;
			if (j == sub.length())
				return i - sub.length();
		}
		else
		{
			if(j>0) j = next[j] - 1;			
		}
	}
	return 0;
}

//int main()
//{
//	std::string s("abcabc");
//	std::string t("abcdabcababcabc");
//	int i = get_index(t, s);
//
//	return 0;
//}
