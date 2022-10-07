
#include <iostream>
#include <vector>
#include <string_view>

typedef uint32_t Hash;

Hash Fnv1a(std::string_view s, uint32_t i = 0)
{
    Hash h{ 0x811C9DC5 };
    static constexpr Hash p{ 0x01000193 };
    h ^= i;
    for (auto symbol : s)
    {
        h ^= symbol;
        h *= p;
    }
    return h;
}

 
std::vector<size_t> rabinKarp(std::string_view text, std::string_view fragment)
{
    std::vector<size_t> indices{};
    const auto textLength{ text.size() };
    const auto fragmentLength{ fragment.size() };
	const auto hashFragment{ Fnv1a(fragment) };
    auto hashText{ Fnv1a(text.substr(0, fragmentLength)) };
    for (size_t i{}; i < textLength - fragmentLength + 1; ++i)
    {
        if (hashText == hashFragment)
        {
            if (text.substr(i, fragmentLength) == fragment)
            {
                indices.push_back(i);
            }
        }
        hashText = Fnv1a(text.substr(i + 1, fragmentLength));
    }
    return indices;
}
