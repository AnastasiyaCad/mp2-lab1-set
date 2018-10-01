// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)	{
		MemLen = len / (sizeof(TELEM) * 8);
		if (len % (sizeof(TELEM) * 8) > 0)
			MemLen++;
		BitLen = len;
		pMem = new TELEM [MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else 
	{
		throw "ERROR";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));	
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n >= 0) && (n <= BitLen)) { 
		TELEM mask = 1;
		int PositionBit = (n % (sizeof(TELEM) * 8));
		mask = mask << PositionBit;
		return mask;
	}
	else{
		throw "ERROR";
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n <= BitLen)) {
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
	else
	{
		throw "ERROR";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n <= BitLen)) {
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	}
	else
	{
		throw "ERROR";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen)) {
		if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == GetMemMask(n))
			return 1;
		else return 0;
	}
	else
	{
		throw "ERROR";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen == bf.MemLen)
	{
		BitLen = bf.BitLen;
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	if (MemLen != bf.MemLen) {
		delete[] pMem;
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen)
	{
		int num = 0;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
				num++;
		if (num == MemLen) 
			return 1;
		else return 0;
	}
	else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen)
	{
		int num = 0;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
				num++;
		if (num == MemLen)
			return 0;
		else return 1;
	}
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < BitLen; i++)
	{
		int NumberBit = i / (sizeof(TELEM) * 8);
		pMem[NumberBit] = pMem[NumberBit] ^ GetMemMask(i);
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string strtmp;
	//cin >> strtmp;
	const char* tmp = strtmp.c_str();
	TBitField b(strlen(tmp));
	for (int i = 0; i < strlen(tmp); i++)
	{
		if (tmp[i] == '1')
		{
			b.SetBit(i);
		}
	}
	bf = b;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		int NumberBit = i / (sizeof(TELEM) * 8);
		if ((bf.pMem[NumberBit] & bf.GetMemMask(i)) == bf.GetMemMask(i))
		{
			ostr << "1";
		}
		else
		{
			ostr << "0";
		}
	}
	return ostr;
}
