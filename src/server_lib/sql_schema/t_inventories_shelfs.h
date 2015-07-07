#ifndef SCHEMA_T_INVENTORIES_SHELFS_H
#define SCHEMA_T_INVENTORIES_SHELFS_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace t_inventories_shelfs_ {

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

		struct C_shelf {
			struct _alias_t {
				static constexpr const char _literal[] ="c_shelf";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_shelf;
						T &operator()() { return c_shelf; }
						const T &operator()() const { return c_shelf; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::require_insert>;
		};
	}

	struct t_inventories_shelfs : sqlpp::table_t<t_inventories_shelfs,
				t_inventories_shelfs_::C_inventory_id,
				t_inventories_shelfs_::C_shelf> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "t_inventories_shelfs";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T t_inventories_shelfs;
					T &operator()() { return t_inventories_shelfs; }
					const T &operator()() const { return t_inventories_shelfs; }
				};
		};
	};
}

#endif
