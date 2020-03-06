#pragma once
#include <string.h>
#include <iostream>
namespace Compiler {
	enum ESYMBOL_CAT
	{
		UNDEFINE = 0,
		GLOBAL_VAR,
		LOCAL_VAR,
		FUNCTION,
		PARAMETER
	};
	class LocalNode
	{
	public:
		LocalNode();
		~LocalNode();

	private:
		int m_line;
		ESYMBOL_CAT m_cat =ESYMBOL_CAT::UNDEFINE;
		std::string m_type;
		int m_dim;
		void*m_val=new int(0);//revisar el auto *
		std::string m_func;
		LocalNode * m_nodolocal = nullptr;
	public:
		//get y set de todos;
		void setLine(int line) { m_line = line; };
		void setCat(ESYMBOL_CAT cat) { m_cat = cat; };
		void setType(std::string type) { m_type = type; };
		void setDim(int dim) { m_dim = dim; };
		void setVal(void* val) { m_val = val; };
		void setFunc(std::string func) { m_func = func; };
		void setNodoLocal(LocalNode * nodolocal) { m_nodolocal = nodolocal; };
		int getLine() { return m_line; };
		ESYMBOL_CAT getCat() { return m_cat; };
		std::string getType() { return m_type; };
		int getDim() { return m_dim; };
		void*getVal() { return m_val; };
		std::string getFunc() { return m_func; };
		LocalNode * getNodolocal() { return m_nodolocal; };
		void reset();
		void remove();



	};
}