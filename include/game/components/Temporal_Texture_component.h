#pragma once
#include "SDL2/SDL_render.h"

namespace Temporal::Game::Components
{
	class Texture_Component
	{
	public:
		Texture_Component(SDL_Renderer* renderer);
		~Texture_Component();
		void render();
		SDL_Renderer* get_renderer() const noexcept;
		SDL_Texture* get_texture() const noexcept;
		void scale(float proportion);
		void rotate(double angle);

	private:
		SDL_Texture* m_texture;
		SDL_Renderer* m_renderer;
	};
}

using Temporal_Texture_Component = Temporal::Game::Components::Texture_Component;