#pragma once

namespace Compiler
{
	class State
	{
	public:
		State() {};
		virtual ~State() {};
		virtual State update() {};
	private:

	};
}

