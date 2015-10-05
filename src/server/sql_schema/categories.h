#ifndef SCHEMA_CATEGORIES_H
#define SCHEMA_CATEGORIES_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace categories_ {

		struct Uid {
			struct _alias_t {
				static constexpr const char _literal[] ="uid";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T uid;
						T &operator()() { return uid; }
						const T &operator()() const { return uid; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Owner {
			struct _alias_t {
				static constexpr const char _literal[] ="owner";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T owner;
						T &operator()() { return owner; }
						const T &operator()() const { return owner; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Stat_group {
			struct _alias_t {
				static constexpr const char _literal[] ="stat_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T stat_group;
						T &operator()() { return stat_group; }
						const T &operator()() const { return stat_group; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Unixperms {
			struct _alias_t {
				static constexpr const char _literal[] ="unixperms";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T unixperms;
						T &operator()() { return unixperms; }
						const T &operator()() const { return unixperms; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
		};

		struct Status {
			struct _alias_t {
				static constexpr const char _literal[] ="status";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T status;
						T &operator()() { return status; }
						const T &operator()() const { return status; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer>;
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

			using _traits = ::sqlpp::make_traits<::sqlpp::text, sqlpp::tag::require_insert>;
		};

		struct Creation_date {
			struct _alias_t {
				static constexpr const char _literal[] ="creation_date";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T creation_date;
						T &operator()() { return creation_date; }
						const T &operator()() const { return creation_date; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar>;
		};

		struct Last_update {
			struct _alias_t {
				static constexpr const char _literal[] ="last_update";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T last_update;
						T &operator()() { return last_update; }
						const T &operator()() const { return last_update; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::can_be_null>;
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
	}

	struct categories : sqlpp::table_t<categories,
				categories_::Uid,
				categories_::Owner,
				categories_::Stat_group,
				categories_::Unixperms,
				categories_::Status,
				categories_::Name,
				categories_::Creation_date,
				categories_::Last_update,
				categories_::Parent_category_id,
				categories_::Description> {
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
