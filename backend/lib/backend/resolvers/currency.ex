defmodule Backend.Resolvers.Currency do
  def list_currencies(_parent, _args, _resolution) do
    IO.puts "here..."
    {:ok, [%{id: "bitcoin", name: "Bitcoin", symbol: "BTC"}]}
  end
end
