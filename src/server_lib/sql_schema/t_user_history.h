#ifndef SCHEMA_T_USER_HISTORY_H
#define SCHEMA_T_USER_HISTORY_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_user_history_ {

		struct C_uid {
			struct _alias_t {
				static constexpr const char _literal[] ="c_uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_uid;
						T &operator()() { return c_uid; }
						const T &operator()() const { return c_uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_action {
			struct _alias_t {
				static constexpr const char _literal[] ="c_action";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_action;
						T &operator()() { return c_action; }
						const T &operator()() const { return c_action; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct C_when {
			struct _alias_t {
				static constexpr const char _literal[] ="c_when";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_when;
						T &operator()() { return c_when; }
						const T &operator()() const { return c_when; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};
	}

	struct t_user_history : sqlpp::table_t<t_user_history,
				t_user_history_::C_uid,
				t_user_history_::C_action,
				t_user_history_::C_when> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_user_history";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_user_history;
					T &operator()() { return t_user_history; }
					const T &operator()() const { return t_user_history; }
				};
		};
	};
}

#endif
