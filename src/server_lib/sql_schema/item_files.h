#ifndef SCHEMA_ITEM_FILES_H
#define SCHEMA_ITEM_FILES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace item_files_ {

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

		struct File_id {
			struct _alias_t {
				static constexpr const char _literal[] ="file_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T file_id;
						T &operator()() { return file_id; }
						const T &operator()() const { return file_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct item_files : sqlpp::table_t<item_files,
				item_files_::Item_id,
				item_files_::File_id> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "item_files";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T item_files;
					T &operator()() { return item_files; }
					const T &operator()() const { return item_files; }
				};
		};
	};
}

#endif
