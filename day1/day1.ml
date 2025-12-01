let file = open_in "input-d1.inv"

let rec read_line file acc =
  try read_line file (input_line file :: acc) with End_of_file -> acc

let moves = read_line file []

let rec rot moves (sum, clicks) =
  match moves with
  | h :: t when String.starts_with "R" h ->
      let n = int_of_string (String.sub h 1 (String.length h - 1)) in
      if abs (sum + n) mod 100 = 0 then rot t ((sum + n) mod 100, clicks + 1)
      else rot t ((sum + n) mod 100, clicks)
  | h :: t when String.starts_with "L" h ->
      let n = int_of_string (String.sub h 1 (String.length h - 1)) in
      let i =
        if sum - n > 0 then (sum - n) mod 100 else 100 - (abs (sum - n) mod 100)
      in
      if abs (sum - n) mod 100 = 0 then rot t (i, clicks + 1)
      else rot t (i, clicks)
  | [] -> (sum, clicks)

let rec rot2 moves (sum, clicks) =
  match moves with
  | h :: t when String.starts_with "R" h ->
      let n = int_of_string (String.sub h 1 (String.length h - 1)) in
      let add_clicks = n / 100 in
      let spin =
        if (sum + n) mod 100 < sum && n != 0 && sum != 0 then 1 else 0
      in
      rot2 t ((sum + n) mod 100, spin + add_clicks + clicks)
  | h :: t when String.starts_with "L" h ->
      let n = int_of_string (String.sub h 1 (String.length h - 1)) in
      let add_clicks = abs n / 100 in
      let i =
        if sum - n > 0 then (sum - n) mod 100 else 100 - (abs (sum - n) mod 100)
      in
      let spin = if i > sum && n != 0 && sum != 0 then 1 else 0 in
      rot2 t (i mod 100, spin + add_clicks + clicks)
  | [] -> (sum, clicks)
;;

snd (rot moves (0, 0));;
snd (rot2 moves (0, 0))
