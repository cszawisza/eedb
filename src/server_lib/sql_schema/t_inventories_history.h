#ifndef SCHEMA_T_INVENTORIES_HISTORY_H
#define SCHEMA_T_INVENTORIES_HISTORY_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_inventories_history_ {

		struct C_inventory_from_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_inventory_from_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_inventory_from_id;
						T &operator()() { return c_inventory_from_id; }
						const T &operator()() const { return c_inventory_from_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_inventory_to_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_inventory_to_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_inventory_to_id;
						T &operator()() { return c_inventory_to_id; }
						const T &operator()() const { return c_inventory_to_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_operation_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_operation_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_operation_id;
						T &operator()() { return c_operation_id; }
						const T &operator()() const { return c_operation_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_amount {
			struct _alias_t {
				static constexpr const char _literal[] ="c_amount";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_amount;
						T &operator()() { return c_amount; }
						const T &operator()() const { return c_amount; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
		};

		struct Date {
			struct _alias_t {
				static constexpr const char _literal[] ="date";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T date;
						T &operator()() { return date; }
						const T &operator()() const { return date; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};
	}

	struct t_inventories_history : sqlpp::table_t<t_inventories_history,
				t_inventories_history_::C_inventory_from_id,
				t_inventories_history_::C_inventory_to_id,
				t_inventories_history_::C_operation_id,
				t_inventories_history_::C_amount,
				t_inventories_history_::Date> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_inventories_history";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_inventories_history;
					T &operator()() { return t_inventories_history; }
					const T &operator()() const { return t_inventories_history; }
				};
		};
	};
}

#endif
