(0 .. 9).each do |n|
  puts "Checking for #{n}..."
  system("./bin/main runtime/example_#{n}.bmp")
end
