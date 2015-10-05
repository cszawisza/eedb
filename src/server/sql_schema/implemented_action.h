#ifndef SCHEMA_IMPLEMENTED_ACTION_H
#define SCHEMA_IMPLEMENTED_ACTION_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace implemented_action_ {

		struct Table_name {
			struct _alias_t {
				static constexpr const char _literal[] ="table_name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T table_name;
						T &operator()() { return table_name; }
						const T &operator()() const { return table_name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Status {
			struct _alias_t {
				static constexpr const char _literal[] ="status";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T status;
						T &operator()() { return status; }
						const T &operator()() const { return status; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct implemented_action : sqlpp::table_t<implemented_action,
				implemented_action_::Table_name,
				implemented_action_::Action,
				implemented_action_::Status> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "implemented_action";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T implemented_action;
					T &operator()() { return implemented_action; }
					const T &operator()() const { return implemented_action; }
				};
		};
	};
}

#endif
