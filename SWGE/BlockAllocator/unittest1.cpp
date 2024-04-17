#include "stdafx.h"
#include "CppUnitTest.h"
#include "Core\Inc\Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SWGE::Core;

namespace BlockAllocatorTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			data = (uint32_t*)blockAllocator.Allocate();
			*data = 10;

			Assert::IsNotNull(data);
		}
		TEST_METHOD(TestMethod2)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			uint32_t* data2{ nullptr };
			data = (uint32_t*)blockAllocator.Allocate();
			data2 = (uint32_t*)blockAllocator.Allocate();
			*data = 10;
			*data2 = 9;

			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
		}
		TEST_METHOD(TestMethod3)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			uint32_t* data2{ nullptr };
			uint32_t* data3{ nullptr };
			uint32_t* data4{ nullptr };
			uint32_t* data5{ nullptr };
			data = (uint32_t*)blockAllocator.Allocate();
			data2 = (uint32_t*)blockAllocator.Allocate();
			data3 = (uint32_t*)blockAllocator.Allocate();
			data4 = (uint32_t*)blockAllocator.Allocate();
			data5 = (uint32_t*)blockAllocator.Allocate();

			*data = 10;
			*data2 = 9;
			*data3 = 12;
			*data4 = 15;

			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
			Assert::IsNotNull(data3);
			Assert::IsNotNull(data4);
			Assert::IsNull(data5);
		}
		TEST_METHOD(TestMethod4)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			uint32_t* data2{ nullptr };
			uint32_t* data3{ nullptr };
			uint32_t* data4{ nullptr };
			uint32_t* data5{ nullptr };
			data = (uint32_t*)blockAllocator.Allocate();
			data2 = (uint32_t*)blockAllocator.Allocate();
			data3 = (uint32_t*)blockAllocator.Allocate();
			data4 = (uint32_t*)blockAllocator.Allocate();

			*data = 10;
			*data2 = 9;
			*data3 = 12;
			*data4 = 15;
			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
			Assert::IsNotNull(data3);
			Assert::IsNotNull(data4);

			blockAllocator.Free(data);
			blockAllocator.Free(data2);
		
		}
		TEST_METHOD(TestMethod5)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			uint32_t* data2{ nullptr };
			uint32_t* data3{ nullptr };
			uint32_t* data4{ nullptr };
			uint32_t* data5{ nullptr };
			data = (uint32_t*)blockAllocator.Allocate();
			data2 = (uint32_t*)blockAllocator.Allocate();
			data3 = (uint32_t*)blockAllocator.Allocate();
			data4 = (uint32_t*)blockAllocator.Allocate();

			*data = 10;
			*data2 = 9;
			*data3 = 12;
			*data4 = 15;
			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
			Assert::IsNotNull(data3);
			Assert::IsNotNull(data4);

			blockAllocator.Free(data);
			blockAllocator.Free(data2);

			uint32_t* data10{ nullptr };
			data10 = (uint32_t*)blockAllocator.Allocate();
			*data10 = 24;
			Assert::IsNotNull(data10);
		}

		TEST_METHOD(TestMethod0000)
		{
			BlockAllocator blockAllocator(4, 4);
			uint32_t* data{ nullptr };
			uint32_t* data2{ nullptr };
			uint32_t* data3{ nullptr };
			uint32_t* data4{ nullptr };
	
			data = (uint32_t*)blockAllocator.Allocate();
			data2 = (uint32_t*)blockAllocator.Allocate();
			data3 = (uint32_t*)blockAllocator.Allocate();
			data4 = (uint32_t*)blockAllocator.Allocate();

			*data = 10;
			*data2 = 9;
			*data3 = 12;
			*data4 = 15;

			Assert::IsNotNull(data);
			Assert::IsNotNull(data2);
			Assert::IsNotNull(data3);
			Assert::IsNotNull(data4);

			blockAllocator.Free(data);
			blockAllocator.Free(data2);
			blockAllocator.Free(data2);
			blockAllocator.Free(data2);
			blockAllocator.Free(data2);


			uint32_t* data10{ nullptr };
			data10 = (uint32_t*)blockAllocator.Allocate();
			*data10 = 24;
			Assert::IsNotNull(data10);
		}


		TEST_METHOD(TemplateAllocatorTest1)
		{

		}
	};
}