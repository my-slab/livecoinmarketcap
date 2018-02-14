defmodule Backend.Schema do
  use Absinthe.Schema
  import_types(Backend.Schema.Currency)

  query do
    @desc "Get all currencies"
    field :currencies, list_of(:currency) do
      resolve(&Backend.Resolvers.Currency.list_currencies/3)
    end
  end
end
