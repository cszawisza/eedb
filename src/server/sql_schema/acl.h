#ifndef SCHEMA_ACL_H
#define SCHEMA_ACL_H

#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace schema {

	namespace acl_ {

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

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
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

		struct Acl_group {
			struct _alias_t {
				static constexpr const char _literal[] ="acl_group";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T acl_group;
						T &operator()() { return acl_group; }
						const T &operator()() const { return acl_group; }
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
	}

	struct acl : sqlpp::table_t<acl,
				acl_::Uid,
				acl_::Owner,
				acl_::Acl_group,
				acl_::Unixperms,
				acl_::Status> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = "acl";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T acl;
					T &operator()() { return acl; }
					const T &operator()() const { return acl; }
				};
		};
	};
}

#endif
