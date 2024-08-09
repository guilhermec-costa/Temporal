#include "utils/Temporal_Asset_Manager.h"
#include "utils/Temporal_logger.h"
#include <SDL2/SDL_image.h>

namespace Temporal::Utils
{

    void Asset_Manager::load_asset(const std::string& path)
    {
        auto loaded_asset = m_surfaces_map.find(path);
        std::string message = "Asset on ";
        message += path;

        if (loaded_asset != m_surfaces_map.end())
        {
            message += " is already loaded";
            LOG_WARNING(message);
            return;
        }

        SDL_Surface *sfc = IMG_Load(path.c_str());
        if (sfc == nullptr)
        {
            message += " failed to load!";
            LOG_ERROR(message);
            return;
        }

        m_surfaces_map.insert(std::make_pair(path, sfc));
        message += " loaded";
        LOG_INFO(message);
    }

    SDL_Surface *Asset_Manager::get_asset(const std::string& path)
    {
        auto loaded_asset = m_surfaces_map.find(path);
        if (loaded_asset == m_surfaces_map.end())
        {
            load_asset(path);
            loaded_asset = m_surfaces_map.find(path);
            if (loaded_asset == m_surfaces_map.end() || loaded_asset->second == nullptr)
            {
                LOG_ERROR("Failed to get asset at: " + std::string(path));
                return nullptr;
            }
        }

        return loaded_asset->second;
    }

    void Asset_Manager::clear_from_asset_map(const std::string& path)
    {
        auto it = m_surfaces_map.find(path);
        if (it == m_surfaces_map.end() || !it->second)
        {
            std::string log = std::string(path) + "is not cached to be removed";
            LOG_ERROR(log);
        }

        m_surfaces_map.erase(path);
    }

}