# mruby-filemagic   [![Build Status](https://travis-ci.org/k0u5uk3/mruby-filemagic.svg?branch=master)](https://travis-ci.org/k0u5uk3/mruby-filemagic)
FileMagic class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'k0u5uk3/mruby-filemagic'
end
```
## example

```ruby

$ ./bin/mirb
mirb - Embeddable Interactive Ruby Shell

> filemagic = FileMagic.new(FileMagic::MAGIC_NONE)
 => #<FileMagic:0x1f128d0>
> filemagic.file("/etc/shadow")
 => "regular file, no read permission"
```

## License
under the MIT License:
- see LICENSE file
