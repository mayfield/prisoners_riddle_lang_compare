import Enum
import List

defmodule PrisonPuzzle do
  def perf(n_trials, n_prisoners) do
    {usecs, successes} = :timer.tc(&trials/2, [n_trials, n_prisoners])

    secs = Float.round(usecs / 1_000_000, 3)
    rate = Float.round(successes / n_trials * 100, 3)

    IO.puts("#{n_trials} trials took #{secs} seconds, with a #{rate}% success rate")
  end

  def trials(n, n_prisoners) do
    reduce(1..n, 0, fn _, successes ->
      if trial(n_prisoners), do: successes + 1, else: successes
    end)
  end

  def trial(n_prisoners) do
    boxes = 1..n_prisoners |> shuffle |> to_tuple
    max_hops = div(n_prisoners, 2)

    reduce_while(1..n_prisoners, true, fn id, _ ->
      n = hops(id, id, boxes)
      if n < max_hops, do: {:cont, true}, else: {:halt, false}
    end)
  end

  defp hops(position, goal, boxes, count \\ 0) do
    content = elem(boxes, position - 1)
    if content == goal, do: count, else: hops(content, goal, boxes, count + 1)
  end
end

PrisonPuzzle.perf(10000, 3000)
