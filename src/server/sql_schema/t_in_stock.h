#ifndef SCHEMA_T_IN_STOCK_H
#define SCHEMA_T_IN_STOCK_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_in_stock_ {

		struct C_item_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_item_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_item_id;
						T &operator()() { return c_item_id; }
						const T &operator()() const { return c_item_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct C_inventory_id {
			struct _alias_t {
				static constexpr const char _literal[] ="c_inventory_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_inventory_id;
						T &operator()() { return c_inventory_id; }
						const T &operator()() const { return c_inventory_id; }
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

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};
	}

	struct t_in_stock : sqlpp::table_t<t_in_stock,
				t_in_stock_::C_item_id,
				t_in_stock_::C_inventory_id,
				t_in_stock_::C_amount> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_in_stock";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_in_stock;
					T &operator()() { return t_in_stock; }
					const T &operator()() const { return t_in_stock; }
				};
		};
	};
}

#endif
