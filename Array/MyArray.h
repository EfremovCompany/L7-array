#pragma once

#include <memory>

template <typename T>
class CMyArray
{
public:

	CMyArray()
	{
	}

	CMyArray(CMyArray const& other)
		:m_size(other.GetSize())
		,m_items(std::make_unique<T[]>(m_size))
	{
		auto newItems = std::make_unique<T[]>(m_size);
		std::copy(other.m_items.get(), other.m_items.get() + m_size, newItems.get());
		m_items = std::move(newItems);
	}

	~CMyArray()
	{
	}

	bool IsEmpty()const
	{
		return m_size == 0;
	}

	size_t GetSize()const
	{
		return m_size;
	}

	T const & operator [] (size_t index)const
	{
		if (index >= m_size)
			throw std::out_of_range("item index is out of range");
		return m_items[index];
	}

	T & operator [] (size_t index)
	{
		if (index >= m_size)
			throw std::out_of_range("item index is out of range");
		return m_items[index];
	}

	void Add(T const & item)
	{
		auto newItems = std::make_unique<T[]>(m_size + 1);
		std::copy(m_items.get(), m_items.get() + m_size, newItems.get());
		newItems[m_size] = item;
		m_items = std::move(newItems);
		++m_size;
	}

	void Resize(size_t newSize)
	{
		auto newItems = std::make_unique<T[]>(newSize);
		size_t oldSize = m_size;
		for (size_t i = 0; newSize > i; i++)
		{
			if (oldSize > 0)
			{
				newItems[i] = m_items[i];
				--oldSize;
			}
			else
			{
				newItems[i] = T();
			}
		}
		m_items = std::move(newItems);
		m_size = newSize;
	}

	void Clear()
	{
		m_items.reset();
		m_size = 0;
	}

	CMyArray& operator = (CMyArray const& other)
	{
		if (addressof(other) != this)
		{
			CMyArray tmp(other);
			m_items = move(tmp.m_items);
			m_size = tmp.m_size;
		}
		return *this;
	}

private:
	std::unique_ptr<T[]> m_items;
	size_t m_size;
};
