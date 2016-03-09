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
p FileMagic.hi
#=> "hi!!"
t = FileMagic.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
