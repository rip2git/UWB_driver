#ifndef USERPACKSCONVERTER_H_
#define USERPACKSCONVERTER_H_


#include "UserPackFW.h"
#include "UserPackHL.h"


/*! ----------------------------------------------------------------------------------------
 * @brief:
 * -----------------------------------------------------------------------------------------
 * */
class UserPacksConverter {
public:
	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	static UserPackHL ToHL(const UserPackFW &pack);
	static UserPackHL ToHL(const std::vector <UserPackFW> &pack);

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	static std::vector<UserPackFW> ToFW(const UserPackHL &pack, const uint8_t buffer_size);

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	UserPacksConverter() = delete;
	~UserPacksConverter() = delete;
	UserPacksConverter(UserPacksConverter const&) = delete;
	UserPacksConverter& operator= (UserPacksConverter const&) = delete;
};

#endif /* USERPACKSCONVERTER_H_ */
