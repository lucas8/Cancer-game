CXXFLAGS=-Wall -Wextra
CXXFLAGS+= `pkg-config --cflags SDLP_event SDLP_tools SDLP_position SDL_image SDL_mixer SDL_ttf guichan-0.8 guichan_sdl-0.8`
CXXFLAGS+= `sdl-config --cflags`
LDFLAGS=`pkg-config --libs SDLP_event SDLP_tools SDLP_position SDL_image SDL_mixer SDL_ttf guichan-0.8 guichan_sdl-0.8`
LDFLAGS+= `sdl-config --libs`
LDFLAGS+= -ltinyxml -lboost_filesystem -lboost_system -lboost_program_options
CC=g++


