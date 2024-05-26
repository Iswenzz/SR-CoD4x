#pragma once
#include "Base.hpp"

namespace SR
{
	/// @brief Utility class.
	class Utils
	{
	public:
		/// @brief Split a string from a delimiter.
		/// @param source - The string source.
		/// @param delimiter - The split delimiter.
		/// @return
		static std::vector<std::string> SplitString(const std::string& source, char delimiter);

		/// @brief Average mode a given vector.
		/// @tparam T - The elemements type.
		/// @param vec - The vector source.
		/// @return
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

		/// @brief Average mean a given vector.
		/// @tparam T - The elemements type.
		/// @param vec - The vector source.
		/// @return
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

		/// @brief Get the difference between 2 containers.
		/// @tparam T - The vector type.
		/// @tparam Container - STL container class.
		/// @tparam Predicate - The predicate function.
		/// @param a - The first container.
		/// @param b - The second container.
		/// @param predicate - The predicate function.
		/// @return
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
