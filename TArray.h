#pragma once
#include <cstdint>
#include <iomanip>
#include <functional>
#include <vector>
#include "TArrayException.h"

namespace aiafpb1
{
	template <typename T>
	class TArray
	{
	private:
		size_t m_size;
		T* m_data;

	public:
		//TArray() = default;
		TArray(const size_t size = 0);
		TArray(const std::initializer_list<T>& list);
		TArray(const TArray&);
		~TArray();
		void clear();
		void resize(size_t tosize);
		void modify(size_t tosize);
		void insert(size_t position, T value);
		void add_first(T value);
		void add_last(T value);
		void remove(size_t position);
		size_t size() const;
		bool tryGetOne(std::function<bool(const T&, T&)>, T&, size_t&);
		std::vector<std::reference_wrapper<T>> getSelection(std::function<bool(const T&, T&)>, T&);
		T& operator[](const size_t);
		const T& operator[](const size_t) const;
		TArray& operator=(const TArray&);
		std::stringstream showByOne() const;
		std::stringstream show() const;
		//std::function<bool(const T&, T&)> selector;
	};

	// Далее определения функций

	template <typename T>
	TArray<T>::TArray(const size_t size) : m_size(size)
	{
		if (size < 0)
		{
			m_size = 0;
			throw TArrayException(etype::invalid_size, __FUNCTION__);
		}

		if (size > 0) m_data = new T[size];
	}

	template <typename T>
	TArray<T>::TArray(const std::initializer_list<T>& list)
	{
		TArray::resize(list.size());
		if (m_size > 0)
		{
			size_t i = 0;
			for (auto const& value : list)
			{
				m_data[i] = value;
				++i;
			}
		}
	}

	template <typename T>
	TArray<T>::TArray(const TArray& a)
	{
		TArray::resize(a.size());
		for (size_t i = 0; i < m_size; i++) { m_data[i] = a.m_data[i]; }
	}

	template <typename T>
	TArray<T>::~TArray() { delete[] m_data; }

	template <typename T>
	void TArray<T>::clear()
	{
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
	}

	template <typename T>
	void TArray<T>::resize(size_t tosize)
	{
		// изменение размера массива без сохранения данных

		if (tosize == m_size) return;
		if (tosize < 0) throw TArrayException(etype::invalid_size, __FUNCTION__);

		TArray::clear();
		m_size = tosize;
		m_data = new T[m_size];
	}

	template <typename T>
	void TArray<T>::modify(size_t tosize)
	{
		// изменение размера массива с сохранением данных в пределах нового размера

		if (tosize == m_size) return;
		if (tosize < 0) throw TArrayException(etype::invalid_size, __FUNCTION__);
		if (tosize == 0)
		{
			TArray::clear();
			return;
		}

		T* data{ new T[tosize] };
		auto copied = (tosize < m_size) ? tosize : m_size;
		for (size_t i = 0; i < copied; i++) { data[i] = m_data[i]; }

		delete[] m_data;
		m_data = data;
		m_size = tosize;
	}

	template <typename T>
	void TArray<T>::insert(size_t position, T value)
	{
		// position: позиция в массиве для вставки - выбирается от 1 до m_size + 1
		if (m_size + 1 < position || position < 1)
		{
			std::string comment = "позиция для вставки может быть в пределах от 1 до значения <размер массива + 1>";
			throw TArrayException(etype::invalid_index, __FUNCTION__, comment);
		}

		// формирование нового массива
		T* data{ new T[m_size + 1] };
		size_t index = position - 1;
		for (size_t i = 0; i < index; i++) { data[i] = m_data[i]; }
		data[index] = value;
		for (size_t i = index; i < m_size; i++) { data[i + 1] = m_data[i]; }

		delete[] m_data;
		m_data = data;
		++m_size;
	}

	template <typename T>
	void TArray<T>::add_first(T value) { TArray::insert(1, value); }

	template <typename T>
	void TArray<T>::add_last(T value) { TArray::insert(m_size + 1, value); }

	template <typename T>
	void TArray<T>::remove(size_t position)
	{
		// position: позиция в массиве удаляемого элемента - выбирается от 1 до m_size
		if (m_size < position || position < 1)
		{
			std::string comment = "позиция удаляемого элемента может быть в пределах от 1 до значения <размер массива>";
			throw TArrayException(etype::invalid_index, __FUNCTION__, comment);
		}

		// удаление единственного элемента в массиве
		if (m_size == 1)
		{
			TArray::clear();
			return;
		}

		// формирование нового массива
		T* data{ new T[m_size - 1] };
		for (size_t i = 0; i < (position - 1); i++) { data[i] = m_data[i]; }
		for (size_t i = position; i < m_size; i++) { data[i - 1] = m_data[i]; }

		delete[] m_data;
		m_data = data;
		--m_size;
	}

	template <typename T>
	size_t TArray<T>::size() const { return m_size; }

	template <typename T>
	bool TArray<T>::tryGetOne(std::function<bool(const T&, T&)> selector, T& comparer, size_t& index)
	{
		bool result = false;
		for (size_t i = 0; i < m_size; i++)
		{
			if (selector(m_data[i], comparer))
			{
				comparer = (m_data[i]);
				index = i;
				result = true;
				break;
			}
		}
		return result;
	}

	// используется std::vector для возможности работы с std::reference_wrapper<T>
	template <typename T>
	std::vector<std::reference_wrapper<T>> TArray<T>::getSelection(std::function<bool(const T&, T&)> selector, T& comparer)
	{
		std::vector<std::reference_wrapper<T>> v;
		for (size_t i = 0; i < m_size; i++) { if (selector(m_data[i], comparer)) v.push_back(std::ref(m_data[i])); }
		return v;
	}

	template <typename T>
	T& TArray<T>::operator[](size_t index)
	{
		if (m_size <= index || index < 0) throw TArrayException(etype::invalid_index, __FUNCTION__);
		return m_data[index];
	}

	template <typename T>
	const T& TArray<T>::operator[](const size_t index) const
	{
		if (m_size <= index || index < 0) throw TArrayException(etype::invalid_index, __FUNCTION__);
		return m_data[index];
	}

	template <typename T>
	TArray<T>& TArray<T>::operator=(const TArray& a)
	{
		if (&a != this)
		{
			TArray::resize(a.size());
			for (size_t i = 0; i < m_size; i++) { m_data[i] = a.m_data[i]; }
		}
		return *this;
	}

	template <typename T>
	inline std::stringstream TArray<T>::showByOne() const
	{
		std::stringstream ss;
		for (size_t i = 0; i < m_size; i++) { ss << m_data[i] << std::endl; }
		return ss;
	}

	template <typename T>
	std::stringstream TArray<T>::show() const
	{
		std::stringstream ss;
		bool byline = true;
		bool bydozen = true;
		size_t n = 10;
		size_t w = 8;
		size_t max1 = 15;
		size_t max2 = 7;
		ss << std::endl;
		for (size_t i = 0; i < m_size; i++)
		{
			std::stringstream box;
			box << m_data[i];
			std::string s = box.str();
			if (s.size() > max1)
			{
				byline = false;
				break;
			}
			if (bydozen && s.size() > max2)
			{
				bydozen = false;
				n = 5;
				w = 16;
			}
		}
		for (size_t i = 0; i < m_size; i++)
		{
			if (byline)
			{
				ss << std::right << std::setw(w) << m_data[i];
				if (!((i + 1) % n)) ss << std::endl;
			}
			else ss << m_data[i] << std::endl;
		}
		return ss;
	}
}
