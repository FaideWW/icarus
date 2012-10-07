--receive
io.write("[Lua] These args were passed into the script from the engine\n")
for i=1, #arg do
	print("     ", i, arg[i])
end

--passback
io.write("[Lua] Returning data to engine\n")
--create a table
local temp = {}
temp[1] = 9
temp[2] = "String literal"

return true, temp, 21, "Mushroom"