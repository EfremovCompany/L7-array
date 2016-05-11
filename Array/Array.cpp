#include "stdafx.h"
#include "MyArray.h"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(MyArrayTests)

BOOST_AUTO_TEST_CASE(CreateEmptyMyArray)
{
	const CMyArray<string> arr;
	BOOST_CHECK(arr.IsEmpty());
	BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
	BOOST_CHECK_THROW(arr[0], out_of_range);
	CMyArray<string> arr2;
	BOOST_CHECK_THROW(arr2[0], out_of_range);
	CMyArray<double> nums;
	BOOST_CHECK(nums.IsEmpty());
	BOOST_CHECK_THROW(nums[0], out_of_range);
}

BOOST_AUTO_TEST_CASE(AddNewElement)
{
	{
		CMyArray<string> arr;
		string element = "hello";
		BOOST_CHECK_NO_THROW(arr.Add(element));
		BOOST_REQUIRE_EQUAL(arr.GetSize(), 1u);
		BOOST_CHECK_EQUAL(arr[0], element);
	}
	{
		CMyArray<double> arr;
		double element = 4.5;
		BOOST_CHECK_NO_THROW(arr.Add(element));
		BOOST_REQUIRE_EQUAL(arr.GetSize(), 1u);
		BOOST_CHECK_EQUAL(arr[0], element);
	}

}

BOOST_AUTO_TEST_CASE(TestResizeMethod)
{
	{
		CMyArray<string> strArr;
		for (int i = 0; i < 5; ++i)
		{
			strArr.Add(to_string(i));
		}
		BOOST_CHECK(!strArr.IsEmpty());
		BOOST_CHECK_EQUAL(strArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(strArr[4], "4");
		strArr.Resize(2);
		BOOST_CHECK_EQUAL(strArr.GetSize(), 2u);
		BOOST_CHECK_EQUAL(strArr[1], "1");
		BOOST_CHECK_THROW(strArr[2], out_of_range);
	}
	{
		CMyArray<double> numArr;
		for (int i = 0; i < 5; ++i)
		{
			numArr.Add(i);
		}
		BOOST_CHECK(!numArr.IsEmpty());
		BOOST_CHECK_EQUAL(numArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(numArr[4], 4);
		numArr.Resize(200);
		BOOST_CHECK_EQUAL(numArr.GetSize(), 200u);
		BOOST_CHECK_EQUAL(numArr[1], 1);
		BOOST_CHECK_EQUAL(numArr[100], 0);
		BOOST_CHECK_THROW(numArr[205], out_of_range);
	}
}

BOOST_AUTO_TEST_CASE(TestClearMethod)
{
	{
		CMyArray<string> strArr;
		for (int i = 0; i < 5; ++i)
		{
			strArr.Add(to_string(i));
		}
		BOOST_CHECK_EQUAL(strArr.GetSize(), 5u);
		strArr.Clear();
		BOOST_CHECK(strArr.IsEmpty());
	}
	{
		CMyArray<double> strArr;
		for (int i = 0; i < 5; ++i)
		{
			strArr.Add(i);
		}
		BOOST_CHECK_EQUAL(strArr.GetSize(), 5u);
		strArr.Clear();
		BOOST_CHECK(strArr.IsEmpty());
	}

}

BOOST_AUTO_TEST_CASE(TestCopyingAndAssignment)
{
	{
		CMyArray<string> strArr;
		for (int i = 0; i < 5; ++i)
		{
			strArr.Add(to_string(i));
		}
		{
			CMyArray<string> newArr(strArr);
			BOOST_REQUIRE_NO_THROW(newArr[4]);
		}
		BOOST_REQUIRE_NO_THROW(strArr[4]);
	}
	{
		CMyArray<string> strArr;
		CMyArray<string> newArr;
		for (int i = 0; i < 5; ++i)
		{
			strArr.Add(to_string(i));
		}
		newArr = strArr;
		BOOST_REQUIRE_NO_THROW(newArr[4]);
		BOOST_CHECK_EQUAL(newArr.GetSize(), 5u);
		BOOST_CHECK_EQUAL(newArr[4], "4");
	}
}

BOOST_AUTO_TEST_CASE(EnsureResizeKeepsOldData)
{
	{
		CMyArray<double> dobArr;
		CMyArray<double> doubleArray;
		dobArr.Add(1.3);
		dobArr.Add(1.43);
		dobArr.Add(1.37);
		dobArr.Add(1.23);
		dobArr[0] = 1.33;
		doubleArray = dobArr;
		{
			doubleArray.Resize(5);
			BOOST_CHECK_EQUAL(dobArr[0], 1.33);
			BOOST_CHECK_EQUAL(doubleArray[0], 1.33);
			BOOST_CHECK_EQUAL(doubleArray[1], 1.43);
			BOOST_CHECK_EQUAL(doubleArray[2], 1.37);
			BOOST_CHECK_EQUAL(doubleArray[3], 1.23);
			BOOST_CHECK_EQUAL(doubleArray.GetSize(), 5u);
			BOOST_CHECK(!doubleArray.IsEmpty());
		}
		BOOST_REQUIRE_NO_THROW(doubleArray[4]);
	}
}

BOOST_AUTO_TEST_SUITE_END()