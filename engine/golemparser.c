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

#include "golemparser.h"
#include "ctype.h"
typedef struct _GolemParserWord GolemParserWord;
typedef struct _GolemParserPrivate GolemParserPrivate;

struct _GolemParserPrivate
{
  GList
    * words,
    * cur_word;
  GQueue
    * saved_point;
};

struct _GolemParserWord
{
  gchar * content;
  gint column, line;
  gint start,end;
  gsize length;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemParser,golem_parser,G_TYPE_OBJECT)

static const gchar * golem_parser_spaces[] = {"\n","\r","\t"," ",NULL};
static const gchar * golem_parser_spliters[] = {"<=",">=","==","!=","&&","||","+","-","*","/","%","!","<",">","=","\\","@","#","$",",",".",";",":","[","]","(",")","{","}",NULL};

static void
golem_parser_word_free(GolemParserWord * word)
{
  g_free(word->content);
  g_free(word);
}

static void
golem_parser_finalize(GObject * instance)
{
  GolemParserPrivate * priv;
  priv = golem_parser_get_instance_private(GOLEM_PARSER(instance));

  g_queue_free(priv->saved_point);
  g_list_free_full(priv->words,(GDestroyNotify)golem_parser_word_free);

  //G_OBJECT_GET_CLASS(instance)->finalize(instance);
}


static void
golem_parser_init(GolemParser * self)
{
  GolemParserPrivate * priv;

  priv = golem_parser_get_instance_private(self);
  priv->cur_word = NULL;
  priv->words = NULL;
  priv->saved_point = g_queue_new();
}

static void
golem_parser_class_init(GolemParserClass * klass)
{
  G_OBJECT_CLASS(klass)->finalize = golem_parser_finalize;
}

GolemParser *
golem_parser_new()
{
  return GOLEM_PARSER(g_object_new(GOLEM_TYPE_PARSER,NULL));
}

gint
golem_parser_index_of(const gchar * str,const gchar ** word_set)
{
  gint word_index = 0;
  for(;*word_set;word_set++)
    {
      if(g_str_has_prefix(str,*word_set))
	{
	  return word_index;
	}
      word_index ++;
    }
  return -1;
}

static const gchar*
golem_parser_skip_space(const gchar * str,const gchar * end)
{
  const gchar * iter = str;
  gboolean in_comment = FALSE;
  for(;iter < end;iter++)
    {
      if (in_comment)
	{
	  if ((*iter == '\n')||(*iter == '\r'))
	    in_comment = FALSE;
	}
      else
	{
	  if (golem_parser_index_of(iter, golem_parser_spaces) == -1)
	    {
	      if (*iter == '#')
		{
		  in_comment = TRUE;
		}
	      else
		{
		  break;
		}
	    }
	}
    }
  if(str > end)
    return end;
  else
    return iter;
}

static gint
golem_parser_get_spliter(const gchar * str)
{
  return golem_parser_index_of(str,golem_parser_spliters);
}

static const gchar*
golem_parser_parse_next_word(const gchar * str,gsize * length,const gchar * end)
{
  gint spliter = golem_parser_get_spliter(str);
  gboolean in_escape;
  gchar literal;
  const gchar * start = str;
  if(spliter != -1)
    {
      *length = g_utf8_strlen(golem_parser_spliters[spliter],-1);
      return start;
    }
  else if(str >= end)
    {
      *length = 0;
      return end;
    }
  else if((*str == '\"')||(*str == '\''))
    {
      literal = *str;
      in_escape = FALSE;
      while( str < end)
	{
	  str++;
	  if (*str == literal)
	    {
	      if (!in_escape)
		break;
	      else
		in_escape = FALSE;
	    }
	  else if (*str == '\\')
	    in_escape = !in_escape;
	  else if (in_escape)
	    in_escape = FALSE;
	}
      str++;
      * length = str - start;
      return start;
    }
  else
    {
      while((str < end) && (golem_parser_index_of(str,golem_parser_spaces) == -1) && (golem_parser_index_of(str,golem_parser_spliters) == -1))
	str ++;
      if( start != str)
	{
	  if(length)
	    *length = str - start;
	  return start;
	}
      else
	{
	  *length = 0;
	  return end;
	}
    }
}

guint
golem_parser_get_line_at(const gchar * value,goffset offset)
{
  guint line = 1;
  for(const gchar * index = value;(index - value) < offset;index++)
    {
      if(*index == '\n')
	line++;
    }
  return line;
}

gboolean
golem_parser_parse(GolemParser * parser,const gchar * str,gssize length)
{
  GolemParserPrivate * priv;
  const gchar * cur,* end;
  GolemParserWord * word;
  gboolean done = TRUE;
  gsize word_length;

  priv = golem_parser_get_instance_private(parser);

  if(length < 0)
    length = g_utf8_strlen(str,-1);

  cur = str;
  end = (cur + length);

  while(cur != end)
    {
      cur = golem_parser_skip_space(cur,end);
      cur = golem_parser_parse_next_word(cur,&word_length,end);
      if((cur < end) && (length > 0))
	{
	  word = g_new(GolemParserWord,1);
	  word->content = g_strndup(cur,word_length);
	  word->start = cur - str;
	  word->end = (cur + word_length) - str;
	  word->length = word_length;
	  word->line = golem_parser_get_line_at(str,word->start);
	  priv->words = g_list_append(priv->words,word);
	  cur += word_length;
	}
      else
	break;
    }

  priv->cur_word = priv->words;
  return done;
}

void
golem_parser_rewind(GolemParser * parser)
{
  GolemParserPrivate * priv;
  priv = golem_parser_get_instance_private(parser);

  priv->cur_word = priv->words;
}

gboolean
golem_parser_is_end(GolemParser * parser)
{
  GolemParserPrivate * priv;
  priv = golem_parser_get_instance_private(parser);
  return priv->cur_word == NULL;
}

gboolean
golem_parser_is_next_word(GolemParser * parser,const gchar * str)
{
  GolemParserPrivate * priv;
  GolemParserWord * word;

  priv = golem_parser_get_instance_private(parser);

  if(priv->cur_word)
    {
      word = (GolemParserWord *)(priv->cur_word->data);
      return g_strcmp0(word->content,str) == 0;
    }
  else
    {
      return FALSE;
    }
}

gboolean
golem_parser_next_word_has_prefix(GolemParser * parser,const gchar * prefix)
{
  GolemParserPrivate * priv;
   GolemParserWord * word;

   priv = golem_parser_get_instance_private(parser);

   if(priv->cur_word)
     {
       word = (GolemParserWord *)(priv->cur_word->data);
       return g_str_has_prefix(word->content,prefix);
     }
   else
     {
       return FALSE;
     }
}

gboolean
golem_parser_next_word_has_suffix(GolemParser * parser,const gchar * suffix)
{
  GolemParserPrivate * priv;
   GolemParserWord * word;

   priv = golem_parser_get_instance_private(parser);

   if(priv->cur_word)
     {
       word = (GolemParserWord *)(priv->cur_word->data);
       return g_str_has_suffix(word->content,suffix);
     }
   else
     {
       return FALSE;
     }
}

gboolean
golem_parser_skip(GolemParser * parser)
{
  GolemParserPrivate * priv;
  GolemParserWord * word;

  priv = golem_parser_get_instance_private(parser);

  if(priv->cur_word)
    {
      priv->cur_word = g_list_next(priv->cur_word);
      return FALSE;
    }
  else
    {
      return TRUE;
    }
}

const gchar *
golem_parser_next_word(GolemParser * parser,gsize * length,gboolean move)
{
  GolemParserPrivate * priv;
  GolemParserWord * word;

  priv = golem_parser_get_instance_private(parser);

  if(priv->cur_word)
    {
      word = (GolemParserWord *)(priv->cur_word->data);
      if(move)
	priv->cur_word = g_list_next(priv->cur_word);
      if(length)
	*length = word->length;
      return word->content;
    }
  else
    {
      if(length)
	*length = 0;
      return NULL;
    }
}

gboolean
golem_parser_next_word_check(GolemParser * parser,const gchar * str)
{
  GolemParserPrivate * priv;
  GolemParserWord * word;

  priv = golem_parser_get_instance_private(parser);

  if(priv->cur_word)
    {
      word = (GolemParserWord *)(priv->cur_word->data);
      if(g_strcmp0(word->content,str) == 0)
	{
	  priv->cur_word = g_list_next(priv->cur_word);
	  return TRUE;
	}
      else
	{
	  return FALSE;
	}
    }
  else
    {
      return FALSE;
    }
}

void
golem_parser_save_point(GolemParser * parser)
{
  GolemParserPrivate * priv;

  priv = golem_parser_get_instance_private(parser);

  if (priv->cur_word)
    g_queue_push_tail(priv->saved_point,priv->cur_word);
}

void
golem_parser_commit_point(GolemParser * parser)
{
  GolemParserPrivate * priv;
  priv = golem_parser_get_instance_private(parser);
  g_queue_pop_tail(priv->saved_point);
}

void
golem_parser_restore_point(GolemParser * parser)
{
  GolemParserPrivate * priv;

  priv = golem_parser_get_instance_private(parser);

  GList * saved_point = g_queue_pop_tail(priv->saved_point);
  if (saved_point)
    priv->cur_word = saved_point;
}

gint
golem_parser_get_line(GolemParser * parser)
{
  GolemParserPrivate * priv;
  priv = golem_parser_get_instance_private(parser);
  if(priv->cur_word)
    return ((GolemParserWord*)priv->cur_word->data)->line;
  else
    return 0;
}

gboolean
golem_parser_check_is_number(GolemParser * parser)
{
  const gchar * word = golem_parser_next_word(parser,NULL,FALSE);
  if(word)
    {
      for(const gchar * c = word;*c != 0;c++)
	{
	  if(!(isdigit(*c) || (*c == 'l') || (*c == 'f')))
	    return FALSE;
	}
      return TRUE;
    }
  return FALSE;
}

gboolean
golem_parser_check_is_hex(GolemParser * parser)
{
  return golem_parser_next_word_has_prefix(parser,"0x");
}

gboolean
golem_parser_check_is_const(GolemParser * parser)
{
  return golem_parser_check_is_number(parser)||
	 golem_parser_check_is_hex(parser)||
	 golem_parser_check_is_string(parser);
}

gboolean
golem_parser_check_is_string(GolemParser * parser)
{
  return (golem_parser_next_word_has_prefix(parser,"\"")
	  && golem_parser_next_word_has_suffix(parser,"\""))
	  ||(golem_parser_next_word_has_prefix(parser,"\'")
	  && golem_parser_next_word_has_suffix(parser,"\'"));
}

gboolean
golem_parser_check_is_named(GolemParser * parser)
{
  const gchar * word = golem_parser_next_word(parser,NULL,FALSE);
    if(word)
      {
	if(!isalpha(*word))
	  return FALSE;
        for(const gchar * c = word;*c != 0;c++)
  	{
  	  if(!isalnum(*c) && *c != '_')
  	    return FALSE;
  	}
        return TRUE;
      }
    return FALSE;
}



