#ifndef SCHEMA_T_PARAMETER_CONVERSIONS_H
#define SCHEMA_T_PARAMETER_CONVERSIONS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_parameter_conversions_ {

		struct C_from {
			struct _alias_t {
				static constexpr const char _literal[] ="c_from";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_from;
						T &operator()() { return c_from; }
						const T &operator()() const { return c_from; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_to {
			struct _alias_t {
				static constexpr const char _literal[] ="c_to";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_to;
						T &operator()() { return c_to; }
						const T &operator()() const { return c_to; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_equation {
			struct _alias_t {
				static constexpr const char _literal[] ="c_equation";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_equation;
						T &operator()() { return c_equation; }
						const T &operator()() const { return c_equation; }
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
