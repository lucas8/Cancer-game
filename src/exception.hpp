
#ifndef DEF_EXCEPTION
#define DEF_EXCEPTION

#include <exception>
#include <string>

class Exception : public std::exception
{
	public:
		enum ErrType{SDL, NONE}; // Définit le type d'erreur à ajouter

		Exception();
		Exception(const std::string& err, const ErrType& errt = NONE);
		void set(const std::string& err, const ErrType& errt = NONE);

		virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;

	private:
		std::string m_err;
};//class Exception

#endif//DEF_EXCEPTION

