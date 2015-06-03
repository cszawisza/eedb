#ifndef SCHEMA_CATEGORIES_H
#define SCHEMA_CATEGORIES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace categories_ {

		struct C_uid {
			struct _alias_t {
				static constexpr const char _literal[] ="c_uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_uid;
						T &operator()() { return c_uid; }
						const T &operator()() const { return c_uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_owner {
			struct _alias_t {
				static constexpr const char _literal[] ="c_owner";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_owner;
						T &operator()() { return c_owner; }
						const T &operator()() const { return c_owner; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_group {
			struct _alias_t {
				static constexpr const char _literal[] ="c_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_group;
						T &operator()() { return c_group; }
						const T &operator()() const { return c_group; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_unixperms {
			struct _alias_t {
				static constexpr const char _literal[] ="c_unixperms";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_unixperms;
						T &operator()() { return c_unixperms; }
						const T &operator()() const { return c_unixperms; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct C_status {
			struct _alias_t {
				static constexpr const char _literal[] ="c_status";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T c_status;
						T &operator()() { return c_status; }
						const T &operator()() const { return c_status; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Parent_category_id {
			struct _alias_t {
				static constexpr const char _literal[] ="parent_category_id";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T parent_category_id;
						T &operator()() { return parent_category_id; }
						const T &operator()() const { return parent_category_id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};

		struct Name {
			struct _alias_t {
				static constexpr const char _literal[] ="name";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T name;
						T &operator()() { return name; }
						const T &operator()() const { return name; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Description {
			struct _alias_t {
				static constexpr const char _literal[] ="description";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T description;
						T &operator()() { return description; }
						const T &operator()() const { return description; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::can_be_null>;
		};

		struct Creationdate {
			struct _alias_t {
				static constexpr const char _literal[] ="creationdate";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T creationdate;
						T &operator()() { return creationdate; }
						const T &operator()() const { return creationdate; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Allow_recipe {
			struct _alias_t {
				static constexpr const char _literal[] ="allow_recipe";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T allow_recipe;
						T &operator()() { return allow_recipe; }
						const T &operator()() const { return allow_recipe; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean>;
		};

		struct Allow_items {
			struct _alias_t {
				static constexpr const char _literal[] ="allow_items";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T allow_items;
						T &operator()() { return allow_items; }
						const T &operator()() const { return allow_items; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::boolean>;
		};
	}

	struct categories : sqlpp::table_t<categories,
				categories_::C_uid,
				categories_::C_owner,
				categories_::C_group,
				categories_::C_unixperms,
				categories_::C_status,
				categories_::Parent_category_id,
				categories_::Name,
				categories_::Description,
				categories_::Creationdate,
				categories_::Allow_recipe,
				categories_::Allow_items> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "categories";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T categories;
					T &operator()() { return categories; }
					const T &operator()() const { return categories; }
				};
		};
	};
}

#endif
