
#ifndef DEF_CORE_CONFIG
#define DEF_CORE_CONFIG

#include <SDLP_position.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
#include <cstdlib>

namespace core
{
	class Config
	{
		public:
			Config();
			Config(int argc, char *argv[]);

			void load(int argc, char *argv[]);

			sdl::AABB size() const;
			bool fullscreen() const;
			boost::filesystem::path sounds() const;
			boost::filesystem::path gtheme() const;

		private:
			boost::program_options::variables_map m_vm;
			boost::program_options::options_description m_opts;

			boost::filesystem::path m_home;

			void setOpts();
			sdl::AABB maxSize() const;
			sdl::AABB parseSize(const std::string& size) const;

			boost::filesystem::path getPath(boost::filesystem::path end) const;

			Config(const Config& cp);
			Config& operator=(const Config& cp);
	};//class Config

	extern Config* cfg;
};//namespace core

#endif//DEF_CORE_CONFIG

