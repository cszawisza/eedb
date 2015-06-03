#ifndef SCHEMA_USER_STORAGES_H
#define SCHEMA_USER_STORAGES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace user_storages_ {

		struct Storage_id {
			struct _alias_t {
				static constexpr const char _literal[] ="storage_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T storage_id;
						T &operator()() { return storage_id; }
						const T &operator()() const { return storage_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct User_id {
			struct _alias_t {
				static constexpr const char _literal[] ="user_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T user_id;
						T &operator()() { return user_id; }
						const T &operator()() const { return user_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct user_storages : sqlpp::table_t<user_storages,
				user_storages_::Storage_id,
				user_storages_::User_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "user_storages";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T user_storages;
					T &operator()() { return user_storages; }
					const T &operator()() const { return user_storages; }
				};
		};
	};
}

#endif
