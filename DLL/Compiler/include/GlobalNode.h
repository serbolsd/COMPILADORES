#pragma once
#include "LocalNode.h"
namespace Compiler {

	class GlobalNode
	{
	public:
		GlobalNode();
		~GlobalNode();
	private:
		int m_line;
		std::string m_symbol;
		ESYMBOL_CAT m_cat;
		std::string m_type;
		int m_dim;
		void*m_val=new int(0);
		std::string m_function;
		LocalNode * m_nodolocal = nullptr;
	public:
		//get y set de todos
		void setLine(int line) { m_line = line; };
		void setSymbol(std::string symbol) { m_symbol = symbol; };
		void setCat(ESYMBOL_CAT cat) { m_cat = cat; };
		void setType(std::string type) { m_type = type; };
		void setDim(int dim) { m_dim = dim; };
		void setVal(void*val) { m_val = val; };
		void setFunction(std::string function) { m_function = function; };
		void setNodolocal(LocalNode * nodolocal) { m_nodolocal = nodolocal; };
		int getLine() { return m_line; };
		std::string getSymbol() { return m_symbol; };
		ESYMBOL_CAT getCat() { return m_cat; };
		std::string getType() { return m_type; };
		int getDim() { return m_dim; };
		void*getVal() { return m_val; };
		std::string getFunction() { return m_function; };
		LocalNode * getNodolocal() { return m_nodolocal; };
		void reset();
	};


}