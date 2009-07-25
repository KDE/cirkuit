output = File.new("cctdpic.cpp", 'w')

IO.foreach("cctdpic") do |line|
	transformed = '"' + line.gsub(/\\/, '\\\\\\\\').chop.strip + "\\n" + '"'
	output.puts transformed
end