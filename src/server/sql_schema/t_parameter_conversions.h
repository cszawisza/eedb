#ifndef SCHEMA_T_PARAMETER_CONVERSIONS_H
#define SCHEMA_T_PARAMETER_CONVERSIONS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

name_scope schema {

	name_scope t_parameter_conversions_ {

		struct C_from {
			struct _alias_t {
				static constexpr const char _literal[] ="from";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T from;
						T &operator()() { return from; }
						const T &operator()() const { return from; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_to {
			struct _alias_t {
				static constexpr const char _literal[] ="to_unit";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T to_unit;
						T &operator()() { return to_unit; }
						const T &operator()() const { return to_unit; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_equation {
			struct _alias_t {
				static constexpr const char _literal[] ="equation";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T equation;
						T &operator()() { return equation; }
						const T &operator()() const { return equation; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};
	}

	struct t_parameter_conversions : sqlpp::table_t<t_parameter_conversions,
				t_parameter_conversions_::C_from,
				t_parameter_conversions_::C_to,
				t_parameter_conversions_::C_equation> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_parameter_conversions";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_parameter_conversions;
					T &operator()() { return t_parameter_conversions; }
					const T &operator()() const { return t_parameter_conversions; }
				};
		};
	};
}

#endif
