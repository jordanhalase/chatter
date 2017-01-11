local chatter = {}

function chatter:loadFile(filename)
  io.input(filename)
  local file = io.read("*all")
  -- removes all new lines and indents
  file = string.gsub(file, "\n%s*", "")
  --print(file)
  self:_parseFile(file)

  --[[
  for line in io.lines(filename) do
    _, _, tag, attName, attVal = string.find(line, pattern)
    if tag == "chat" then
      self[attVal] = {}
      chat = attVal
    elseif tag == "npc" then
      -- next line is
    elseif tag == "resp" then

    end
    lineCount = lineCount + 1
  end
  ]]
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

function chatter:_parseFile(str)
  local pattern = "^<(.-)%s?(.-)>(.-)</%1>(.*)"
  -- splits string into current semantic block, and the remainder
  local i, j, tag, params, contents, remainder = string.find(str, pattern)
  -- if
  if tag then
    print(tag)
    chatter:_parseFile(contents)
  end


  if remainder then
    --print(remainder)
    chatter:_parseFile(remainder)
  end
end

function chatter:_parseTagParams(params)
  local pattern = ""
  local _, _, par, val = string.find(params, pattern)
  local loadedParams = {}
  loadedParams[par] = val
  return loadedParams
end

return chatter
