#pragma once
#include "LexAnalyzer.h"
#include "ErrorModule.h"
#include "SymbolTable.h"
#include "SyntaxState.h"
#include <vector>
#include <string>

namespace Compiler 
{
	class SyntaxAnalysis
	{
	private:
		LexAnalyzer *m_lex;
	public:
		msclr::gcroot<ErrorModule^>m_err;
		SymbolTable * m_stab;
		SyntaxAnalysis(LexAnalyzer *lex, ErrorModule ^err, SymbolTable * stab);
		~SyntaxAnalysis();
		void checkSyntax(SyntaxAnalysis * syn);
		std::vector<std::string> m_IDs;
		std::vector<std::string> m_ParamsIDs;
		std::vector<std::string> m_LocalIDs;
		std::vector<std::string> m_Dimension;
		std::vector<std::string> m_LocalDimension;
		std::vector<std::string> m_DimensionParams;
		std::vector<int> linea;
		std::vector<int> lineaParams;
		std::vector<int> lineaLocal;
		std::string tipe = "<UNKNOW>";
		std::string inFunctionType = "<UNKNOW>";
		ESYMBOL_CAT category = ESYMBOL_CAT::GLOBAL_VAR;
		ESYMBOL_CAT inFunctionCategory = ESYMBOL_CAT::GLOBAL_VAR;
		std::string function = "<GLOBAL SCOPE>";
		void cleanIDs();
		void cleanParams();
		void cleanLocal();
		String^ getSymbolTable();
		bool isMain = false;
		bool finishAnalysis = false;;
		bool inFunction = false;;
		void clean();
	};


}