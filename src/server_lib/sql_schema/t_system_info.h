#ifndef SCHEMA_T_SYSTEM_INFO_H
#define SCHEMA_T_SYSTEM_INFO_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_system_info_ {

		struct C_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_id;
						T &operator()() { return c_id; }
						const T &operator()() const { return c_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
		};

		struct C_name {
			struct _alias_t {
				static constexpr const char _literal[] ="c_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_name;
						T &operator()() { return c_name; }
						const T &operator()() const { return c_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};

		struct C_value {
			struct _alias_t {
				static constexpr const char _literal[] ="c_value";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_value;
						T &operator()() { return c_value; }
						const T &operator()() const { return c_value; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	}

	struct t_system_info : sqlpp::table_t<t_system_info,
				t_system_info_::C_id,
				t_system_info_::C_name,
				t_system_info_::C_value> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_system_info";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_system_info;
					T &operator()() { return t_system_info; }
					const T &operator()() const { return t_system_info; }
				};
		};
	};
}

#endif
