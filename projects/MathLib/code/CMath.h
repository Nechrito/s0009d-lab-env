#pragma once

#include <algorithm>
#include <vector>
#include <chrono>

class CMath
{
public:
	
	/// Compares the object by a set of boundaries 
	template <typename T>
	static T Clamp(const T& n, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(n, upper));
	}

	template <typename T>
	static T Saturate(const T& n)
	{
		return std::max(0.0f, std::min(n, 1.0f));
	}

	template <typename T>
	static float Lerp(const T& a, const T& b, const T& f)
	{
		return a + f * (b - a);
	}
	
	/// Returns the base raised to the power exponent
	template <typename T>
	static T Pow(const T& base, const T& exp)
	{
		double result = base;

		if (exp <= 1)
			return result;
		
		for (int i = 1; i <= exp; i++)
			result *= base;

		return result;
	}

	/// Finds an element in a vector and returns a pair of index & a value determining if element was found or not
	/// bool: If value was found or not 
	template <typename T>
	static std::pair<T, int> Find(const std::vector<T>& elements, const T& element)
	{
		std::pair<T, int> result;

		T iterator = std::find(elements.begin(), elements.end(), element);

		// element was found
		if (iterator != elements.end())
		{
			result.first = *iterator; // element
			result.second = distance(elements.begin(), iterator); // index
		}
		else 
		{
			result.first = false;
			result.second = -1;
		}

		return result;
	}
	
	static std::chrono::steady_clock::time_point CurrentTime()
	{
		return std::chrono::steady_clock::now();
	}

	static double TimeSince(const std::chrono::steady_clock::time_point& start)
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(CurrentTime() - start).count();
	}
};
