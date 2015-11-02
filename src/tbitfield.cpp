// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{ 
	if (len < 0)
		throw std::exception("TBitField(int len): wrong len");
	else {
	BitLen = len;
	MemLen = (BitLen + (8 * sizeof(TELEM) - 1)) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
 	for (int i = 0; i < MemLen; i++)
 	{
		pMem[i] = 0;
	}
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
	if (pMem != NULL)
		delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen))
		throw std::exception("TGetMemIndex(const int n): wrong index");
	else 
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen))
		throw std::exception("GetMemMask(const int n): wrong index");
	else
	return 1 << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{ 
	if ((n < 0) || (n > BitLen))
		throw std::exception("SetBit(const int n): wrong index");
	else
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw std::exception("ClrBit(const int n): wrong index");
	else
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw std::exception("GetBit(const int n): wrong index");
	else {
		TELEM temp = GetMemMask(n);
		if((pMem[GetMemIndex(n)]&temp) == 0)
			return 0;
		else
			return 1;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete []pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM [MemLen];
	}

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
		{
			if(pMem[i] != bf.pMem[i])
				return 0;
		}
		
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
		return 1;
	else
		for (int i = 0; i < MemLen; i++)
		{
			if(pMem[i] != bf.pMem[i])
				return 1;
		}
		
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	int maxLen = BitLen;
	if (bf.BitLen > BitLen)
		maxLen = bf.BitLen;

	TBitField tmp(maxLen);

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] = pMem[i]; 
	}

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = bf.pMem[i]|tmp.pMem[i]; 
	}

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	
	
	int maxLen = BitLen;
	if (bf.BitLen > BitLen)
		maxLen = bf.BitLen;

	TBitField tmp(maxLen);

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] = pMem[i]; 
	}
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] =  bf.pMem[i]&tmp.pMem[i]; 		
	}

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (this->GetBit(i) == 0)
			tmp.SetBit(i);
	}

	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i;
	for (int i = 0; i < bf.BitLen; i ++)
	{
		while ((i != 0) && (i != 1))
			istr >> i;
		if (i != 0)
			bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
