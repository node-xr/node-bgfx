local util = {}

function util.to_snake_case(s)
  local s_first = s:sub(1,1):upper()
  local s_rem = s:sub(2,-1)
  s = s_first .. s_rem
  local res = {}
  --if s == s:lower() then return s end
  for v in s:gmatch "[%u%d]+%l*" do
    res[#res+1] = v:lower()
  end
  return table.concat(res, "_")
end

function util.prefix(lines, prefix)
  local ret = {}
  for line_idx = 1, #lines do
    ret[line_idx] = prefix .. lines[line_idx]
  end
  return ret
end

function util.comment_out(lines)
  return util.prefix(lines, "//")
end

function util.indent(lines, indent)
  indent = indent or 2
  if type(indent) == 'number' then
    indent = string.rep(" ", indent)
  end
  return util.prefix(lines, indent)
end

function util.concat(lists)
  local ret = {}
  for _, list in ipairs(lists) do
    if type(list) == 'table' then
      local dpos = #ret
      for idx, v in ipairs(list) do
        ret[dpos+idx] = v
      end
    else
      ret[#ret + 1] = list
    end
  end
  return ret
end

return util