﻿#pragma once

#include "Scaner.h"
#include "Tree.h"

class Diagram
{
private:
	Scaner *scaner;
	Tree *tree;

	void Data();					 // Данные
	void Named_const();				 // Именованная константа
	void Function();				 // Функция
	void Type();					 // Тип
	void Assignment();				 // Присваивание
	void Expression();				 // Выражение
	void CompositeOperator();		 // Составной оператор
	void OperatorsAndDescriptions(); // Операторы и описания
	void Operator();				 // Оператор
	void FunctionCall();			 // Вызов функции
	void Comparison();				 // Сравнение
	void Summand();					 // Слагаемое
	void Multiplier();				 // Множитель
	void UnaryOperation();			 // Унарная операция
	void ElementaryExpression();	 // Элементарное выражение
	void For_operator();			 // Цикл
	int LookForward(int pointer);
	int Scan(type_lex lex);

public:
	Diagram(Scaner *scaner, Tree *tree);
	void Program(); // Программа
};