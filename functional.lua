io.write('[Lua] Calling C function\n')
a,b = displayLuaFunction(12, 3.141592, 'holla')

io.write('[Lua] The C function returned <' .. a .. '> and <' .. b .. '> \n')
