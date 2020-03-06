#pragma once
#include <string.h>
#include <iostream>
#include <map>
#include "GlobalNode.h"
#include <vector>
#include "ErrorModule.h"

#include "windows.h"
#include "vcclr.h"
namespace Compiler
{

	class SymbolTable
	{

	public:
		SymbolTable();
		SymbolTable(ErrorModule ^err);
		~SymbolTable();
	private:
		//std::map<std::string, GlobalNode*> m_symbols;
	public:
		std::vector<GlobalNode*> m_symbols;
		void getAllSymbols();
		bool addSymbol(int lineNum, std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp);
		bool symbolExists(int lineNum, std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp);
		std::string getSymbolScope(std::string name);
		std::string getSymbolType();
		bool updateSymbolType();
		void reset();
		void* getSymbol(std::string name, ESYMBOL_CAT cat, std::string func);
		msclr::gcroot<ErrorModule^>m_err;
	};
}