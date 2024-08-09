#include "utils/Temporal_Asset_Manager.h"
#include "utils/Temporal_logger.h"
#include <SDL2/SDL_image.h>

namespace Temporal::Utils
{

    Asset_Manager &Asset_Manager::get()
    {
        static Asset_Manager instance;
        return instance;
    }

    void Asset_Manager::load_asset(const char *path)
    {
        auto loaded_asset = m_surfaces.find(path);
        std::string message = "Asset on ";
        message += path;

        if (loaded_asset != m_surfaces.end())
        {
            message += " is already loaded";
            LOG_INFO(message);
            return;
        }

        SDL_Surface *sfc = IMG_Load(path);
        m_surfaces.insert(std::make_pair(path, sfc));

        message += " loaded";
        LOG_INFO(message);
    }

    SDL_Surface *Asset_Manager::get_asset(const char *path)
    {
        auto loaded_asset = m_surfaces.find(path);
        if (loaded_asset == m_surfaces.end())
        {
            load_asset(path);
        }

        return m_surfaces[path];
    }
    
    void Asset_Manager::clear_from_asset_map(const char* path)
    {
        auto it = m_surfaces.find(path);
        if(it == m_surfaces.end())
        {
            std::string log = std::string(path) + "is not cached to be removed"; 
            LOG_ERROR(log);
        }

        m_surfaces.erase(path);
    }

}