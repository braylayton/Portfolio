#include "stdafx.h"
#include "CppUnitTest.h"

#include <Math/Inc/QMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SWGE::Math;

namespace MathTest
{		
	TEST_CLASS(Vector3Test)
	{
	public:

		TEST_METHOD(QuaternionAddition)
		{
			Quaternion a{ 1.0f, 2.0f, 3.0f, 4.0f };
			Quaternion b{ 4.0f, 3.0f, 2.0f, 1.0f };
			Quaternion c = a + b;
			Assert::IsTrue(c.x == 5.0f);
			Assert::IsTrue(c.y == 5.0f);
			Assert::IsTrue(c.z == 5.0f);
			Assert::IsTrue(c.w == 5.0f);
		}
		TEST_METHOD(QuaternionSubtraction)
		{
			Quaternion a{ 1.0f, 2.0f, 3.0f, 4.0f };
			Quaternion b{ 4.0f, 3.0f, 2.0f, 1.0f };
			Quaternion c = a - b;
			Assert::IsTrue(c.x == -3.0f);
			Assert::IsTrue(c.y == -1.0f);
			Assert::IsTrue(c.z == 1.0f);
			Assert::IsTrue(c.w == 3.0f);
		}
		TEST_METHOD(QuaternionScalerMultiplication)
		{
			Quaternion a{ 1.0f, 2.0f, 3.0f, 4.0f };
			float b{2.0f};
			Quaternion c = a * b;
			Assert::IsTrue(c.x == 2.0f);
			Assert::IsTrue(c.y == 4.0f);
			Assert::IsTrue(c.z == 6.0f);
			Assert::IsTrue(c.w == 8.0f);
		}
		TEST_METHOD(QuaternionMultiplication)
		{
			Quaternion a{ 1.0f, 2.0f, 3.0f, 4.0f };
			Quaternion b{ 4.0f, 3.0f, 2.0f, 1.0f };
			Quaternion c = a * b;
			Assert::IsTrue(c.x == 12.0f);
			Assert::IsTrue(c.y == 24.0f);
			Assert::IsTrue(c.z == 6.0f);
			Assert::IsTrue(c.w == -12.0f);
		}
		TEST_METHOD(MatrixToQuaternion)
		{
			Quaternion q{ 2.0f,2.0f,2.0f,2.0f };
			Matrix4 mat = QuaternionToMatrix4(q);
			Assert::IsTrue(mat._11 == 0.0f);
			Assert::IsTrue(mat._12 == 0.0f);
			Assert::IsTrue(mat._13 == 1.0f);
			Assert::IsTrue(mat._14 == 0.0f);
			Assert::IsTrue(mat._21 == 1.0f);
			Assert::IsTrue(mat._22 == 0.0f);
			Assert::IsTrue(mat._23 == 0.0f);
			Assert::IsTrue(mat._24 == 0.0f);
			Assert::IsTrue(mat._31 == 0.0f);
			Assert::IsTrue(mat._32 == 1.0f);
			Assert::IsTrue(mat._33 == 0.0f);
			Assert::IsTrue(mat._34 == 0.0f);
			Assert::IsTrue(mat._41 == 0.0f);
			Assert::IsTrue(mat._42 == 0.0f);
			Assert::IsTrue(mat._43 == 0.0f);
			Assert::IsTrue(mat._44 == 1.0f);
			

		}

	};
}