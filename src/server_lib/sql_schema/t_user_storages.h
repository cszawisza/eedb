#ifndef SCHEMA_T_USER_STORAGES_H
#define SCHEMA_T_USER_STORAGES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_user_storages_ {

		struct C_storage_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_storage_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_storage_id;
						T &operator()() { return c_storage_id; }
						const T &operator()() const { return c_storage_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_user_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_user_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_user_id;
						T &operator()() { return c_user_id; }
						const T &operator()() const { return c_user_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct t_user_storages : sqlpp::table_t<t_user_storages,
				t_user_storages_::C_storage_id,
				t_user_storages_::C_user_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_user_storages";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_user_storages;
					T &operator()() { return t_user_storages; }
					const T &operator()() const { return t_user_storages; }
				};
		};
	};
}

#endif
