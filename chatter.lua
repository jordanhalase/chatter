local chatter = {}

function chatter:loadFile(filename)
  local pattern = "<(%a+)%s(%a+)='(%d+)'>"
  local lineCount = 1

  local chat

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
end

function chatter:print(chatID)
  local cid = chatID or 1

end

function chatter:_parseFile(str)
  local pattern = "<.*>.*<.*>"
end

return chatter
