#ifndef SCHEMA_USER_INVENTORIES_H
#define SCHEMA_USER_INVENTORIES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace user_inventories_ {

		struct Inventory_id {
			struct _alias_t {
				static constexpr const char _literal[] ="inventory_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T inventory_id;
						T &operator()() { return inventory_id; }
						const T &operator()() const { return inventory_id; }
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

	struct user_inventories : sqlpp::table_t<user_inventories,
				user_inventories_::Inventory_id,
				user_inventories_::User_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "user_inventories";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T user_inventories;
					T &operator()() { return user_inventories; }
					const T &operator()() const { return user_inventories; }
				};
		};
	};
}

#endif
