/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GOLEMCLOSURE_H_
#define GOLEMCLOSURE_H_

typedef enum _GolemClosureType GolemClosureType;
typedef enum _GolemClosureContext GolemClosureContext;

typedef struct _GolemClosure GolemClosure;
typedef struct _GolemSignal GolemSignal;
typedef struct _GolemSymbol GolemSymbol;
typedef struct _GolemFunction GolemFunction;
typedef struct _GolemClosureInfo GolemClosureInfo;
typedef struct _GolemClosureInfoPrivate GolemClosureInfoPrivate;
typedef struct _GolemClosureParameter GolemClosureParameter;

typedef void (*GolemClosureCallback)(GolemClosure *closure,
		                    GValue *return_value,
		                    guint n_param_values,
		                    const GValue *param_values,
		                    GError ** error);

#define GOLEM_TYPE_CLOSURE_INFO	(golem_closure_info_get_type())

#define G_CLOSURE(c)		((GClosure*)c)
#define GOLEM_CLOSURE(c)	((GolemClosure*)c)
#define GOLEM_SYMBOL(c)		((GolemSymbol*)c)
#define GOLEM_SIGNAL(c)		((GolemSignal*)c)
#define GOLEM_FUNCTION(c)	((GolemFunction*)c)


#define G_VALUE_HOLDS_CLOSURE(v) (G_VALUE_TYPE(v) == G_TYPE_CLOSURE)

G_DECLARE_FINAL_TYPE(GolemClosureInfo,golem_closure_info,GOLEM,CLOSURE_INFO,GObject)

enum _GolemClosureType
{
  GOLEM_CLOSURE_SYMBOL,
  GOLEM_CLOSURE_FUNCTION,
  GOLEM_CLOSURE_SIGNAL,
  GOLEM_CLOSURE_EXTERNAL
};

enum _GolemClosureContext
{
  GOLEM_CLOSURE_CONTEXT_CLASSED,
  GOLEM_CLOSURE_CONTEXT_INSTANCED,
  GOLEM_CLOSURE_CONTEXT_NONE
};

struct _GolemClosure
{
  GClosure 		parent_boxed;
  GolemClosureType	type;
  GolemClosureInfo * 	info;
  GolemClosureContext 	context_type;

  GolemClosureCallback	callback;

  union {
    GType	class_type;
    gpointer    instance;
  } context;

};

struct _GolemSignal
{
  GClosure	parent_boxed;
  guint		signal_id;
};

struct _GolemSymbol
{
  GolemClosure 	parent_boxed;
  gpointer	symbol_address;
};

struct _GolemFunction
{
  GolemClosure 	parent_boxed;
  GolemContext*	context;
  GolemStatement * sentence;
};

struct _GolemClosureParameter
{
  gchar * 	name;
  gchar *	type_name;
  GType 	type;
  gboolean 	is_array: 1;
  gboolean	is_reference: 1;
};

struct _GolemClosureInfoClass
{
  GObjectClass 	parent_class;
};


struct _GolemClosureInfo
{
  GObject 	parent_instance;
  GType 	return_type;
  gboolean	return_const;
  gint 		throw_at;
  GList * 	parameters;
  GolemClosureInfoPrivate * priv;
};

GType			golem_closure_info_get_type(void);

GolemClosureInfo * 	golem_closure_info_parse(GolemParser * parser,GError ** error);

GolemClosureInfo * 	golem_closure_info_parse_anonymous(GolemParser * parser,GError ** error);

gboolean		golem_closure_info_resolve(GolemClosureInfo * info,GolemContext * context,GError ** error);

const gchar *		golem_closure_info_get_name(GolemClosureInfo * info);

GType			golem_closure_info_get_return_type(GolemClosureInfo * info);

GList *			golem_closure_info_get_parameters(GolemClosureInfo * info);

GolemClosure *		golem_closure_new(GolemClosureCallback * callback);

GolemClosure *		golem_closure_instanced_new(gpointer instance,GolemClosureCallback * callback);

gpointer		golem_closure_get_instance(GolemClosure * closure);

GTypeClass *		golem_closure_get_class(GolemClosure * closure);

GolemClosureType	golem_closure_get_type(GolemClosure * closure);

GolemClosure *		golem_symbol_new(GolemClosureInfo * info,gpointer symbol_address);

GolemClosure *		golem_function_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * sentence);





#endif /* GOLEMCLOSURE_H_ */
