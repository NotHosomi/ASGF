#include <type_traits>
#include "Window.h"
#include "Input.h"

namespace ASGF
{
	class Simulation
	{
		Simulation();
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	template <typename _Ty>
	concept _DerivedSimType = std::is_base_of<Simulation, _Ty>::value;
	template<_DerivedSimType T>
	void Run(int nWidth, int nHeight)
	{
		Window w(nWidth, nHeight);
		Game game();
		w.Run(std::bind(&Game::Update, &game),
		  std::bind(&Game::Render, &game));
		w.Close();
	}
}