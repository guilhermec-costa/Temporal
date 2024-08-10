#pragma once
#include "game/Temporal_game.h"
#include "utils/Temporal_logger.h"
#include "utils/Temporal_Asset_Manager.h"
#include "utils/Temporal_Texture_manager.h"
#include "game/Texture_paths.hpp"
#include "game/entities/Temporal_Player.h"

typedef Temporal::Game::TemporalGame TemporalGame;
typedef Temporal::Game::Temporal_SDL_Renderer Temporal_SDL_Renderer;
typedef Temporal::Game::Temporal_SDL_Window Temporal_SDL_Window;
typedef Temporal::Utils::Asset_Manager Temporal_Asset_Manager;
typedef Temporal::Utils::Temporal_Texture_Manager Temporal_Texture_Manager;
typedef Temporal::Game::Entities::Player Temporal_Player;
namespace Temporal_Resources = Temporal::Resources;
typedef Temporal::Utils::Logger Logger;

