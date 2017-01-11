local chatter = {
  loadedChat = {}
}

function chatter:loadFile(filename)
  io.input(filename)
  local file = io.read("*all")
  -- removes all new lines and indents
  file = string.gsub(file, "\n%s*", "")
  --print(file)
  local table = {}
  self:_parseFile(file, table)
  tprint(table)
end

function chatter:print(chatID)
  local cid = chatID or 1

end

function chatter:_printAll()
  for _, conv in pairs(self.conv) do
    for _, chat in pairs(conv) do
      for  _, item in pairs(chat) do
        print(item)
      end
    end
  end
end

function chatter:_parseFile(str, tbl)
  -- to recursively hold info. If top level, uses chatter table
  local tbl = tbl or {}
  local pattern = "^<(.-)%s?(.-)>(.-)</%1>(.*)$"
  -- splits string into current semantic block, and the remainder
  local _, _, tag, params, contents, remainder = string.find(str, pattern)

  -- depth-first recursive traversal
  if tag then
    local _, val = chatter:_parseTagParams(params)
    val = val or ""
    local tag = tag .. val
    print(tag)
    -- if there are more nested tags, then recurse
    if string.find(contents, pattern) then
      tbl[tag] = {}
      chatter:_parseFile(contents, tbl[tag])
    -- else leaf, containing string
    else
      tbl[tag] = contents
    end
  end


  if remainder then
    chatter:_parseFile(remainder, tbl)
  end

  --return tbl
end

function chatter:_parseTagParams(params)
  local pattern = "(.-)='(%d*)'"
  local _, _, par, val = string.find(params, pattern)
  --print(par, val)
  return par, val
end

function tprint (tbl, indent)
  if not indent then indent = 0 end
  for k, v in pairs(tbl) do
    formatting = string.rep("  ", indent) .. k .. ": "
    if type(v) == "table" then
      print(formatting)
      tprint(v, indent+1)
    else
      local v = tostring(v)
      print(formatting .. v)
    end
  end
end

return chatter
