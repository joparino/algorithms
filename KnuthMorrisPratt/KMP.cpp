
#include <iostream>
#include <vector>

std::vector<size_t> findBorders(std::string_view fragment)
{
	std::vector<size_t> borders;
	borders.push_back(0);

	const auto fragmentLength{ fragment.size() };
	for (size_t i{}; i < fragmentLength; ++i)
	{
		size_t border{};
		for (size_t span{ i }; span >= 1; --span)
		{
			if (std::string_view{ &fragment[0], span } ==
				std::string_view{ &fragment[i + 1 - span], span })
			{
				border = span;
				break;
			}
		}
		borders.push_back(border);
	}
	return borders;
}

std::vector<size_t> knuthMorrisPratt(std::string_view text, std::string_view fragment) noexcept(false)
{
	std::vector<size_t> indices;
	const auto fragmentLength{ fragment.size() };
	const auto textLength{ text.size() };
	const auto borders{ findBorders(fragment) };
	size_t j{};
	for (size_t i{}; i < textLength; ++i)
	{
		while (j > 0 && fragment[j] != text[i])
		{
			j = borders[j];
		}
		if (fragment[j] == text[i]) 
		{
			++j;
		}
		if (j == fragmentLength)
		{
			indices.push_back(i - j + 1);
			j = borders[j];
		}
	}
	return indices;
}
