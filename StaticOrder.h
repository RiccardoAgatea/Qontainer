#ifndef STATICORDER_H
#define STATICORDER_H
#include <vector>
#include <map>

class StaticOrder
{
public:
	class Empty
	{
	public:
		Empty(const std::string &);
	};
	enum class DetailType
	{
		CheckBox,
		SmallText,
		LargeText
	};
	static std::vector<std::string> types;
	static const
	std::multimap<std::string, std::pair<DetailType, std::string>>
			info;
};

#endif // STATICORDER_H