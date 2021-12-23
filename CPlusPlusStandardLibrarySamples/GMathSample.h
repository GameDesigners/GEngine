#ifndef GMATH_SAMPLE_H
#define GMATH_SAMPLE_H
#include <GVector2.h>
#include <GVector3.h>
#include <GVector4.h>
#include <GMatrix2X2.h>
using namespace GEngine::GMath;

void GMathSample()
{
	GVector2 direction(-1, 1);
	GVector2 normal(0, 1);
	GVector2 reflction = GVector2::Reflect(direction, normal);
	cout << "(" << reflction.x << "," << reflction.y << ")" << endl;

	cout << "min:" << GFLOAT_MIN << endl;
	cout << "max:" << GFLOAT_NAX << endl;

	wcout << GVector2::One.ToString().c_str() << endl;
	wcout << GVector2Int::One.ToString().c_str() << endl;
	wcout << GVector3::One.ToString().c_str() << endl;
	wcout << GVector3Int::Right.ToString().c_str() << endl;

	GVector3 vector3 = GVector3::One;
	cout << "(" << vector3.x << "," << vector3.y << "," << vector3.z << ")" << endl;
	cout << "(" << vector3[0] << "," << vector3[1] << "," << vector3[2] << ")" << endl;
	cout << "(" << vector3.x << "," << vector3.y << "," << vector3.z << ")" << endl;



	GMatrix2X2 matrix2x2_1(1, 2, 3, 4);
	GMatrix2X2 matrix2x2_2(1, 1, 1, 1);
	//matrix2x2_1.Transpose();
	wcout << matrix2x2_1.ToString().c_str() << endl;
	wcout << matrix2x2_2.ToString().c_str() << endl;
	GMatrix2X2 addres = matrix2x2_1 + matrix2x2_2;
	GMatrix2X2 subres = matrix2x2_1 - matrix2x2_2;
	GMatrix2X2 mulres = matrix2x2_1 * matrix2x2_2;

	wcout << "ADD:" << endl << addres.ToString().c_str() << endl;
	wcout << "SUB:" << endl << subres.ToString().c_str() << endl;
	wcout << "MUL:" << endl << mulres.ToString().c_str() << endl;

}

#endif // !GMATH_SAMPLE_H
