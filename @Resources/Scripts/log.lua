-- ============================================================
--  log.lua — ring buffer for W19 / ALERTS (§6.1a)
--  Rainmeter has no arrays and variables are single-line, so the
--  buffer must live in Lua. Shared by both variants (§17.6).
--
--  Call from a skin:
--    [!CommandMeasure mLog "Add('WARN','poller stale')"]
--  Read back:
--    [mLog]            -> most recent formatted line
--    Last(n)           -> nth most recent (1 = newest)
-- ============================================================

local buf, seq, MAX = {}, 0, 200

function Initialize()
  seq = 0
  buf = {}
  Add('OK', 'shell started')
end

function Add(level, msg)
  seq = seq + 1
  local t = os.date('%H:%M:%S')
  table.insert(buf, { t = t, lv = level, msg = msg, n = seq })
  if #buf > MAX then table.remove(buf, 1) end
  -- expose newest to the skin without needing an Update tick
  SKIN:Bang('!SetVariable', 'LogLast', Format(buf[#buf]))
  SKIN:Bang('!SetVariable', 'LogSeq', tostring(seq))
end

function Format(e)
  if not e then return '' end
  return string.format('log[%s] %-5s %s', e.t, e.lv, e.msg)
end

-- nth most recent; 1 = newest. Used by the ALERTS panel (§6.2).
function Last(n)
  n = tonumber(n) or 1
  local e = buf[#buf - (n - 1)]
  return Format(e)
end

function Level(n)
  n = tonumber(n) or 1
  local e = buf[#buf - (n - 1)]
  return e and e.lv or ''
end

function Count() return seq end

function Clear()
  buf, seq = {}, 0
  Add('INFO', 'log cleared')
end

function Update()
  return Format(buf[#buf])
end
