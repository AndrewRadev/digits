(0 .. 9).each do |n|
  puts "Checking for #{n}..."
  system("./bin/main experiments/example_#{n}.bmp")
end
