MRuby::Gem::Specification.new('mruby-filemagic') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Kousuke Shimofuji'
  spec.linker.libraries << 'magic'
  spec.add_dependency 'mruby-io'
end

