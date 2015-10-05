#ifndef SCHEMA_STAT_H
#define SCHEMA_STAT_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace stat_ {

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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Creation_date {
			struct _alias_t {
				static constexpr const char _literal[] ="creation_date";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T creation_date;
						T &operator()() { return creation_date; }
						const T &operator()() const { return creation_date; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Last_acces {
			struct _alias_t {
				static constexpr const char _literal[] ="last_acces";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T last_acces;
						T &operator()() { return last_acces; }
						const T &operator()() const { return last_acces; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Last_update {
			struct _alias_t {
				static constexpr const char _literal[] ="last_update";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T last_update;
						T &operator()() { return last_update; }
						const T &operator()() const { return last_update; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};
	}

	struct stat : sqlpp::table_t<stat,
				stat_::Name,
				stat_::Creation_date,
				stat_::Last_acces,
				stat_::Last_update> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "stat";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T stat;
					T &operator()() { return stat; }
					const T &operator()() const { return stat; }
				};
		};
	};
}

#endif
