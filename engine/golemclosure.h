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

typedef struct _GolemClosureInfoPrivate GolemClosureInfoPrivate;
typedef struct _GolemClosureParameter GolemClosureParameter;
typedef struct _GolemClosureInvoke GolemClosureInvoke;

typedef gboolean (*GolemClosureInvokeFunc)(GolemClosure * closure,GolemClosureInvoke * invoke,gpointer data);
typedef void	 (*GolemClosureFinalizeFunc)(GolemClosure * closure,gpointer data);

typedef gpointer (*GolemClosureHoldNativeAddressFunc)(GolemClosure * closure,gpointer data);
typedef void	 (*GolemClosureReleaseNativeAddressFunc)(GolemClosure * closure,gpointer data,gpointer native_address);



#define GOLEM_TYPE_CLOSURE_INFO	(golem_closure_info_get_type())
#define GOLEM_TYPE_CLOSURE	(golem_closure_get_type())

#define G_CLOSURE(c)		((GClosure*)c)
#define GOLEM_CLOSURE(c)	((GolemClosure*)c)

#define G_VALUE_HOLDS_CLOSURE(v) (G_VALUE_TYPE(v) == G_TYPE_CLOSURE || G_VALUE_TYPE(v) == GOLEM_TYPE_CLOSURE)

G_DECLARE_FINAL_TYPE(GolemClosureInfo,golem_closure_info,GOLEM,CLOSURE_INFO,GObject)


struct _GolemClosure
{
  GClosure 		parent_boxed;

  GolemClosureInvokeFunc   invoke_func;
  GolemClosureFinalizeFunc finalize_func;

  GolemClosureHoldNativeAddressFunc hold_native_address_func;
  GolemClosureReleaseNativeAddressFunc release_native_address_func;

  gpointer data;

  GValue this_value;
};

struct _GolemClosureInvoke
{
	GList * arguments;
	GList * current;
	GValue result;
	GError * error;
};

struct _GolemClosureParameter
{
  gchar * 	name;
  gchar *	type_name;
  GType 	type;
};

struct _GolemClosureInfoClass
{
  GObjectClass 	parent_class;
};


struct _GolemClosureInfo
{
  GObject 	parent_instance;
  GolemClosureInfoPrivate * priv;
};

/*
 *	Golem Invoke Boxed
 */

GolemClosureInvoke * 	golem_closure_invoke_new();

GolemClosureInvoke * 	golem_closure_invoke_new_with_values(guint n_param_values,const GValue *param_values);

gsize			golem_closure_invoke_get_length(GolemClosureInvoke * closure_invoke);

void			golem_closure_invoke_rewind(GolemClosureInvoke * closure_invoke);

void			golem_closure_invoke_push(GolemClosureInvoke * closure_invoke,const GValue * value);

gboolean		golem_closure_invoke_next(GolemClosureInvoke * closure_invoke,GValue * value);

GType			golem_closure_invoke_get_gtype(GolemClosureInvoke * closure_invoke,gint index);

void			golem_closure_invoke_get_value(GolemClosureInvoke * closure_invoke,gint index,GValue * value);

guchar			golem_closure_invoke_get_char(GolemClosureInvoke * closure_invoke,gint index);

gint32			golem_closure_invoke_get_int(GolemClosureInvoke * closure_invoke,gint index);

gint64			golem_closure_invoke_get_int64(GolemClosureInvoke * closure_invoke,gint index);

gfloat			golem_closure_invoke_get_float(GolemClosureInvoke * closure_invoke,gint index);

gdouble			golem_closure_invoke_get_double(GolemClosureInvoke * closure_invoke,gint index);

gpointer		golem_closure_invoke_get_pointer(GolemClosureInvoke * closure_invoke,gint index);

gpointer		golem_closure_invoke_get_boxed(GolemClosureInvoke * closure_invoke,gint index);

gpointer		golem_closure_invoke_get_object(GolemClosureInvoke * closure_invoke,gint index);

const gchar *	golem_closure_invoke_get_string(GolemClosureInvoke * closure_invoke,gint index);

void			golem_closure_invoke_set_error(GolemClosureInvoke * closure_invoke,GError * error);

GError *		golem_closure_invoke_get_error(GolemClosureInvoke * closure_invoke);

void			golem_closure_invoke_set_result(GolemClosureInvoke * closure_invoke,const GValue * value);

void			golem_closure_invoke_get_result(GolemClosureInvoke * closure_invoke,GValue * value);

void			golem_closure_invoke_free(GolemClosureInvoke * closure_invoke);

/*
 * 	Golem Closure Info Object
 */

GType			golem_closure_info_get_type(void);

GolemClosureInfo * 	golem_closure_info_parse(GolemParser * parser,GError ** error);

GolemClosureInfo * 	golem_closure_info_parse_anonymous(GolemParser * parser,GError ** error);

gboolean		golem_closure_info_resolve(GolemClosureInfo * info,GolemContext * context,GError ** error);

const gchar *		golem_closure_info_get_name(GolemClosureInfo * info);

GType			golem_closure_info_get_return_type(GolemClosureInfo * info);

GList *			golem_closure_info_get_parameters(GolemClosureInfo * info);

/*
 * 	Golem Closure Boxed
 */

GType			golem_closure_get_type(void);

GolemClosure *		golem_closure_new(GolemClosureInvokeFunc invoke_func,GolemClosureFinalizeFunc finalize_func,gpointer data);

gboolean		golem_closure_invoke(GolemClosure * closure,GolemClosureInvoke * invoke);

void			golem_closure_set_this(GolemClosure * closure,const GValue * src);

gpointer		golem_closure_hold_address(GolemClosure * closure);

void			golem_closure_release_address(GolemClosure * closure,gpointer native_address);

GolemClosure *		golem_symbol_new(GolemClosureInfo * info,gpointer symbol_address);

GolemClosure *		golem_function_new(GolemClosureInfo * info,GolemContext * context,GolemStatement * sentence);



#endif /* GOLEMCLOSURE_H_ */
