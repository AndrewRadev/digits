(0 .. 9).each do |n|
  puts "Checking for #{n}..."
  system("./bin/squeeze_match experiments/example_#{n}.bmp")
end
