#ifndef SCHEMA_INVENTORIES_HISTORY_H
#define SCHEMA_INVENTORIES_HISTORY_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace inventories_history_ {

		struct Inventory_from_id {
			struct _alias_t {
				static constexpr const char _literal[] ="inventory_from_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T inventory_from_id;
						T &operator()() { return inventory_from_id; }
						const T &operator()() const { return inventory_from_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct Inventory_to_id {
			struct _alias_t {
				static constexpr const char _literal[] ="inventory_to_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T inventory_to_id;
						T &operator()() { return inventory_to_id; }
						const T &operator()() const { return inventory_to_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct Operation_id {
			struct _alias_t {
				static constexpr const char _literal[] ="operation_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T operation_id;
						T &operator()() { return operation_id; }
						const T &operator()() const { return operation_id; }
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

	struct inventories_history : sqlpp::table_t<inventories_history,
				inventories_history_::Inventory_from_id,
				inventories_history_::Inventory_to_id,
				inventories_history_::Operation_id,
				inventories_history_::Amount,
				inventories_history_::Date> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "inventories_history";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T inventories_history;
					T &operator()() { return inventories_history; }
					const T &operator()() const { return inventories_history; }
				};
		};
	};
}

#endif
