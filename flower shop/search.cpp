#include "search.h"

template<class T>
T Search::search<T>::toLower(T s)
{
		for (int i = 0; i < s.size(); i++)
		{
				if (s[i] >= 'A' && s[i] <= 'Z')
						s[i] = s[i] - ('Z' - 'z');
				if (s[i] >= '�' && s[i] <= '�')
						s[i] = s[i] - ('�' - '�');
		}
		return s;
}