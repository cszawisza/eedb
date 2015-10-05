#ifndef SCHEMA_USER_HISTORY_H
#define SCHEMA_USER_HISTORY_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace user_history_ {

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

		struct Uid {
			struct _alias_t {
				static constexpr const char _literal[] ="uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T uid;
						T &operator()() { return uid; }
						const T &operator()() const { return uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};

		struct Action {
			struct _alias_t {
				static constexpr const char _literal[] ="action";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T action;
						T &operator()() { return action; }
						const T &operator()() const { return action; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};

		struct When_happen {
			struct _alias_t {
				static constexpr const char _literal[] ="when_happen";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T when_happen;
						T &operator()() { return when_happen; }
						const T &operator()() const { return when_happen; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};
	}

	struct user_history : sqlpp::table_t<user_history,
				user_history_::Id,
				user_history_::Uid,
				user_history_::Action,
				user_history_::When_happen> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "user_history";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T user_history;
					T &operator()() { return user_history; }
					const T &operator()() const { return user_history; }
				};
		};
	};
}

#endif
