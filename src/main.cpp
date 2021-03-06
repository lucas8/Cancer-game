#include "core/exception.hpp"
#include "i18n.hpp"
#include <guichan.hpp>
#include <exception>
#include <boost/bind.hpp>
#include <SDL/SDL.h>

#include "core/config.hpp"
#include "core/sounds.hpp"
#include "core/event.hpp"
#include "graphics/gui.hpp"

#include "menu.hpp"

int main(int argc, char *argv[])
{
	int retCode = 0;
	core::cfg = NULL;
	core::sounds = NULL;
	core::ev = NULL;
	graphics::gui = NULL;

	try{
		// On charge la configuration
		core::cfg = new core::Config(argc, argv);

		// On charge la SDL
		if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		{
			throw core::Exception( _i("Can't load SDL library.") );
		}
		SDL_EnableUNICODE(SDL_ENABLE);

		// On ouvre la fenêtre
		sdl::AABB size = core::cfg->size();
		Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE;
		if( core::cfg->fullscreen() )
			flags |= SDL_FULLSCREEN;

		if( SDL_SetVideoMode(size->w, size->h, 24, flags) == NULL )
		{
			throw core::Exception( _i("Can't load the window.") );
		}

		// On charge la gui
		graphics::gui = new graphics::Gui(core::cfg->size(), core::cfg->gtheme());

		// On charge le moteur sonore
		core::sounds = new core::Sounds(core::cfg->sounds());
		core::sounds->setMusicVolume( core::cfg->volume() );
		core::sounds->setSoundsVolume( core::cfg->volume(true) );

		// On charge le moteur d'évènements
		core::ev = new sdl::Event;
		core::ev->addQuitKey(SDLK_ESCAPE);
		core::ev->setOnCaptedEventCallback( boost::bind(&graphics::Gui::processEvent, graphics::gui, _1) );

		Menu menu;
		menu.run();
	}
	catch(const core::Exception& e)
	{
		std::cerr << _i("A game error appened : ") << e.what() << std::endl;
		retCode =  1;
	}
	catch(const gcn::Exception& e)
	{
		std::cerr << _i("A guichan error appened : \"") << e.getMessage() << _i("\"") << std::endl;
		retCode =  1;
	}
	catch(const std::exception& e)
	{
		std::cerr << _i("An internal error appened : ") << e.what() << std::endl;
		retCode =  1;
	}
	catch(...)
	{
		std::cerr << _i("An unknown error appened.") << std::endl;
		retCode =  1;
	}

	if( core::cfg != NULL )
		delete core::cfg;
	if( core::sounds != NULL )
		delete core::sounds;
	if( core::ev != NULL )
		delete core::ev;
	if( graphics::gui != NULL )
		delete graphics::gui;

	SDL_Quit();

	return retCode;
}

