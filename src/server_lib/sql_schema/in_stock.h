#ifndef SCHEMA_IN_STOCK_H
#define SCHEMA_IN_STOCK_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace in_stock_ {

		struct Item_id {
			struct _alias_t {
				static constexpr const char _literal[] ="item_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T item_id;
						T &operator()() { return item_id; }
						const T &operator()() const { return item_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct Storage_id {
			struct _alias_t {
				static constexpr const char _literal[] ="storage_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T storage_id;
						T &operator()() { return storage_id; }
						const T &operator()() const { return storage_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct Amount {
			struct _alias_t {
				static constexpr const char _literal[] ="amount";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T amount;
						T &operator()() { return amount; }
						const T &operator()() const { return amount; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};
	}

	struct in_stock : sqlpp::table_t<in_stock,
				in_stock_::Item_id,
				in_stock_::Storage_id,
				in_stock_::Amount> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "in_stock";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T in_stock;
					T &operator()() { return in_stock; }
					const T &operator()() const { return in_stock; }
				};
		};
	};
}

#endif
