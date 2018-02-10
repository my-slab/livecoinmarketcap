defmodule Backend.Schema.Currency do
  use Absinthe.Schema.Notation

  object :currency do
    field(:name, :string)
    field(:id, :id)
    field(:symbol, :string)
  end
end
