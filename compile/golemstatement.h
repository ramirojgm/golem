/*
	Copyright (C) 2018 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GOLEMSTATEMENT_H_
#define GOLEMSTATEMENT_H_

#define	GOLEM_DEFINE_STATEMENT(N,n)  static void n##_init(N * statement);\
				     static gboolean n##_parse  (N * statement,\
								  GolemParser * parser,\
								  GolemExpressionLimit limit,\
								  GError ** error);\
				     static gboolean n##_compile (N* statement,\
								  GolemVMBody * body,\
								  GolemScopeBuilder * scope_builder,\
								  GError ** error);\
				     static GolemTypeCode n##_value_type (N* statement,\
								  GolemScopeBuilder * scope_builder,\
								  GError ** error);\
				     static void n##_dispose     (N * statement);\
				     static gboolean n##_check   (GolemParser * parser);\
				     static GolemStatementClass  _##n##_class = {\
								     (GolemStatementInit)n##_init,\
								     (GolemStatementParse)n##_parse,\
								     (GolemStatementCompile)n##_compile,\
								     (GolemStatementValueType)n##_value_type,\
								     (GolemStatementDispose)n##_dispose,\
								     (GolemStatementCheck)n##_check,\
								     sizeof(N)\
								  };\
				    GolemStatementClass * n##_get_class() { return &_##n##_class; }


typedef struct _GolemStatementClass GolemStatementClass;
typedef struct _GolemStatement GolemStatement;
typedef struct _GolemStatementExt GolemStatementExt;
typedef enum _GolemExpressionLimit GolemExpressionLimit;

typedef void 	 (*GolemStatementInit)(GolemStatement * statement);

typedef gboolean (*GolemStatementParse)(GolemStatement * statement,
					GolemParser * parser,
					GolemExpressionLimit limit,
					GError ** error);

typedef gboolean (*GolemStatementCompile)(GolemStatement * statement,
					  GolemVMBody * body,
					  GolemScopeBuilder * scope_builder,
					  GError ** error);

typedef GolemTypeCode (*GolemStatementValueType)(GolemStatement * statement,
						GolemScopeBuilder * scope_builder,
						GError ** error);

typedef void 	 (*GolemStatementDispose)(GolemStatement * statement);

typedef gboolean (*GolemStatementCheck)(GolemParser * parser);

struct _GolemStatementClass {
  /* instance */
  GolemStatementInit init;
  GolemStatementParse parse;
  GolemStatementCompile compile;
  GolemStatementValueType value_type;
  GolemStatementDispose dispose;

  /* static */
  GolemStatementCheck check;

  gsize  size;
};

struct _GolemStatement {
  GolemStatementClass * klass;
  gchar * source;
  guint line;
};

struct _GolemStatementExt {
  GolemStatement parent;
  GolemStatement * base;
};


GolemStatement * golem_statement_parse(GolemParser * parser,GError ** error);

gboolean	 golem_statement_check(GolemStatementClass * klass,
				       GolemParser* parser);

gboolean	 golem_statement_compile(GolemStatement * statement,
					GolemVMBody * body,
					GolemScopeBuilder * scope_builder,
					GError ** error);

GolemTypeCode	 golem_statement_value_type(GolemStatement * statement,
					    GolemScopeBuilder * scope_builder,
					    GError ** error);

void		 golem_statement_free(GolemStatement * statement);

#endif /* GOLEMSTATEMENT_H_ */
