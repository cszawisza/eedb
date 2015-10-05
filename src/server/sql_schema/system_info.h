#ifndef SCHEMA_SYSTEM_INFO_H
#define SCHEMA_SYSTEM_INFO_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace system_info_ {

		struct Id {
			struct _alias_t {
				static constexpr const char _literal[] ="id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T id;
						T &operator()() { return id; }
						const T &operator()() const { return id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
		};

		struct Name {
			struct _alias_t {
				static constexpr const char _literal[] ="name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T name;
						T &operator()() { return name; }
						const T &operator()() const { return name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};

		struct Value {
			struct _alias_t {
				static constexpr const char _literal[] ="value";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T value;
						T &operator()() { return value; }
						const T &operator()() const { return value; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};
	}

	struct system_info : sqlpp::table_t<system_info,
				system_info_::Id,
				system_info_::Name,
				system_info_::Value> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "system_info";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T system_info;
					T &operator()() { return system_info; }
					const T &operator()() const { return system_info; }
				};
		};
	};
}

#endif
