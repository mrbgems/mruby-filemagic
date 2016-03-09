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

assert("FileMagic File Method") do 
  t = FileMagic.new(FileMagic::MAGIC_NONE)
  assert_equal("ASCII text",  t.file(__FILE__))
end

