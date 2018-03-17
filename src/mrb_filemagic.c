/*
** mrb_filemagic.c - FileMagic class
**
** Copyright (c) Kousuke Shimofuji 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mrb_filemagic.h"
#include <string.h>
#include <magic.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  struct magic_set *magic;
} mrb_filemagic_data;

static void filemagic_free(mrb_state *mrb, void *p)
{
  mrb_filemagic_data *data = p;
  if(data && data->magic){
    magic_close(data->magic);
  }
  mrb_free(mrb, p);
}

static const struct mrb_data_type mrb_filemagic_data_type = {
  "mrb_filemagic_data", filemagic_free,
};

static mrb_value mrb_filemagic_init(mrb_state *mrb, mrb_value self)
{
  mrb_filemagic_data *data;
  int flag;
  struct magic_set *magic = NULL;

  data = (mrb_filemagic_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_filemagic_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "i", &flag);

  magic = magic_open(flag);
  if(magic == NULL){
    mrb_raisef(mrb, E_RUNTIME_ERROR, "unknown magic flag %S", mrb_str_new_cstr(mrb, "failed magic file open"));
  }

  if(magic_load(magic, NULL) == -1){
    mrb_raisef(mrb, E_RUNTIME_ERROR, "unknown magic flag %S", mrb_str_new_cstr(mrb, "magic file is null"));
  }

  data = (mrb_filemagic_data *)mrb_malloc(mrb, sizeof(mrb_filemagic_data));
  data->magic = magic;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_filemagic_file(mrb_state *mrb, mrb_value self)
{
  mrb_filemagic_data *data = DATA_PTR(self);
  struct magic_set *magic = NULL;
  char *path_str;
  int  path_len; 
  const char *result;

  magic = data->magic;
  mrb_get_args(mrb, "s", &path_str, &path_len);

  if((result = magic_file(magic, path_str)) == NULL){
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S:%S", mrb_str_new_cstr(mrb, path_str), mrb_str_new_cstr(mrb, magic_error(magic)));
  }

  return mrb_str_new_cstr(mrb, result);
}

static mrb_value mrb_filemagic_buffer(mrb_state *mrb, mrb_value self)
{
  mrb_filemagic_data *data = DATA_PTR(self);
  struct magic_set *magic = NULL;
  char *buf;
  int  buf_len;
  const char *result;

  magic = data->magic;
  mrb_get_args(mrb, "s", &buf, &buf_len);

  if((result = magic_buffer(magic, buf, buf_len)) == NULL){
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S", mrb_str_new_cstr(mrb, magic_error(magic)));
  }

  return mrb_str_new_cstr(mrb, result);
}


static mrb_value mrb_filemagic_close(mrb_state *mrb, mrb_value self)
{
  mrb_filemagic_data *data = DATA_PTR(self);
  struct magic_set *magic = NULL;
  magic = data->magic;
  magic_close(magic);
  data->magic = NULL;
  return mrb_true_value();
}

void mrb_mruby_filemagic_gem_init(mrb_state *mrb)
{
    struct RClass *filemagic;
    filemagic = mrb_define_class(mrb, "FileMagic", mrb->object_class);
    MRB_SET_INSTANCE_TT(filemagic, MRB_TT_DATA);

    // defined constants
    mrb_define_const(mrb, filemagic, "MAGIC_NONE", mrb_fixnum_value(MAGIC_NONE));
    mrb_define_const(mrb, filemagic, "MAGIC_DEBUG", mrb_fixnum_value(MAGIC_DEBUG));
    mrb_define_const(mrb, filemagic, "MAGIC_SYMLINK", mrb_fixnum_value(MAGIC_SYMLINK));
    mrb_define_const(mrb, filemagic, "MAGIC_COMPRESS", mrb_fixnum_value(MAGIC_COMPRESS));
    mrb_define_const(mrb, filemagic, "MAGIC_DEVICES", mrb_fixnum_value(MAGIC_DEVICES));
    mrb_define_const(mrb, filemagic, "MAGIC_MIME_TYPE", mrb_fixnum_value(MAGIC_MIME_TYPE));
    mrb_define_const(mrb, filemagic, "MAGIC_CONTINUE", mrb_fixnum_value(MAGIC_CONTINUE));
    mrb_define_const(mrb, filemagic, "MAGIC_CHECK", mrb_fixnum_value(MAGIC_CHECK));
    mrb_define_const(mrb, filemagic, "MAGIC_PRESERVE_ATIME", mrb_fixnum_value(MAGIC_PRESERVE_ATIME));
    mrb_define_const(mrb, filemagic, "MAGIC_RAW", mrb_fixnum_value(MAGIC_RAW));
    mrb_define_const(mrb, filemagic, "MAGIC_ERROR", mrb_fixnum_value(MAGIC_ERROR));

    // defined methods
    mrb_define_method(mrb, filemagic, "initialize", mrb_filemagic_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, filemagic, "file", mrb_filemagic_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, filemagic, "buffer", mrb_filemagic_buffer, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, filemagic, "close", mrb_filemagic_close, MRB_ARGS_NONE());
    DONE;
}

void mrb_mruby_filemagic_gem_final(mrb_state *mrb)
{

}
