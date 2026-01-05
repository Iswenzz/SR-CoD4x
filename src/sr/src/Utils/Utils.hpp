#pragma once
#include "Base.hpp"

namespace SR
{
	class Utils
	{
	public:
		static std::vector<std::string> SplitString(const std::string& source, char delimiter);

		template <class T>
		static T VectorAverageMode(const std::vector<T>& vec)
		{
			std::size_t size = vec.size();

			if (size <= 0)
				return 0;

			const T* set = vec.data();
			T mode = set[0];

			int current = 0;
			int mostOccured = 0;

			for (int x = 0; x < size && size > 1; x++)
			{
				if (set[x] == set[x + 1])
					current++;
				else
				{
					if (current > mostOccured)
					{
						mostOccured = current;
						mode = set[x];
					}
					current = 0;
				}
			}
			return mode;
		}

		template <class T>
		static T VectorAverageMean(const std::vector<T>& vec)
		{
			T mean = 0;
			std::size_t size = vec.size();

			if (size <= 0)
				return 0;

			for (int i = 0; i < size; i++)
				mean += vec[i];
			return mean / size;
		}

		template <typename T, class Container, typename Predicate>
		static std::vector<T> GetArrayDifference(const Container& a, const Container& b, Predicate predicate)
		{
			std::vector<T> difference;
			typename Container::const_iterator itA = a.begin(), itB = b.begin();

			while (itA != a.end() || itB != b.end())
			{
				if (!predicate(*itA, *itB))
					difference.push_back(*itA);
				itA++;
				itB++;
			}
			return difference;
		}
	};
}
