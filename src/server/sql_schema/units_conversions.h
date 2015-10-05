#ifndef SCHEMA_UNITS_CONVERSIONS_H
#define SCHEMA_UNITS_CONVERSIONS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace units_conversions_ {

		struct From_unit {
			struct _alias_t {
				static constexpr const char _literal[] ="from_unit";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T from_unit;
						T &operator()() { return from_unit; }
						const T &operator()() const { return from_unit; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct To_unit {
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

		struct Equation {
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

	struct units_conversions : sqlpp::table_t<units_conversions,
				units_conversions_::From_unit,
				units_conversions_::To_unit,
				units_conversions_::Equation> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "units_conversions";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T units_conversions;
					T &operator()() { return units_conversions; }
					const T &operator()() const { return units_conversions; }
				};
		};
	};
}

#endif
