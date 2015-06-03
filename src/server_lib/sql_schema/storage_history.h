#ifndef SCHEMA_STORAGE_HISTORY_H
#define SCHEMA_STORAGE_HISTORY_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace storage_history_ {

		struct Storage_from_id {
			struct _alias_t {
				static constexpr const char _literal[] ="storage_from_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T storage_from_id;
						T &operator()() { return storage_from_id; }
						const T &operator()() const { return storage_from_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};

		struct Storage_to_id {
			struct _alias_t {
				static constexpr const char _literal[] ="storage_to_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T storage_to_id;
						T &operator()() { return storage_to_id; }
						const T &operator()() const { return storage_to_id; }
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

	struct storage_history : sqlpp::table_t<storage_history,
				storage_history_::Storage_from_id,
				storage_history_::Storage_to_id,
				storage_history_::Operation_id,
				storage_history_::Amount,
				storage_history_::Date> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "storage_history";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T storage_history;
					T &operator()() { return storage_history; }
					const T &operator()() const { return storage_history; }
				};
		};
	};
}

#endif
