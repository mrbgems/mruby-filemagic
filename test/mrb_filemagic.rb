##
## FileMagic Test
##

assert("FileMagic Const") do 
  assert_equal(0x000000, FileMagic::MAGIC_NONE)
  assert_equal(0x000001, FileMagic::MAGIC_DEBUG)
  assert_equal(0x000002, FileMagic::MAGIC_SYMLINK)
  assert_equal(0x000004, FileMagic::MAGIC_COMPRESS)
  assert_equal(0x000008, FileMagic::MAGIC_DEVICES)
  assert_equal(0x000010, FileMagic::MAGIC_MIME_TYPE)
  assert_equal(0x000020, FileMagic::MAGIC_CONTINUE)
  assert_equal(0x000040, FileMagic::MAGIC_CHECK)
  assert_equal(0x000080, FileMagic::MAGIC_PRESERVE_ATIME)
  assert_equal(0x000100, FileMagic::MAGIC_RAW)
  assert_equal(0x000200, FileMagic::MAGIC_ERROR)
end

assert("FileMagic file method test for mruby script") do 
  t = FileMagic.new(FileMagic::MAGIC_NONE)
  assert_equal("HOGE ASCII text",  t.file(__FILE__))
end

assert("FileMagic file method test for binary file") do 
  t = FileMagic.new(FileMagic::MAGIC_NONE)
  assert_equal("ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=4c031db67d94dad77c4ae86b708ea73866db3ccf, not stripped", t.file(File.expand_path('../hoge', __FILE__)))
end


